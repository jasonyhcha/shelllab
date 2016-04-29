//Cha, Yoon Ho: 32075491
//Wong, Brian: 34216498

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
	printf("A Simple Shell: Type 'quit' to exit.\n");

	char line[80];
	char* commands[50];        //command parameters for execvp
	int status = 0;

	while(strcmp(line,"quit")!=0){
		printf("prompt>");
		if (!fgets(line, 80, stdin)){  //so ctrld doest mess up the console
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

    //Check if run process in background
    int background = 0;
    int k = i-1;
    size_t amp = strlen(commands[k]);
    if(commands[k][amp-1] == '&'){
        commands[k][amp-1] = '\0';
        background = 1;
    }


    int job = 1;
    int pid= fork();              //fork child
    if(pid==0){               //Child
        if(strcmp(line,"quit")==0){
            kill(pid, SIGPIPE);
            break;
        }
        execvp(commands[0],commands);
        fprintf(stderr, "INVALID COMMAND\n");
    }
    else{
        if(background){
            printf("Performing processes in background\n");
            printf("[%d] %d\n",job, pid);
            job++;
        }
        else{
            waitpid(pid,NULL,0);
        }
    }
 }
 return 0;
}
