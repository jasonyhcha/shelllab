#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

int main(){
    printf("A Simple Shell: Type 'quit' to exit.\n");

    char line[80];
    char* commands[50];        //command parameters for execvp

    while(strcmp(line,"quit")!=0){
        printf("prompt>");
        if (!fgets(line, 80, stdin)){  //so ctrl+d doest mess up the console
            break;
        }

        size_t length = strlen(line);
        if (line[length - 1] == '\n'){   //remove new line
            line[length - 1] = '\0';
        }

        char *param;                  //split command into separate strings
        param = strtok(line," ");
        int i=0;
        while(param!=NULL){
            commands[i]=param;
            param = strtok(NULL," ");
            i++;
        }
        commands[i]=NULL;                     //set last value to NULL for execvp

        //char path[20] ="/bin/";
        //strcat(path,commands[0]);
        // size_t lengthp = strlen(path);
        // if (path[lengthp - 1] == '\n'){   //remove new line
        //     path[lengthp - 1] = '\0';
        // }
        // printf(path);
        int pid= fork();              //fork child
        if(pid==0){               //Child
            execvp(commands[0],commands);
            fprintf(stderr, "INVALID COMMAND\n");

        }
        wait(NULL);


        //printf(line);  //debugging
    }
    return 0;
}
