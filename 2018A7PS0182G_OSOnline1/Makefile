driver.out: driver.c initializeMemory.o memTest.o printScore.o printMemoryState.o addToMemory.o
	gcc driver.c initializeMemory.o printScore.o printMemoryState.o addToMemory.o memTest.o -o main.out

initializeMemory.o: initializeMemory.c memInterface.h
	gcc -c initializeMemory.c

memTest.o: memTest.c memInterface.h
	gcc -c memTest.c

printScore.o: printScore.c memInterface.h
	gcc -c printScore.c

printMemoryState.o: printMemoryState.c memInterface.h
	gcc -c printMemoryState.c

addToMemory.o: addToMemory.c memInterface.h
	gcc -c addToMemory.c

clean:
	rm -f *.o *.out