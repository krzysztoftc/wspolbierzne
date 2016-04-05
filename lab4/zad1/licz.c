#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>

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

	//printf("Uruchomiono licz z param: %d %d %d\n", pocz, kon, proc);

	int licz = 0,i;
	for (i = pocz ; i <= kon ; i++){
		if (pierwsza(i)) licz++;
	}
	//printf("Proces %d znalazl %d liczb pierwszych \n", proc, licz);
	
	//int f;
	FILE *f;

	f = fopen("wynik.txt", "a");
	if (f == NULL ) {
		perror("fopen"); 
		exit(1);
	}
	int fd = fileno(f);
	flock(fd, LOCK_EX);
	fprintf(f, "Proces: %d\tliczb pierwszych: %d\n",proc, licz);
	flock(fd, LOCK_UN);
	fclose(f);

	exit(licz);
}
