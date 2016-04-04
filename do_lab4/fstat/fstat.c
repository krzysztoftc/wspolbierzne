#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 

int main (int argc, char* argv[]){

	if (argc < 2){
		printf ("%s\n", "Uzycie: fstat <nazwa_pliku>");
		exit(1);
	}
	
	struct stat file_stats;
	
	if ( (stat (argv[1], &file_stats))){
		printf ("%s\n", "Nie mozna otworzyc pliku");
		exit(1);
	}
	   
    printf("Nazwa: %s\n", argv[1]);
    printf("Rozmiar: %d B\n", (int)file_stats.st_size);
    printf("Dowiazania: %d\n", (int)file_stats.st_nlink);
    printf("Pozwolenia: ");
    printf ( "%c", (S_ISDIR(file_stats.st_mode)) ? 'd' : '-');
    printf ( "%c", (S_ISLNK(file_stats.st_mode)) ? 'l' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IRUSR) ? 'r' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IWUSR) ? 'w' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IXUSR) ? 'x' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IRGRP) ? 'r' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IWGRP) ? 'w' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IXGRP) ? 'x' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IROTH) ? 'r' : '-');
    printf ( "%c", ((file_stats.st_mode) & S_IWOTH) ? 'w' : '-');
    printf ( "%c\n", ((file_stats.st_mode) & S_IXOTH) ? 'x' : '-');
    printf("Link: %c\n", (S_ISLNK(file_stats.st_mode))? 'T':'N');
	
	return 0;
}
