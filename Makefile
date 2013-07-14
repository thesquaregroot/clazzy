# The basic structure of this makefile should work in any UNIX environment.
# It should also work automatically with makedepend, should you be so inclined to use it.

# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -g -std=c++11 -Wall
LIBRARIES = -lpthread

# Creating a .o file
COMPILE_SRC = $(CXX) $(CXXFLAGS) -c
COMPILE_EXE = $(CXX) $(LIBRARIES)

# Name of the executable.
EXE = cranberry
SOURCE_DIR = src

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>.
#   In this case there isn't one.
all: generated_files Makefile $(EXE)

#
# Start by defining how to build any generated files...
#
GENERATED_FILES = src/lex.yy.cpp

generated_files : $(GENERATED_FILES)

src/lex.yy.cpp : src/cranberry.lex
	flex -+ -o src/lex.yy.cpp src/cranberry.lex

#
# Next, update this makefile to handle dependancies (requires makedepend)
#
Makefile : $(GENERATED_FILES) $(SRCS)
	makedepend -Y src/*.cpp 2>/dev/null

#
# Automatically find cpp files and associate them with object files
#
# NOTE: the shell command will not find generated files, 
#	hence having to make those object assosciations as well
#
SRCS = $(shell ls $(SOURCE_DIR)/*.cpp)
OBJS = $(GENERATED_FILES:.cpp=.o) $(SRCS:.cpp=.o)

#
# compile it all together
#

# An object file is dependent on the corresponding source file
# "$<" is the name of the first prerequisite.
# But there should only be one anyway.
#  This is mainly here for non gnu-make versions of make.
$(SOURCE_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(COMPILE_SRC) -o $@ $<

# The variable "$@" stands for the current target. "$^" is everything 
# it depends on.  In this case, the executable depends on all the object files.
$(EXE) : $(OBJS)
	$(COMPILE_EXE) $^ -o $@

# Get rid of all the signs of compilation.
clean:
	rm -rf $(EXE) $(SOURCE_DIR)/*.o Makefile.bak

# Below this: Stuff from makedepend. Or rules in a similar form as above.
# DO NOT DELETE

src/class_def.o: src/h/class_def.h src/h/function.h src/h/member.h
src/function.o: src/h/function.h
src/lang_cpp.o: src/h/lang_cpp.h src/h/language.h
src/lex.yy.o: src/h/token.h src/h/parser.h
src/member.o: src/h/member.h
src/parser.o: src/h/parser.h src/h/class_def.h src/h/function.h
src/parser.o: src/h/member.h src/h/token.h src/h/lang_cpp.h src/h/language.h
