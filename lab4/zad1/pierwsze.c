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

//pocz koniec procesy
int main (int argc, char *argv[]){

	double start = time(NULL);

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int proc = (int)strtol(argv[3], NULL, 10);
	int krok = (kon - pocz) / proc;
	
	int f;
	f = open("wynik.bin", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (f < 0 ) {
		perror("fopen"); 
		exit(1);
	}
	close(f);

	printf ("Zakres: %d %d procesow: %d\n", pocz, kon, proc); 
	
	int i, p;
	for (i = 0, p = pocz; i < proc ; i++, p += krok +1) {
		pid_t pid;
		
		if((pid = fork()) == 0) {
			//int e = execl("./licz", "licz", (char*)p, (char*)(p+krok), (char*)(i),(char*)NULL);
			char arg1[10],arg2[10],arg3[10];
			
			sprintf(arg1,"%d", p);
			(i == proc -1) ? sprintf(arg2,"%d", kon): sprintf(arg2,"%d", p+krok);
			sprintf(arg3,"%d", i);
			
			execl("./licz", "licz", arg1,arg2,arg3 , NULL);
		}
	}

	int suma = 0;

	for (i = 0; i < proc; i++){
		int status;
		pid_t pid = wait(&status);
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}

	f = open("wynik.bin", O_RDONLY);
	
	if (f < 0) {
		perror("fopen"); 
		exit(1);
	}
	
	wynik_t readed;
	
	for (i = 0; i < proc; i++){
		int proc;
		read(f, &readed, sizeof(readed));
		suma += readed.ile;
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	close(f);

	double koniec = time(NULL);
	printf("\n\n\nLiczb pierwszych w zakresie [%d,%d] jest: %d obliczenie zajely: %f [s]\n\n", pocz, kon, suma, (koniec - start));
}
