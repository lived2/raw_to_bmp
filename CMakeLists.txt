cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -W")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")
project (
    raw_to_bmp
    VERSION 0.1
    DESCRIPTION raw_to_bmp
    LANGUAGES CXX)
add_executable(raw_to_bmp
    main.cpp
    )
