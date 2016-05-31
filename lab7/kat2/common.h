#ifndef common_h
#define common_h

#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPENR  1
// Otwarcie pliku do odczytu 
#define OPENW  2
// Otwarcie pliku do zapisu 
#define READ   3
// Odczyt fragmentu pliku 
#define CLOSE  4
// Zamkniecie pliku 
#define WRITE  5
// Zapis fragmentu pliku 
#define STOP  10
// Zatrzymanie serwera 

#define PORT 9950
#define PORT_CLI 9951
#define SRV_IP "127.0.0.1"
#define BUFLEN 80

#define SIZE 512 
typedef struct  { 
    int  typ;       // typ zlecenia 
    int  ile; 
  // liczba bajtow 
    int  fh;        // uchwyt pliku 
    char buf[SIZE]; // bufor 
} mms_t; 





#endif
