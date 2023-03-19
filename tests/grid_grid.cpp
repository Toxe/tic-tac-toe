#include <algorithm>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

#include "../src/grid/grid.hpp"

namespace tic_tac_toe {

Grid<int> create_grid_with_test_values(const int cols, const int rows)
{
    Grid<int> grid{cols, rows};

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            grid[row][col] = (row + 1) * 10 + col + 1;

    return grid;
}

std::ostream& operator<<(std::ostream& os, const Grid<int>::const_grid_rows_type::iterator& iter) { return os << fmt::format("{} ({})", fmt::ptr(std::addressof(iter)), (*iter).front()); }
std::ostream& operator<<(std::ostream& os, const Grid<int>::const_grid_rows_type::reverse_iterator& iter) { return os << fmt::format("{} ({})", fmt::ptr(std::addressof(iter)), (*iter).front()); }
std::ostream& operator<<(std::ostream& os, const Grid<int>::const_grid_rows_type::iterator::row_or_col_type::iterator& iter) { return os << fmt::format("{} ({})", fmt::ptr(std::addressof(iter)), *iter); }
std::ostream& operator<<(std::ostream& os, const Grid<int>::const_grid_rows_type::iterator::row_or_col_type::reverse_iterator& iter) { return os << fmt::format("{} ({})", fmt::ptr(std::addressof(iter)), *iter); }

// generic tests
template <typename Iter>
void check_bidirectional_iterator_requirements(Iter iter)
{
    // addressof(--a) == addressof(a)
    {
        auto a = iter;
        CHECK(std::addressof(--a) == std::addressof(a));
    }

    // bool(a-- == b)
    {
        auto a = iter;
        auto b = iter;
        CHECK(a-- == b);
    }

    // after evaluating both a-- and --b, bool(a == b) is still true
    {
        auto a = iter;
        auto b = iter;
        a--;
        --b;
        CHECK(a == b);
    }

    // ++(--a) == b
    {
        auto a = iter;
        auto b = iter;
        CHECK(++(--a) == b);
    }

    // --(++a) == b
    {
        auto a = iter;
        auto b = iter;
        CHECK(--(++a) == b);
    }
}

template <typename Iter>
void check_random_access_iterator_requirements(Iter iter1, Iter iter2)
{
    const auto n = iter2 - iter1;

    // (a += n) is equal to b
    {
        auto a = iter1;
        auto b = iter2;
        CHECK((a += n) == b);
    }

    // std::addressof(a += n) is equal to std::addressof(a)
    {
        auto a = iter1;
        CHECK(std::addressof(a += n) == std::addressof(a));
    }

    // (a + n) is equal to (a += n)
    {
        auto a = iter1;
        auto a2 = iter1;
        CHECK((a + n) == (a2 += n));
    }

    // (a + n) is equal to (n + a)
    {
        auto a = iter1;
        CHECK((a + n) == (n + a));
    }

    // for any two positive integers x and y, if a + (x + y) is valid, then a + (x + y) is equal to (a + x) + y
    {
        auto a = iter1;
        const int x = 2;
        const int y = 3;
        CHECK((a + (x + y)) == ((a + x) + y));
    }

    // a + 0 is equal to a
    {
        auto a = iter1;
        CHECK((a + 0) == a);
    }

    // if (a + (n - 1)) is valid, then --b is equal to (a + (n - 1))
    {
        auto a = iter1;
        auto b = iter2;
        CHECK((a + (n - 1)) == --b);
    }

    // (b += -n) and (b -= n) are both equal to a
    {
        auto a = iter1;
        auto b = iter2;
        CHECK((b += -n) == a);
    }

    {
        auto a = iter1;
        auto b = iter2;
        CHECK((b -= n) == a);
    }

    // std::addressof(b -= n) is equal to std::addressof(b)
    {
        auto b = iter2;
        CHECK(std::addressof(b -= n) == std::addressof(b));
    }

    // (b - n) is equal to (b -= n)
    {
        auto b = iter2;
        auto b2 = iter2;
        CHECK((b - n) == (b2 -= n));
    }

    // if b is dereferenceable, then a[n] is valid and is equal to *b
    {
        auto a = iter1;
        auto b = iter2;
        CHECK(a[n] == *b);
    }

    // bool(a <= b) is true
    {
        auto a = iter1;
        auto b = iter2;
        CHECK(a <= b);
    }
}

template <typename Iter>
void check_spaceship_operator(Iter begin, Iter end)
{
    SECTION("operator==")
    {
        CHECK(begin == begin);
        CHECK((begin == end) == false);
    }

    SECTION("operator!=")
    {
        CHECK(begin != end);
        CHECK((begin != begin) == false);
    }

    SECTION("operator<")
    {
        CHECK(begin < end);
        CHECK((end < begin) == false);
    }

    SECTION("operator<=")
    {
        CHECK(begin <= begin);
        CHECK(begin <= end);
        CHECK((end <= begin) == false);
    }

    SECTION("operator>")
    {
        CHECK(end > begin);
        CHECK((begin > end) == false);
    }

    SECTION("operator>=")
    {
        CHECK(end >= end);
        CHECK(end >= begin);
        CHECK((begin >= end) == false);
    }
}

template <typename Iter, typename distance_type>
void check_distance_between_elements(Iter begin, Iter end, distance_type distance_begin_to_end)
{
    CHECK(begin - begin == 0);
    CHECK((begin + 1) - begin == 1);
    CHECK((begin + 2) - begin == 2);
    CHECK(begin - (begin + 1) == -1);
    CHECK(begin - (begin + 2) == -2);
    CHECK(begin - end == -distance_begin_to_end);
    CHECK(end - begin == distance_begin_to_end);
}

template <typename Iterator, typename Values, typename GetValueFunc>
void check_iterator_operations(Iterator begin, Iterator end, Values values, GetValueFunc get_value)
{
    SECTION("std::next")
    {
        auto it = begin;

        CHECK(get_value(std::next(it)) == values[1]);
        CHECK(get_value(std::next(it, 3)) == values[3]);
    }

    SECTION("std::prev")
    {
        auto it = end;

        CHECK(get_value(std::prev(it)) == values[values.size() - 1]);
        CHECK(get_value(std::prev(it, 3)) == values[values.size() - 3]);
    }

    SECTION("std::advance")
    {
        auto it1 = begin;

        std::advance(it1, 1);
        CHECK(get_value(it1) == values[1]);

        std::advance(it1, 2);
        CHECK(get_value(it1) == values[3]);

        auto it2 = end;

        std::advance(it2, -1);
        CHECK(get_value(it2) == values[values.size() - 1]);

        std::advance(it2, -2);
        CHECK(get_value(it2) == values[values.size() - 3]);
    }

    SECTION("std::distance")
    {
        CHECK(std::distance(begin, end) == static_cast<std::ptrdiff_t>(values.size()));
        CHECK(std::distance(end, begin) == -static_cast<std::ptrdiff_t>(values.size()));
    }
}

// GridRowsOrCols
template <typename GridRowsOrCols, typename Values>
void grid_rows_or_cols_check_basic_functionality(GridRowsOrCols rows_or_cols, Values values)
{
    const auto num_values = static_cast<typename GridRowsOrCols::size_type>(values.size());

    SECTION("size() returns the number of Grid rows/cols")
    {
        CHECK(rows_or_cols.size() == num_values);
    }

    SECTION("front() returns the first row/col")
    {
        CHECK(rows_or_cols.front().front() == values[0]);
    }

    SECTION("back() returns the last row/col")
    {
        CHECK(rows_or_cols.back().front() == values[values.size() - 1]);
    }
}

template <typename Const_GridRowsOrCols, typename NonConst_GridRowsOrCols, typename Values>
void grid_rows_or_cols_check_iterators(Const_GridRowsOrCols const_rows_or_cols, NonConst_GridRowsOrCols non_const_rows_or_cols, Values values)
{
    SECTION("const")
    {
        SECTION("begin")
        {
            auto it1 = const_rows_or_cols.begin();
            auto it2 = const_rows_or_cols.cbegin();
            auto it3 = const_rows_or_cols.rbegin();
            auto it4 = const_rows_or_cols.crbegin();

            CHECK(it1 == it2);
            CHECK(it3 == it4);
            CHECK(it1->front() == values[0]);
            CHECK(it2->front() == values[0]);
            CHECK(it3->front() == values[values.size() - 1]);
            CHECK(it4->front() == values[values.size() - 1]);
        }

        SECTION("end")
        {
            auto it1 = const_rows_or_cols.end();
            auto it2 = const_rows_or_cols.cend();
            auto it3 = const_rows_or_cols.rend();
            auto it4 = const_rows_or_cols.crend();

            CHECK(it1 == it2);
            CHECK(it3 == it4);
            CHECK((it1 - 1)->front() == values[values.size() - 1]);
            CHECK((it2 - 1)->front() == values[values.size() - 1]);
            CHECK((it3 - 1)->front() == values[0]);
            CHECK((it4 - 1)->front() == values[0]);
        }
    }

    SECTION("non-const")
    {
        SECTION("begin")
        {
            auto it1 = non_const_rows_or_cols.begin();
            auto it2 = non_const_rows_or_cols.rbegin();

            REQUIRE(it1->front() == values[0]);
            REQUIRE(it2->front() == values[values.size() - 1]);

            it1->front() = 100;
            it2->front() = 200;

            CHECK(non_const_rows_or_cols.front().front() == 100);
            CHECK(non_const_rows_or_cols.back().front() == 200);
        }

        SECTION("end")
        {
            auto it1 = non_const_rows_or_cols.end();
            auto it2 = non_const_rows_or_cols.rend();

            REQUIRE((it1 - 1)->front() == values[values.size() - 1]);
            REQUIRE((it2 - 1)->front() == values[0]);

            (it1 - 1)->front() = 100;
            (it2 - 1)->front() = 200;

            CHECK(non_const_rows_or_cols.back().front() == 100);
            CHECK(non_const_rows_or_cols.front().front() == 200);
        }
    }
}

template <typename Const_GridRowsOrCols, typename NonConst_GridRowsOrCols, typename Values>
void grid_rows_or_cols_check_operators(Const_GridRowsOrCols const_rows_or_cols, NonConst_GridRowsOrCols non_const_rows_or_cols, Values values)
{
    SECTION("operator[]")
    {
        SECTION("const")
        {
            CHECK(const_rows_or_cols[0].front() == values[0]);
            CHECK(const_rows_or_cols[1].front() == values[1]);
            CHECK(const_rows_or_cols[2].front() == values[2]);
        }

        SECTION("non-const")
        {
            REQUIRE(non_const_rows_or_cols[0].front() == values[0]);
            REQUIRE(non_const_rows_or_cols[1].front() == values[1]);
            REQUIRE(non_const_rows_or_cols[2].front() == values[2]);

            non_const_rows_or_cols[0].front() = 100;
            non_const_rows_or_cols[1].front() = 200;
            non_const_rows_or_cols[2].front() = 300;

            CHECK((*const_rows_or_cols.begin()).front() == values[0]);
            CHECK((*(const_rows_or_cols.begin() + 1)).front() == values[1]);
            CHECK((*(const_rows_or_cols.begin() + 2)).front() == values[2]);
        }
    }
}

// RowOrCol
template <typename RowOrCol, typename Values>
void row_or_col_check_basic_functionality(RowOrCol row_or_col, Values values, Values other_row_or_col_values)
{
    const auto num_values = static_cast<typename RowOrCol::size_type>(values.size());

    SECTION("size() returns the number of row/col values")
    {
        CHECK(row_or_col.size() == num_values);
    }

    SECTION("front() returns the first value")
    {
        CHECK(row_or_col.front() == row_or_col[0]);
    }

    SECTION("back() returns the last value")
    {
        CHECK(row_or_col.back() == row_or_col[num_values - 1]);
    }

    SECTION("advance() moves to another row/col")
    {
        REQUIRE(row_or_col.front() == values[0]);

        row_or_col.advance(3);
        CHECK(row_or_col.front() == other_row_or_col_values[3]);

        row_or_col.advance(-2);
        CHECK(row_or_col.front() == other_row_or_col_values[1]);
    }

    SECTION("next() returns another row/col")
    {
        row_or_col.advance(2);
        REQUIRE(row_or_col.front() == other_row_or_col_values[2]);

        CHECK(row_or_col.next(1).front() == other_row_or_col_values[3]);
        CHECK(row_or_col.next(-2).front() == other_row_or_col_values[0]);
    }
}

template <typename ConstRowOrCol, typename NonConstRowOrCol, typename Values>
void row_or_col_check_iterators(ConstRowOrCol const_row_or_col, NonConstRowOrCol non_const_row_or_col, Values values)
{
    const auto num_values = static_cast<typename NonConstRowOrCol::size_type>(values.size());

    SECTION("const")
    {
        SECTION("begin")
        {
            auto it1 = const_row_or_col.begin();
            auto it2 = const_row_or_col.cbegin();
            auto it3 = const_row_or_col.rbegin();
            auto it4 = const_row_or_col.crbegin();

            CHECK(it1 == it2);
            CHECK(it3 == it4);
            CHECK(*it1 == values[0]);
            CHECK(*it2 == values[0]);
            CHECK(*it3 == values[values.size() - 1]);
            CHECK(*it4 == values[values.size() - 1]);
        }

        SECTION("end")
        {
            auto it1 = const_row_or_col.end();
            auto it2 = const_row_or_col.cend();
            auto it3 = const_row_or_col.rend();
            auto it4 = const_row_or_col.crend();

            CHECK(it1 == it2);
            CHECK(it3 == it4);
            CHECK(*(it1 - 1) == values[values.size() - 1]);
            CHECK(*(it2 - 1) == values[values.size() - 1]);
            CHECK(*(it3 - 1) == values[0]);
            CHECK(*(it4 - 1) == values[0]);
        }
    }

    SECTION("non-const")
    {
        SECTION("begin")
        {
            auto it1 = non_const_row_or_col.begin();
            auto it2 = non_const_row_or_col.rbegin();

            REQUIRE(*it1 == values[0]);
            REQUIRE(*it2 == values[values.size() - 1]);

            *it1 = 100;
            *it2 = 200;

            CHECK(non_const_row_or_col[0] == 100);
            CHECK(non_const_row_or_col[num_values - 1] == 200);
        }

        SECTION("end")
        {
            auto it1 = non_const_row_or_col.end();
            auto it2 = non_const_row_or_col.rend();

            REQUIRE(*(it1 - 1) == values[values.size() - 1]);
            REQUIRE(*(it2 - 1) == values[0]);

            *(it1 - 1) = 100;
            *(it2 - 1) = 200;

            CHECK(non_const_row_or_col[num_values - 1] == 100);
            CHECK(non_const_row_or_col[0] == 200);
        }
    }
}

template <typename ConstRowOrCol, typename NonConstRowOrCol, typename Values>
void row_or_col_check_other_operators(ConstRowOrCol const_row_or_col, NonConstRowOrCol non_const_row_or_col, Values values)
{
    SECTION("operator-")
    {
        CHECK(const_row_or_col.next() - const_row_or_col == 1);
        CHECK(const_row_or_col.next(2) - const_row_or_col.next() == 1);
        CHECK(const_row_or_col.next(2) - const_row_or_col == 2);

        CHECK(non_const_row_or_col.next() - non_const_row_or_col == 1);
        CHECK(non_const_row_or_col.next(2) - non_const_row_or_col.next() == 1);
        CHECK(non_const_row_or_col.next(2) - non_const_row_or_col == 2);
    }

    SECTION("operator[]")
    {
        SECTION("const")
        {
            CHECK(const_row_or_col[0] == values[0]);
            CHECK(const_row_or_col[1] == values[1]);
            CHECK(const_row_or_col[2] == values[2]);
        }

        SECTION("non-const")
        {
            REQUIRE(non_const_row_or_col[0] == values[0]);
            REQUIRE(non_const_row_or_col[1] == values[1]);
            REQUIRE(non_const_row_or_col[2] == values[2]);

            non_const_row_or_col[0] = 100;
            non_const_row_or_col[1] = 200;
            non_const_row_or_col[2] = 300;

            CHECK(*(non_const_row_or_col.begin()) == 100);
            CHECK(*(non_const_row_or_col.begin() + 1) == 200);
            CHECK(*(non_const_row_or_col.begin() + 2) == 300);
        }
    }
}

// RowOrColIterator
template <typename RowOrColIterator, typename Values>
void row_or_col_iterator_check_other_operators(RowOrColIterator begin, RowOrColIterator end, Values values)
{
    SECTION("operator*")
    {
        auto row = *begin;

        CHECK(row[0] == values[0]);
    }

    SECTION("operator->")
    {
        CHECK(begin->front() == values[0]);
    }

    SECTION("operator++")
    {
        auto it = begin;

        CHECK((++it)->front() == values[1]);
        CHECK((it++)->front() == values[1]);
        CHECK((it++)->front() == values[2]);
    }

    SECTION("operator--")
    {
        auto it = end;

        CHECK((--it)->front() == values[values.size() - 1]);
        CHECK((it--)->front() == values[values.size() - 1]);
        CHECK((it--)->front() == values[values.size() - 2]);
    }

    SECTION("operator+=")
    {
        auto it = begin;
        it += 2;

        CHECK(it->front() == values[2]);
    }

    SECTION("operator-=")
    {
        auto it = end;
        it -= 3;

        CHECK(it->front() == values[values.size() - 3]);
    }

    SECTION("operator+")
    {
        CHECK((begin + 2)->front() == values[2]);
        CHECK((2 + begin)->front() == values[2]);
    }

    SECTION("operator-")
    {
        CHECK((end - 3)->front() == values[values.size() - 3]);
    }

    SECTION("operator[]")
    {
        auto it = begin;

        CHECK(it[0].front() == values[0]);
        CHECK(it[1].front() == values[1]);
        CHECK(it[2].front() == values[2]);
    }
}

template <typename RowOrColIterator, typename Values>
void row_or_col_iterator_check_modifying_values(RowOrColIterator it, Values values)
{
    REQUIRE(it[1].front() == values[1]);
    REQUIRE(it[2].front() == values[2]);

    it[1].front() = 100;
    it[2].front() = 200;

    CHECK(it[1].front() == 100);
    CHECK(it[2].front() == 200);
}

// ValueIterator
template <typename ValueIterator, typename Values>
void value_iterator_check_other_operators(ValueIterator begin, ValueIterator end, Values values)
{
    SECTION("operator*")
    {
        auto it = begin;

        CHECK(*it == values[0]);
    }

    SECTION("operator++")
    {
        auto it = begin;

        CHECK(*(++it) == values[1]);
        CHECK(*(it++) == values[1]);
        CHECK(*(it++) == values[2]);
    }

    SECTION("operator--")
    {
        auto it = end;

        CHECK(*(--it) == values[values.size() - 1]);
        CHECK(*(it--) == values[values.size() - 1]);
        CHECK(*(it--) == values[values.size() - 2]);
    }

    SECTION("operator+=")
    {
        auto it = begin;
        it += 2;

        CHECK(*it == values[2]);
    }

    SECTION("operator-=")
    {
        auto it = end;
        it -= 3;

        CHECK(*it == values[values.size() - 3]);
    }

    SECTION("operator+")
    {
        CHECK(*(begin + 2) == values[2]);
        CHECK(*(2 + begin) == values[2]);
    }

    SECTION("operator-")
    {
        CHECK(*(end - 3) == values[values.size() - 3]);
    }

    SECTION("operator[]")
    {
        auto it = begin;

        CHECK(it[0] == values[0]);
        CHECK(it[1] == values[1]);
        CHECK(it[2] == values[2]);
    }
}

template <typename ValueIterator, typename Values>
void value_iterator_check_modifying_values(ValueIterator it, Values values)
{
    REQUIRE(it[1] == values[1]);
    REQUIRE(it[2] == values[2]);

    it[1] = 100;
    *(it + 2) = 200;

    CHECK(it[1] == 100);
    CHECK(it[2] == 200);
}

template <typename ConstValueIterator, typename NonConstValueIterator, typename Value>
void value_iterator_check_arrow_operator(ConstValueIterator const_it, NonConstValueIterator non_const_it, Value value)
{
    CHECK(const_it->x == value);
    CHECK(non_const_it->x == value);

    non_const_it->x = value + 1;

    CHECK(non_const_it->x == value + 1);
}

TEST_CASE("grid/grid")
{
    SECTION("Grid")
    {
        SECTION("can create new Grid with default initialized elements")
        {
            const Grid<int> grid{4, 3};

            CHECK(std::all_of(grid.begin(), grid.end(), [](int i) { return i == 0; }));
        }

        SECTION("can create new Grid with default values")
        {
            const Grid<int> grid{4, 3, -1};

            CHECK(std::all_of(grid.begin(), grid.end(), [](int i) { return i == -1; }));
        }

        SECTION("can create Grid with different Coords types")
        {
            const Grid<int, Coords<int8_t>> grid_with_i8_bit_coords{4, 4, 42};
            const Grid<int, Coords<int16_t>> grid_with_i16_bit_coords{4, 4, 42};
            const Grid<int, Coords<int32_t>> grid_with_i32_bit_coords{4, 4, 42};
            // const Grid<int, Coords<int64_t>> grid_with_i64_bit_coords{4, 4, 42};  // not supported
            const Grid<int, Coords<uint8_t>> grid_with_u8_bit_coords{4, 4, 42};
            const Grid<int, Coords<uint16_t>> grid_with_u16_bit_coords{4, 4, 42};
            // const Grid<int, Coords<uint32_t>> grid_with_u32_bit_coords{4, 4, 42};  // not supported
            // const Grid<int, Coords<uint64_t>> grid_with_u64_bit_coords{4, 4, 42};  // not supported

            CHECK(grid_with_i8_bit_coords.at({2, 2}) == 42);
            CHECK(grid_with_i16_bit_coords.at({2, 2}) == 42);
            CHECK(grid_with_i32_bit_coords.at({2, 2}) == 42);
            // CHECK(grid_with_i64_bit_coords.at({2, 2}) == 42);
            CHECK(grid_with_u8_bit_coords.at({2, 2}) == 42);
            CHECK(grid_with_u16_bit_coords.at({2, 2}) == 42);
            // CHECK(grid_with_u32_bit_coords.at({2, 2}) == 42);
            // CHECK(grid_with_u64_bit_coords.at({2, 2}) == 42);
        }

        SECTION("can create maximum sized Grid")
        {
            const Grid<char, Coords<int8_t>> grid_with_7_bit_coords{128, 128, 42};
            const Grid<char, Coords<uint8_t>> grid_with_8_bit_coords{256, 256, 42};

            CHECK(grid_with_7_bit_coords.at({127, 127}) == 42);
            CHECK(grid_with_8_bit_coords.at({255, 255}) == 42);
        }

        SECTION("width() and height() return the correct values")
        {
            const Grid<int> grid{4, 3};

            CHECK(grid.width() == 4);
            CHECK(grid.height() == 3);
        }

        SECTION("size() returns the number of Grid elements")
        {
            const Grid<int> grid1{1, 1};
            const Grid<int> grid2{1, 3};
            const Grid<int> grid3{3, 1};
            const Grid<int> grid4{5, 6};

            CHECK(grid1.size() == 1);
            CHECK(grid2.size() == 3);
            CHECK(grid3.size() == 3);
            CHECK(grid4.size() == 30);
        }

        SECTION("data() returns a pointer to the first value")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 3);
                auto pi = grid.data();

                REQUIRE(grid.data() != nullptr);
                CHECK(*(grid.data()) == 11);
                CHECK(*pi == 11);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 3);
                auto pi = grid.data();

                REQUIRE(grid.data() != nullptr);
                CHECK(*(grid.data()) == 11);
                CHECK(*pi == 11);

                *pi = 42;

                CHECK(*(grid.data()) == 42);
                CHECK(*pi == 42);
            }
        }

        SECTION("can use at() to access and change values")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 3);

                CHECK(grid.at(0, 0) == 11);
                CHECK(grid.at(1, 0) == 12);
                CHECK(grid.at(0, 1) == 21);
                CHECK(grid.at(3, 2) == 34);

                CHECK(grid.at(Coords{0, 0}) == 11);
                CHECK(grid.at(Coords{1, 0}) == 12);
                CHECK(grid.at(Coords{0, 1}) == 21);
                CHECK(grid.at(Coords{3, 2}) == 34);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 3);

                grid.at(0, 0) = 111;
                grid.at(1, 0) = 222;
                grid.at(0, 1) = 333;
                grid.at(3, 2) = 444;

                CHECK(grid.at(0, 0) == 111);
                CHECK(grid.at(1, 0) == 222);
                CHECK(grid.at(0, 1) == 333);
                CHECK(grid.at(3, 2) == 444);

                grid.at(Coords{0, 0}) = 1111;
                grid.at(Coords{1, 0}) = 2222;
                grid.at(Coords{0, 1}) = 3333;
                grid.at(Coords{3, 2}) = 4444;

                CHECK(grid.at(0, 0) == 1111);
                CHECK(grid.at(1, 0) == 2222);
                CHECK(grid.at(0, 1) == 3333);
                CHECK(grid.at(3, 2) == 4444);
            }
        }

        SECTION("row() returns a Row")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 5);
                auto row0 = grid.row(0);
                auto row1 = grid.row(1);
                auto row2 = grid.row(2);

                CHECK(row0[0] == 11);
                CHECK(row1[0] == 21);
                CHECK(row2[0] == 31);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 5);
                auto row0 = grid.row(0);
                auto row1 = grid.row(1);
                auto row2 = grid.row(2);

                CHECK(row0[0] == 11);
                CHECK(row1[0] == 21);
                CHECK(row2[0] == 31);

                row0[0] = 100;
                row1[0] = 200;
                row2[0] = 300;

                CHECK(grid.at(0, 0) == 100);
                CHECK(grid.at(0, 1) == 200);
                CHECK(grid.at(0, 2) == 300);
            }
        }

        SECTION("rows() returns GridRows")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 5);
                auto rows = grid.rows();

                CHECK(rows[0][0] == 11);
                CHECK(rows[1][0] == 21);
                CHECK(rows[2][0] == 31);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 5);
                auto rows = grid.rows();

                CHECK(rows[0][0] == 11);
                CHECK(rows[1][0] == 21);
                CHECK(rows[2][0] == 31);

                rows[0][0] = 100;
                rows[1][0] = 200;
                rows[2][0] = 300;

                CHECK(grid.at(0, 0) == 100);
                CHECK(grid.at(0, 1) == 200);
                CHECK(grid.at(0, 2) == 300);
            }
        }

        SECTION("col() returns a Col")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 5);
                auto col0 = grid.col(0);
                auto col1 = grid.col(1);
                auto col2 = grid.col(2);

                CHECK(col0[0] == 11);
                CHECK(col1[0] == 12);
                CHECK(col2[0] == 13);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 5);
                auto col0 = grid.col(0);
                auto col1 = grid.col(1);
                auto col2 = grid.col(2);

                REQUIRE(col0[0] == 11);
                REQUIRE(col1[0] == 12);
                REQUIRE(col2[0] == 13);

                col0[0] = 100;
                col1[0] = 200;
                col2[0] = 300;

                CHECK(grid.at(0, 0) == 100);
                CHECK(grid.at(1, 0) == 200);
                CHECK(grid.at(2, 0) == 300);
            }
        }

        SECTION("cols() returns GridCols")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 5);
                auto cols = grid.cols();

                CHECK(cols[0][0] == 11);
                CHECK(cols[1][0] == 12);
                CHECK(cols[2][0] == 13);
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 5);
                auto cols = grid.cols();

                REQUIRE(cols[0][0] == 11);
                REQUIRE(cols[1][0] == 12);
                REQUIRE(cols[2][0] == 13);

                cols[0][0] = 100;
                cols[1][0] = 200;
                cols[2][0] = 300;

                CHECK(grid.at(0, 0) == 100);
                CHECK(grid.at(1, 0) == 200);
                CHECK(grid.at(2, 0) == 300);
            }
        }

        SECTION("can use Grid with POD types")
        {
            int i = 10;

            const Grid<int> grid1{3, 3, 42};
            const Grid<double> grid2{3, 3, 42.0};
            const Grid<int*> grid3{3, 3, &i};

            CHECK(grid1.at(1, 2) == 42);
            CHECK(grid2.at(1, 2) == Catch::Approx(42.0));
            CHECK(grid3.at(1, 2) == &i);
            CHECK(*grid3.at(1, 2) == 10);
        }

        SECTION("can use Grid with objects")
        {
            struct S {
                int x, y;
            };

            const Grid<S> grid{3, 3, {11, 22}};

            CHECK(grid[1][2].x == 11);
            CHECK(grid[1][2].y == 22);
        }

        SECTION("can use Grid with std::string")
        {
            Grid<std::string> grid{3, 3};
            grid.at(1, 2) = "abc";

            CHECK(grid.at(1, 1).size() == 0);
            CHECK(grid.at(1, 2).size() == 3);
            CHECK_THAT(grid.at(1, 1), Catch::Matchers::Equals(""));
            CHECK_THAT(grid.at(1, 2), Catch::Matchers::Equals("abc"));
        }

        SECTION("iterators for all Grid values")
        {
            SECTION("const")
            {
                const Grid<int> grid = create_grid_with_test_values(4, 3);

                SECTION("begin")
                {
                    auto it1 = grid.begin();
                    auto it2 = grid.cbegin();
                    auto it3 = grid.rbegin();
                    auto it4 = grid.crbegin();

                    CHECK(it1 == it2);
                    CHECK(it3 == it4);
                    CHECK(*it1 == grid.at(0, 0));
                    CHECK(*it2 == grid.at(0, 0));
                    CHECK(*it3 == grid.at(3, 2));
                    CHECK(*it4 == grid.at(3, 2));
                }

                SECTION("end")
                {
                    auto it1 = grid.end();
                    auto it2 = grid.cend();
                    auto it3 = grid.rend();
                    auto it4 = grid.crend();

                    CHECK(it1 == it2);
                    CHECK(it3 == it4);
                    CHECK(*(it1 - 1) == grid.at(3, 2));
                    CHECK(*(it2 - 1) == grid.at(3, 2));
                    CHECK(*(it3 - 1) == grid.at(0, 0));
                    CHECK(*(it4 - 1) == grid.at(0, 0));
                }
            }

            SECTION("non-const")
            {
                Grid<int> grid = create_grid_with_test_values(4, 3);

                SECTION("begin")
                {
                    auto it1 = grid.begin();
                    auto it2 = grid.rbegin();

                    CHECK(grid.at(0, 0) == 11);
                    CHECK(grid.at(3, 2) == 34);

                    *it1 = 100;
                    *it2 = 200;

                    CHECK(grid.at(0, 0) == 100);
                    CHECK(grid.at(3, 2) == 200);
                }

                SECTION("end")
                {
                    auto it1 = grid.end();
                    auto it2 = grid.rend();

                    CHECK(grid.at(0, 0) == 11);
                    CHECK(grid.at(3, 2) == 34);

                    *(it1 - 1) = 100;
                    *(it2 - 1) = 200;

                    CHECK(grid.at(0, 0) == 200);
                    CHECK(grid.at(3, 2) == 100);
                }
            }
        }

        SECTION("operators")
        {
            SECTION("operator[]")
            {
                SECTION("const")
                {
                    const Grid<int> grid = create_grid_with_test_values(4, 5);
                    auto row0 = grid[0];
                    auto second_row_third_value = grid[1][2];

                    CHECK(row0[0] == 11);
                    CHECK(row0[1] == 12);
                    CHECK(second_row_third_value == 23);
                }

                SECTION("non-const")
                {
                    Grid<int> grid = create_grid_with_test_values(4, 5);
                    auto row0 = grid[0];
                    auto& second_row_third_value = grid[1][2];

                    CHECK(row0[0] == 11);
                    CHECK(row0[1] == 12);
                    CHECK(second_row_third_value == 23);

                    row0[0] = 100;
                    row0[1] = 200;
                    second_row_third_value = 300;

                    CHECK(grid.at(0, 0) == 100);
                    CHECK(grid.at(1, 0) == 200);
                    CHECK(grid.at(2, 1) == 300);
                }
            }
        }
    }

    SECTION("Grid::GridRows")
    {
        const Grid<int> const_grid = create_grid_with_test_values(4, 5);
        auto const_rows = const_grid.rows();

        Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
        auto non_const_rows = non_const_grid.rows();

        const std::vector first_value_of_each_row_test_values{11, 21, 31, 41, 51};

        SECTION("basic functionality")
        {
            grid_rows_or_cols_check_basic_functionality(const_rows, first_value_of_each_row_test_values);
            grid_rows_or_cols_check_basic_functionality(non_const_rows, first_value_of_each_row_test_values);
        }

        SECTION("iterators")
        {
            grid_rows_or_cols_check_iterators(const_rows, non_const_rows, first_value_of_each_row_test_values);
        }

        SECTION("operators")
        {
            grid_rows_or_cols_check_operators(const_rows, non_const_rows, first_value_of_each_row_test_values);
        }
    }

    SECTION("Grid::GridCols")
    {
        const Grid<int> const_grid = create_grid_with_test_values(4, 5);
        auto const_cols = const_grid.cols();

        Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
        auto non_const_cols = non_const_grid.cols();

        const std::vector first_value_of_each_col_test_values{11, 12, 13, 14};

        SECTION("basic functionality")
        {
            grid_rows_or_cols_check_basic_functionality(const_cols, first_value_of_each_col_test_values);
            grid_rows_or_cols_check_basic_functionality(non_const_cols, first_value_of_each_col_test_values);
        }

        SECTION("iterators")
        {
            grid_rows_or_cols_check_iterators(const_cols, non_const_cols, first_value_of_each_col_test_values);
        }

        SECTION("operators")
        {
            grid_rows_or_cols_check_operators(const_cols, non_const_cols, first_value_of_each_col_test_values);
        }
    }

    SECTION("Grid::Row")
    {
        const Grid<int> const_grid = create_grid_with_test_values(4, 5);
        auto const_row = const_grid.row(0);

        Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
        auto non_const_row = non_const_grid.row(0);

        const std::vector test_values{11, 12, 13, 14};

        SECTION("basic functionality")
        {
            row_or_col_check_basic_functionality(const_row, test_values, std::vector{11, 21, 31, 41, 51});
            row_or_col_check_basic_functionality(non_const_row, test_values, std::vector{11, 21, 31, 41, 51});
        }

        SECTION("iterators")
        {
            row_or_col_check_iterators(const_row, non_const_row, test_values);
        }

        SECTION("operators")
        {
            SECTION("operator<=>")
            {
                check_spaceship_operator(const_grid.rows().front(), const_grid.rows().back());
                check_spaceship_operator(non_const_grid.rows().front(), non_const_grid.rows().back());
            }

            SECTION("other operators")
            {
                row_or_col_check_other_operators(const_row, non_const_row, test_values);
            }
        }
    }

    SECTION("Grid::Col")
    {
        const Grid<int> const_grid = create_grid_with_test_values(4, 5);
        auto const_col = const_grid.col(0);

        Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
        auto non_const_col = non_const_grid.col(0);

        const std::vector test_values{11, 21, 31, 41, 51};

        SECTION("basic functionality")
        {
            row_or_col_check_basic_functionality(const_col, test_values, std::vector{11, 12, 13, 14});
            row_or_col_check_basic_functionality(non_const_col, test_values, std::vector{11, 12, 13, 14});
        }

        SECTION("iterators")
        {
            row_or_col_check_iterators(const_col, non_const_col, test_values);
        }

        SECTION("operators")
        {
            SECTION("operator<=>")
            {
                check_spaceship_operator(const_grid.rows().front(), const_grid.rows().back());
                check_spaceship_operator(non_const_grid.rows().front(), non_const_grid.rows().back());
            }

            SECTION("other operators")
            {
                row_or_col_check_other_operators(const_col, non_const_col, test_values);
            }
        }
    }

    SECTION("Grid::GridRows::iterator")
    {
        const std::vector test_values{11, 21, 31, 41, 51};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto rows = grid.rows();

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto row = rows.begin(); row != rows.end(); ++row)
                    for (auto it = row->begin(); it != row->end(); ++it)
                        sum += *it;

                CHECK(sum == 650);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (auto row : rows)
                    for (auto i : row)
                        sum += i;

                CHECK(sum == 650);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_rows = const_grid.rows();

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_rows = non_const_grid.rows();

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_rows.begin(), const_rows.end(), 5);
                check_distance_between_elements(non_const_rows.begin(), non_const_rows.end(), 5);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_rows.begin());
                check_bidirectional_iterator_requirements(non_const_rows.begin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_rows.begin() + 1, const_rows.end() - 2);
                check_random_access_iterator_requirements(non_const_rows.begin() + 1, non_const_rows.end() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return it->front(); };

                check_iterator_operations(const_rows.begin(), const_rows.end(), test_values, get_value);
                check_iterator_operations(non_const_rows.begin(), non_const_rows.end(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_rows.begin(), const_rows.end());
                    check_spaceship_operator(non_const_rows.begin(), non_const_rows.end());
                }

                SECTION("other operators")
                {
                    row_or_col_iterator_check_other_operators(const_rows.begin(), const_rows.end(), test_values);
                    row_or_col_iterator_check_other_operators(non_const_rows.begin(), non_const_rows.end(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            row_or_col_iterator_check_modifying_values(non_const_grid.rows().begin(), test_values);
        }
    }

    SECTION("Grid::GridRows::reverse_iterator")
    {
        const std::vector test_values{51, 41, 31, 21, 11};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto rows = grid.rows();

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto row = rows.rbegin(); row != rows.rend(); ++row)
                    for (auto it = row->rbegin(); it != row->rend(); ++it)
                        sum += *it;

                CHECK(sum == 650);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_rows = const_grid.rows();

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_rows = non_const_grid.rows();

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_rows.rbegin(), const_rows.rend(), 5);
                check_distance_between_elements(non_const_rows.rbegin(), non_const_rows.rend(), 5);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_rows.rbegin());
                check_bidirectional_iterator_requirements(non_const_rows.rbegin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_rows.rbegin() + 1, const_rows.rend() - 2);
                check_random_access_iterator_requirements(non_const_rows.rbegin() + 1, non_const_rows.rend() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return it->front(); };

                check_iterator_operations(const_rows.rbegin(), const_rows.rend(), test_values, get_value);
                check_iterator_operations(non_const_rows.rbegin(), non_const_rows.rend(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_rows.rbegin(), const_rows.rend());
                    check_spaceship_operator(non_const_rows.rbegin(), non_const_rows.rend());
                }

                SECTION("other operators")
                {
                    row_or_col_iterator_check_other_operators(const_rows.rbegin(), const_rows.rend(), test_values);
                    row_or_col_iterator_check_other_operators(non_const_rows.rbegin(), non_const_rows.rend(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            row_or_col_iterator_check_modifying_values(non_const_grid.rows().rbegin(), test_values);
        }
    }

    SECTION("Grid::GridCols::iterator")
    {
        const std::vector test_values{11, 12, 13, 14};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto cols = grid.cols();

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto col = cols.begin(); col != cols.end(); ++col)
                    for (auto it = col->begin(); it != col->end(); ++it)
                        sum += *it;

                CHECK(sum == 650);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (auto col : cols)
                    for (auto i : col)
                        sum += i;

                CHECK(sum == 650);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_cols = const_grid.cols();

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_cols = non_const_grid.cols();

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_cols.begin(), const_cols.end(), 4);
                check_distance_between_elements(non_const_cols.begin(), non_const_cols.end(), 4);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_cols.begin());
                check_bidirectional_iterator_requirements(non_const_cols.begin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_cols.begin() + 1, const_cols.end() - 2);
                check_random_access_iterator_requirements(non_const_cols.begin() + 1, non_const_cols.end() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return it->front(); };

                check_iterator_operations(const_cols.begin(), const_cols.end(), test_values, get_value);
                check_iterator_operations(non_const_cols.begin(), non_const_cols.end(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_cols.begin(), const_cols.end());
                    check_spaceship_operator(non_const_cols.begin(), non_const_cols.end());
                }

                SECTION("other operators")
                {
                    row_or_col_iterator_check_other_operators(const_cols.begin(), const_cols.end(), test_values);
                    row_or_col_iterator_check_other_operators(non_const_cols.begin(), non_const_cols.end(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            row_or_col_iterator_check_modifying_values(non_const_grid.cols().begin(), test_values);
        }
    }

    SECTION("Grid::GridCols::reverse_iterator")
    {
        const std::vector test_values{14, 13, 12, 11};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto cols = grid.cols();

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto col = cols.rbegin(); col != cols.rend(); ++col)
                    for (auto it = col->rbegin(); it != col->rend(); ++it)
                        sum += *it;

                CHECK(sum == 650);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (auto col : cols)
                    for (auto i : col)
                        sum += i;

                CHECK(sum == 650);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_cols = const_grid.cols();

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_cols = non_const_grid.cols();

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_cols.rbegin(), const_cols.rend(), 4);
                check_distance_between_elements(non_const_cols.rbegin(), non_const_cols.rend(), 4);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_cols.rbegin());
                check_bidirectional_iterator_requirements(non_const_cols.rbegin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_cols.rbegin() + 1, const_cols.rend() - 2);
                check_random_access_iterator_requirements(non_const_cols.rbegin() + 1, non_const_cols.rend() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return it->front(); };

                check_iterator_operations(const_cols.rbegin(), const_cols.rend(), test_values, get_value);
                check_iterator_operations(non_const_cols.rbegin(), non_const_cols.rend(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_cols.rbegin(), const_cols.rend());
                    check_spaceship_operator(non_const_cols.rbegin(), non_const_cols.rend());
                }

                SECTION("other operators")
                {
                    row_or_col_iterator_check_other_operators(const_cols.rbegin(), const_cols.rend(), test_values);
                    row_or_col_iterator_check_other_operators(non_const_cols.rbegin(), non_const_cols.rend(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            row_or_col_iterator_check_modifying_values(non_const_grid.cols().rbegin(), test_values);
        }
    }

    SECTION("Grid::Row::iterator")
    {
        const std::vector test_values{11, 12, 13, 14};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto row = grid.row(0);

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto it = row.begin(); it != row.end(); ++it)
                    sum += *it;

                CHECK(sum == 50);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (const int i : row)
                    sum += i;

                CHECK(sum == 50);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_row = const_grid.row(0);

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_row = non_const_grid.row(0);

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_row.begin(), const_row.end(), 4);
                check_distance_between_elements(non_const_row.begin(), non_const_row.end(), 4);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_row.begin());
                check_bidirectional_iterator_requirements(non_const_row.begin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_row.begin() + 1, const_row.end() - 2);
                check_random_access_iterator_requirements(non_const_row.begin() + 1, non_const_row.end() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return *it; };

                check_iterator_operations(const_row.begin(), const_row.end(), test_values, get_value);
                check_iterator_operations(non_const_row.begin(), non_const_row.end(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator->")
                {
                    struct S {
                        int x = 42;
                    };

                    const Grid<S> const_struct_grid{4, 3};
                    Grid<S> non_const_struct_grid{4, 3};

                    value_iterator_check_arrow_operator(const_struct_grid.row(0).begin(), non_const_struct_grid.row(0).begin(), 42);
                }

                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_row.begin(), const_row.end());
                    check_spaceship_operator(non_const_row.begin(), non_const_row.end());
                }

                SECTION("other operators")
                {
                    value_iterator_check_other_operators(const_row.begin(), const_row.end(), test_values);
                    value_iterator_check_other_operators(non_const_row.begin(), non_const_row.end(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            value_iterator_check_modifying_values(non_const_grid.row(0).begin(), test_values);
        }
    }

    SECTION("Grid::Row::reverse_iterator")
    {
        const std::vector test_values{14, 13, 12, 11};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto row = grid.row(0);

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto it = row.rbegin(); it != row.rend(); ++it)
                    sum += *it;

                CHECK(sum == 50);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_row = const_grid.row(0);

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_row = non_const_grid.row(0);

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_row.rbegin(), const_row.rend(), 4);
                check_distance_between_elements(non_const_row.rbegin(), non_const_row.rend(), 4);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_row.rbegin());
                check_bidirectional_iterator_requirements(non_const_row.rbegin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_row.rbegin() + 1, const_row.rend() - 2);
                check_random_access_iterator_requirements(non_const_row.rbegin() + 1, non_const_row.rend() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return *it; };

                check_iterator_operations(const_row.rbegin(), const_row.rend(), test_values, get_value);
                check_iterator_operations(non_const_row.rbegin(), non_const_row.rend(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator->")
                {
                    struct S {
                        int x = 42;
                    };

                    const Grid<S> const_struct_grid{4, 3};
                    Grid<S> non_const_struct_grid{4, 3};

                    value_iterator_check_arrow_operator(const_struct_grid.row(0).rbegin(), non_const_struct_grid.row(0).rbegin(), 42);
                }

                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_row.rbegin(), const_row.rend());
                    check_spaceship_operator(non_const_row.rbegin(), non_const_row.rend());
                }

                SECTION("other operators")
                {
                    value_iterator_check_other_operators(const_row.rbegin(), const_row.rend(), test_values);
                    value_iterator_check_other_operators(non_const_row.rbegin(), non_const_row.rend(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            value_iterator_check_modifying_values(non_const_grid.row(0).rbegin(), test_values);
        }
    }

    SECTION("Grid::Col::iterator")
    {
        const std::vector test_values{11, 21, 31, 41, 51};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto col = grid.col(0);

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto it = col.begin(); it != col.end(); ++it)
                    sum += *it;

                CHECK(sum == 155);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (const int i : col)
                    sum += i;

                CHECK(sum == 155);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_col = const_grid.col(0);

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_col = non_const_grid.col(0);

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_col.begin(), const_col.end(), 5);
                check_distance_between_elements(non_const_col.begin(), non_const_col.end(), 5);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_col.begin());
                check_bidirectional_iterator_requirements(non_const_col.begin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_col.begin() + 1, const_col.end() - 2);
                check_random_access_iterator_requirements(non_const_col.begin() + 1, non_const_col.end() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return *it; };

                check_iterator_operations(const_col.begin(), const_col.end(), test_values, get_value);
                check_iterator_operations(non_const_col.begin(), non_const_col.end(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator->")
                {
                    struct S {
                        int x = 42;
                    };

                    const Grid<S> const_struct_grid{4, 3};
                    Grid<S> non_const_struct_grid{4, 3};

                    value_iterator_check_arrow_operator(const_struct_grid.col(0).begin(), non_const_struct_grid.col(0).begin(), 42);
                }

                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_col.begin(), const_col.end());
                    check_spaceship_operator(non_const_col.begin(), non_const_col.end());
                }

                SECTION("other operators")
                {
                    value_iterator_check_other_operators(const_col.begin(), const_col.end(), test_values);
                    value_iterator_check_other_operators(non_const_col.begin(), non_const_col.end(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            value_iterator_check_modifying_values(non_const_grid.col(0).begin(), test_values);
        }
    }

    SECTION("Grid::Col::reverse_iterator")
    {
        const std::vector test_values{51, 41, 31, 21, 11};

        SECTION("iterate values")
        {
            const Grid<int> grid = create_grid_with_test_values(4, 5);
            auto col = grid.col(0);

            SECTION("traditional for loop")
            {
                int sum = 0;

                for (auto it = col.rbegin(); it != col.rend(); ++it)
                    sum += *it;

                CHECK(sum == 155);
            }

            SECTION("range-based for loop")
            {
                int sum = 0;

                for (const int i : col)
                    sum += i;

                CHECK(sum == 155);
            }
        }

        SECTION("const and non-const tests")
        {
            const Grid<int> const_grid = create_grid_with_test_values(4, 5);
            auto const_col = const_grid.col(0);

            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);
            auto non_const_col = non_const_grid.col(0);

            SECTION("distance between elements")
            {
                check_distance_between_elements(const_col.rbegin(), const_col.rend(), 5);
                check_distance_between_elements(non_const_col.rbegin(), non_const_col.rend(), 5);
            }

            SECTION("bidirectional_iterator requirements")
            {
                check_bidirectional_iterator_requirements(const_col.rbegin());
                check_bidirectional_iterator_requirements(non_const_col.rbegin());
            }

            SECTION("random_access_iterator requirements")
            {
                check_random_access_iterator_requirements(const_col.rbegin() + 1, const_col.rend() - 2);
                check_random_access_iterator_requirements(non_const_col.rbegin() + 1, non_const_col.rend() - 2);
            }

            SECTION("iterator operations")
            {
                auto get_value = [](auto it) { return *it; };

                check_iterator_operations(const_col.rbegin(), const_col.rend(), test_values, get_value);
                check_iterator_operations(non_const_col.rbegin(), non_const_col.rend(), test_values, get_value);
            }

            SECTION("operators")
            {
                SECTION("operator->")
                {
                    struct S {
                        int x = 42;
                    };

                    const Grid<S> const_struct_grid{4, 3};
                    Grid<S> non_const_struct_grid{4, 3};

                    value_iterator_check_arrow_operator(const_struct_grid.col(0).rbegin(), non_const_struct_grid.col(0).rbegin(), 42);
                }

                SECTION("operator<=>")
                {
                    check_spaceship_operator(const_col.rbegin(), const_col.rend());
                    check_spaceship_operator(non_const_col.rbegin(), non_const_col.rend());
                }

                SECTION("other operators")
                {
                    value_iterator_check_other_operators(const_col.rbegin(), const_col.rend(), test_values);
                    value_iterator_check_other_operators(non_const_col.rbegin(), non_const_col.rend(), test_values);
                }
            }
        }

        SECTION("modifying values")
        {
            Grid<int> non_const_grid = create_grid_with_test_values(4, 5);

            value_iterator_check_modifying_values(non_const_grid.col(0).rbegin(), test_values);
        }
    }
}

}  // namespace tic_tac_toe
