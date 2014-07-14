cmake_minimum_required(VERSION 2.8)

# clazzy
project(clazzy)

# get all source files
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB SRCS ${SRC_DIR}/*.cpp)
add_executable(clazzy ${SRC_DIR}/clazzy.cpp ${SRCS})

# flex
find_package(FLEX REQUIRED)
set(LIBRARIES ${LIBRARIES} ${FLEX_LIBRARIES})
flex_target(ClazzyScanner ${SRC_DIR}/clazzy.lex ${SRC_DIR}/clazzy.cpp COMPILE_FLAGS -+)

# threading
find_package(Threads REQUIRED)
set(LIBRARIES ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# C++11
set(CMAKE_CXX_FLAGS -std=c++11)

# g++ options
if (CMAKE_COMPILER_IS_GNUCXX)
    # set options for everything but clazzy.cpp (flex-generated)
    list(REMOVE_ITEM SRCS ${SRC_DIR}/clazzy.cpp)
    set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused")
endif()

# link everything together
target_link_libraries(clazzy ${LIBRARIES})

# provide make install option
install(TARGETS clazzy RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/man/ DESTINATION man)

