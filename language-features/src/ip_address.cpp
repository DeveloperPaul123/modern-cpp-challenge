#include <ip_address.h>

#include <iterator>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>

#pragma region Utilities
template<typename Output>
void split(const std::string &s, char delim, Output result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

#pragma endregion

ip::invalid_format_exception::invalid_format_exception(const std::string& invalid_format) noexcept
    : invalid_format_(invalid_format)
{
}

char const* ip::invalid_format_exception::what() const noexcept
{
    std::ostringstream oss;
    oss << "Invalid IP address format: " << invalid_format_;
    return oss.str().c_str();
}

ip::address::address(value_type const first, value_type const second, value_type const third, value_type const fourth)
{
    data_[0] = first;
    data_[1] = second;
    data_[2] = third;
    data_[3] = fourth;
}

ip::address::address(const std::array<unsigned char, 4>& data)
{
    data_ = data;
}

ip::address::address(uint32_t const value)
{
    data_[0] = value >> 24 & 0xFF;
    data_[1] = value >> 16 & 0xFF;
    data_[2] = value >> 8 & 0xFF;
    data_[3] = value & 0xFF;
}

ip::address::reference ip::address::operator[](const int& index)
{
    return data_.at(index);
}

ip::address::value_type ip::address::operator[](const int& index) const
{
    return data_.at(index);
}

ip::address& ip::address::operator++()
{
	auto value = to_uint32(*this);
	++value;                     
	(*this) = address(value);
	return *this;
}

::ip::address ip::address::operator++(int)
{
	const auto result(*this);
    ++(*this);
    return result;
}

ip::address& ip::address::operator--()
{
	auto value = to_uint32(*this); 
	--value;                     
	(*this) = address(value);
	return *this;
}

::ip::address ip::address::operator--(int)
{
	const auto result(*this);
    --(*this);
    return result;
}

bool ip::operator<(const ip::address& first, const ip::address& second)
{
	return to_uint32(first) < to_uint32(second);
}

bool ip::operator==(const ip::address& first, const ip::address& second)
{
    return to_uint32(first) == to_uint32(second);
}

std::ostream& ip::operator<<(std::ostream& output, const ip::address& address)
{
    for(auto i = 0; i < 3; i++)
    {
		output << +address[i] << ".";
    }
    output << +address[3];
    return output;
}

ip::address ip::from_string(const std::string &view)
{
    auto parts = split(view, '.');
    if (parts.size() != 4)
    {
        throw invalid_format_exception(view);
    }

    return {
        ip::address::value_type(std::stoi(parts[0])),
        ip::address::value_type(std::stoi(parts[1])),
        ip::address::value_type(std::stoi(parts[2])),
        ip::address::value_type(std::stoi(parts[3]))
    };
}

std::string ip::to_string(const address& address)
{
    std::ostringstream string_stream;
    string_stream << address;
    return string_stream.str();
}

uint32_t ip::to_uint32(const address& address)
{
	const uint32_t value = address[0] << 24 | address[1] << 16 | address[2] << 8 | address[3];
	return value;
}




