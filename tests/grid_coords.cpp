#include <limits>
#include <type_traits>

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

#include "../src/grid/coords.hpp"

namespace tic_tac_toe {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Coords<T>& coords) { return os << fmt::format("({}/{})", static_cast<int64_t>(coords.x), static_cast<int64_t>(coords.y)); }

template <typename CoordsType>
void check_coords()
{
    SECTION("creation")
    {
        CHECK(CoordsType{}.x == 0);
        CHECK(CoordsType{}.y == 0);
        CHECK(CoordsType{2, 3}.x == 2);
        CHECK(CoordsType{2, 3}.y == 3);
    }

    SECTION("assignment")
    {
        const CoordsType a{4, 5};

        CoordsType b = a;

        CoordsType c;
        c = a;

        CHECK(b == a);
        CHECK(c == a);

        b += CoordsType{2, 1};
        c -= CoordsType{1, 2};

        CHECK(b == CoordsType{6, 6});
        CHECK(c == CoordsType{3, 3});
    }

    SECTION("arithmetic")
    {
        CHECK(CoordsType{4, 5} + CoordsType{2, 1} == CoordsType{6, 6});
        CHECK(CoordsType{4, 5} - CoordsType{1, 2} == CoordsType{3, 3});
    }

    SECTION("comparison")
    {
        CHECK(CoordsType{2, 3} == CoordsType{2, 3});
        CHECK((CoordsType{2, 3} == CoordsType{3, 2}) == false);

        CHECK(CoordsType{2, 3} != CoordsType{3, 2});
        CHECK((CoordsType{2, 3} != CoordsType{2, 3}) == false);

        CHECK(CoordsType{2, 2} < CoordsType{3, 3});
        CHECK(CoordsType{2, 3} < CoordsType{3, 3});
        CHECK(CoordsType{3, 2} < CoordsType{3, 3});
        CHECK((CoordsType{2, 2} < CoordsType{2, 2}) == false);
        CHECK((CoordsType{3, 3} < CoordsType{2, 2}) == false);
        CHECK((CoordsType{3, 3} < CoordsType{2, 3}) == false);
        CHECK((CoordsType{3, 3} < CoordsType{3, 2}) == false);

        CHECK(CoordsType{3, 3} > CoordsType{2, 2});
        CHECK(CoordsType{3, 3} > CoordsType{2, 3});
        CHECK(CoordsType{3, 3} > CoordsType{3, 2});
        CHECK((CoordsType{3, 3} > CoordsType{3, 3}) == false);
        CHECK((CoordsType{2, 2} > CoordsType{3, 3}) == false);
        CHECK((CoordsType{2, 3} > CoordsType{3, 3}) == false);
        CHECK((CoordsType{3, 2} > CoordsType{3, 3}) == false);

        CHECK(CoordsType{2, 2} <= CoordsType{2, 2});
        CHECK(CoordsType{2, 2} <= CoordsType{3, 3});
        CHECK(CoordsType{2, 3} <= CoordsType{3, 3});
        CHECK(CoordsType{3, 2} <= CoordsType{3, 3});
        CHECK((CoordsType{3, 3} <= CoordsType{2, 2}) == false);
        CHECK((CoordsType{3, 3} <= CoordsType{2, 3}) == false);
        CHECK((CoordsType{3, 3} <= CoordsType{3, 2}) == false);

        CHECK(CoordsType{3, 3} >= CoordsType{3, 3});
        CHECK(CoordsType{3, 3} >= CoordsType{2, 2});
        CHECK(CoordsType{3, 3} >= CoordsType{2, 3});
        CHECK(CoordsType{3, 3} >= CoordsType{3, 2});
        CHECK((CoordsType{2, 2} >= CoordsType{3, 3}) == false);
        CHECK((CoordsType{2, 3} >= CoordsType{3, 3}) == false);
        CHECK((CoordsType{3, 2} >= CoordsType{3, 3}) == false);
    }

    SECTION("col() and row() return x and y coordinates")
    {
        CHECK(CoordsType{}.col() == 0);
        CHECK(CoordsType{}.row() == 0);
        CHECK(CoordsType{2, 3}.col() == 2);
        CHECK(CoordsType{2, 3}.row() == 3);
    }

    SECTION("move()")
    {
        CoordsType a{10, 10};
        CoordsType b{a};

        a.move(2, 1);
        b.move(CoordsType{2, 1});

        CHECK(a == CoordsType{12, 11});
        CHECK(b == CoordsType{12, 11});

        a.move(-6, -9);
        CHECK(a == CoordsType{6, 2});

        if constexpr (std::is_signed_v<typename CoordsType::coordinates_type>) {
            b.move(CoordsType{-6, -9});
            CHECK(b == CoordsType{6, 2});
        }
    }

    SECTION("move horizontally and vertically")
    {
        CoordsType a{1, 2};

        a.move_horizontally(3);
        CHECK(a == CoordsType{4, 2});

        a.move_horizontally(-1);
        CHECK(a == CoordsType{3, 2});

        a.move_vertically(-1);
        CHECK(a == CoordsType{3, 1});

        a.move_vertically(3);
        CHECK(a == CoordsType{3, 4});
    }

    SECTION("move in relative directions")
    {
        CoordsType a{10, 10};
        CoordsType b{10, 10};

        a.move_up(3);
        b.move_up(-3);
        CHECK(a == CoordsType{10, 7});
        CHECK(b == CoordsType{10, 13});

        a.move_down(5);
        b.move_down(-5);
        CHECK(a == CoordsType{10, 12});
        CHECK(b == CoordsType{10, 8});

        a.move_right(5);
        b.move_right(-5);
        CHECK(a == CoordsType{15, 12});
        CHECK(b == CoordsType{5, 8});

        a.move_left(8);
        b.move_left(-8);
        CHECK(a == CoordsType{7, 12});
        CHECK(b == CoordsType{13, 8});
    }

    SECTION("move in cardinal directions")
    {
        CoordsType a{10, 10};
        CoordsType b{10, 10};

        a.move_north(3);
        b.move_north(-3);
        CHECK(a == CoordsType{10, 7});
        CHECK(b == CoordsType{10, 13});

        a.move_south(5);
        b.move_south(-5);
        CHECK(a == CoordsType{10, 12});
        CHECK(b == CoordsType{10, 8});

        a.move_east(5);
        b.move_east(-5);
        CHECK(a == CoordsType{15, 12});
        CHECK(b == CoordsType{5, 8});

        a.move_west(8);
        b.move_west(-8);
        CHECK(a == CoordsType{7, 12});
        CHECK(b == CoordsType{13, 8});
    }

    SECTION("maximum coordinates")
    {
        constexpr auto max = std::numeric_limits<typename CoordsType::coordinates_type>::max();

        CoordsType a;
        a += CoordsType{max, max};
        CHECK(a.x == max);
        CHECK(a.y == max);

        CoordsType b;
        b.move(max, max);
        CHECK(b.x == max);
        CHECK(b.y == max);

        CoordsType c;
        c.move_horizontally(max);
        c.move_vertically(max);
        CHECK(c.x == max);
        CHECK(c.y == max);
    }
}

TEST_CASE("grid/coords")
{
    SECTION("int8_t") { check_coords<Coords<int8_t>>(); }
    SECTION("int16_t") { check_coords<Coords<int16_t>>(); }
    SECTION("int32_t") { check_coords<Coords<int32_t>>(); }
    // SECTION("int64_t") { check_coords<Coords<int64_t>>(); }  // not supported
    SECTION("uint8_t") { check_coords<Coords<uint8_t>>(); }
    SECTION("uint16_t") { check_coords<Coords<uint16_t>>(); }
    // SECTION("uint32_t") { check_coords<Coords<uint32_t>>(); }  // not supported
    // SECTION("uint64_t") { check_coords<Coords<uint64_t>>(); }  // not supported
}

}  // namespace tic_tac_toe
