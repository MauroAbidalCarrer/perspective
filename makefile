.PHONY = all clean

all:
	gcc -c source\ code/*.c
	gcc *.o -o perspective 

clean: all
	rm -f *.o

