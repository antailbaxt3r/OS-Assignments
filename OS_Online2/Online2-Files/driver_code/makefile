driver.out: driver.c stringToFloat.o
	gcc driver.c stringToFloat.o -o driver.out

stringToFloat.o: stringToFloat.c stringToFloat.h
	gcc -c stringToFloat.c

clean: 
	rm -f *.o *.out
