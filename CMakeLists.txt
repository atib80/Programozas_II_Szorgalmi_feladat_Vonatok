cmake_minimum_required(VERSION 3.22)
set(this trains)
project(${this})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -Wpedantic -O3 -DNDEBUG")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(BOOST_ENABLE_CMAKE ON)

set(header_files
include/string_helper_functions.h
include/train.h
include/passenger_train.h
include/intercity.h
include/trainstation.h
)

set(src_files 
src/string_helper_functions.cpp
src/impl.cpp
src/train.cpp
src/passenger_train.cpp
src/intercity.cpp
src/trainstation.cpp
src/main.cpp
)

add_executable(${this} ${header_files} ${src_files})
target_include_directories(${this} PUBLIC include)

