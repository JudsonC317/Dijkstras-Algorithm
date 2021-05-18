# The makefile for MP6
# Type:
# 		make			-- to build program lab6
# 		make clean	-- to delete executable files, object files, and core

lab6 : dijkstra.c lab6.c
	gcc -Wall -g dijkstra.c lab6.c -o lab6 -lm

clean : 
	rm -f *.o lab6 core a.out


