/* Mark Fitzgibbon
	Code for WPI CS4513 Project 1
	
	
*/
#include <stdio.h>
#include <stdlib.h>		/* for getenv() */

#include <sys/types.h>
#include <sys/stat.h>		/* for stat() */
#include <unistd.h>

char *getenv(const char *name);
char *getTrash(); //retrieve the trash directory as set by the environment

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

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Useage: rm <filename>\n");
	}
	else{
		//confirm file exists
		if(!access(argv[1], F_OK)){	//only checks if file exists (success on access() returns 0)
			char* bin = getTrash(); 	//Confirm TRASH variable is set, and place it in a string
			
			
		}
		else{
			perror("Given file does not exist or cannot be accessed.");
		}
	
		
	}

}