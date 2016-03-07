#include <stdlib.h>
#include <stdio.h>
 
main() { 
	printf("Moj PID: %d\n", getpid());
	printf("Macierzysty PID: %d\n", getppid());
	printf("Rzeczywisty ID uzytkownika: %d\n", getuid());
	printf("Rzeczywisty ID grupy: %d\n", getgid());
	printf("Efektywny ID uzytkownika: %d\n", geteuid());
	printf("Efektywny ID grupy: %d\n", getegid());
	printf("Priorytet: %d\n", getpriority());
	
} 
