Author: Mark Fitzgibbon

Programs: 
	* rm
	* dv
	* dump
	
Source code content:
	* rm.c - source code to the remove tool
	* dv.c - source code to the dive tool
	* dump.c - source code to the dump tool
	* scruffy.c/h - source code for the functions used in rm and dv
	
Pre-requisites:
	* compile the code using the included makefile and make all
	* The environmental variable TRASH must already exist and be set
	* The folder TRASH refers to must also exist and be accessible.
	
RM - Remove a file
	Options:
		-r Recursive. Remove a folder and it's contents. By default, folders are not opened if -r is not set
		-f Force. Remove all contents, but do not back up into TRASH.
		-h Help. Display a basic use message.
	Make sure the prerequisites are set, and run the rm utility on any file or directory. 
	RM will fail with an error if none of the prerequisites are set.
	If the file or directory does not exist, rm messages the user and quits the delete attempt
	Directories require the -r flag to be set in order to delete sucessfully.
	If a file in trash exists with the same name, an incremented number is appended to the backup.
	
	Cross-partition attempts will copy instead of link().
	
	NOTE: Behavior if the current working directory is the trash is not treated as normal.
	
DV - Recover a file
	Options:
		-h Help. Display a basic use message
		
	Make sure all prerequisites are set, and run the dv tool
	If a trash item had an appended number at the end, it will maintain this number when recovered.
	
DUMP - Empty the trash
	Options:
		-h Help. Display a basic use message.
		
	Ensure that all prerequisites are correct before running dump
	dump essentially functions as "rm -rf $TRASH" with an additional mkdir call to replace the trash directory
	
Known error:
	Attempting to recursively remove a directory across partitions has been failing with strange memory affecting filenames. Unsure of how to fix. 
	Only appears to happen with multiple files inside the directory. Empty directories complete sucessfully, as well as singular files. 
	This error also seems to happen when a user attempts to delete multiple files at a time.