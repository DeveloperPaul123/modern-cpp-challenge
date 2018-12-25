# modern-cpp-challenge
Code implementations for various C++ challenges as found in the book [The Modern C++ Challenge](https://www.packtpub.com/application-development/modern-c-challenge). The code is organized into folders that follow the various sections of the books. Each solutions will include a readme or a full write up on my [blog](https://developerpaul123.github.io). 

# Table of Contents
  - [Building the Code](#building-the-code)
  - [Challenges](#challenges)
    - [Language Features](#language-features)
      - [IPv4](#ipv4)


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
Full write up is availble on my [blog](https://developerpaul123.github.io/c++/modeling-an-ip-address-in-c++/).

#### 2D Array with Basic Operators
This challenge involved modeling a 2D array in C++ with support for:
* Element access (`at()` and `data()`)
* Capacity querying
* Iterators
* Filling
* Swapping
* Movable

````cpp

mcc::matrix<double, 3, 3> data;
std::iota(data.begin(), data.end(), 1.0);
/*
  data now looks like
  1.0, 2.0, 3.0,
  4.0, 5.0, 6.0,
  7.0, 8.0, 9.0
*/
````