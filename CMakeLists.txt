cmake_minimum_required(VERSION 2.8)

project(P005_RCM)


if(${CMAKE_BUILD_TYPE} MATCHES "Release" OR
        ${CMAKE_BUILD_TYPE} MATCHES "MinSizeRe")
    set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -s")
endif(${CMAKE_BUILD_TYPE} MATCHES "Release" OR
    ${CMAKE_BUILD_TYPE} MATCHES "MinSizeRe")

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
add_library(addition STATIC
    "listener.cpp"
    "performer.cpp"
    "sender.cpp"
    "initialization.cpp"
    "addition.h")
add_library(mySTL STATIC "mySTL.cpp" "mySTL.h")
add_executable(main main.cpp )
target_link_libraries(main addition mySTL ws2_32)
