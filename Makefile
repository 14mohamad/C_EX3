CC = gcc
CFLAGS = -Wall -g
TARGET = StrList
OBJS = StrList.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c StrList.c

main.o: main.c StrList.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)
