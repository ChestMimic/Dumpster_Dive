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
#include <dirent.h>



char *getTrash(); //retrieve the trash directory as set by the environment
char *getTrashWithTarget(char* dir, char* file);
void moveFile(char* filename, char* dest, int force, int recurse);
	void printUseMessage();

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
	
	return loc;
}

void moveFile(char* filename, char* dest, int force, int recurse){
	struct stat  buf;
		
	struct utimbuf  puttime;
	char* destination = getTrashWithTarget(dest, filename);//Perform getname
	
	if(access(destination, F_OK)){		//Confirm TRASH variable doesn't point to nothing
		mkdir(destination, 0777);
	}
	
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

void printUseMessage(){
	printf("Usage: rm (-f:-h:-r) <filename>\n");
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
				fcounter = 1;
				break;
			case 'h' :
				hcounter = 1;
				break;
			case 'r' :
				printf("Recursive is set\n");
				rcounter = 1;
				break;
			case '?' :
				perror("Getopt error.");
				break;
			
		}
	}


	if(argc < 2 ){
		printUseMessage();
		exit(1);
	}
	else{
		if(hcounter){
			printUseMessage();
		}
		char* filename = argv[fileArgPos];
		struct stat  buf;
		
		struct utimbuf  puttime;
		char* bin = getTrash(); 	//Confirm TRASH variable is set, and place it in a string
			if(access(bin, F_OK)){		//Confirm TRASH variable doesn't point to nothing
				mkdir(bin, 0777);
			}
		/*
		
		*/
		//confirm file exists
		moveFile(filename, bin, fcounter, rcounter);
	
		
	}

}