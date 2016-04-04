#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

	int pocz = (int)strtol(argv[1], NULL, 10);

	FILE *f;

	f = fopen("plik.txt", "w");
	if (f == NULL ) {
		perror("fopen"); 
		exit(1);
	}

	fwrite (&pocz, sizeof(int), 1, f);

	fclose(f);
 
	FILE *r;
	r = fopen("plik.txt", "r");
	if (r == NULL ) {
		perror("fopen"); 
		exit(1);
	}
	int readed = 0;

	fread (&readed, sizeof(int), 1, r);

	printf ("Saved: %d, readed: %d\n\n", pocz, readed);

	fclose(r);

	exit(0);
}
