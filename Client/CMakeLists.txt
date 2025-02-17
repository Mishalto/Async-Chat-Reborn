cmake_minimum_required(VERSION 3.15)
project(Client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_ROOT "D:/Libs/boost_1_87_0")

add_executable(Client src/main.cpp)

target_include_directories(Client PRIVATE ${BOOST_ROOT})

target_include_directories(Client PRIVATE include)

target_compile_options(Client PRIVATE -Wall -Wextra -Werror)
