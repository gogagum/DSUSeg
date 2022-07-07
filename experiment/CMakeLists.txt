cmake_minimum_required(VERSION 3.22)

project(cpp_python_test_lib VERSION 0.0.1 DESCRIPTION "Demo c++ library.")

find_package(PythonLibs REQUIRED)
find_package(Boost COMPONENTS python COMPONENTS numpy3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(cpp_python_test_lib SHARED test_cpp_functions.cpp)
set_target_properties(cpp_python_test_lib PROPERTIES VERSION ${PROJECT_VERSION} POSITION_INDEPENDENT_CODE ON)

target_link_libraries(cpp_python_test_lib ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )