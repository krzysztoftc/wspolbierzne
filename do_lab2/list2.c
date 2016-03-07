// Ilustracja działania funkcji execl – uruchomienie programu potomny 

#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 

void main(void){ 
	int pid,status; 
	if((pid = fork()) == 0) { /* Proces potomny pot ---*/ 
		execl("./pot","pot",NULL); 
	}   
 /* Proces macierzysty */ 
	printf("Macierzysty = %d \n",getpid());   
	pid = wait(&status); 
	printf("Proces %d zakonczony status: %d\n",pid,status); 
} 
