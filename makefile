CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -g -lm

.PHONY: clean

donut: main.c helper.o
	$(CC) $(CFLAGS) $^ -o $@


helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -Wno-unused-command-line-argument -c $< -o $@


clean:
	-$(RM) -r *.o donut *.dSYM
