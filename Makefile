CC=g++ # compiler name
CCFLAGS=-std=c++11 -g# flags passed to the compiler

run: samp
	./samp -r 44100 -b 8 -c 1 -rev susan

samp: Audio.o FileIO.o Driver.o Audio.h FileIO.h
	$(CC) $(CCFLAGS) Audio.o FileIO.o Driver.o -o samp 

Audio.o: Audio.cpp Audio.h
	$(CC) $(CCFLAGS) Audio.cpp -c

Driver.o: Driver.cpp Audio.h
	$(CC) $(CCFLAGS) Driver.cpp -c

FileIO.o: FileIO.cpp FileIO.h
	$(CC) $(CCFLAGS) FileIO.cpp -c

clean:
	rm -f *.o
	rm samp


