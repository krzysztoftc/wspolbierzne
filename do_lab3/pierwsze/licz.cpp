#include <stdlib.h>
#include <stdio.h>

int pierwsza(int n){

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

	int licz = 0;
	for (int i = pocz ; i <= kon ; i++){
		if (pierwsza(i)) licz++;
	}
	printf("Proces %d znalazl %d liczb pierwszych \n", proc, licz);
	exit(licz);
}
