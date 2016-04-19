all: init konsument producent 
init: init.c
	gcc -o init init.c -lrt
konsument: konsument.c
	gcc -o konsument konsument.c -lrt
producent: producent.c
	gcc -o	producent producent.c -lrt
clean:
	rm *.o init konsument producent

	
