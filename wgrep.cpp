#include <iostream>

#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <string>


using namespace std;

int main(int argc, char *argv[]){

    int fileDesc;
    if (argc == 1){
        cout << "wgrep: searchterm [file ...]" << endl;
        return 1;
    }

    string searchTerm = argv[1];
    int i = 2;

    // Iterate through all input files
    do {
        
        if (argc == 2){
            fileDesc = STDIN_FILENO;
        }else
        {
            fileDesc = open(argv[i], O_RDONLY);
        }
        
        //check for file opening error
        if(fileDesc == -1){
            cout << "wgrep: cannot open file" << endl;
            return 1;
        }


        int bytesRead;
        char buffer;
        string line = "";
        int linecount = 0;

        //  Read from file using a buffer
        while( (bytesRead = read(fileDesc, &buffer, 1)) > 0){
            if( buffer != '\n'){
                line += buffer;
            }else{
                line += buffer;
                linecount ++;
                if (line.find(searchTerm) != string::npos){
                    char const* lineOut = line.c_str();
                    write(STDOUT_FILENO, lineOut, line.length());
                }
                line = "";
            }
        }

        //close file
        if(fileDesc != -1){
            close(fileDesc);
        }
        i++;
    }while (i < argc);

    return 0;

}












