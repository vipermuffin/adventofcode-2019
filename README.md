# adventofcode-2019
Solutions to 2019 [Advent of Code] [1]

## Project Setup
This project builds on what I learned from the 2018 puzzles.  Basic structure is:

Folder  	| Description
-------		| ------------- 
DayXX    	| Contains solutions for the day    
Templates	| Submodule containing cmake templates used for generating the code for the day
Tools		| Submodule containing scripts used to automate generation of the days project files
lib			| Submodule containing libraries created for Advent of code.  Mostly used to parse input data

#### DayXX Details
File			| Description
----------------|------------------
CMakeLists.txt	| Main project file.  Setups to build a main project (**YYYY_AoC_VM_DayXX**) and a Unit Test Project (**runUnitTests**) which is built using googletest framework.  This comes from the CMakeLists.txt.in template.
CMakeVars.txt	| This contains a few variables used to customize the CMAkeLists.txt file (Day, Year, etc).  This is generated from the Download day python script.
DayXX.cxx		| This is the main file of interest.  This contains the code for the solutions.  The *day.cxx.in* template generates the skeleton for this file.
DayXX.h			| Header file for *DayXX.cxx*. Generated from *day.h.in* template. Mostly used to declare any function prototypes or classes that are also needed in the unit test project.
DayXX.md		| Puzzle text downloaded from [Advent of Code] [1]
DayXX.txt		| My specific puzzle input
DayXX_main.cxx	| Main runner for the solutions.  Prints out part 1 and 2 solutions for the day.
DayXX_tests.cxx	| Unit tests for the day. At a minimum I will have the answers for my specific input (most of the time).

#### Templates
This folder is brought in as a submodule and used to generate stub files for each day.  Details for the template files can be found at the [Templates] [2] project page.

#### Tools
This folder is brought in as a submodule.  The main script used is ```Generate2019Day.sh``` to generate the day's project.  I also run ```DownloadDay.py``` again after solving to get the second part of the puzzle text.  More details on the scripts can be found at the [Tools] [3] project page.

#### Library (lib)
This folder is brought in as a submodule. See the [Library] [4] project for details.

## Building a Solution
### Prerequisites
* CMake (>= 3.1)
* clang or g++

Tested using Mac OS X and XCode and Linux (Rasperian running on Raspberry Pi 3)

### Basic Command Line Build
This can be build using standard cmake build process.  For example, enter the day of interests folder, create a build directory and run cmake from that folder.

    > mkdir build
    > cd build
    > cmake .. && make
    > ./YYYY_AoC_VM_DayXX
    > ./runUnitTests
    
### Generating XCode project
Similar to a command line build, the cmake generator (-G) can be used to create a XCode project. One thing to note is that cmake will copy the input for the day into xcode_build, however, once XCode will require this to be in the Debug folder created after building.

    > mkdir xcode_build
    > cd xcode_build
    > cmake -G Xcode ..
    > xcodebuild -scheme ALL_BUILD build
    > cp DayXX.txt Debug/

 [1]: https://adventofcode.com/        "Advent of Code"
 [2]: https://github.com/vipermuffin/adventofcode-cmake-templates        "Templates"
 [3]: https://github.com/vipermuffin/adventofcode-tools        "Tools"
 [4]: https://github.com/vipermuffin/adventofcode-lib        "Library"