# Dijkstras-Algorithm

This was a school project for one of my C programming courses.

This application provides an implementation of Dijkstra's algorithm for finding the shortest path
on a graph. The user can specify a graph type and a few other settings when running the program.

To run the application, run ./lab6 and follow with the flags for which graph type, graph operation,
and other settings you would like to use.

-g x: run with graph type 'x', using graph type 1 though 3.   
            1: weakly-connected directed graph.  
            2: strongly-connected directed graph.  
            3: random graph.  
-n N: use N vertices in graph.  
-a R: approximate number of adjacent vertices 0<R<N  
-h x: graph operation x.  
            1: shortest path  
            2: network diameter  
            3: multipe link-disjoint paths  
-s S: number of the source vertext 0<=S<N  
-d D: number of the destination vertext 0<=D<N  
-v: verbose output.  
-r x: seed for random number generator.  
-t: enable testing mode (prints adjacency matrix).  

Below is a brief description of each file in the application. Further information can be found
in the header comment of each file. 

lab6.c: Contains the main loop and drivers to test the Dijkstra's algorithm module.  
dijkstra.c: Provides functions for editing a graph, and implementing Dijkstra's algorithm.  
MP6testScript.c: Test script to test functionality of the application by running serveral test cases.  
dijkstra.h: Function prototype declarations and struct definitions for dijkstra.c.  
makefile: Compiles the application.  

