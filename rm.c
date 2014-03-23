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
#include <utime.h>		



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
	//look for matching trashed files
	int i = 0;
	
	while(!access(loc, F_OK)){
		if(i != 0){
			char* appended = (char*) malloc(sizeof(char)*10);
			sprintf(appended, ".%i", i);
			int j = strlen(appended);
			int len = strlen(loc);
			loc[len-j] = 0;//truncate
			//remove the last piece
		}
		i++;
		char* dst = (char*) malloc(sizeof(char)*10);
		sprintf(dst, ".%i", i);
		strcat(loc, dst);
		
	}
	printf("%s\n", loc);
	return loc;
}

int main(int argc, char* argv[]){
	int c;
	int fcounter = 0, hcounter = 0, rcounter = 0;
	int fileArgPos = argc-1; //position of file to be removed in arguments should be last
	
	//get all options
	while((c = getopt(argc, argv, ":fhr")) != -1){
		switch(c) {
			case 'f' :
				printf("Force is set.\n");
				fcounter++;
				break;
			case 'h' :
				hcounter++;
				break;
			case 'r' :
				printf("Recursive is set\n");
				rcounter++;
				break;
			case '?' :
				perror("Getopt error.");
				break;
			
		}
	}


	if(argc < 2 ){
		printf("Usage: rm (-f:-h:-r) <filename>\n");
		exit(1);
	}
	else{
		if(hcounter){
			printf("Usage: rm (-f:-h:-r) <filename>\n");
		}
		char* filename = argv[fileArgPos];
		struct stat  buf;
		
		struct utimbuf  puttime;
		
		/*
		
		*/
		//confirm file exists
		if(!access(filename, F_OK)){	//only checks if file exists (success on access() returns 0)
			char* bin = getTrash(); 	//Confirm TRASH variable is set, and place it in a string
			if(access(bin, F_OK)){		//Confirm TRASH variable doesn't point to nothing
				mkdir(bin, 0777);
			}
			
			if(!(fcounter > 0)){ //if force is set, just do a normal delete
				char* dest = getTrashWithTarget(bin, filename);
				link(filename, dest);	//Create file in trash
				
				stat(filename, &buf);
				puttime.actime = buf.st_atime;
				puttime.modtime = buf.st_mtime;
				utime(dest, &puttime);
			}
			unlink(filename);		//destroy pointed to link
		}
		else{
			perror("Given file does not exist or cannot be accessed.");
			exit(1);
		}
	
		
	}

}