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
include CMakeFiles/raw4_raster.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raw4_raster.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raw4_raster.dir/flags.make

CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj: CMakeFiles/raw4_raster.dir/flags.make
CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj: CMakeFiles/raw4_raster.dir/includes_CXX.rsp
CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj: ../src/raw4_raster/raw4_raster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\raw4_raster.dir\src\raw4_raster\raw4_raster.cpp.obj -c C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw4_raster\raw4_raster.cpp

CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw4_raster\raw4_raster.cpp > CMakeFiles\raw4_raster.dir\src\raw4_raster\raw4_raster.cpp.i

CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\raw4_raster\raw4_raster.cpp -o CMakeFiles\raw4_raster.dir\src\raw4_raster\raw4_raster.cpp.s

# Object files for target raw4_raster
raw4_raster_OBJECTS = \
"CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj"

# External object files for target raw4_raster
raw4_raster_EXTERNAL_OBJECTS =

raw4_raster.exe: CMakeFiles/raw4_raster.dir/src/raw4_raster/raw4_raster.cpp.obj
raw4_raster.exe: CMakeFiles/raw4_raster.dir/build.make
raw4_raster.exe: libppgso.a
raw4_raster.exe: ../dependencies/lib/mingw/libglfw3.a
raw4_raster.exe: ../dependencies/lib/mingw/libglew32.a
raw4_raster.exe: CMakeFiles/raw4_raster.dir/linklibs.rsp
raw4_raster.exe: CMakeFiles/raw4_raster.dir/objects1.rsp
raw4_raster.exe: CMakeFiles/raw4_raster.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raw4_raster.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raw4_raster.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raw4_raster.dir/build: raw4_raster.exe

.PHONY : CMakeFiles/raw4_raster.dir/build

CMakeFiles/raw4_raster.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\raw4_raster.dir\cmake_clean.cmake
.PHONY : CMakeFiles/raw4_raster.dir/clean

CMakeFiles/raw4_raster.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles\raw4_raster.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raw4_raster.dir/depend

