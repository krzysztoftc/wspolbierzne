#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

void main(void){ 
	int pid,status,i; 
	if((pid = fork()) == 0) {
		for(i=0;i<10;i++) { 
			printf(" Potomny krok: %d\n",i); 
			sleep(1); 
		} 
      exit(0); 
  }   


 printf("Macierzysty = %d 'n",getpid());   
 pid = wait(&status); 
 printf("Proces %d zakonczony status: %d\n",pid,status); 
} 
