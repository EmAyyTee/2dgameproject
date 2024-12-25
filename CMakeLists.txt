cmake_minimum_required(VERSION 3.29)
project(theBidingOfOri)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        10.1.0
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_Makeavailable(fmt SFML)


add_executable(main main.cpp
        MainWindow.cpp
        Engine.cpp
        Engine.h
        MainWindow.h
        Character.h
        Character.cpp
        Player.h
        Player.cpp
        Animation.h
        Animation.cpp
        TextureLoader.h
        TextureLoader.cpp
)
target_link_libraries(main
        fmt::fmt
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)
