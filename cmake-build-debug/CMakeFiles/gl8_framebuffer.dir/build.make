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
include CMakeFiles/gl8_framebuffer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gl8_framebuffer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gl8_framebuffer.dir/flags.make

CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj: CMakeFiles/gl8_framebuffer.dir/flags.make
CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj: CMakeFiles/gl8_framebuffer.dir/includes_CXX.rsp
CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj: ../src/gl8_framebuffer/gl8_framebuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gl8_framebuffer.dir\src\gl8_framebuffer\gl8_framebuffer.cpp.obj -c C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\gl8_framebuffer\gl8_framebuffer.cpp

CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\gl8_framebuffer\gl8_framebuffer.cpp > CMakeFiles\gl8_framebuffer.dir\src\gl8_framebuffer\gl8_framebuffer.cpp.i

CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\src\gl8_framebuffer\gl8_framebuffer.cpp -o CMakeFiles\gl8_framebuffer.dir\src\gl8_framebuffer\gl8_framebuffer.cpp.s

# Object files for target gl8_framebuffer
gl8_framebuffer_OBJECTS = \
"CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj"

# External object files for target gl8_framebuffer
gl8_framebuffer_EXTERNAL_OBJECTS =

gl8_framebuffer.exe: CMakeFiles/gl8_framebuffer.dir/src/gl8_framebuffer/gl8_framebuffer.cpp.obj
gl8_framebuffer.exe: CMakeFiles/gl8_framebuffer.dir/build.make
gl8_framebuffer.exe: libppgso.a
gl8_framebuffer.exe: libshaders.a
gl8_framebuffer.exe: ../dependencies/lib/mingw/libglfw3.a
gl8_framebuffer.exe: ../dependencies/lib/mingw/libglew32.a
gl8_framebuffer.exe: CMakeFiles/gl8_framebuffer.dir/linklibs.rsp
gl8_framebuffer.exe: CMakeFiles/gl8_framebuffer.dir/objects1.rsp
gl8_framebuffer.exe: CMakeFiles/gl8_framebuffer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gl8_framebuffer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gl8_framebuffer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gl8_framebuffer.dir/build: gl8_framebuffer.exe

.PHONY : CMakeFiles/gl8_framebuffer.dir/build

CMakeFiles/gl8_framebuffer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\gl8_framebuffer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/gl8_framebuffer.dir/clean

CMakeFiles/gl8_framebuffer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug C:\Users\juraj\Desktop\FIIT-JurajZ\5.Semester\PPGSO\ppgso-project\cmake-build-debug\CMakeFiles\gl8_framebuffer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gl8_framebuffer.dir/depend

