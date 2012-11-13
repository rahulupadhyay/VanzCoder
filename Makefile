JAVACC=javac
JAVAFILE=Author.java

all:
	$(JAVACC) $(JAVAFILE)
clean:
	rm *.class
