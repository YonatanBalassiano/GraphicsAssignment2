# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug

# Include any dependencies generated for this target.
include res/includes/glfw/tests/CMakeFiles/events.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include res/includes/glfw/tests/CMakeFiles/events.dir/compiler_depend.make

# Include the progress variables for this target.
include res/includes/glfw/tests/CMakeFiles/events.dir/progress.make

# Include the compile flags for this target's objects.
include res/includes/glfw/tests/CMakeFiles/events.dir/flags.make

res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/flags.make
res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o: /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/tests/events.c
res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o -MF CMakeFiles/events.dir/events.c.o.d -o CMakeFiles/events.dir/events.c.o -c /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/tests/events.c

res/includes/glfw/tests/CMakeFiles/events.dir/events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/events.dir/events.c.i"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/tests/events.c > CMakeFiles/events.dir/events.c.i

res/includes/glfw/tests/CMakeFiles/events.dir/events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/events.dir/events.c.s"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/tests/events.c -o CMakeFiles/events.dir/events.c.s

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/flags.make
res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/getopt.c
res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o -MF CMakeFiles/events.dir/__/deps/getopt.c.o.d -o CMakeFiles/events.dir/__/deps/getopt.c.o -c /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/getopt.c

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/getopt.c.i"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/getopt.c > CMakeFiles/events.dir/__/deps/getopt.c.i

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/getopt.c.s"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/getopt.c -o CMakeFiles/events.dir/__/deps/getopt.c.s

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/flags.make
res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/glad_gl.c
res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: res/includes/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o -MF CMakeFiles/events.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/events.dir/__/deps/glad_gl.c.o -c /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/glad_gl.c

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/glad_gl.c.i"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/glad_gl.c > CMakeFiles/events.dir/__/deps/glad_gl.c.i

res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/glad_gl.c.s"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/deps/glad_gl.c -o CMakeFiles/events.dir/__/deps/glad_gl.c.s

# Object files for target events
events_OBJECTS = \
"CMakeFiles/events.dir/events.c.o" \
"CMakeFiles/events.dir/__/deps/getopt.c.o" \
"CMakeFiles/events.dir/__/deps/glad_gl.c.o"

# External object files for target events
events_EXTERNAL_OBJECTS =

res/includes/glfw/tests/events: res/includes/glfw/tests/CMakeFiles/events.dir/events.c.o
res/includes/glfw/tests/events: res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o
res/includes/glfw/tests/events: res/includes/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o
res/includes/glfw/tests/events: res/includes/glfw/tests/CMakeFiles/events.dir/build.make
res/includes/glfw/tests/events: res/includes/glfw/src/libglfw3.a
res/includes/glfw/tests/events: res/includes/glfw/tests/CMakeFiles/events.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable events"
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/events.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
res/includes/glfw/tests/CMakeFiles/events.dir/build: res/includes/glfw/tests/events
.PHONY : res/includes/glfw/tests/CMakeFiles/events.dir/build

res/includes/glfw/tests/CMakeFiles/events.dir/clean:
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/events.dir/cmake_clean.cmake
.PHONY : res/includes/glfw/tests/CMakeFiles/events.dir/clean

res/includes/glfw/tests/CMakeFiles/events.dir/depend:
	cd /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2 /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/res/includes/glfw/tests /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests /Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/cmake-build-debug/res/includes/glfw/tests/CMakeFiles/events.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : res/includes/glfw/tests/CMakeFiles/events.dir/depend

