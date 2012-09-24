CC=gcc
CFLAGS=-c -Wall
FILES=principal.adb listas.adb

all:
	$(CC) $(CFLAGS) $(FILES)
	gnatbind principal
	gnatlink principal

clean:
	rm *.ali *.o principal
