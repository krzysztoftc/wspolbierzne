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
#include <mqueue.h> 

//pocz koniec procesy
int main (int argc, char *argv[]){

	double start = time(NULL);

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int odc = (int)strtol(argv[3], NULL, 10);
	int proc = (int)strtol(argv[4], NULL, 10);
	int krok = (kon - pocz) / odc;
	
	
	int res; 
	unsigned int prior = 10; 
	mqd_t  mq_odcinki, mq_wyniki; 
	struct mq_attr attr, got_attr; 
	
	/* Utworzenie kolejki komunikatow -----------------*/ 
	attr.mq_msgsize = sizeof(wynik_t); 
	attr.mq_maxmsg = 10; 
	attr.mq_flags = 0; 
	
	mq_unlink("/Odcinki");
	mq_odcinki = mq_open("/Odcinki", O_RDWR | O_CREAT , 0660, &attr ); 

	if( mq_odcinki == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}
	
	mq_unlink("/Wyniki");
	mq_wyniki =mq_open("/Wyniki", O_RDWR | O_CREAT , 0660, &attr ); 

	if( mq_wyniki == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}
	

	int i, p, o;
	
	//tworzymy proces uzupelniajacy koejke odcinkow
	pid_t pid;
	if((pid = fork()) == 0) {		
		for (i = 0, o = pocz ; i < odc; i++, o+=krok+1){
			odcinek tmp;
			tmp.poczatek = o;
			tmp.koniec = (i == odc -1) ? kon: o+krok;
			tmp.numer = i;
			mq_send(mq_odcinki,(char*)&tmp,sizeof(tmp),prior);
			printf("Utworzono odcinek %d od %d do %d\n", tmp.numer, tmp.poczatek , tmp.koniec); 
		}
		exit(0);
	}
	
	do{
		mq_getattr(mq_odcinki, &got_attr);
	}while(got_attr.mq_curmsgs <= 0);
	
	printf("Forkujemy na licz\n");
	
	for (i = 0; i < proc ; i++) {
		pid_t pid;
		char buff[255];
		sprintf(buff, "%d", i);
		if((pid = fork()) == 0) {		
			execl("./licz", "licz", buff, NULL);
		}
	}
		

	int suma = 0;
	
	wynik_t readed;
	
	for (i = 0; i < odc; i++){
		
		mq_receive(mq_wyniki,(char *)&readed,sizeof(readed),&prior);
		suma += readed.ile; 
		printf("odczytano odcinek %d - %d ile %d\n", readed.pocz, readed.kon, readed.ile);
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	printf("Oczytano wszystkei odcinki\n");
	
	for (i = 0; i < proc; i++){
		int status;
		pid_t pid = wait(&status);
		//printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
	
	printf("zakonczone procesy\n");
	
	
	mq_close(mq_odcinki);
	mq_close(mq_wyniki);

	double koniec = time(NULL);
	printf("\n\n\nLiczb pierwszych w zakresie [%d,%d] jest: %d obliczenie zajely: %f [s]\n\n", pocz, kon, suma, (koniec - start));
}
