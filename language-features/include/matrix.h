#pragma once

#include <array>

namespace mcc
{
    template<typename T, std::size_t M, std::size_t N>
    class matrix
    {
    public:

#pragma regiond Type definitions
        using value_type = T;
        using size_type = std::size_t;
        using container_type = std::array<value_type, M*N>;
        using reference = typename container_type::reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        using iterator = typename container_type::iterator;
        using const_iterator = typename container_type::const_iterator;
        using reverse_iterator = typename container_type::reverse_iterator;
        using const_reverse_iterator = typename container_type::const_reverse_iterator;
#pragma endregion

        matrix();
        explicit matrix(const T& value);
        explicit matrix(std::array<value_type, M*N> &data);
        matrix(std::initializer_list<value_type> values);
        value_type operator[](const size_type & index);

        T at(const std::size_t &row, const std::size_t &col);
        T* data();
        T* data() const;
        reference operator()(const std::size_t& row, const std::size_t &col);
        size_type columns() const;
        size_type rows() const;

        iterator begin(); 
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

        void fill(const T& value);

        constexpr bool empty() const noexcept;

    private:
        std::size_t size_ = M * N;
        std::size_t rows_;
        std::size_t columns_;
        std::array<T, M*N> data_;
    };

    template <typename T, std::size_t M, std::size_t N>
    constexpr bool matrix<T, M, N>::empty() const noexcept
    {
        return M == 0 || N == 0;
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix() : rows_(M), columns_(N)
    {
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(const T& value) : rows_(M), columns_(N)
    {
        fill(value);
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(std::array<value_type, M * N>& data): rows_(M), columns_(N)
    {
        data_ = data;
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(std::initializer_list<value_type> values) : rows_(M), columns_(N)
    {
        assert(values.size() == size_);
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::value_type matrix<T, M, N>::operator[](const size_type& index)
    {
        return data_[index];
    }

    template <typename T, std::size_t M, std::size_t N>
    T matrix<T, M, N>::at(const std::size_t& row, const std::size_t& col)
    {
        // assumes data is ordered in row major order. 
        const auto index = row * columns_ + col;
        return data_.at(index);
    }

    template <typename T, std::size_t M, std::size_t N>
    T* matrix<T, M, N>::data()
    {
        return data_.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    T* matrix<T, M, N>::data() const
    {
        return data_.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reference matrix<T, M, N>::operator()(const std::size_t& row, const std::size_t& col)
    {
        return data_[row * columns_ + col];
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::size_type matrix<T, M, N>::columns() const
    {
        return columns_;
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::size_type matrix<T, M, N>::rows() const
    {
        return rows_;
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::iterator matrix<T, M, N>::begin()
    {
        return data_.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::iterator matrix<T, M, N>::end()
    {
        return data_.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_iterator matrix<T, M, N>::begin() const
    {
        return data_.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_iterator matrix<T, M, N>::end() const
    {
        return data_.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reverse_iterator matrix<T, M, N>::rbegin()
    {
        return data_.rbegin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reverse_iterator matrix<T, M, N>::rend()
    {
        return data_.rend();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_reverse_iterator matrix<T, M, N>::rbegin() const
    {
        return data_.rbegin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_reverse_iterator matrix<T, M, N>::rend() const
    {
        return data_.rend();
    }


    template <typename T, std::size_t M, std::size_t N>
    void matrix<T, M, N>::fill(const T& value)
    {
        std::fill(data_.begin(), data_.end(), value);
    }
}
