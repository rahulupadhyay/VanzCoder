FLAGS=

all:
	as $(FLAGS) -o exit.o  exit.s
	ld exit.o -o exit
	as $(FLAGS) -o maximum.o  maximum.s
	ld maximum.o -o maximum

clean:
	rm exit.o exit	
	rm maximum.o maximum	
