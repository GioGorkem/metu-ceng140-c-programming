CC = gcc
CFLAGS = -ansi -Wall -Wextra -pedantic-errors -O0 -g
LDFLAGS = -lm

all: the1_sim

the1_sim: the1_wave_pressure.c
	$(CC) $(CFLAGS) the1_wave_pressure.c -o the1_sim $(LDFLAGS)

clean:
	rm -f the1_sim the1_sim.exe *.o
