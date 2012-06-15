DoSH
====

This is an attempt at an extensible shell framework for the DCPU16 platform.
It is intended to be compiled under the [DCPUToolchain](http://github.com/DCPUTeam/DCPUToolchain).

HINT: to compile, compile the dosh.c file. Everything else is included into that one file

TODO:
* implement scrolling :P
 		will most likely either require a buffer (array?)
		to store the information whilst it scrolls
 		will probably implement a function for this :smile:
* implement previous commands; rather than writing the read_in_command to NULL :P
		REM_COMMAND will store the constant that defines how many to remember
