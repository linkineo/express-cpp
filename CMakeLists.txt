cmake_minimum_required(VERSION 2.8.0)

project(express-cpp)
set(CMAKE_BUILD_TYPE Debug)
enable_testing()

add_definitions(--std=c++11)

find_package(Boost 1.59 REQUIRED COMPONENTS system thread coroutine context filesystem regex)
find_package(Threads REQUIRED)

include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Simple-Web-Server)


file(GLOB_RECURSE EXPRESS_SRC "src/*.cpp")
add_library(express-cpp SHARED ${EXPRESS_SRC})
target_link_libraries(express-cpp ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(express-test test/main.cpp)
target_link_libraries(express-test express-cpp)

add_test(initial-test express-test)
