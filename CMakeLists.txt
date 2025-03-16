cmake_minimum_required(VERSION 3.16)

project(ipfilter_hw2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ipfilter_hw2 main.cpp)

include(GNUInstallDirs)

install(TARGETS ipfilter_hw2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
