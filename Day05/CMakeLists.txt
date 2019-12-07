#cmake 3.1 required for set_source_files_properties
cmake_minimum_required (VERSION 3.1)

#define variables and project name
include(CMakeVars.txt)
set (NAMESPACE "Aoc${DAY_PREFIX}")
set (INPUT_FILE_NAME "${DAY_PREFIX}.txt")
set (CONFIG_HEADER_NAME "${DAY_PREFIX}.h")
set (PROJECT_NAME "${YEAR}_AoC_VM_${DAY_PREFIX}")
set (CMAKE_CXX_STANDARD 11)
project (${PROJECT_NAME})
string(TIMESTAMP TODAY "%m/%d/%Y")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

#Create sources and add them to the project source list
configure_file(${INPUT_FILE_NAME} ${INPUT_FILE_NAME} COPYONLY) #copies into executable directory
include_directories("${PROJECT_SOURCE_DIR}/../lib/")
set (SOURCES "${DAY_PREFIX}_main.cxx" "${DAY_PREFIX}.cxx")
set (LIBRARY_SOURCES "${DAY_PREFIX}.cxx" "${PROJECT_SOURCE_DIR}/../lib/AoCUtils.cxx")
if(USEMD5)
    list(APPEND LIBRARY_SOURCES "${PROJECT_SOURCE_DIR}/../lib/md5.cpp")
endif()
add_library("${PROJECT_NAME}_lib" ${LIBRARY_SOURCES} )

#additional configuration for IDEs (XCode)
set(PROJ_RESOURCE_FILES	${INPUT_FILE_NAME})
set_source_files_properties(${INPUT_FILE_NAME} PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(${CONFIG_HEADER_NAME} PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("${PROJECT_SOURCE_DIR}/../lib/AoCUtils.h" PROPERTIES HEADER_FILE_ONLY TRUE)
list(APPEND SOURCES ${PROJ_RESOURCE_FILES} ${CONFIG_HEADER_NAME} "${PROJECT_SOURCE_DIR}/../lib/AoCUtils.h")
if(USEMD5)
    set_source_files_properties("${PROJECT_SOURCE_DIR}/../lib/md5.hpp" PROPERTIES HEADER_FILE_ONLY TRUE)
    list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/../lib/md5.hpp")
endif()

#Setup Executable
add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_lib" Threads::Threads)
set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE ${PROJ_RESOURCE_FILES})

#Setup Unit Testing
if (skip_test)
    #We apparently don't want unit tests so just go ahead a not make them
else (skip_test)
    set(TEST_PROJ_NAME "${PROJECT_NAME}_Tests")
	if (APPLE)
		add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
		add_definitions(-D__GLIBCXX__)
	endif (APPLE)

	# This adds another subdirectory, which has 'project(gtest)'.
	add_subdirectory("${PROJECT_SOURCE_DIR}/../lib/gtest" ./gtest)

	enable_testing()

	# Include the gtest library. gtest_SOURCE_DIR is available due to
	# 'project(gtest)' above.
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	##############
	# Unit Tests
	##############
	add_executable(runUnitTests "${DAY_PREFIX}_tests.cxx")

	# Standard linking to gtest stuff.
	target_link_libraries(runUnitTests gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(runUnitTests "${PROJECT_NAME}_lib")

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable runUnitTests to see those specific tests.
	add_test(NAME "${TEST_PROJ_NAME}" COMMAND runUnitTests)

	# You can also omit NAME and COMMAND. The second argument could be some other
	# test executable.
	#add_test(that-other-test-I-made runUnitTests)
endif()
