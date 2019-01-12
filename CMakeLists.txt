cmake_minimum_required(VERSION 2.8)

project(P005_RCM)


if(${CMAKE_BUILD_TYPE} MATCHES "Release" OR
        ${CMAKE_BUILD_TYPE} MATCHES "MinSizeRe")
    set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -s ")
endif(${CMAKE_BUILD_TYPE} MATCHES "Release" OR
    ${CMAKE_BUILD_TYPE} MATCHES "MinSizeRe")
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

add_executable(main
    "main.cpp"
    "listener.cpp"
    "listener.h"
    "performer.cpp"
    "performer.h"
    "sender.cpp"
    "sender.h"
    "initialization.cpp"
    "initialization.h"
    "addition.h"
    "mySTL.cpp"
    "mySTL.h")
target_link_libraries(main ws2_32)
