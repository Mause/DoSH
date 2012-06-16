cmake_minimum_required (VERSION 2.6)
project(DoSH)

# Define the location of the toolchain.
set(DCPUTOOLCHAIN ..)

# set verbosity
set( CMAKE_VERBOSE_MAKEFILE true )
set( CMAKE_VERBOSE true )
set( VERBOSE true )

# Include DCPU-16 Toolchain.
include(DCPUToolchain.cmake)

set(VERBOSE TRUE)

# Main version information.
set(VERSION_STAGE "alpha")
execute_process(COMMAND git rev-parse HEAD OUTPUT_VARIABLE git_hash)
if("${git_hash}" STREQUAL "")
	MESSAGE(STATUS "Huh")
else("${git_hash}" STREQUAL "")
	string(STRIP ${git_hash} git_hash)
	string(SUBSTRING ${git_hash} 0 9 git_hash)
	set(VERSION_GIT ${git_hash})
endif("${git_hash}" STREQUAL "")

# write a file with the GITVERSION define
file(WRITE src\\version.h "#define GITVERSION \"${git_hash}\"\n")


# Define DoSH.
add_dcpu_image(DoSH
	stdlib.dlib16
	src/builtins.c
	src/main.c
)

