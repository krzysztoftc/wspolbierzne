#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include "wynik.h"
#include <mqueue.h> 

int pierwsza(int n){

	if (n < 2) return 0;
	int i,j=0; 
  	for(i=2;i*i<=n;i++) { 
    	if(n%i == 0) return(0) ; 
 	} 

 return(1); 
}

//pocz koniec numer procesu
int main (int argc, char *argv[]){

	int pocz = (int)strtol(argv[1], NULL, 10);
	int kon = (int)strtol(argv[2], NULL, 10);
	int proc = (int)strtol(argv[3], NULL, 10);

	printf("Uruchomiono licz z param: %d %d %d\n", pocz, kon, proc);

	int licz = 0,i;
	for (i = pocz ; i <= kon ; i++){
		if (pierwsza(i)) licz++;
	}
	//printf("Proces %d znalazl %d liczb pierwszych \n", proc, licz);
	
	
	wynik_t wynik;
	wynik.pocz = pocz;
	wynik.kon = kon;
	wynik.ile = licz;
	
	int res; 
	unsigned int prior = 10; 
	mqd_t  mq; 
	struct mq_attr attr; 
	
	/* Utworzenie kolejki komunikatow -----------------*/ 
	attr.mq_msgsize = sizeof(wynik_t); 
	attr.mq_maxmsg = 10; 
	attr.mq_flags = 0; 
	
	mq=mq_open("/Wyniki", O_RDWR, 0660, NULL ); 
	
	if( mq == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}
	
	mq_send(mq,(char*)&wynik,sizeof(wynik),prior); 
	
	mq_close(mq);
	//printf("koniec licz z param: %d %d %d\n", pocz, kon, proc);
	exit(licz);
}
