//execl(”./licz”,”licz”,pocz,kon,numerP,0 )
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h> 

#include <time.h>
#include "wynik.h"

//pocz koniec procesy
int main (int argc, char *argv[]){

	double start = time(NULL);

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int proc = (int)strtol(argv[3], NULL, 10);
	int krok = (kon - pocz) / proc;
	
	wynik_t msg;
	int i, res; 
	unsigned int prior = 1; 
	mqd_t  mq; 
	struct mq_attr attr; 
	
	/* Utworzenie kolejki komunikatow -----------------*/ 
	attr.mq_msgsize = sizeof(wynik_t); 
	attr.mq_maxmsg = 10; 
	attr.mq_flags = 0; 
	
	mq_unlink("/Wyniki");
	mq=mq_open("/Wyniki", O_RDWR | O_CREAT , 0660, &attr ); 

	if( mq == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}

	printf ("Zakres: %d %d procesow: %d\n", pocz, kon, proc); 
	
	int p;
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
	
	wynik_t readed;
	
	for (i = 0; i < proc; i++){
		
		mq_receive(mq,(char *)&readed,sizeof(readed),&prior);
		suma += readed.ile; 

		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	

	for (i = 0; i < proc; i++){
		int status;
		pid_t pid = wait(&status);
//		printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	
	mq_close(mq);

	double koniec = time(NULL);
	printf("\n\n\nLiczb pierwszych w zakresie [%d,%d] jest: %d obliczenie zajely: %f [s]\n\n", pocz, kon, suma, (koniec - start));
}
