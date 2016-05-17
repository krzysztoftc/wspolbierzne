#include <stdio.h> 
#include <mqueue.h> 
#include "common.h"

int main(int argc, char *argv[]) { 
	unsigned int  kroki;
	sscanf(argv[1], "%d", &kroki );
	
	bufor_t  *buf; 
	int  fd, res; // Deskryptor segmentu  
	
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
	
	msg_type msg;
	int i;
	for(i = 0; i < kroki; i++) { 
		sem_wait(&(buf -> empty));
		sem_wait(&(buf -> mutex));
		
		printf("Odebrano[%d]: %s \n", i, buf->buf[buf->tail]);
		buf -> cnt --;
		buf -> tail = (buf -> head + 1) % BSIZE;
		
		sem_post(&(buf -> mutex));
		sem_post(&(buf -> full));
	} 

	return 0;
} 
