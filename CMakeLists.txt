cmake_minimum_required (VERSION 2.6)
project(DoSH)

# Define the location of the toolchain.
set(DCPUTOOLCHAIN ..)

# Include DCPU-16 Toolchain.
include(DCPUToolchain.cmake)

# Define AtlasOS.
add_dcpu_image(DoSH
	src/builtins.c
	src/main.c
)

