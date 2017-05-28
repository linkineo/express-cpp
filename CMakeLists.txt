cmake_minimum_required(VERSION 2.8.0)

project(express-cpp)
enable_testing()

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)

set (VERSION_STRING_INSTALL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

if (NOT BUILD_SHARED_LIBRARIES) 
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif() 

find_package(Boost 1.59 REQUIRED COMPONENTS regex coroutine context thread filesystem system date_time)
find_package(Threads REQUIRED)

set(EXPRESS_HDR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SIMPLE_WEB_SERVER_HDR ${CMAKE_CURRENT_SOURCE_DIR}/Simple-Web-Server)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${EXPRESS_HDR})
include_directories(${SIMPLE_WEB_SERVER_HDR})


file(GLOB_RECURSE EXPRESS_SRC "src/*.cpp")
add_library(express-cpp ${EXPRESS_SRC})
set_target_properties(express-cpp PROPERTIES VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
target_link_libraries(express-cpp ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_executable(express-test test/main.cpp)
target_link_libraries(express-test express-cpp)

add_test(initial-test express-test)

#installing headers, libs and binaries
install(TARGETS express-cpp
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)

install(DIRECTORY ${EXPRESS_HDR}/ ${SIMPLE_WEB_SERVER_HDR}/ DESTINATION include/express
FILES_MATCHING PATTERN "*.hpp")

##cmake for cmake
include(CMakePackageConfigHelpers)
set(INCLUDE_INSTALL_DIR include/express)
set(LIB_INSTALL_DIR lib)
get_property(LIB_OUTPUT_NAME TARGET express-cpp PROPERTY LOCATION)
get_filename_component(LIB_OUTPUT_NAME ${LIB_OUTPUT_NAME} NAME)

configure_package_config_file(cmake/libexpressConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/libexpressConfig.cmake
INSTALL_DESTINATION ${LIB_INSTALL_DIR}/libexpress/cmake
PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR LIB_OUTPUT_NAME)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/libexpressConfigVersion.cmake
VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libexpressConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/libexpressConfigVersion.cmake
DESTINATION ${LIB_INSTALL_DIR}/cmake/libexpress-${VERSION_STRING_INSTALL})

