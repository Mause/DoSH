"performs minimal edit to build.make"

import os

def check():
    """checks whether file needs to be edited,
	and if it does, edits it"""
    output_message = ''
    removed_data = {}
    if (os.path.exists('build/CMakeFiles/DoSH.dir/build.make') or
    	os.path.exists('CMakeFiles/DoSH.dir/build.make')):
        if os.path.exists('CMakeFiles/DoSH.dir/build.make'):
            fte = 'CMakeFiles/DoSH.dir/build.make'
    	else:
    	    fte = 'build/CMakeFiles/DoSH.dir/build.make'
        output_message = 'File edited...'
        filehandler = open(fte, 'r')
        data = filehandler.readlines()
        filehandler.close()
        filehandler = open(fte, 'w')
        line_number = 0
        for line in data:
            line_number += 1
            print line[:80]
            if '../src/main.o: ../dtcc' not in line:
                filehandler.write(line)
            else:
                removed_data[str(line_number)] = line
        filehandler.close()
    else:
        output_message = 'File could not be found, please run make'
		#os.system('cd build; make')
    print '#'*50
    for line in removed_data:
        print line, ':', removed_data[line]
    print '#'*50
    return output_message



if __name__ == '__main__':
    print check()