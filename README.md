DoSH
=======

This is an attempt at an extensible shell framework for the DCPU16 platform.
It is intended to be compiled under the [DCPUToolchain](http://DCPUToolcha.in).

### Build Instructions;
First of all, you require a copy of the DCPUToolchain; binaries for linux or windows can be downloaded from [the official website](http://DCPUToolcha.in). If you require a Mac OS X version, unless things have changed since i wrote this, you will have to compile the toolchain from scratch. Once you have extracted the files somewhere, cd to the directory where you extracted the tarball's contents in the shell of your choice, and execute the following;
```shell
$ mkdir DoSH
$ cd DoSH
$ git clone https://github.com/Mause/DoSH .
```
You now have a copy of the DoSH source, which can be easily updated from the [GitHub repo](https://github.com/Mause/DoSH). However, before you can compile, some alterations must be made to the ```CMakeLists.txt``` file. Because cmake cannot easily guess where the DCPUToolchain is located, you must edit the DCPUTOOLCHAIN variable in the ```CMakeLists.txt``` file to point to the location of the binaries/whereever you extracted the contents of the binary tarball. If you followed the above instructions, you may leave it as is, as the cmake variable is pre-configured to point to the directory above the source code directory.

Etc, etc...

![End product](http://new.tinygrab.com/2ec775809c632d5c60b68f25f9c0d28ef972474461.png)

### TODO;
Refer to [issues](https://github.com/Mause/DoSH/issues)

### Support or Contact me
Send me an email at [me@mause.me](mailto:me@mause.me), i'll help you if i can

### Credits and thanks
Um, thanks to the guys at @DCPUTeam for the creating the [toolchain](http://dcputoolcha.in) in the first place, and thanks to the team at @Lysdev for supporting me in my endeavours :)
