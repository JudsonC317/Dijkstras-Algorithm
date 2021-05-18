/* lab6.c
 * Judson Cooper
 * MP6
 *
 * Purpose: This file contains drivers to test the Dijkstra's algorithm module,
 * 	and the graph functions it provides for solving shortest path problems.
 *
 * Assumptions: The program will accept command line input from the user to
 * 	control which driver is used, and which settings are used for the
 * 	creation of the graph.
 *
 * Bugs: None known.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#include "dijkstra.h"

// global variables for command line parameters
int GraphType = -1;
int NumVertices = -1;
int AdjacentVertices = -1;
int GraphOperation = -1;
int SourceVertex = -1;
int DestinationVertex = -1;
int Verbose = FALSE;
int Seed = 10212018;
int Testing = FALSE;

// prototypes for private functions in this file
void getCommandLine (int argc, char** argv);
void PrintPath(graph_t* G, int Source, int Dest);
void RemovePath(graph_t* G, int Source, int Dest);

int main(int argc, char **argv) {
	graph_t *G = NULL;
	clock_t start, end;

	getCommandLine(argc, argv);
	printf("Seed: %d\n", Seed);
	srand48(Seed);
	
	// build graph based on type from -g argument
	if (GraphType == 1) { // weakly-connected directed graph
		
		G = graph_construct(NumVertices);
		
		graph_add_edge(G, 1, 2, 3);
		graph_add_edge(G, 1, 6, 5);
		graph_add_edge(G, 2, 3, 7);
		graph_add_edge(G, 2, 4, 3);
		graph_add_edge(G, 2, 6, 10);
		graph_add_edge(G, 3, 4, 5);
		graph_add_edge(G, 3, 5, 1);
		graph_add_edge(G, 4, 5, 6);
		graph_add_edge(G, 5, 6, 7);
		graph_add_edge(G, 6, 0, 4);
		graph_add_edge(G, 6, 3, 8);
		graph_add_edge(G, 6, 4, 9);

		if (Testing) {
			graph_debug_print(G);
		}
	}

	else if (GraphType == 2) { // strongly-connected directed graph
		double weight = 0;
		int i = 0, j = 0;

		if (NumVertices == -1) {
			fprintf(stderr, "NumVertices was not specified (use -n flag)\n");
			exit(1);
		}
		
		G = graph_construct(NumVertices);

		// add an edge for each vertice i and j, calculating the edge weight
		// based on the number of each vertice
		for (i = 0; i < NumVertices; i++) {
			for (j = 0; j < NumVertices; j++) {
				if (i != j) {
					weight = abs(i-j) + pow(i-j+2, 2) + 3*j;
				} else {
					weight = 0;
				}
				graph_add_edge(G, i, j, weight);
			}
		}

		if (Testing) {
			graph_debug_print(G);
		}
	}

	else if (GraphType == 3) { // random graph
		double distance, weight;
		double C, M, F;
		double *xVal, *yVal;

		// NumVertices is a good initializer for min adjacent vertices as the
		// min cannot possibly end up larger than this value
		int totalV = 0, maxV = 0, minV = NumVertices, thisTotal = 0;
		float averageV = 0;

		int i = 0, j = 0;
		
		if (NumVertices == -1) {
			fprintf(stderr, "NumVertices was not specified (use -n flag)\n");
			exit(1);
		}
		if (AdjacentVertices == -1) {
			fprintf(stderr, "AdjacentVertices was not specified (use -a flag)\n");
			exit(1);
		}
		
		G = graph_construct(NumVertices);

		// these arrays will hold the location for each vertice
		xVal = (double*) malloc(NumVertices * sizeof(double));
		yVal = (double*) malloc(NumVertices * sizeof(double));

		// find normalized comm range and min data rate, which will be used for all verts
		C = sqrt(AdjacentVertices / (NumVertices * M_PI));
		M = log10(1 + pow(1/C, 2));

		// assign a random location in x and y coord system to each vertice
		for (i = 0; i < NumVertices; i++) {
			xVal[i] = drand48();
			yVal[i] = drand48();
			// printf("x: %0.3f, y: %0.3f\n", xVal[i], yVal[i]);
		}
		// want vertice 0 and vertice N-1 to be these values instead
		xVal[0] = 0; yVal[0] = 0.5;
		xVal[NumVertices-1] = 1; yVal[NumVertices-1] = 0.5;

		// now use the location of the vertices to calculate their edge weights
		for (i = 0; i < NumVertices; i++) {
			thisTotal = 0;
			for (j = 0; j < NumVertices; j++) {
				// figure out what case holds for weight
				if (i == j) {
					weight = 0;
				}
				else {
					distance = sqrt(pow(xVal[i]-xVal[j], 2) + pow(yVal[i]-yVal[j], 2));
					if (distance <= C) {
						F = log10(1 + pow(1 / (distance + (C/1000)), 2));
						weight = M / F;
						thisTotal++;
						totalV++;
					}
					else {
						weight = INF;
					}
				}
				graph_add_edge(G, i, j, weight);
			}

			// check if new max or min vert count for this 'i'
			if (thisTotal > maxV) {
				maxV = thisTotal;
			}
			else if (thisTotal < minV) {
				minV = thisTotal;
			}
		}

		// free the location arrays, no longer necessary
		free(xVal);
		free(yVal);
		
		if (Testing) {
			graph_debug_print(G);
		}

		averageV = (float)totalV / (float)NumVertices;
		printf("Average adjacent vertices: %0.3f\n", averageV);
		printf("Maximum adjacent vertices: %d\n", maxV);
		printf("Minimum adjacent vertices: %d\n", minV);
	}


	puts(""); // make formatting less ugly


	if (GraphType == -1) {
		fprintf(stderr, "Cannot perform graph operations without valid graph type\n");
		exit(1);
	}

	// perform graph operation based on -h argument
	if (GraphOperation == 1) { // shortest path
		if (SourceVertex == -1) {
			fprintf(stderr, "SourceVertex was not specified (use -s flag)\n");
			graph_destruct(G);
			exit(1);
		}
		if (DestinationVertex == -1) {
			fprintf(stderr, "DestinationVertex was not specified (use -d flag)\n");
			graph_destruct(G);
			exit(1);
		}

		// execute and measure runtime of Dijkstra's algorithm
		start = clock();
		graph_shortest_path(G, SourceVertex);
		end = clock();

		// display results
		if (G->ShortestDistance[DestinationVertex] < INF) {
			printf("The cost to %d from %d is %0.3f\n", SourceVertex, 
				DestinationVertex, G->ShortestDistance[DestinationVertex]);
			
			PrintPath(G, SourceVertex, DestinationVertex);
			puts("");
			printf("Dijkstra's algorithm runtime: %g ms\n", 
				1000*((double)(end-start))/CLOCKS_PER_SEC);
		}
		else {
			printf("A path does not exist between %d and %d\n", 
				SourceVertex, DestinationVertex);
		}
	}

	if (GraphOperation == 2) { // network diameter
		int src = 0, dest = 0;
		int largeS = -1, largeD = -1;
		double largeCost = -1;
		int isINFpath = 0;

		start = clock();
		for (src = 0; src < NumVertices; src++) {
			// run Dijkstra's for each possible src
			graph_shortest_path(G, src);
			for (dest = 0; dest < NumVertices; dest++) {
				// compare each possible dest to see if new max
				if ((G->ShortestDistance[dest] < INF) && 
				(G->ShortestDistance[dest] > largeCost)) {
					// new max found, save its info
					largeCost = G->ShortestDistance[dest];
					largeS = src;
					largeD = dest;
				}
				else if (G->ShortestDistance[dest] == INF) {
					isINFpath = 1;
				}
			}
		}
		end = clock();

		if (isINFpath == 1) {
			printf("Graph contains at least one pair of vertices without a path\n");
		}

		printf("The path from %d to %d has the largest cost less than infinity"
			" of %0.3f\n", largeS, largeD, largeCost);
		// table needs to be rebuilt for this source, it was likely overwritten
		graph_shortest_path(G, largeS);
		PrintPath(G, largeS, largeD);
		puts("");
		printf("Network diameter runtime: %g ms\n", 
			1000*((double)(end-start))/CLOCKS_PER_SEC);

	}

	if (GraphOperation == 3) { // multiple link-disjoint paths
		int isPath = 1;

		if (SourceVertex == -1) {
			fprintf(stderr, "SourceVertex was not specified (use -s flag)\n");
			graph_destruct(G);
			exit(1);
		}
		if (DestinationVertex == -1) {
			fprintf(stderr, "DestinationVertex was not specified (use -d flag)\n");
			graph_destruct(G);
			exit(1);
		}

		while (isPath) {
			graph_shortest_path(G, SourceVertex);
			// see if there still exists a shortest path
			if (G->ShortestDistance[DestinationVertex] == INF) {
				isPath = 0;
			}
			else {
				// display current shortest path
				printf("The cost to %d from %d is %0.3f\n", SourceVertex, 
					DestinationVertex, G->ShortestDistance[DestinationVertex]);
				PrintPath(G, SourceVertex, DestinationVertex);
				puts("");

				// remove current shortest path before looking for another
				RemovePath(G, SourceVertex, DestinationVertex);
				printf("This path has now been removed\n\n");
			}
		}

		printf("No more paths between %d and %d\n", SourceVertex, DestinationVertex);

	}


	// make sure graph actually made before trying to free it
	if (GraphType != -1) {
		graph_destruct(G);
	}

	return 0;
}


/* Read in command line arguments and store in global variables for easy
 * access by other functions.
 *
 * argc - number of command line arguments
 * argv - array of the command line arguments
 */
void getCommandLine (int argc, char **argv) {
	 int c, index;

	 while ((c = getopt(argc, argv, "g:n:a:h:s:d:vr:t")) != -1) {
		 switch(c) {
			 case 'g': 
			 	GraphType = atoi(optarg);
				if ((GraphType < 1) || (GraphType > 3)) {
					fprintf(stderr, "invalid graph type: %d\n", GraphType);
					exit(1);
				}
				if (GraphType == 1) {
					// NumVertices not set by user for this graph
					NumVertices = 7;
				}
				break;
		
			 case 'n': 
			  	 NumVertices = atoi(optarg);
				 if (NumVertices <= 0) {
					 fprintf(stderr, "invalid number of vertices %d\n", NumVertices);
					 exit(1);
				 }
				 break;
			 
			 case 'a': 
			 	AdjacentVertices = atoi(optarg);
				if ((AdjacentVertices <= 0) || (AdjacentVertices >= NumVertices)) {
					fprintf(stderr, "invalid number of adjacent vertices %d\n",
						AdjacentVertices);
					exit(1);
				}
				break;
			 
			 case 'h': 
			 	GraphOperation = atoi(optarg);			
				if ((GraphOperation < 1) || (GraphOperation > 3)) {
					fprintf(stderr, "invalid graph operation %d\n", GraphOperation);
					exit(1);
				}
				break;
			 
			 case 's': 
			 	SourceVertex = atoi(optarg);
			 	if ((SourceVertex < 0) || (SourceVertex >= NumVertices)) {
					fprintf(stderr, "invalid source vertex %d\n", SourceVertex);
					exit(1);
				}
			 	break;
			 
			 case 'd': 
			 	DestinationVertex = atoi(optarg);
			 	if ((DestinationVertex < 0) || (DestinationVertex >= NumVertices)) {
					 fprintf(stderr, "invalid destination vertex %d\n", DestinationVertex);
					 exit(1);
				}
			 	break;
			 
			 case 'v': 
			 	Verbose = TRUE;								
			 	break;
			 
			 case 'r': 
			 	Seed = atoi(optarg);
			 	break;

			 case 't':
			 	Testing = TRUE;
				break;

			 case '?':
			 	if (isprint(optopt)) {
					fprintf(stderr, "Unknown option %d.\n", optopt);
				}
				else {
					fprintf(stderr, "Unknown option character `\\x%x.\n", optopt);
				}
			
			default:
				puts("Lab6 command line options\n");
				puts("  -g [1|2|3]     Graph type");
				puts("  -n N           Number of vertices in graph");
				puts("  -a R           Approximate number of adjacent vertices 0<R<N");
				puts("  -h [1|2|3]     Graph operation");
				puts("  -s S           Number of the source vertex 0<=S<N");
				puts("  -d D           Number of the destination vertex 0<=D<N");
				puts("  -v             Enable verbose output");
				puts("  -r 1234567     Seed for the uniform random number generator");
				puts("  -t             Enable testing mode (prints adjacency matrix)");
				exit(1);
		 }
	 }
	 for (index = optind; index < argc; index++) {
		 printf("Non-option argument %s\n", argv[index]);
	 }
}


/* Prints out in text the shortest path in a graph from the source to a given
 * destination.
 *
 * G - the graph.
 * Source - the source vertex for the path to be printed.
 * Dest - the destination vertex for the path to be printed.
 */
void PrintPath(graph_t* G, int Source, int Dest) {
	if (Source == Dest) {
		printf("%d", Dest);
	}
	else {
		PrintPath(G, Source, G->Predecessor[Dest]);
		printf(" -- %d", Dest);
	}
}

/* Removes the shortest path between a given source and destination in a graph.
 *
 * G - the graph.
 * Source - the source vertex for the path to be removed.
 * Dest - the destination vertex for the path to be removed.
 */
void RemovePath(graph_t* G, int Source, int Dest) {
	if (G->Predecessor[Dest] == Source) {
		graph_remove_edge(G, Source, Dest);
	}
	else {
		RemovePath(G, Source, G->Predecessor[Dest]);
		graph_remove_edge(G, G->Predecessor[Dest], Dest);
	}
}

/*
typedef struct graph_tag {
	int vertCount;
	double** adjMat;
	
	// these are to be used for the implementation of Dijkstra's algorithm
	int source;
	double* ShortestDistance;
	int* Predecessor;
} graph_t;
*/



