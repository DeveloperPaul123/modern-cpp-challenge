# modern-cpp-challenge
Code implementations for various C++ challenges as found in the book [The Modern C++ Challenge](https://www.packtpub.com/application-development/modern-c-challenge). The code is organized into folders that follow the various sections of the books. Each solutions will include a readme or a full write up on my [blog](https://developerpaul123.github.io). 

## Building the Code
The code in this repository requires:
* C++17 compliant compiler
* CMake

Optionally, you can also build unit tests for most of the code. If you turn this option on, you will also need:
* GTest

Simply configure and build with CMake. No other external dependencies are needed. 

## Challenges

### Language Features

#### IPv4
This challenge involved modeling an IPv4 address in C++. The specific requirements were:
* Be able to read an address from a string like:
````
ip::address addr = ip::from_string("127.0.0.1");
````
* Be able to write an address to a string.
* Be able to enumerate a range of addresses; for example:
````
ip::address start = {0,0,0,0};
ip::address end = {255, 255, 255, 255};

while(start < end)
{
  start++;
  std::cout << start << std::endl;
}
````
