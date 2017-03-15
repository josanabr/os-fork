all: findprime findprime2 findprime2a findprime2b
	
clean:
	rm -f a.out fork findprime findprime2 findprime2a findprime2b
findprime:
	gcc -o findprime findprime.c
findprime2:
	gcc -o findprime2 findprime2.c
findprime2a:
	gcc -o findprime2a findprime2a.c
findprime2b:
	gcc -o findprime2b findprime2b.c
