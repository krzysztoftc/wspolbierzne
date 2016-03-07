#include <stdlib.h>
#include <stdio.h>
 
main(int argc, char* argv[]) { 
	int i;		
	pid_t parentpid = getpid();
	printf("Proces macierzysty %d exit:\n", getpid());

	for (i = 0; i < argc; i++){

		pid_t pid;
		if((pid = fork()) == 0) {
			int j;
			for(j=0; j<(int)strtol(argv[i+2], NULL, 10); j++) { 
				printf("Potomny %d: PID: %d krok: %d\n",i,getpid(),j); 
				sleep(1); 
			} 
			exit(i);
		}
		
	}

	if (getpid() == parentpid){
		int j;
		for(j=0; j<(int)strtol(argv[1], NULL, 10); j++) { 
			printf("macierzysty: PID: %d krok: %d\n",getpid(),j); 
			sleep(1); 
			} 
	}
	

	for (i = 0; i < argc; i++){
		int status;
		pid_t pid = wait(&status);
		printf("Zakonczono %d exit: %d\n", pid, WEXITSTATUS(status));
	}
} 
