cmake_minimum_required(VERSION 2.8)

# clazzy
project(CLAZZY)

# get all source files
aux_source_directory(src SRCS)
# make sure clazzy.cpp is excluded (flex-generated)
list(REMOVE_ITEM SRCS src/clazzy.cpp)
# executable is still dependent upon all of them (including clazzy.cpp)
add_executable(clazzy src/clazzy.cpp ${SRCS})

# C++11
set(CMAKE_CXX_FLAGS -std=c++11)

# g++ options
if (CMAKE_COMPILER_IS_GNUCXX)
    set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused")
endif()

# flex
find_package(FLEX)

if (FLEX_FOUND)
    flex_target(ClazzyScanner src/clazzy.lex src/clazzy.cpp COMPILE_FLAGS -+)

    set(LIBRARIES ${LIBRARIES} ${FLEX_LIBRARIES})
endif()

# threading
find_package(Threads REQUIRED)
set(LIBRARIES ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# link everything together
target_link_libraries(clazzy ${LIBRARIES})

# provide make install option
install(TARGETS clazzy RUNTIME DESTINATION bin)

