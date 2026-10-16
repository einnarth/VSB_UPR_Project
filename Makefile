CC = gcc

CFLAGS = -Wall -Wextra -g -fsanitize=address

NAME = epidemic

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) *.o

.PHONY: all clean
