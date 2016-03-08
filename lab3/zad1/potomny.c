#include <stdlib.h>
#include <stdio.h>
 
 
//numer procesu kroki
main(int argc, char* argv[]) { 

			int j;
			for(j=0; j<(int)strtol(argv[2], NULL, 10); j++) { 
				printf("Potomny %d: PID: %d krok: %d\n",(int)strtol(argv[1], NULL, 10),getpid(),j); 
				sleep(1); 
			} 
			exit((int)strtol(argv[1], NULL, 10));
} 
