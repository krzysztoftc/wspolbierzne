#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include "wynik.h"
#include "odcinek.h"
#include <mqueue.h> 

int pierwsza(int n){

	int i,j=0; 
  	for(i=2;i*i<=n;i++) { 
    	if(n%i == 0) return(0) ; 
 	} 

 return(1); 
}

//pocz koniec numer procesu
int main (int argc, char *argv[]){

	int proc = (int)strtol(argv[1], NULL, 10);

	int res; 
	unsigned int prior = 10; 
	mqd_t  mq_odcinki, mq_wyniki; 
	struct mq_attr attr, got_attr; 
	
	/* Utworzenie kolejki komunikatow -----------------*/ 
	attr.mq_msgsize = sizeof(wynik_t); 
	attr.mq_maxmsg = 10; 
	attr.mq_flags = 0; 
	
	mq_odcinki = mq_open("/Odcinki", O_RDWR , 0660, &attr ); 

	if( mq_odcinki == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}
	
	mq_wyniki =mq_open("/Wyniki", O_RDWR , 0660, &attr ); 

	if( mq_wyniki == -1 ) {  
		perror("Nie udalo sie otworzyc kolejki: "); 
		exit(1);  
	}
	
	odcinek r;

	int i = 0;
	
	while (1){
		mq_getattr(mq_odcinki, &got_attr);
		if (got_attr.mq_curmsgs <= 0) break;
		mq_receive(mq_odcinki,(char *)&r,sizeof(r),&prior);
		
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
		
		mq_send(mq_wyniki,(char*)&wynik,sizeof(wynik),prior); 
		
	}
	
	printf("Koniec licz %d\n",proc);

	exit(0);
}
