cmake_minimum_required(VERSION 3.0.0)

project(express-cpp)
set(CMAKE_BUILD_TYPE Debug)
enable_testing()

add_definitions(--std=c++11)



set(BOOST_ALL_DYN_LINK ON)
set(BOOST_USE_STATIC_LIB OFF)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.59 REQUIRED COMPONENTS system thread coroutine context filesystem)
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
