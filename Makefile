
EXE = clazzy
SOURCE_DIR = src
OBJECT_DIR = obj
GENERATED_FILES = $(SOURCE_DIR)/lex.yy.cpp
BUILD_FILE = Makefile.build
DEPEND_FILE = Makefile.depend

#
# Next, update this makefile to handle dependancies (requires makedepend)
#  This updates the makefile itself
#
.PHONY : generated_files
.PHONY : makefiles
all : generated_files makefiles $(EXE)

install : $(EXE)
	install clazzy /usr/bin/

generated_files : $(GENERATED_FILES)
makefiles : Makefile $(BUILD_FILE) $(DEPEND_FILE)

#
# Start by defining how to build any generated files...
#
$(SOURCE_DIR)/lex.yy.cpp : $(SOURCE_DIR)/$(EXE).lex
	flex -+ -o $(SOURCE_DIR)/lex.yy.cpp $(SOURCE_DIR)/$(EXE).lex

SRCS = $(shell ls $(SOURCE_DIR)/*.cpp)
HEADERS = $(shell ls $(SOURCE_DIR)/h/*.h)

$(DEPEND_FILE) : $(GENERATED_FILES) $(SRCS) $(HEADERS)
	makedepend -Y -f- $(SOURCE_DIR)/*.cpp 2>/dev/null | sed 's/$(SOURCE_DIR)\//$(OBJECT_DIR)\//' > $(DEPEND_FILE)

$(EXE) : $(SRCS) $(HEADERS)
	make -f $(BUILD_FILE)

# Get rid of all the signs of compilation.
clean:
	find . -name "clazzy_*" -type d -prune -exec rm -rf "{}" \;
	rm -rf $(EXE) $(OBJECT_DIR)/*.o Makefile.bak Makefile.depend

