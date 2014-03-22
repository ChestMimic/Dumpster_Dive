/* Mark Fitzgibbon
	Code for WPI CS4513 Project 1
	
	
*/
#include <stdio.h>
#include <string.h> //strcpy
#include <stdlib.h>		
#include <sys/types.h>
#include <sys/stat.h>		
#include <unistd.h>
#include <libgen.h> //Basename & dirname

char *getTrash(); //retrieve the trash directory as set by the environment
char *getTrashWithTarget(char* dir, char* file);

char *getTrash(){
	extern char **environ;	/* externally declared */
	char *match;			
	
	match = getenv("TRASH");
	if (!match){
		printf("No match for '%s' in environment, make sure it is set\n", "TRASH");
		exit(1);
	}
	else{
		
		return match;
	}
}

char *getTrashWithTarget(char* dir, char* file){
	//create full destination directory from filename appended to trash directory (dir)
	char* direct = basename(file);
	char* loc = (char*)malloc(512);
	strcat(loc, dir);
	strcat(loc, "/");
	strcat(loc, direct);
	return loc;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Useage: rm <filename>\n");
	}
	else{
		//confirm file exists
		if(!access(argv[1], F_OK)){	//only checks if file exists (success on access() returns 0)
			char* bin = getTrash(); 	//Confirm TRASH variable is set, and place it in a string
			if(!access(bin, F_OK)){		//Confirm TRASH variable doesn't point to junk
				char* dest = getTrashWithTarget(bin, argv[1]);
				link(argv[1], dest);
				unlink(argv[1]);
			}
			else{
				perror("TRASH variable directory does not exist");
				exit(1);
			}
			
		}
		else{
			perror("Given file does not exist or cannot be accessed.");
			exit(1);
		}
	
		
	}

}