#include "catch2/catch_test_macros.hpp"

#include "../src/game/square.hpp"

namespace tic_tac_toe {

TEST_CASE("game/square")
{
    SECTION("default construct")
    {
        const Square square;

        CHECK(square.row == 0);
        CHECK(square.col == 0);
    }

    SECTION("construct")
    {
        const Square square{1, 2};

        CHECK(square.row == 1);
        CHECK(square.col == 2);
    }

    SECTION("row and column must be between 0 to 2")
    {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                CHECK_NOTHROW(Square{row, col});
    }

    SECTION("throws exception if row and column are out of bounds")
    {
        CHECK_THROWS(Square{-1, 1});
        CHECK_THROWS(Square{3, 1});
        CHECK_THROWS(Square{1, -1});
        CHECK_THROWS(Square{1, 3});
    }

    SECTION("can compare squares")
    {
        CHECK(Square{1, 2} == Square{1, 2});
        CHECK(Square{1, 2} != Square{0, 0});
    }
}

}  // namespace tic_tac_toe
