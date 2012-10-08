"performs minimal edit to build.make"
import os


def check(fte):
    output_message = ''
    removed_data = []
    fte = os.path.join(os.getcwd(), fte)
    if os.path.exists(fte):
        with open(fte, 'r') as filehandler:
            data = filehandler.readlines()

        with open(fte, 'w') as filehandler:
            for line in data:
                if ('../src/main.o: ../dtcc' not in line and
                    '../src/builtins.o: ../dtcc' not in line):
                    filehandler.write(line)
                else:
                    removed_data.append(line)
    if not removed_data:
        print 'Nothing was done'
    else:
        print 'Work was done'
    return output_message

if __name__ == '__main__':
    print check('build/CMakeFiles/DoSH.dir/build.make')
