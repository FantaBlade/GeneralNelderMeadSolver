cmake_minimum_required(VERSION 2.8.0)
set(GNMS general_nelder_mead_solver)
PROJECT (${GNMS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#加入依赖库
add_subdirectory(external)

set(SOURCE_FILES src/main.cpp src/neldermead/neldermead.h test/neldermead.cpp )
add_executable(${GNMS} ${SOURCE_FILES})

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${GNMS} gtest)