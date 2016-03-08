#include <stdlib.h>
#include <stdio.h>
 
#include <sys/types.h>
#include <sys/wait.h> 
 
main(int argc, char* argv[]) { 
	int i;		
	pid_t parentpid = getpid();
	printf("Proces macierzysty %d exit:\n", getpid());

	for (i = 0; i < argc; i++){

		pid_t pid;
		if((pid = fork()) == 0) {
			char proces[10];
			char kroki[10];
			
			sprintf(proces, "%d", i);
			sprintf(kroki, "%d", (int)strtol(argv[i+2], NULL, 10));
			execl("./potomny","potomny",proces,kroki,NULL);
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
