cmake_minimum_required(VERSION 3.29)
project(theBidingOfOri)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        10.1.0
)

FetchContent_Makeavailable(fmt)


add_executable(main main.cpp
        engine.cpp
        engine.h)
target_link_libraries(main fmt::fmt)