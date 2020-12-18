cmake_minimum_required(VERSION 3.15)
project(sdl_a_star)

set(CMAKE_CXX_STANDARD 14)

include_directories(header)
include_directories(src)

add_executable(sdl_a_star
        header/app.hpp
        header/loader.hpp
        header/converter.hpp
        header/rectangle.hpp
        header/star.hpp
        src/app.cpp
        src/loader.cpp
        src/converter.cpp
        src/star.cpp
        main.cpp)

find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
