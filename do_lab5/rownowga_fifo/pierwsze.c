//execl(”./licz”,”licz”,pocz,kon,numerP,0 )
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include "wynik.h"
#include "odcinek.h"

//pocz koniec procesy
int main (int argc, char *argv[]){

	double start = time(NULL);

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int odc = (int)strtol(argv[3], NULL, 10);
	int proc = (int)strtol(argv[4], NULL, 10);
	int krok = (kon - pocz) / odc;
	
	int wejscie = mkfifo("fifo_wejscie", 0666);
	
	if (wejscie < 0 ) {
		perror("mkfifo"); 
		exit(1);
	}
	
	wejscie = open("fifo_wejscie", O_RDWR | O_NONBLOCK);
	
	if (wejscie < 0 ) {
		perror("open fifo"); 
		exit(2);
	}
	
	int fifo;
	fifo = mkfifo("fifo", 0666);
	
	if (fifo < 0 ) {
		perror("mkfifo"); 
		exit(1);
	}
	
	fifo = open("fifo", O_RDWR | O_NONBLOCK);
	if (fifo < 0 ) {
		perror("open fifo"); 
		exit(2);
	}
	

	int i, p, o;
	
	for (i = 0, o = pocz ; i < odc; i++, o+=krok+1){
		odcinek tmp;
		tmp.poczatek = o;
		tmp.koniec = (i == odc -1) ? kon: o+krok;
		tmp.numer = i;
		printf ("Wrote %d\n",write (wejscie, &tmp, sizeof(tmp)));
	}
	
	printf("wejscie utworzone\n");
	
	for (i = 0, p = pocz; i < proc ; i++) {
		pid_t pid;
		char buff[255];
		sprintf(buff, "%d", odc);
		if((pid = fork()) == 0) {		
			execl("./licz", "licz", buff, NULL);
		}
	}
	
	printf("zrobione forki\n");
	

	

	int suma = 0;

	for (i = 0; i < proc; i++){
		int status;
		pid_t pid = wait(&status);
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	
	printf("zakonczone procesy\n");
	
	wynik_t readed;
	
	for (i = 0; i < odc; i++){
		int proc;
		read(fifo, &readed, sizeof(readed));
		suma += readed.ile;
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	close(wejscie);
	close(fifo);

	double koniec = time(NULL);
	printf("\n\n\nLiczb pierwszych w zakresie [%d,%d] jest: %d obliczenie zajely: %f [s]\n\n", pocz, kon, suma, (koniec - start));
}
