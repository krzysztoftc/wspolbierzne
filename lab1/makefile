all: pierwszy drugi
pierwszy: pierwszy.c wspolny.c wspolny.h
	gcc -o pierwszy pierwszy.c wspolny.c
drugi: drugi.c wspolny.c wspolny.h
	gcc -o drugi drugi.c wspolny.c
clean:
	rm *.o pierwszy drugi
archiv: pierwszy.c drugi.c wspolny.c wspolny.h
	tar -cvf prace.tar *.c *.h makefile
	gzip prace.tar
	mv prace.tar.gz prace.tgz

	
