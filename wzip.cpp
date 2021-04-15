#include <iostream>

#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

int main (int argc, char *argv[]){

    if (argc == 1){
        cout << "wzip: file1 [file2 ...]" << endl;
        return 1;
    }

    int fileDesc;

    int bytesRead;
    char buffer;
    char current;
    int count = 0;

    for (int i = 1; i < argc; i++){

        fileDesc = open(argv[i], O_RDONLY);

        if(fileDesc == -1){
            cout << "wzip: cannot open file" << endl;
            return 1;
        }
        
        
        while( (bytesRead = read(fileDesc, &buffer, 1)) > 0){

            if(count == 0){
                current = buffer;
                count ++;
            }else if(current == buffer){
                count ++;
            }else{
                write(STDOUT_FILENO, &count, 4);
                write(STDOUT_FILENO, &current, 1);
                count = 1;
                current = buffer;
            }

        }
        

    }
    write(STDOUT_FILENO, &count, 4);
    write(STDOUT_FILENO, &current, 1);



    return 0;
}










