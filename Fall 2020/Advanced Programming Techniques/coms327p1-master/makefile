
#makes all files in coms327p1
all: playsong

playsong: playsong.o gensnd.o process.o iosnd.o
	gcc playsong.o gensnd.o process.o iosnd.o -o playsong -lm

playsong.o: playsong.c gensnd.h process.h
	gcc -c playsong.c
gensnd.o: gensnd.c gensnd.h
	gcc -c gensnd.c
process.o: process.c process.h
	gcc -c process.c
iosnd.o: iosnd.c iosnd.h
	gcc -c iosnd.c
\
clean:
	rm *.o playsong

