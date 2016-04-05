//execl(”./licz”,”licz”,pocz,kon,numerP,0 )
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <time.h>
#include "wynik.h"

int pierwsza(int n){

	int i,j=0; 
  	for(i=2;i*i<=n;i++) { 
    	if(n%i == 0) return(0) ; 
 	} 

 return(1); 
}

//pocz koniec procesy
int main (int argc, char *argv[]){

	double start = time(NULL);

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int proc = (int)strtol(argv[3], NULL, 10);
	int krok = (kon - pocz) / proc;
	
	printf ("Zakres: %d %d procesow: %d\n", pocz, kon, proc); 
	
	int fd[2];
	wynik_t wynik;
	pipe(fd);
	int i, p;
	for (i = 0, p = pocz; i < proc ; i++, p += krok +1) {
		pid_t pid;
		
		if((pid = fork()) == 0) {
			
			int k = ((i == proc -1 ) ? kon : p+krok);
			int licz = 0,i;
			for (i = p ; i <= k ; i++){
				if (pierwsza(i)) licz++;
			}
			
			wynik.pocz = pocz;
			wynik.kon = kon;
			wynik.ile = licz;
			
			close(fd[0]);
			write(fd[1], &wynik, sizeof(wynik));
			close(fd[1]);
			exit(0);
		}
	}

	int suma = 0;

	wynik_t readed;

	
	for (i = 0; i < proc; i++){
		close(fd[1]);
		read(fd[0], &readed, sizeof(readed));
		suma += readed.ile;
	}

	for (i = 0; i < proc; i++){
		int status;
		pid_t pid = wait(&status);
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}

	double koniec = time(NULL);
	printf("\n\n\nLiczb pierwszych w zakresie [%d,%d] jest: %d obliczenie zajely: %f [s]\n\n", pocz, kon, suma, (koniec - start));
}
