# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/playground.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/playground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playground.dir/flags.make

CMakeFiles/playground.dir/src/playground/playground.cpp.obj: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/src/playground/playground.cpp.obj: CMakeFiles/playground.dir/includes_CXX.rsp
CMakeFiles/playground.dir/src/playground/playground.cpp.obj: ../src/playground/playground.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/playground.dir/src/playground/playground.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\playground.dir\src\playground\playground.cpp.obj -c C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\playground\playground.cpp

CMakeFiles/playground.dir/src/playground/playground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playground.dir/src/playground/playground.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\playground\playground.cpp > CMakeFiles\playground.dir\src\playground\playground.cpp.i

CMakeFiles/playground.dir/src/playground/playground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playground.dir/src/playground/playground.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\playground\playground.cpp -o CMakeFiles\playground.dir\src\playground\playground.cpp.s

# Object files for target playground
playground_OBJECTS = \
"CMakeFiles/playground.dir/src/playground/playground.cpp.obj"

# External object files for target playground
playground_EXTERNAL_OBJECTS =

playground.exe: CMakeFiles/playground.dir/src/playground/playground.cpp.obj
playground.exe: CMakeFiles/playground.dir/build.make
playground.exe: libppgso.a
playground.exe: libshaders.a
playground.exe: ../dependencies/lib/mingw/libglfw3.a
playground.exe: ../dependencies/lib/mingw/libglew32.a
playground.exe: CMakeFiles/playground.dir/linklibs.rsp
playground.exe: CMakeFiles/playground.dir/objects1.rsp
playground.exe: CMakeFiles/playground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable playground.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\playground.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playground.dir/build: playground.exe

.PHONY : CMakeFiles/playground.dir/build

CMakeFiles/playground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\playground.dir\cmake_clean.cmake
.PHONY : CMakeFiles/playground.dir/clean

CMakeFiles/playground.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles\playground.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/playground.dir/depend
