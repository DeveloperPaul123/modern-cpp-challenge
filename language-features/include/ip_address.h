#pragma once

#include <array>
#include <string>
#include <string_view>
#include <stdint.h>

namespace ip
{
    /**
     * @brief Thrown when there is an invalid ip address passed via
     * string.
     */
    class invalid_format_exception : public std::exception
    {
        std::string invalid_format_;
    public:
        invalid_format_exception(const std::string &invalid_format) noexcept;
		virtual ~invalid_format_exception() noexcept {};
        char const* what() const noexcept override;
    };

    /**
     * Class that models a IPv4 address. 
     */
    class address
    {
    public:

#pragma region Type definitions
        using value_type = uint8_t;
		using storage_type = std::array<value_type, 4>;
        using reference = value_type & ;
        using pointer = value_type * ;
        using size_type = std::array<value_type, 4>::size_type;
#pragma endregion

        /**
         * @brief Create an IP address representation from the 
         * four parts of the address definition. 
         * @param first the first part of the address 
         * @param second the second part of the address
         * @param third the third part of the address.
         * @param fourth the fourth part of the address.
         * @details Example:
         * @code
         * ip::address addr(127, 0, 0, 1);
         * @endcode
         */
        address(value_type first, value_type second,
            value_type third, value_type fourth);

        /**
         * @brief Create an IP address representaiton from an
         * array.
         * @param data the data array. 
         * @details Example:
         * @code
         * ip::address addr = {127, 0, 0, 1};
         * @endcode
         */
        address(const std::array<unsigned char, 4> &data);

        /**
         * @brief Create an IP adderss representation from a 
         * unsigned 32 bit integer.
         * @param value the integer representation of an IP address.
         */
        explicit address(uint32_t value);

        /**
         * @brief Access operator.
         * @param index the index to access. 
         */
        reference operator[](const int &index) noexcept(false);

        /**
         * @brief Const version of the access operator.
         */
        value_type operator[](const int &index) const noexcept(false);

        /**
         * @brief Prefix increment operator.
         */
        address& operator++();

        /**
         * @brief Postfix increment operator.
         */
        address operator++(int);

        /**
         * @brief Prefix decrement operator.
         */
        address& operator--();

        /**
         * @brief Postfix decrement operator.
         */
        address operator--(int);
    private:
        storage_type data_{};
    };

    bool operator<(const ip::address &first, const ip::address &second);
    bool operator==(const ip::address &first, const ip::address &second);
    std::ostream& operator<<(std::ostream& output, const ip::address &address);
    address from_string(const std::string &view);
    std::string to_string(const address& address);
	uint32_t to_uint32(const address& address);
}