#include <iostream>

#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[]){

    if(argc == 1){
        cout << "wunzip: file1 [file2 ...]" << endl;
        return 1;
    }

    int fileDesc;

    int bytesRead;
    char buffer[5];
    char current;
    int count = 0;


    for (int i = 1; i < argc; i++){
        fileDesc = open(argv[i], O_RDONLY);

        if(fileDesc == -1){
            cout << "wzip: cannot open file" << endl;
            return 1;
        }

        while( (bytesRead = read(fileDesc, buffer, 5)) > 0){

            count = (int)buffer[0] + 256*(int)buffer[1] + 256*256*(int)buffer[2]+ 256*256*256*(int)buffer[3];
            current = buffer[4];
            for (int i = 0; i < count; i++){
                write(STDOUT_FILENO, &current, 1);
            }
            

        }

    }


    return 0;
}