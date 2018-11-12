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

ip::invalid_format_exception::invalid_format_exception(const std::string& invalid_format)
    : invalid_format_(invalid_format)
{
}

char const* ip::invalid_format_exception::what() const
{
    std::ostringstream oss;
    oss << "Invalid IP address format: " << invalid_format_;
    return oss.str().c_str();
}

ip::address::address(const value_type & first, const value_type & second, const value_type & third, const value_type & fourth)
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

ip::address::address(const uint32_t& value)
{
    data_[0] = value >> 24 & 0xFF;
    data_[1] = value >> 16 & 0xFF;
    data_[2] = value >> 8 & 0xFF;
    data_[3] = value & 0xFF;
}

uint32_t ip::address::operator()() const
{
    const uint32_t value = data_[0] << 24 | data_[1] << 16 | data_[2] << 8 | data_[3];
    return value;
}

ip::address::reference ip::address::operator[](const int& index)
{
    return data_.at(index);
}

ip::address::value_type ip::address::operator[](const int& index) const
{
    return data_.at(index);
}

void ip::address::operator++()
{
    auto location = std::find_if(data_.rbegin(), data_.rend(), [](const unsigned char& data)
    {
        return data < 255;
    });

    if(location != std::rend(data_))
    {
        const auto r_index = std::distance(data_.rbegin(), location);
        auto index = 4 - r_index - 1;
        data_[index]++;
    }
}

::ip::address& ip::address::operator++(int)
{
    auto result(*this);
    ++(*this);
    return result;
}

void ip::address::operator--()
{
    auto location = std::find_if(data_.rbegin(), data_.rend(), [](const unsigned char& data)
    {
        return data < 255;
    });

    if (location != std::rend(data_))
    {
        const auto r_index = std::distance(data_.rbegin(), location);
        auto index = 4 - r_index - 1;
        data_[index]--;
    }
}

::ip::address& ip::address::operator--(int)
{
    auto result(*this);
    --(*this);
    return result;
}

ip::address::iterator ip::address::begin()
{
    return data_.begin();
}

ip::address::const_iterator ip::address::end() const
{
    return data_.end();
}

bool ip::operator<(const ip::address& first, const ip::address& second)
{
    return (uint32_t)first() < (uint32_t)second();
}

bool ip::operator==(const ip::address& first, const ip::address& second)
{
    return (uint32_t)first() == (uint32_t) second();
}

ip::address::const_iterator ip::address::begin() const
{
    return data_.begin();
}

ip::address::iterator ip::address::end()
{
    return data_.end();
}

std::ostream& ip::operator<<(std::ostream& output, const ip::address& address)
{
    std::copy(address.begin(), address.end()-1, 
        std::ostream_iterator<short>(output, "."));
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
        (ip::address::value_type)std::stoi(parts[0]),
        (ip::address::value_type)std::stoi(parts[1]),
        (ip::address::value_type)std::stoi(parts[2]),
        (ip::address::value_type)std::stoi(parts[3])
    };
}

std::string ip::to_string(const address& address)
{
    std::ostringstream string_stream;
    string_stream << address;
    return string_stream.str();
}




