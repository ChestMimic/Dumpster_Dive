#ifndef SCRUFFY_H
#define SCRUFFY_H

char *getTrash(); //retrieve the trash directory as set by the environment
char *getTrashWithTarget(char* dir, char* file);
void moveFile(char* filename, char* dest, int force, int recurse);
void printUseMessage();

#endif