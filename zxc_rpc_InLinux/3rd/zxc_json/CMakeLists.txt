cmake_minimum_required(VERSION 2.6)
project(zxc_json)

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
        -fno-omit-frame-pointer # linux perf
        # -Wall
        # -Wextra
        # -Werror
        # -Wconversion
        # -Wno-unused-parameter
        # -Wold-style-cast
        # -Woverloaded-virtual
        # -Wpointer-arith
        # -Wshadow
        # -Wwrite-strings
        -std=c++17
        -march=native
        -rdynamic)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message(STATUS "json project PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR}   PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR} CMAKE_BUILD_NO_EXAMPLES is ${CMAKE_BUILD_NO_EXAMPLES}  ")


# include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(zxc_json)

if(NOT CMAKE_BUILD_NO_EXAMPLES)
    add_subdirectory(example)
	message(STATUS " I'm in json first  ")
endif()

# if (CMAKE_BUILD_TESTS)
    # add_subdirectory(zxc_json/test)
	# message(STATUS " I'm in json second ")
# endif()

# if (CMAKE_BUILD_BENCHMARK)
    # add_subdirectory(zxc_json/bench)
	# message(STATUS " I'm in json third ")
# endif()

