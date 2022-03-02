all:TestMain

TestMain: TestMain.o wave.o soundio.o SoundSamples.o
	g++ TestMain.o wave.o soundio.o SoundSamples.o -o TestMain -lm
TestMain.o: TestMain.cpp wave.h soundio.h
	g++ -c TestMain.cpp
wave.o: wave.cpp wave.h
	g++ -c wave.cpp
soundio.o: soundio.cpp soundio.h
	g++ -c soundio.cpp
SoundSamples.o: SoundSamples.cpp SoundSamples.h
	g++ -c SoundSamples.cpp
	

clean:
	rm *.o TestMain