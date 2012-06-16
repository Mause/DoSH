DoSH
====

This is an attempt at an extensible shell framework for the DCPU16 platform.
It is intended to be compiled under the [DCPUToolchain](http://github.com/DCPUTeam/DCPUToolchain).


#### Build Instructions;
You first require a copy of the DCPUToolchain; binaries can be downloaded from [here](http://DCPUToolcha.in)
Once you have extracted the files somewhere, you edit the DCPUTOOLCHAIN variable in the CMakeLists.txt to point to the location of the binaries/whereever you extracted the contents of the tarball.



#### TODO;
* implement scrolling :P
 		will most likely either require a buffer (array?)
		to store the information whilst it scrolls
 		will probably implement a function for this :smile:
* implement previous commands; rather than writing the read_in_command to NULL :P
		REM_COMMAND will store the constant that defines how many to remember
