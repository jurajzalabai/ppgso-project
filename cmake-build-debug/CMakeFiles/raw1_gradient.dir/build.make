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
include CMakeFiles/raw1_gradient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raw1_gradient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raw1_gradient.dir/flags.make

CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj: CMakeFiles/raw1_gradient.dir/flags.make
CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj: CMakeFiles/raw1_gradient.dir/includes_CXX.rsp
CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj: ../src/raw1_gradient/raw1_gradient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\raw1_gradient.dir\src\raw1_gradient\raw1_gradient.cpp.obj -c C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw1_gradient\raw1_gradient.cpp

CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw1_gradient\raw1_gradient.cpp > CMakeFiles\raw1_gradient.dir\src\raw1_gradient\raw1_gradient.cpp.i

CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw1_gradient\raw1_gradient.cpp -o CMakeFiles\raw1_gradient.dir\src\raw1_gradient\raw1_gradient.cpp.s

# Object files for target raw1_gradient
raw1_gradient_OBJECTS = \
"CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj"

# External object files for target raw1_gradient
raw1_gradient_EXTERNAL_OBJECTS =

raw1_gradient.exe: CMakeFiles/raw1_gradient.dir/src/raw1_gradient/raw1_gradient.cpp.obj
raw1_gradient.exe: CMakeFiles/raw1_gradient.dir/build.make
raw1_gradient.exe: libppgso.a
raw1_gradient.exe: ../dependencies/lib/mingw/libglfw3.a
raw1_gradient.exe: ../dependencies/lib/mingw/libglew32.a
raw1_gradient.exe: CMakeFiles/raw1_gradient.dir/linklibs.rsp
raw1_gradient.exe: CMakeFiles/raw1_gradient.dir/objects1.rsp
raw1_gradient.exe: CMakeFiles/raw1_gradient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raw1_gradient.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raw1_gradient.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raw1_gradient.dir/build: raw1_gradient.exe

.PHONY : CMakeFiles/raw1_gradient.dir/build

CMakeFiles/raw1_gradient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\raw1_gradient.dir\cmake_clean.cmake
.PHONY : CMakeFiles/raw1_gradient.dir/clean

CMakeFiles/raw1_gradient.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles\raw1_gradient.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raw1_gradient.dir/depend

