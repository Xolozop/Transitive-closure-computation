# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maria/Documents/trans-clos/clean

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maria/Documents/trans-clos/clean

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maria/Documents/trans-clos/clean/CMakeFiles /home/maria/Documents/trans-clos/clean//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maria/Documents/trans-clos/clean/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named SCC

# Build rule for target.
SCC: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SCC
.PHONY : SCC

# fast build rule for target.
SCC/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/build
.PHONY : SCC/fast

algorithms/cr_tc.o: algorithms/cr_tc.cpp.o
.PHONY : algorithms/cr_tc.o

# target to build an object file
algorithms/cr_tc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/cr_tc.cpp.o
.PHONY : algorithms/cr_tc.cpp.o

algorithms/cr_tc.i: algorithms/cr_tc.cpp.i
.PHONY : algorithms/cr_tc.i

# target to preprocess a source file
algorithms/cr_tc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/cr_tc.cpp.i
.PHONY : algorithms/cr_tc.cpp.i

algorithms/cr_tc.s: algorithms/cr_tc.cpp.s
.PHONY : algorithms/cr_tc.s

# target to generate assembly for a file
algorithms/cr_tc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/cr_tc.cpp.s
.PHONY : algorithms/cr_tc.cpp.s

algorithms/ebert.o: algorithms/ebert.cpp.o
.PHONY : algorithms/ebert.o

# target to build an object file
algorithms/ebert.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/ebert.cpp.o
.PHONY : algorithms/ebert.cpp.o

algorithms/ebert.i: algorithms/ebert.cpp.i
.PHONY : algorithms/ebert.i

# target to preprocess a source file
algorithms/ebert.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/ebert.cpp.i
.PHONY : algorithms/ebert.cpp.i

algorithms/ebert.s: algorithms/ebert.cpp.s
.PHONY : algorithms/ebert.s

# target to generate assembly for a file
algorithms/ebert.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/ebert.cpp.s
.PHONY : algorithms/ebert.cpp.s

algorithms/schmitz.o: algorithms/schmitz.cpp.o
.PHONY : algorithms/schmitz.o

# target to build an object file
algorithms/schmitz.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/schmitz.cpp.o
.PHONY : algorithms/schmitz.cpp.o

algorithms/schmitz.i: algorithms/schmitz.cpp.i
.PHONY : algorithms/schmitz.i

# target to preprocess a source file
algorithms/schmitz.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/schmitz.cpp.i
.PHONY : algorithms/schmitz.cpp.i

algorithms/schmitz.s: algorithms/schmitz.cpp.s
.PHONY : algorithms/schmitz.s

# target to generate assembly for a file
algorithms/schmitz.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/schmitz.cpp.s
.PHONY : algorithms/schmitz.cpp.s

algorithms/stack_tc.o: algorithms/stack_tc.cpp.o
.PHONY : algorithms/stack_tc.o

# target to build an object file
algorithms/stack_tc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/stack_tc.cpp.o
.PHONY : algorithms/stack_tc.cpp.o

algorithms/stack_tc.i: algorithms/stack_tc.cpp.i
.PHONY : algorithms/stack_tc.i

# target to preprocess a source file
algorithms/stack_tc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/stack_tc.cpp.i
.PHONY : algorithms/stack_tc.cpp.i

algorithms/stack_tc.s: algorithms/stack_tc.cpp.s
.PHONY : algorithms/stack_tc.s

# target to generate assembly for a file
algorithms/stack_tc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/algorithms/stack_tc.cpp.s
.PHONY : algorithms/stack_tc.cpp.s

graph.o: graph.cpp.o
.PHONY : graph.o

# target to build an object file
graph.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/graph.cpp.o
.PHONY : graph.cpp.o

graph.i: graph.cpp.i
.PHONY : graph.i

# target to preprocess a source file
graph.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/graph.cpp.i
.PHONY : graph.cpp.i

graph.s: graph.cpp.s
.PHONY : graph.s

# target to generate assembly for a file
graph.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/graph.cpp.s
.PHONY : graph.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/main.cpp.s
.PHONY : main.cpp.s

representations/intervals.o: representations/intervals.cpp.o
.PHONY : representations/intervals.o

# target to build an object file
representations/intervals.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/intervals.cpp.o
.PHONY : representations/intervals.cpp.o

representations/intervals.i: representations/intervals.cpp.i
.PHONY : representations/intervals.i

# target to preprocess a source file
representations/intervals.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/intervals.cpp.i
.PHONY : representations/intervals.cpp.i

representations/intervals.s: representations/intervals.cpp.s
.PHONY : representations/intervals.s

# target to generate assembly for a file
representations/intervals.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/intervals.cpp.s
.PHONY : representations/intervals.cpp.s

representations/succ_list.o: representations/succ_list.cpp.o
.PHONY : representations/succ_list.o

# target to build an object file
representations/succ_list.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/succ_list.cpp.o
.PHONY : representations/succ_list.cpp.o

representations/succ_list.i: representations/succ_list.cpp.i
.PHONY : representations/succ_list.i

# target to preprocess a source file
representations/succ_list.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/succ_list.cpp.i
.PHONY : representations/succ_list.cpp.i

representations/succ_list.s: representations/succ_list.cpp.s
.PHONY : representations/succ_list.s

# target to generate assembly for a file
representations/succ_list.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/representations/succ_list.cpp.s
.PHONY : representations/succ_list.cpp.s

utils.o: utils.cpp.o
.PHONY : utils.o

# target to build an object file
utils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/utils.cpp.o
.PHONY : utils.cpp.o

utils.i: utils.cpp.i
.PHONY : utils.i

# target to preprocess a source file
utils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/utils.cpp.i
.PHONY : utils.cpp.i

utils.s: utils.cpp.s
.PHONY : utils.s

# target to generate assembly for a file
utils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SCC.dir/build.make CMakeFiles/SCC.dir/utils.cpp.s
.PHONY : utils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... SCC"
	@echo "... algorithms/cr_tc.o"
	@echo "... algorithms/cr_tc.i"
	@echo "... algorithms/cr_tc.s"
	@echo "... algorithms/ebert.o"
	@echo "... algorithms/ebert.i"
	@echo "... algorithms/ebert.s"
	@echo "... algorithms/schmitz.o"
	@echo "... algorithms/schmitz.i"
	@echo "... algorithms/schmitz.s"
	@echo "... algorithms/stack_tc.o"
	@echo "... algorithms/stack_tc.i"
	@echo "... algorithms/stack_tc.s"
	@echo "... graph.o"
	@echo "... graph.i"
	@echo "... graph.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... representations/intervals.o"
	@echo "... representations/intervals.i"
	@echo "... representations/intervals.s"
	@echo "... representations/succ_list.o"
	@echo "... representations/succ_list.i"
	@echo "... representations/succ_list.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

