cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ipfilter LANGUAGES CXX VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GTEST_TEST "Whether to build GTest test" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

add_library(${PROJECT_NAME}_lib verify_lib.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_lib
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    add_executable(${PROJECT_NAME}_test1 test1_verify.cpp)

    set_target_properties(${PROJECT_NAME}_test1 PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(${PROJECT_NAME}_test1
        ${Boost_LIBRARIES}
        ${PROJECT_NAME}_lib
    )
endif()

install(TARGETS ${PROJECT_NAME}
    # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(${PROJECT_NAME}_test1 ${PROJECT_NAME}_test1)
endif()
