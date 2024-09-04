#https://habr.com/ru/articles/155201/

# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC = gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS = -c

all: main

main: main.o snakeFunctions.o queue.o
	$(CC) main.o factorial.o hello.o -o hello

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

snakeFunctions.o: snakeFunctions.c
	$(CC) $(CFLAGS) -c snakeFunctions.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -rf *.o main