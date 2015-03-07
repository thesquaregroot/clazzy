cmake_minimum_required(VERSION 2.8)

# clazzy
project(libclazzy)

# get all source files
set(SRC_DIR "${PROJECT_SOURCE_DIR}/libclazzy")
file(GLOB SRCS ${SRC_DIR}/*.cpp)
add_library(clazzy STATIC ${SRCS})

# C++11
set(CMAKE_CXX_FLAGS -std=c++11)

# g++ options
if (CMAKE_COMPILER_IS_GNUCXX)
    set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused")
endif()

