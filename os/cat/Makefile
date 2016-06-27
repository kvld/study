all: link

clean:
	rm -f cat cat.o

compile:
	gcc -c cat.c -o cat.o

link: compile
	gcc cat.o -o cat
