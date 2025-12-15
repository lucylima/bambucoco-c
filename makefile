CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g -fsanitize=address

PRODFLAGS = -O3 -std=c11 -w

SRCS = main.c ./lib/interface.c ./lib/bambucoco.c

OBJS = $(SRCS:.c=.o)

TARGET = main

EXE = bambucoco

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


install: 
	${CC} ${PRODFLAGS} ${SRCS} -o ${EXE}

%.o: %.c
	$(CC) $(PRODFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)
