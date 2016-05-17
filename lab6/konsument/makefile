all: init konsument producent 
init: init.c
	gcc -o init init.c -lrt -pthread
konsument: konsument.c
	gcc -o konsument konsument.c -lrt -pthread
producent: producent.c
	gcc -o	producent producent.c -lrt -pthread
clean:
	rm *.o init konsument producent

	
