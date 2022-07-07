cmake_minimum_required(VERSION 3.23)

project(cpp_python_experiment)

find_package(PythonLibs REQUIRED)
find_package(Python3 COMPONENTS Interpreter NumPy REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(cpp_python_experiment test_cpp_python.cpp)

target_link_libraries(cpp_python_experiment ${PYTHON_LIBRARIES} Python3::NumPy)
