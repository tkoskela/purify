#include "purify/config.h"
#include "purify/mpi_utilities.h"
#include "purify/distribute.h"
#include <iostream>
#include <type_traits>

namespace purify {
namespace utilities {
void regroup(vis_params &uv_params, std::vector<t_int> const &groups_) {
  std::vector<t_int> groups = groups_;
  // Figure out size of each group
  std::map<t_int, t_int> sizes;
  for (auto const &group : groups)
    if (sizes.count(group) == 0)
      sizes[group] = 1;
    else
      ++sizes[group];

  std::map<t_int, t_int> indices, ends;
  auto i = 0;
  for (auto const &item : sizes) {
    indices[item.first] = i;
    i += item.second;
    ends[item.first] = i;
  }

  auto const expected = [&ends](t_int i) {
    t_int j = 0;
    for (auto const end : ends) {
      if (i < end.second)
        return j;
      ++j;
    }
    return j;
  };

  i = 0;
  while (i < uv_params.u.size()) {
    auto const expected_proc = expected(i);
    if (groups[i] == expected_proc) {
      ++i;
      continue;
    }
    auto &swapper = indices[groups[i]];
    if (groups[swapper] == expected(swapper)) {
      ++swapper;
      continue;
    }
    std::swap(groups[i], groups[swapper]);
    std::swap(uv_params.u(i), uv_params.u(swapper));
    std::swap(uv_params.v(i), uv_params.v(swapper));
    std::swap(uv_params.w(i), uv_params.w(swapper));
    std::swap(uv_params.vis(i), uv_params.vis(swapper));
    std::swap(uv_params.weights(i), uv_params.weights(swapper));

    ++swapper;
  }
}

vis_params regroup_and_scatter(vis_params const &params,
                               std::vector<t_int> const &groups,
                               sopt::mpi::Communicator const &comm) {
  if (comm.size() == 1)
    return params;
  if (comm.rank() != comm.root_id())
    return scatter_visibilities(comm);

  std::vector<t_int> sizes(comm.size());
  std::fill(sizes.begin(), sizes.end(), 0);
  for (auto const &group : groups) {
    if (group > comm.size())
      throw std::out_of_range("groups should go from 0 to comm.size()");
    ++sizes[group];
  }

  vis_params copy = params;
  regroup(copy, groups);
  return scatter_visibilities(copy, sizes, comm);
}

vis_params scatter_visibilities(vis_params const &params,
                                std::vector<t_int> const &sizes,
                                sopt::mpi::Communicator const &comm) {
  if (comm.size() == 1)
    return params;
  if (not comm.is_root())
    return scatter_visibilities(comm);

  comm.scatter_one(sizes);
  vis_params result;
  result.u = comm.scatterv(params.u, sizes);
  result.v = comm.scatterv(params.v, sizes);
  result.w = comm.scatterv(params.w, sizes);
  result.vis = comm.scatterv(params.vis, sizes);
  result.weights = comm.scatterv(params.weights, sizes);
  result.units = comm.broadcast(params.units);
  result.ra = comm.broadcast(params.ra);
  result.dec = comm.broadcast(params.dec);
  result.average_frequency = comm.broadcast(params.average_frequency);
  return result;
}

vis_params scatter_visibilities(sopt::mpi::Communicator const &comm) {
  if (comm.is_root())
    throw std::runtime_error(
        "The root node should call the *other* scatter_visibilities function");

  auto const local_size = comm.scatter_one<t_int>();
  vis_params result;
  result.u = comm.scatterv<decltype(result.u)::Scalar>(local_size);
  result.v = comm.scatterv<decltype(result.v)::Scalar>(local_size);
  result.w = comm.scatterv<decltype(result.w)::Scalar>(local_size);
  result.vis = comm.scatterv<decltype(result.vis)::Scalar>(local_size);
  result.weights = comm.scatterv<decltype(result.weights)::Scalar>(local_size);
  result.units = comm.broadcast(decltype(result.units)(""));
  result.ra = comm.broadcast<std::remove_const<decltype(result.ra)>::type>();
  result.dec = comm.broadcast<std::remove_const<decltype(result.dec)>::type>();
  result.average_frequency = comm.broadcast<
      std::remove_const<decltype(result.average_frequency)>::type>();
  return result;
}
}
} // namespace purify
