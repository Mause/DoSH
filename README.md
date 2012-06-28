DoSH
=======

This is an attempt at an extensible shell framework for the DCPU16 platform.
It is intended to be compiled under the [DCPUToolchain](http://github.com/DCPUTeam/DCPUToolchain).

### Build Instructions;
First of all, you require a copy of the DCPUToolchain; binaries can be downloaded from [the official website](http://DCPUToolcha.in). Once you have extracted the files somewhere, cd to the directory where you extracted the tarball's contents in the shell of your choice, and execute the following;
```shell
$ mkdir DoSH
$ cd DoSH
$ git clone https://github.com/Mause/DoSH .
```
You now have a copy of the DoSH source, which can be easily updated from the official site. However, before you can compile you must edit the DCPUTOOLCHAIN variable in the ```CMakeLists.txt``` file to point to the location of the binaries/whereever you extracted the contents of the tarball; if you followed the above instructions, you may leave it as is, as the script variable is pre-configured to point to the directory above the source code directory.

### TODO;
Refer to [issues](https://github.com/Mause/DoSH/issues)

### Support or Contact me
Send me an email at me@mause.me, i'll help you if i can

### Credits and thanks
Um, thanks to the guys at @DCPUTeam