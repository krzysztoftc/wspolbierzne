#include <semaphore.h>
#include <sys/mman.h>

typedef struct {
int pocz;
int kon;
int ile;
} wynik_t;
 
 #define BSIZE 8
    		
typedef struct { 
    int head; // Tutaj producent wstawia nowy element 
    int tail; // Stąd pobiera element konsument 
    int cnt;  // Liczba elementów w buforze  
    sem_t mutex; // Semafor chroniący sekcję krytyczną
    sem_t empty; // Semafor wstrzymujący producenta 
    sem_t full;  // Semafor wstrzymujący konsumenta 
    wynik_t buf[BSIZE]; 
} bufor_t;
