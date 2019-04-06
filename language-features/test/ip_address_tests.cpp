#include <gtest/gtest.h>
#include <ip_address.h>

#include <string_view>

/**
 * Test incrementing of an IP address. 
 */
TEST(IpAddressTests, Increment)
{
    ip::address ipv4 = { 0, 0, 0, 255 };
	++ipv4;
	ASSERT_EQ(ipv4[3], 0);
	ASSERT_EQ(ipv4[2], 1);
}

/**
 * Test decrementing an IP address. 
 */
TEST(IpAddressTests, Decrement)
{
    ip::address addr = { 198, 1, 1, 11 };

    for(int i = 0; i < 11; i++)
    {
        addr--;
    }

    std::cout << addr << std::endl;

    ASSERT_EQ(addr[3], 0);
}

/**
 * Test conversion of ip::address to/from a string. 
 */
TEST(IpAddressTests, ToFromString)
{
    // to string
    const ip::address addr = { 198, 1, 0, 11 };
    auto string = ip::to_string(addr);
    ASSERT_EQ(string, "198.1.0.11");

    // from string
    EXPECT_NO_THROW(
        {
            ip::address address = ip::from_string("127.192.37.1");
            std::cout << "Read ip address: " << address << std::endl;
            EXPECT_EQ(address[0], 127);
            EXPECT_EQ(address[1], 192);
            EXPECT_EQ(address[2], 37);
            EXPECT_EQ(address[3], 1);
        }
    );
}

/**
 * Test conversino to/from an unsigned 32 bit integer. 
 */
TEST(IpAddressTests, ToFromLong)
{
    ip::address addr = { 192, 1, 1, 11 };
    auto value = ip::to_uint32(addr);
    ASSERT_EQ(value, 3221291275);

    ip::address test_addr(value);

    for(auto i = 0; i < 4; i++)
    {
        EXPECT_EQ(addr[i], test_addr[i]);
    }
}