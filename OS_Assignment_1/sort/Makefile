bubblesort.out: main.c bubble_sort.o
	gcc main.c bubble_sort.o -o bubblesort.out

insertionsort.out: main.c insertion_sort.o
	gcc main.c insertion_sort.o -o insertionsort.out

mergesort.out: main.c merge_sort.o
	gcc main.c merge_sort.o -o mergesort.out

quicksort.out: main.c quick_sort.o
	gcc main.c quick_sort.o -o quicksort.out

bubble_sort.o: bubble_sort.c sort.h
	gcc -c bubble_sort.c

merge_sort.o: merge_sort.c sort.h
	gcc -c merge_sort.c

insertion_sort.o: insertion_sort.c sort.h
	gcc -c insertion_sort.c

quick_sort.o: quick_sort.c sort.h
	gcc -c quick_sort.c

clean:
	rm -f *.o *.out