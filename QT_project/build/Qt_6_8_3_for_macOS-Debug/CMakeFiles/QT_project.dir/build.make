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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sihwan/VEDA_QTproject/QT_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug

# Include any dependencies generated for this target.
include CMakeFiles/QT_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/QT_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/QT_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QT_project.dir/flags.make

QT_project_autogen/timestamp: /Users/sihwan/Qt/6.8.3/macos/libexec/moc
QT_project_autogen/timestamp: /Users/sihwan/Qt/6.8.3/macos/libexec/uic
QT_project_autogen/timestamp: CMakeFiles/QT_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target QT_project"
	/opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E cmake_autogen /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles/QT_project_autogen.dir/AutogenInfo.json Debug
	/opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E touch /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/QT_project_autogen/timestamp

CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o: CMakeFiles/QT_project.dir/flags.make
CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o: QT_project_autogen/mocs_compilation.cpp
CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o: CMakeFiles/QT_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o -MF CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o -c /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/QT_project_autogen/mocs_compilation.cpp

CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/QT_project_autogen/mocs_compilation.cpp > CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.i

CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/QT_project_autogen/mocs_compilation.cpp -o CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.s

CMakeFiles/QT_project.dir/main.cpp.o: CMakeFiles/QT_project.dir/flags.make
CMakeFiles/QT_project.dir/main.cpp.o: /Users/sihwan/VEDA_QTproject/QT_project/main.cpp
CMakeFiles/QT_project.dir/main.cpp.o: CMakeFiles/QT_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/QT_project.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QT_project.dir/main.cpp.o -MF CMakeFiles/QT_project.dir/main.cpp.o.d -o CMakeFiles/QT_project.dir/main.cpp.o -c /Users/sihwan/VEDA_QTproject/QT_project/main.cpp

CMakeFiles/QT_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QT_project.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sihwan/VEDA_QTproject/QT_project/main.cpp > CMakeFiles/QT_project.dir/main.cpp.i

CMakeFiles/QT_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QT_project.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sihwan/VEDA_QTproject/QT_project/main.cpp -o CMakeFiles/QT_project.dir/main.cpp.s

CMakeFiles/QT_project.dir/mainwindow.cpp.o: CMakeFiles/QT_project.dir/flags.make
CMakeFiles/QT_project.dir/mainwindow.cpp.o: /Users/sihwan/VEDA_QTproject/QT_project/mainwindow.cpp
CMakeFiles/QT_project.dir/mainwindow.cpp.o: CMakeFiles/QT_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/QT_project.dir/mainwindow.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QT_project.dir/mainwindow.cpp.o -MF CMakeFiles/QT_project.dir/mainwindow.cpp.o.d -o CMakeFiles/QT_project.dir/mainwindow.cpp.o -c /Users/sihwan/VEDA_QTproject/QT_project/mainwindow.cpp

CMakeFiles/QT_project.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QT_project.dir/mainwindow.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sihwan/VEDA_QTproject/QT_project/mainwindow.cpp > CMakeFiles/QT_project.dir/mainwindow.cpp.i

CMakeFiles/QT_project.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QT_project.dir/mainwindow.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sihwan/VEDA_QTproject/QT_project/mainwindow.cpp -o CMakeFiles/QT_project.dir/mainwindow.cpp.s

# Object files for target QT_project
QT_project_OBJECTS = \
"CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/QT_project.dir/main.cpp.o" \
"CMakeFiles/QT_project.dir/mainwindow.cpp.o"

# External object files for target QT_project
QT_project_EXTERNAL_OBJECTS =

QT_project.app/Contents/MacOS/QT_project: CMakeFiles/QT_project.dir/QT_project_autogen/mocs_compilation.cpp.o
QT_project.app/Contents/MacOS/QT_project: CMakeFiles/QT_project.dir/main.cpp.o
QT_project.app/Contents/MacOS/QT_project: CMakeFiles/QT_project.dir/mainwindow.cpp.o
QT_project.app/Contents/MacOS/QT_project: CMakeFiles/QT_project.dir/build.make
QT_project.app/Contents/MacOS/QT_project: /Users/sihwan/Qt/6.8.3/macos/lib/QtWidgets.framework/Versions/A/QtWidgets
QT_project.app/Contents/MacOS/QT_project: /Users/sihwan/Qt/6.8.3/macos/lib/QtGui.framework/Versions/A/QtGui
QT_project.app/Contents/MacOS/QT_project: /Users/sihwan/Qt/6.8.3/macos/lib/QtCore.framework/Versions/A/QtCore
QT_project.app/Contents/MacOS/QT_project: CMakeFiles/QT_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable QT_project.app/Contents/MacOS/QT_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QT_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QT_project.dir/build: QT_project.app/Contents/MacOS/QT_project
.PHONY : CMakeFiles/QT_project.dir/build

CMakeFiles/QT_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QT_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QT_project.dir/clean

CMakeFiles/QT_project.dir/depend: QT_project_autogen/timestamp
	cd /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sihwan/VEDA_QTproject/QT_project /Users/sihwan/VEDA_QTproject/QT_project /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug /Users/sihwan/VEDA_QTproject/QT_project/build/Qt_6_8_3_for_macOS-Debug/CMakeFiles/QT_project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/QT_project.dir/depend

