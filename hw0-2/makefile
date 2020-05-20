CC = gcc
TARGET = testlib

$(TARGET) : main.o list.o hash.o bitmap.o
	    $(CC) -o $(TARGET) main.o list.o hash.o bitmap.o -Wall

main.o : main.c 
	$(CC) -c main.c

list.o : list.c list.h
	$(CC) -c list.c

hash.o : hash.c hash.h
	$(CC) -c hash.c

bitmap.o : bitmap.c stdio.c bitmap.h limits.h round.h
	$(CC) -c -w bitmap.c

clean : 
	rm *.o $(TARGET)
