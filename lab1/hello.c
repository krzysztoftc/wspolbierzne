#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){

	#ifdef DEBUG
	printf("argc: %d argv[0]: %s\n", argc, argv[0]);
	#endif
	printf("Dzien dobry\n");
	
	return 0;
}
