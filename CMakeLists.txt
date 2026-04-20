cmake_minimum_required(VERSION 3.5)

project(b-zombie LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
link_libraries (SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories (/usr/include/SDL2)
add_executable(b-zombie main.cpp)

include(GNUInstallDirs)
install(TARGETS b-zombie
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
