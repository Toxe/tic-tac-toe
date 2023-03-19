#pragma once

#include <cassert>
#include <compare>
#include <iterator>
#include <vector>

#include "gridcell.hpp"

namespace tic_tac_toe {

template <typename T = int, typename CoordsType = Coords<int>>
class Grid {
public:
    using difference_type = std::ptrdiff_t;
    using size_type = int;

    constexpr static difference_type direction_forward = 1;
    constexpr static difference_type direction_reverse = -1;

private:
    template <typename pointer, typename reference>
    class ValueIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = Grid::difference_type;

        ValueIterator() : ptr_{}, stride_{} { }
        ValueIterator(pointer ptr, const difference_type stride)
        {
            assert(ptr != nullptr);
            assert(stride > 0);
            ptr_ = ptr;
            stride_ = stride;
        }

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        ValueIterator& operator++()
        {
            ptr_ += stride_;
            return *this;
        }

        ValueIterator operator++(int)
        {
            const ValueIterator tmp{*this};
            ++(*this);
            return tmp;
        }

        ValueIterator& operator--()
        {
            ptr_ -= stride_;
            return *this;
        }

        ValueIterator operator--(int)
        {
            const ValueIterator tmp{*this};
            --(*this);
            return tmp;
        }

        ValueIterator& operator+=(const difference_type off)
        {
            ptr_ += off * stride_;
            return *this;
        }

        ValueIterator& operator-=(const difference_type off)
        {
            ptr_ -= off * stride_;
            return *this;
        }

        ValueIterator operator+(const difference_type off) const { return ValueIterator{ptr_ + off * stride_, stride_}; }
        ValueIterator operator-(const difference_type off) const { return ValueIterator{ptr_ - off * stride_, stride_}; }
        friend ValueIterator operator+(const difference_type off, const ValueIterator& a) { return ValueIterator{a.ptr_ + off * a.stride_, a.stride_}; }
        friend difference_type operator-(const ValueIterator& a, const ValueIterator& b)
        {
            assert(a.stride_ == b.stride_);
            return (a.ptr_ - b.ptr_) / a.stride_;
        };

        reference operator[](const difference_type off) const { return *(ptr_ + off * stride_); }

        auto operator<=>(const ValueIterator& rhs) const { return ptr_ <=> rhs.ptr_; }
        bool operator==(const ValueIterator& rhs) const { return ptr_ == rhs.ptr_; }

    private:
        pointer ptr_;
        difference_type stride_;
    };

    template <typename pointer, typename reference>
    class RowOrCol {
    public:
        using const_pointer = const T*;
        using const_reference = const T&;
        using difference_type = Grid::difference_type;
        using size_type = Grid::size_type;
        using iterator = ValueIterator<pointer, reference>;
        using const_iterator = ValueIterator<const_pointer, const_reference>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        RowOrCol() : ptr_{}, size_{}, stride_{}, value_iter_stride_{} { }
        RowOrCol(pointer ptr, const size_type size, const difference_type stride, const difference_type value_iter_stride)
        {
            assert(ptr != nullptr);
            assert(size > 0);
            assert(stride > 0);
            assert(value_iter_stride > 0);
            ptr_ = ptr;
            size_ = size;
            stride_ = stride;
            value_iter_stride_ = value_iter_stride;
        }

        size_type size() const { return size_; }

        iterator begin() { return iterator{ptr_, value_iter_stride_}; }
        const_iterator begin() const { return const_iterator{ptr_, value_iter_stride_}; }
        const_iterator cbegin() const { return begin(); }

        iterator end() { return iterator{ptr_ + size_ * value_iter_stride_, value_iter_stride_}; }
        const_iterator end() const { return const_iterator{ptr_ + size_ * value_iter_stride_, value_iter_stride_}; }
        const_iterator cend() const { return end(); }

        reverse_iterator rbegin() { return reverse_iterator{end()}; }
        const_reverse_iterator rbegin() const { return const_reverse_iterator{end()}; }
        const_reverse_iterator crbegin() const { return rbegin(); }

        reverse_iterator rend() { return reverse_iterator{begin()}; }
        const_reverse_iterator rend() const { return const_reverse_iterator{begin()}; }
        const_reverse_iterator crend() const { return rend(); }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }

        reference back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }

        friend difference_type operator-(const RowOrCol& a, const RowOrCol& b)
        {
            assert(a.stride_ == b.stride_);
            return (a.ptr_ - b.ptr_) / a.stride_;
        }

        reference operator[](const size_type pos) { return *(begin() + pos); }
        const_reference operator[](const size_type pos) const { return *(begin() + pos); }

        auto operator<=>(const RowOrCol& rhs) const { return ptr_ <=> rhs.ptr_; }
        bool operator==(const RowOrCol& rhs) const { return ptr_ == rhs.ptr_; }

        void advance(const difference_type off) { ptr_ += stride_ * off; }
        RowOrCol next(const difference_type off = 1) const { return RowOrCol{ptr_ + stride_ * off, size_, stride_, value_iter_stride_}; }

    private:
        pointer ptr_;
        size_type size_;
        difference_type stride_;
        difference_type value_iter_stride_;
    };

    template <typename grid_value_type_pointer, typename grid_value_type_reference, typename Grid::difference_type direction>
    class RowOrColIterator {
    public:
        using row_or_col_type = RowOrCol<grid_value_type_pointer, grid_value_type_reference>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = row_or_col_type;
        using pointer = row_or_col_type*;
        using reference = row_or_col_type&;
        using const_reference = const row_or_col_type&;
        using const_pointer = const row_or_col_type*;
        using difference_type = Grid::difference_type;
        using size_type = Grid::size_type;

        static_assert(direction == direction_forward || direction == direction_reverse);

        RowOrColIterator(const row_or_col_type& row_or_col) : row_or_col_{row_or_col} { }
        RowOrColIterator(grid_value_type_pointer ptr, const size_type row_or_col_size, const difference_type row_or_col_stride, const difference_type value_iter_stride)
        {
            assert(ptr != nullptr);
            assert(row_or_col_size > 0);
            assert(row_or_col_stride > 0);
            assert(value_iter_stride > 0);
            row_or_col_ = row_or_col_type{ptr, row_or_col_size, row_or_col_stride, value_iter_stride};
        }

        reference operator*() { return row_or_col_; }
        const_reference operator*() const { return row_or_col_; }
        pointer operator->() { return &row_or_col_; }

        RowOrColIterator& operator++()
        {
            row_or_col_.advance(direction);
            return *this;
        }

        RowOrColIterator operator++(int)
        {
            const RowOrColIterator tmp{*this};
            ++(*this);
            return tmp;
        }

        RowOrColIterator& operator--()
        {
            row_or_col_.advance(-direction);
            return *this;
        }

        RowOrColIterator operator--(int)
        {
            const RowOrColIterator tmp{*this};
            --(*this);
            return tmp;
        }

        RowOrColIterator& operator+=(const difference_type off)
        {
            row_or_col_.advance(off * direction);
            return *this;
        }

        RowOrColIterator& operator-=(const difference_type off)
        {
            row_or_col_.advance(-off * direction);
            return *this;
        }

        RowOrColIterator operator+(const difference_type off) const { return RowOrColIterator{row_or_col_.next(off * direction)}; }
        RowOrColIterator operator-(const difference_type off) const { return RowOrColIterator{row_or_col_.next(-off * direction)}; }
        friend RowOrColIterator operator+(const difference_type off, const RowOrColIterator& a) { return RowOrColIterator{a.row_or_col_.next(off * direction)}; }
        friend difference_type operator-(const RowOrColIterator& a, const RowOrColIterator& b)
        {
            if constexpr (direction == direction_forward)
                return a.row_or_col_ - b.row_or_col_;
            else
                return b.row_or_col_ - a.row_or_col_;
        }

        row_or_col_type operator[](const difference_type off) const { return row_or_col_.next(off * direction); }

        bool operator==(const RowOrColIterator&) const = default;
        auto operator<=>(const RowOrColIterator& rhs) const
        {
            if constexpr (direction == direction_forward)
                return row_or_col_ <=> rhs.row_or_col_;
            else
                return rhs.row_or_col_ <=> row_or_col_;
        }

    private:
        row_or_col_type row_or_col_;
    };

    template <typename pointer, typename reference>
    class GridRowsOrCols {
    public:
        using const_pointer = const T*;
        using const_reference = const T&;
        using difference_type = Grid::difference_type;
        using size_type = Grid::size_type;
        using iterator = RowOrColIterator<pointer, reference, direction_forward>;
        using const_iterator = RowOrColIterator<const_pointer, const_reference, direction_forward>;
        using reverse_iterator = RowOrColIterator<pointer, reference, direction_reverse>;
        using const_reverse_iterator = RowOrColIterator<const_pointer, const_reference, direction_reverse>;

        GridRowsOrCols(pointer ptr, const size_type size, const size_type row_or_col_size, const difference_type row_or_col_stride, const difference_type value_iter_stride)
        {
            assert(ptr != nullptr);
            assert(size > 0);
            assert(row_or_col_size > 0);
            assert(row_or_col_stride > 0);
            assert(value_iter_stride > 0);
            ptr_ = ptr;
            size_ = size;
            row_or_col_size_ = row_or_col_size;
            row_or_col_stride_ = row_or_col_stride;
            value_iter_stride_ = value_iter_stride;
        }

        size_type size() const { return size_; }

        iterator begin() { return iterator{ptr_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_iterator begin() const { return const_iterator{ptr_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_iterator cbegin() const { return begin(); }

        iterator end() { return iterator{ptr_ + size_ * row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_iterator end() const { return const_iterator{ptr_ + size_ * row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_iterator cend() const { return end(); }

        reverse_iterator rbegin() { return reverse_iterator{ptr_ + (size_ - 1) * row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_reverse_iterator rbegin() const { return const_reverse_iterator{ptr_ + (size_ - 1) * row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_reverse_iterator crbegin() const { return rbegin(); }

        reverse_iterator rend() { return reverse_iterator{ptr_ - row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_reverse_iterator rend() const { return const_reverse_iterator{ptr_ - row_or_col_stride_, row_or_col_size_, row_or_col_stride_, value_iter_stride_}; }
        const_reverse_iterator crend() const { return rend(); }

        auto front() { return *begin(); }
        auto front() const { return *begin(); }

        auto back() { return *(end() - 1); }
        auto back() const { return *(end() - 1); }

        auto operator[](const size_type pos) { return *(begin() + pos); }

    private:
        pointer ptr_;
        size_type size_;
        size_type row_or_col_size_;
        difference_type row_or_col_stride_;
        difference_type value_iter_stride_;
    };

public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using coords_type = CoordsType;
    using grid_rows_type = GridRowsOrCols<pointer, reference>;
    using grid_cols_type = GridRowsOrCols<pointer, reference>;
    using const_grid_rows_type = GridRowsOrCols<const_pointer, const_reference>;
    using const_grid_cols_type = GridRowsOrCols<const_pointer, const_reference>;
    using grid_cell_type = GridCell<Grid<T, coords_type>*, coords_type>;
    using const_grid_cell_type = GridCell<const Grid<T, coords_type>*, coords_type>;

    Grid(size_type cols, size_type rows);
    Grid(size_type cols, size_type rows, const T& value);

    size_type width() const { return cols_; }
    size_type height() const { return rows_; }

    size_type size() const { return static_cast<size_type>(data_.size()); }

    pointer data() { return data_.data(); }
    const_pointer data() const { return data_.data(); }

    [[nodiscard]] reference at(size_type col, size_type row) { return data_[idx(col, row)]; }
    [[nodiscard]] const_reference at(size_type col, size_type row) const { return data_[idx(col, row)]; }

    [[nodiscard]] reference at(const coords_type& coords) { return data_[idx(coords)]; }
    [[nodiscard]] const_reference at(const coords_type& coords) const { return data_[idx(coords)]; }

    [[nodiscard]] grid_cell_type cell(const coords_type& coords) { return grid_cell_type{this, coords}; }
    [[nodiscard]] const_grid_cell_type cell(const coords_type& coords) const { return const_grid_cell_type{this, coords}; }

    [[nodiscard]] grid_cell_type cell(size_type col, size_type row) { return cell(coords_type{static_cast<typename coords_type::coordinates_type>(col), static_cast<typename coords_type::coordinates_type>(row)}); }
    [[nodiscard]] const_grid_cell_type cell(size_type col, size_type row) const { return cell(coords_type{static_cast<typename coords_type::coordinates_type>(col), static_cast<typename coords_type::coordinates_type>(row)}); }

    auto begin() { return data_.begin(); }
    auto begin() const { return data_.cbegin(); }
    auto cbegin() const { return data_.cbegin(); }

    auto end() { return data_.end(); }
    auto end() const { return data_.cend(); }
    auto cend() const { return data_.cend(); }

    auto rbegin() { return data_.rbegin(); }
    auto rbegin() const { return data_.crbegin(); }
    auto crbegin() const { return data_.crbegin(); }

    auto rend() { return data_.rend(); }
    auto rend() const { return data_.crend(); }
    auto crend() const { return data_.crend(); }

    [[nodiscard]] auto rows() { return grid_rows_type(data(), height(), width(), width(), 1); }
    [[nodiscard]] auto rows() const { return const_grid_rows_type(data(), height(), width(), width(), 1); }
    [[nodiscard]] auto cols() { return grid_cols_type(data(), width(), height(), 1, width()); }
    [[nodiscard]] auto cols() const { return const_grid_cols_type(data(), width(), height(), 1, width()); }

    [[nodiscard]] auto row(const size_type pos) { return *(rows().begin() + pos); }
    [[nodiscard]] auto row(const size_type pos) const { return *(rows().begin() + pos); }
    [[nodiscard]] auto col(const size_type pos) { return *(cols().begin() + pos); }
    [[nodiscard]] auto col(const size_type pos) const { return *(cols().begin() + pos); }

    auto operator[](const size_type pos) { return row(pos); }
    auto operator[](const size_type pos) const { return row(pos); }

private:
    size_type cols_;
    size_type rows_;

    std::vector<T> data_;

    [[nodiscard]] inline std::size_t idx(size_type col, size_type row) const;
    [[nodiscard]] inline std::size_t idx(const coords_type& coords) const;
};

template <typename T, typename CoordsType>
Grid<T, CoordsType>::Grid(const size_type cols, const size_type rows)
{
    assert(cols > 0 && rows > 0);
    assert(cols - 1 <= coords_type::max());
    assert(rows - 1 <= coords_type::max());
    cols_ = cols;
    rows_ = rows;
    data_ = std::vector<T>(static_cast<std::size_t>(cols * rows));
}

template <typename T, typename CoordsType>
Grid<T, CoordsType>::Grid(const size_type cols, const size_type rows, const T& value)
{
    assert(cols > 0 && rows > 0);
    assert(cols - 1 <= coords_type::max());
    assert(rows - 1 <= coords_type::max());
    cols_ = cols;
    rows_ = rows;
    data_ = std::vector<T>(static_cast<std::size_t>(cols * rows), value);
}

template <typename T, typename CoordsType>
std::size_t Grid<T, CoordsType>::idx(const size_type col, const size_type row) const
{
    assert(col >= 0 && col < cols_);
    assert(row >= 0 && row < rows_);
    return static_cast<std::size_t>(row * cols_ + col);
}

template <typename T, typename CoordsType>
std::size_t Grid<T, CoordsType>::idx(const coords_type& coords) const
{
    assert(coords.x >= 0 && coords.x < cols_);
    assert(coords.y >= 0 && coords.y < rows_);
    return static_cast<std::size_t>(coords.y * cols_ + coords.x);
}

}  // namespace tic_tac_toe
