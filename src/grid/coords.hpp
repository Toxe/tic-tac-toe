#pragma once

#include <compare>
#include <limits>

namespace tic_tac_toe {

template <typename CoordinatesType = int>
struct Coords {
    using coordinates_type = CoordinatesType;

    static_assert(std::numeric_limits<coordinates_type>::digits <= std::numeric_limits<int>::digits, "maximum supported coordinates type is int32");

    coordinates_type x{};
    coordinates_type y{};

    Coords() : x{}, y{} { }
    Coords(coordinates_type x_coord, coordinates_type y_coord) : x{x_coord}, y{y_coord} { }

    static coordinates_type max() { return std::numeric_limits<coordinates_type>::max(); }

    [[nodiscard]] coordinates_type col() const { return x; }
    [[nodiscard]] coordinates_type row() const { return y; }

    void move(const int dx, const int dy)
    {
        x = static_cast<coordinates_type>(x + dx);
        y = static_cast<coordinates_type>(y + dy);
    }

    void move(const Coords& delta)
    {
        x += delta.x;
        y += delta.y;
    }

    void move_horizontally(const int distance) { x = static_cast<coordinates_type>(x + distance); }
    void move_vertically(const int distance) { y = static_cast<coordinates_type>(y + distance); }

    void move_up(const int distance = 1) { move_vertically(-distance); }
    void move_down(const int distance = 1) { move_vertically(distance); }
    void move_left(const int distance = 1) { move_horizontally(-distance); }
    void move_right(const int distance = 1) { move_horizontally(distance); }

    void move_north(const int distance = 1) { move_vertically(-distance); }
    void move_south(const int distance = 1) { move_vertically(distance); }
    void move_west(const int distance = 1) { move_horizontally(-distance); }
    void move_east(const int distance = 1) { move_horizontally(distance); }

    Coords operator+(const Coords& other) const { return Coords{static_cast<coordinates_type>(x + other.x), static_cast<coordinates_type>(y + other.y)}; }
    Coords operator-(const Coords& other) const { return Coords{static_cast<coordinates_type>(x - other.x), static_cast<coordinates_type>(y - other.y)}; }

    Coords& operator+=(const Coords& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Coords& operator-=(const Coords& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    auto operator<=>(const Coords& rhs) const = default;
};

}  // namespace tic_tac_toe
