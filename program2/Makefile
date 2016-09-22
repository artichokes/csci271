# Default target executed when no arguments are given to CXX.
default_target: all

.PHONY : default_target

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute CXX rules.
SHELL = /bin/sh

# The c++ compiler executable.
CXX = /usr/bin/g++ -std=c++0x -O3

# The command to remove a file.
RM_RF = rm -rf

MKDIR_P = mkdir -p

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

#=============================================================================
# Targets.

# The main all target
all: clean test
.PHONY : all

# The main clean target
clean:
	$(RM_RF) $(OBJ_FILES) obj/test.o obj test
.PHONY : clean

test: $(OBJ_FILES) obj/test.o
	$(CXX) -o test $^

obj/test.o: test.cpp
	$(MKDIR_P) obj
	$(CXX) -c -o $@ $<

obj/%.o: src/%.cpp
	$(MKDIR_P) obj
	$(CXX) -c -o $@ $<

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... test"
.PHONY : help

CC_FLAGS += -MMD
-include $(OBJFILES:.o=.d)
