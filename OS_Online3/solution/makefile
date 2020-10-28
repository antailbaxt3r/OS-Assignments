driver.out: driver.c cricket.o
	gcc driver.c cricket.o -o main.out

cricket.o: cricket.c cricket.h
	gcc -c cricket.c

clean:
	rm -f *.o *.out