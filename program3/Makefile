# Default target executed when no arguments are given to CXX.
default_target: all

.PHONY : default_target

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute CXX rules.
SHELL = /bin/sh

# The c++ compiler executable.
CXX = g++ -std=c++0x -O3

# The command to remove a file.
RM_RF = rm -rf

MKDIR_P = mkdir -p

#=============================================================================
# Targets.

# The main all target
all: clean main
.PHONY : all

# The main clean target
clean:
	$(RM_RF) obj/BST.o obj/main.o obj main
.PHONY : clean

main: $(OBJ_FILES) obj/main.o
	$(CXX) -o main $^

obj/main.o: obj/BST.o main.cpp
	$(MKDIR_P) obj
	$(CXX) -c -o obj/main.o main.cpp

obj/BST.o: BST.h
	$(MKDIR_P) obj
	$(CXX) -c -o $@ $<

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... main"
.PHONY : help

CC_FLAGS += -MMD
