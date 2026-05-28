CC = gcc
CFLAGS = -ansi -Wall -Wextra -pedantic-errors -O0 -g

all: sensor_sim

sensor_sim: main.c sensor_network.c sensor_network.h
	$(CC) $(CFLAGS) main.c sensor_network.c -o sensor_sim

check-leaks: sensor_sim
	valgrind --leak-check=full --show-leak-kinds=all ./sensor_sim

clean:
	rm -f sensor_sim sensor_sim.exe *.o
