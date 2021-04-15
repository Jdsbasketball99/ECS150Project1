#include <iostream>

#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[]){

    int fileDesc;

    // Iterate through all input files
    for (int i = 1; i < argc; i++){

        fileDesc = open(argv[i], O_RDONLY);

        //check for file opening error
        if(fileDesc == -1){
            cout << "wcat: cannot open file" << endl;
            return 1;
        }

        int bytesRead;
        char buffer[4096];

        //  Read from file using a buffer
        while( (bytesRead = read(fileDesc, buffer, 4096)) > 0){
            write(STDOUT_FILENO, buffer, bytesRead);
        }

        //close file
        if(fileDesc != -1){
            close(fileDesc);
        }
    }

    return 0;

}