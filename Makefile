CC=g++ # compiler name
CCFLAGS=-std=c++11 -g# flags passed to the compiler

run: samp
	./samp -r 44100 -b 16 -c 2 -o out -add sample_input/beez18sec_44100_signed_16bit_stereo sample_input/beez18sec_44100_signed_16bit_stereo

samp: Audio.o FileIO.o Driver.o Audio.h FileIO.h
	$(CC) $(CCFLAGS) Audio.o FileIO.o Driver.o -o samp 

Audio.o: Audio.cpp Audio.h
	$(CC) $(CCFLAGS) Audio.cpp -c

Driver.o: Driver.cpp Audio.h
	$(CC) $(CCFLAGS) Driver.cpp -c

FileIO.o: FileIO.cpp FileIO.h
	$(CC) $(CCFLAGS) FileIO.cpp -c

tests: UnitTests.o Audio.h 
	$(CC) $(CCFLAGS) UnitTests.o -o tests

UnitTests.o: UnitTests.cpp
	$(CC) $(CCFLAGS) UnitTests.cpp -c

clean:
	rm -f *.o
	rm samp

testsClean:
	rm -f *.o
	rm tests
