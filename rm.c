/* Mark Fitzgibbon
	Code for WPI CS4513 Project 1
	
	
*/
#include <stdio.h>
#include <stdlib.h>		/* for getenv() */

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
	printf("%s=%s\n", "TRASH", getTrash());
}