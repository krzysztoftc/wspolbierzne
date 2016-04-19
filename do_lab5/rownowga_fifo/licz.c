#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include "wynik.h"
#include "odcinek.h"

int pierwsza(int n){

	int i,j=0; 
  	for(i=2;i*i<=n;i++) { 
    	if(n%i == 0) return(0) ; 
 	} 

 return(1); 
}

//pocz koniec numer procesu
int main (int argc, char *argv[]){

	int odc = (int)strtol(argv[1], NULL, 10);

	int fifo;
	int wejscie = open("fifo_wejscie", O_RDONLY | O_NONBLOCK);
	
	printf("licz %d\n", wejscie);
	
	if (wejscie < 0) {
		perror("fifo open"); 
		exit(1);
	}		
	
	fifo = open("fifo", O_RDWR | O_NONBLOCK);
	
	if (fifo < 0) {
		perror("fifo open"); 
		exit(1);
	}
	
	printf("otwarte\n");
	odcinek r;

	int i = 0;
	
	while (read(wejscie, &r, sizeof(r)) > 0){

		int pocz = r.poczatek;
		int kon = r.koniec;
		int proc = r.numer;
	
		printf("wejscie odczytane przedzial %d, poczatek  %d, koniec %d\n", proc, pocz, kon);
		//printf("Uruchomiono licz z param: %d %d %d\n", pocz, kon, proc);

		int licz = 0,i;
		for (i = pocz ; i <= kon ; i++){
			if (pierwsza(i)) licz++;
		}
		printf("Proces %d znalazl %d liczb pierwszych \n", proc, licz);

		wynik_t wynik;
		wynik.pocz = pocz;
		wynik.kon = kon;
		wynik.ile = licz;
		
		printf("Koniec, wrote: %d\n", write(fifo, &wynik, sizeof(wynik)));
		
	}
	printf("Koniec licz\n");

	exit(0);
}
