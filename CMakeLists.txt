cmake_minimum_required(VERSION 3.0...3.2)

set(PROJECT_NAME codecrafter_api)
set(SOURCE_DIR src)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_GENERATOR_PLATFORM x64)

include_directories(X:/TGRKIT/builds/boost/include/boost-1_85)

set(BOOST_ROOT "X:/TGRKIT/builds/boost")
set(BOOST_INCLUDEDIR "X:/TGRKIT/builds/boost/include/boost-1_85")
find_package(Boost REQUIRED filesystem)

if(Boost_FOUND)
  include_directories(SYSTEM ${Boost_INCLUDE_DIR})
endif()

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
add_executable(parser ${SOURCE_DIR}/tools/parser/parser.cpp)

add_library(filesystem ${SOURCE_DIR}/tools/filesystem/filesystem.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE filesystem)
target_link_libraries(parser PRIVATE filesystem)

if(Boost_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
else()
  message("boost not found")
endif()