heap1: main.o heap.o utils.o
	gcc -Wall -o heap1 main.o heap.o utils.o -g

main.o: string_main.c
	gcc -Wall -c -o main.o string_main.c -g

heap.o: heap.c heap.h
	gcc -Wall -c -o heap.o heap.c -g

utils.o: utils.c utils.h
	gcc -Wall -c -o utils.o utils.c -g

clean:
	rm -f *.o
	rm heap1
