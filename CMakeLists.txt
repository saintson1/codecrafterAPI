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

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(X:/TGRKIT/builds/boost/include/boost-1_85)

set(BOOST_ROOT "X:/TGRKIT/builds/boost")
set(BOOST_INCLUDEDIR "X:/TGRKIT/builds/boost/include/boost-1_85")
find_package(Boost REQUIRED filesystem)

if(Boost_FOUND)
  include_directories(SYSTEM ${Boost_INCLUDE_DIR})
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCE_DIR}/codecrafter/codecrafter.cpp ${SOURCE_DIR}/tools/filesystem/filesystem.cpp)

add_executable(main ${SOURCE_DIR}/main.cpp)

if(Boost_FOUND)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
else()
  message("boost not found")
endif()

target_link_libraries(main PUBLIC ${PROJECT_NAME})