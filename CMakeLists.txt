# clazzy

project(CLAZZY)

aux_source_directory(src SRCS)
add_executable(clazzy src/clazzy.cpp ${SRCS})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11") # -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")
endif()

# flex
find_package(FLEX)

if (FLEX_FOUND)
    FLEX_TARGET(ClazzyScanner src/clazzy.lex src/clazzy.cpp COMPILE_FLAGS -+)

    set(LIBRARIES ${LIBRARIES} ${FLEX_LIBRARIES})
endif()

# threading
find_package(Threads REQUIRED)
set(LIBRARIES ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(clazzy ${LIBRARIES})

install(TARGETS clazzy RUNTIME DESTINATION bin)

