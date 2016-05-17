#include <semaphore.h>
#include <sys/mman.h>

typedef struct  { 
        int  type;        
/* typ procesu:  1 PROD, 2 KONS  */ 
        int  pnr ;        
/* numer procesu     */   
        char text[255];  
/* tekst  komunikatu */ 
 } msg_type; 
 
 #define BSIZE 3
 #define LSIZE 8
    		
typedef struct { 
    int head; // Tutaj producent wstawia nowy element 
    int tail; // Stąd pobiera element konsument 
    int cnt;  // Liczba elementów w buforze  
    sem_t mutex; // Semafor chroniący sekcję krytyczną
    sem_t empty; // Semafor wstrzymujący producenta 
    sem_t full;  // Semafor wstrzymujący konsumenta 
    char buf[BSIZE][LSIZE]; 
} bufor_t;
