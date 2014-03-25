all: rm dump dv

rm.o: rm.c
	gcc -c rm.c
	
dv.o: dv.c
	gcc -c dv.c
	
dump.o: dump.c
	gcc -c dump.c
	
scruffy.o: scruffy.c
	gcc -c scruffy.c
	
dv: dv.o scruffy.o
	gcc dv.o scruffy.o -o dv
	
rm: rm.o scruffy.o
	gcc rm.o scruffy.o -o rm
	
dump: dump.o
	gcc dump.o -o dump
	
clean: 
	rm *.o