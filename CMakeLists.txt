cmake_minimum_required(VERSION 3.0)

project(OctreeColorQuantizer)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)

message("------------------------------------")
find_package(OpenCV 3.4 REQUIRED)
message(STATUS "Found OpenCV-Version ${OpenCV_VERSION}")
message(STATUS "OpenCV Include: ${OpenCV_INCLUDE_DIRS}")

add_subdirectory(src/impl)

add_executable(${PROJECT_NAME} src/sample.cpp)
target_link_libraries(${PROJECT_NAME} impl ${OpenCV_LIBS})
