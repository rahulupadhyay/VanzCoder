CC = gcc
CFLAGS = -c -Wall

all:
	$(CC) $(CFLAGS) Principal.adb
	gnatbind Principal
	gnatlink Principal

nolista:
	$(CC) $(CFLAGS) noslista.adb noslista.ads

clean:
	rm *.ali *.o Principal


