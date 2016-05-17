#include <stdio.h> 
#include <mqueue.h> 
#include "common.h"

int main(int argc, char *argv[]) { 

	bufor_t  *buf; 
	int  fd, res; // Deskryptor segmentu  
	
	shm_unlink("Bufor");    
	// Utworzenie segmentu pamieci  ---------------------  
	
	 if((fd=shm_open("Bufor",O_RDWR|O_CREAT,0664))==-1) { 
	    perror("shm_open"); 
	    exit(-1); 
	 } 
	
	 // Okreslenie rozmiaru obszaru pamieci ---------------     
	res = ftruncate(fd,sizeof(bufor_t)); 
 	
 	if(res < 0) {
 		perror("ftrunc");
 		return 0;
 	}
 	 
 	// Odwzorowanie segmentu fd w obszar pamieci procesow  
	 buf = (bufor_t *) mmap(0,sizeof(bufor_t), PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0); 
	
	 if(buf == NULL) {
	 	perror("mmap"); 
	 	exit(-1); 
	 } 
	
	//inicjalizacja obszaru
	buf -> head = 0;
	buf -> tail = 0;
	buf -> cnt = 0;
	
	if(sem_init(&(buf->mutex), 1, 1)){ 
		perror("mutex");
		exit(0);  
	}
	
	if(sem_init(&(buf->empty), 1, 1)){ 
		perror("mutex");
		exit(0);  
	}
	
	if(sem_init(&(buf->full), 1, 2)){ 
		perror("mutex");
		exit(0);  
	}
	
	printf ("Init OK\n");
	
	return 0;
}  
