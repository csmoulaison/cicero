# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_SOURCE_DIR = /home/csmoulaison/repos/cicero/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/csmoulaison/repos/cicero/build

# Include any dependencies generated for this target.
include CMakeFiles/cicero.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cicero.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cicero.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cicero.dir/flags.make

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o: CMakeFiles/cicero.dir/flags.make
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o: /home/csmoulaison/repos/cicero/src/file.c
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o: CMakeFiles/cicero.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/csmoulaison/repos/cicero/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o -MF CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o.d -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o -c /home/csmoulaison/repos/cicero/src/file.c

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.i"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csmoulaison/repos/cicero/src/file.c > CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.i

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.s"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csmoulaison/repos/cicero/src/file.c -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.s

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o: CMakeFiles/cicero.dir/flags.make
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o: /home/csmoulaison/repos/cicero/src/lex.c
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o: CMakeFiles/cicero.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/csmoulaison/repos/cicero/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o -MF CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o.d -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o -c /home/csmoulaison/repos/cicero/src/lex.c

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.i"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csmoulaison/repos/cicero/src/lex.c > CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.i

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.s"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csmoulaison/repos/cicero/src/lex.c -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.s

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o: CMakeFiles/cicero.dir/flags.make
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o: /home/csmoulaison/repos/cicero/src/main.c
CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o: CMakeFiles/cicero.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/csmoulaison/repos/cicero/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o -MF CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o.d -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o -c /home/csmoulaison/repos/cicero/src/main.c

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.i"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csmoulaison/repos/cicero/src/main.c > CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.i

CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.s"
	/sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csmoulaison/repos/cicero/src/main.c -o CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.s

# Object files for target cicero
cicero_OBJECTS = \
"CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o" \
"CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o" \
"CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o"

# External object files for target cicero
cicero_EXTERNAL_OBJECTS =

/home/csmoulaison/repos/cicero/bin/cicero: CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/file.c.o
/home/csmoulaison/repos/cicero/bin/cicero: CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/lex.c.o
/home/csmoulaison/repos/cicero/bin/cicero: CMakeFiles/cicero.dir/home/csmoulaison/repos/cicero/src/main.c.o
/home/csmoulaison/repos/cicero/bin/cicero: CMakeFiles/cicero.dir/build.make
/home/csmoulaison/repos/cicero/bin/cicero: CMakeFiles/cicero.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/csmoulaison/repos/cicero/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable /home/csmoulaison/repos/cicero/bin/cicero"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cicero.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cicero.dir/build: /home/csmoulaison/repos/cicero/bin/cicero
.PHONY : CMakeFiles/cicero.dir/build

CMakeFiles/cicero.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cicero.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cicero.dir/clean

CMakeFiles/cicero.dir/depend:
	cd /home/csmoulaison/repos/cicero/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csmoulaison/repos/cicero/build /home/csmoulaison/repos/cicero/build /home/csmoulaison/repos/cicero/build /home/csmoulaison/repos/cicero/build /home/csmoulaison/repos/cicero/build/CMakeFiles/cicero.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cicero.dir/depend

