cmake_minimum_required(VERSION 3.22)

project(dsu_seg_backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -fsized-deallocation)

find_package(PythonLibs REQUIRED)
find_package(Boost COMPONENTS python COMPONENTS numpy3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(dsu_seg_backend SHARED lib/dsu_seg.cpp lib/include/dsu_seg_impl.cpp lib/include/impl/data_view.cpp lib/include/impl/pixel_view.cpp lib/include/impl/segment.cpp)
add_subdirectory(lib/include/DSUWithData/lib)

set_target_properties(dsu_seg_backend PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(dsu_seg_backend ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} DSUWithData)
