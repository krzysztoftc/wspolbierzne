#include <stdio.h> 
#include <mqueue.h> 
#include "common.h"

int main(int argc, char *argv[]) { 
	unsigned int dlugosc_kolejki;
	sscanf(argv[1], "%d", &dlugosc_kolejki );
	
	msg_type msg;
	int i, res; 
	unsigned int prior; 
	mqd_t  mq; 
	struct mq_attr attr; 
	
	/* Utworzenie kolejki komunikatow -----------------*/ 
	attr.mq_msgsize = sizeof(msg_type); 
	attr.mq_maxmsg = dlugosc_kolejki; 
	attr.mq_flags = 0; 
	mq_unlink("/Kolejka");
	printf("sizeof msg: %ld \n", sizeof(msg));
	mq=mq_open("/Kolejka", O_RDWR | O_CREAT , 0660, &attr ); 
	mq_close(mq);
	return 0;
}  
