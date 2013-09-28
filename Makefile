# The basic structure of this makefile should work in any UNIX environment.
# It should also work automatically with makedepend, should you be so inclined to use it.

# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -std=c++11
LIBRARIES = -lpthread

# Creating a .o file
COMPILE_SRC = $(CXX) $(CXXFLAGS) -c
COMPILE_EXE = $(CXX) $(LIBRARIES)

# Name of the executable.
EXE = clazzy
SOURCE_DIR = src
OBJECT_DIR = obj
DEPEND_FILE = Makefile.depend

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>.
#   In this case there isn't one.
.PHONY : generated_files

all: generated_files $(DEPEND_FILE) $(OBJECT_DIR) $(EXE)

$(OBJECT_DIR) : 
	mkdir -p $(OBJECT_DIR)

#
# Start by defining how to build any generated files...
#
GENERATED_FILES = src/lex.yy.cpp

generated_files : $(GENERATED_FILES)

src/lex.yy.cpp : src/$(EXE).lex
	flex -+ -o src/lex.yy.cpp src/$(EXE).lex

#
# Automatically find cpp files and associate them with object files
#
# NOTE: the shell command will not find generated files, 
#	hence having to make those object assosciations as well
#
SRCS = $(shell ls $(SOURCE_DIR)/*.cpp)
OBJS = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o, $(GENERATED_FILES) $(SRCS))
HEADERS = $(shell ls $(SOURCE_DIR)/h/*.h)

#
# Next, update this makefile to handle dependancies (requires makedepend)
#  This updates the makefile itself
#
-include $(DEPEND_FILE)
$(DEPEND_FILE) : Makefile $(GENERATED_FILES) $(SRCS) $(HEADERS)
	makedepend -Y -f- $(SOURCE_DIR)/*.cpp 2>/dev/null | sed 's/src\//obj\//' > $(DEPEND_FILE)

#
# compile it all together
#

# An object file is dependent on the corresponding source file
# "$<" is the name of the first prerequisite.
# But there should only be one anyway.
#  This is mainly here for non gnu-make versions of make.
$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(COMPILE_SRC) -o $@ $<

# The variable "$@" stands for the current target. "$^" is everything 
# it depends on.  In this case, the executable depends on all the object files.
$(EXE) : $(OBJS)
	$(COMPILE_EXE) $^ -o $@

# Get rid of all the signs of compilation.
clean:
	find . -name "clazzy_*" -type d -prune -exec rm -rf "{}" \;
	rm -rf $(EXE) $(OBJECT_DIR)/*.o Makefile.bak Makefile.depend
