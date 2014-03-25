/* I'm Scruffy.h. The janitor
	Mark Fitzgibbon
*/

#include "scruffy.h"
#include <stdio.h>
#include <string.h> //strcpy
#include <stdlib.h>		
#include <sys/types.h>
#include <sys/stat.h>		
#include <unistd.h>
#include <libgen.h> //Basename & dirname
#include <utime.h>		
#include <dirent.h>

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
	
	if(access(dir, F_OK)){		//Confirm TRASH variable doesn't point to nothing
		printf("Making directory %s\n", dir);
		mkdir(dir, 0777);
	}
	
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
	
	return loc;
}

void moveFile(char* filename, char* dest, int force, int recurse){
	struct stat  buf;
		
	struct utimbuf  puttime;
	char* destination = getTrashWithTarget(dest, filename);//Perform getname
	
	
	
	//Is filename directory? Yes/No
	//Yes:
	
		
	
		//Is Empty? Yes/No
		//Yes:
		//Trash next file appropriatley
		//No:
		//Recursive call to moveFIle()
	//No:
	//Move file
	if(!access(filename, F_OK)){
		if(stat(filename, &buf) != 0){
			perror("Stat failed.");
			exit(1);
		}
				
		if(S_ISREG(buf.st_mode)){ //recieved file is not a directory
			if(!force){
			
				link(filename, destination);	//Create file in trash
				puttime.actime = buf.st_atime;
				puttime.modtime = buf.st_mtime;
				utime(destination, &puttime);
			}
			
			unlink(filename);
		}
		else{
		
			if(recurse == 1){
				//go into directory, moveFile()
				DIR *dp;
				struct dirent *d;
				
				dp = opendir(filename);
				if (dp == NULL) {
					perror("open");
					exit(1);
				}
				d = readdir(dp);
				
				while(d){
					printf("%s/%s\n", destination, filename);
					if(strcmp(d->d_name, ".") && strcmp(d->d_name, "..")){
					
						chdir(filename);
						moveFile(d->d_name, destination, force, recurse);
						chdir("..");
					}
					d = readdir(dp);
				}
				closedir(dp);
				
				rmdir(filename);
			}
			else{
			//directory
				printf("Directory, but not recursively set\n");
				exit(1);
			}
		}
		
		
	}
	else{
		printf("%s/%s", getcwd(NULL, 0), filename);
		perror("Given file does not exist or cannot be accessed.");
		exit(1);
	}

	printf("Name will be %s/%s\n", dest, filename);
	
}

