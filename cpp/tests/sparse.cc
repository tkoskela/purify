#include "catch.hpp"

#include "utilities.h"

#include "directories.h"
using namespace purify;
using namespace purify::notinstalled;

TEST_CASE("sparse [iterator]", "[iterator]") {
    t_int NZnum = 40;
    std::vector<t_tripletList> entries;
    entries.reserve(NZnum);
    Vector<t_int> rows = Vector<t_int>::LinSpaced(NZnum, 0, 2*NZnum);
    Vector<t_int> cols = Vector<t_int>::LinSpaced(NZnum, 0, 3*NZnum);

    for (t_int i = 0; i < NZnum; ++i)
    {
        entries.emplace_back(rows(i), cols(i), i);
    }
    const t_int total_rows = 5 * NZnum;
    const t_int total_cols = 4 * NZnum;
    Sparse<t_complex> G(total_rows, total_cols);
    G.setFromTriplets(entries.begin(), entries.end());
    for (t_int i = 0; i < total_cols; ++i)
    {
        for (Eigen::SparseMatrix<t_complex>::InnerIterator pix(G,i); pix; ++pix)
        {
            std::cout << pix.row() << " " << pix.col() << " " << std::real(pix.value()) << '\n';
        }
    }
    //CHECK(expected.isApprox(output, 1e-13));
}

