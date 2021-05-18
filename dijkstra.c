/* dijkstra.c
 * Judson Cooper
 * MP6
 *
 * Purpose: This file contains the functions for creation and editing of a
 * 	graph, and implementation of Dijkstra's algorithm for finding the
 * 	shortest path in a graph.
 *
 * Assumptions: The graph will be created using the adjancency matrix 
 * 	representation. This matrix will hold the edge weights for the connections
 * 	between vertices. There will be a header block to hold the graph, which
 * 	will contain the adjacency matrix as well as a count of the number of
 * 	vertices in the graph. It is assumed that two unconnected vertices will
 * 	have a weight of infinity, and the edge between a vertice and itself
 * 	will have a weight of 0.
 *
 * Bugs: None known.
 */

#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

extern int Verbose; // used in ShortestPath for prints

// private functions for this file
int array_full (int array[], int size);

/* Creates the header block for the graph.
 *
 * NumVertices - the number of vertices the graph will contain
 *
 * Returns a pointer to the header block.
 */
graph_t* graph_construct (int NumVertices) {
	graph_t* newGraph = (graph_t*) malloc(sizeof(graph_t));
	int i = 0, j = 0;

	// initialize members of graph struct
	newGraph->vertCount = NumVertices;
	newGraph->adjMat = (double**) malloc(NumVertices * sizeof(double*));
	newGraph->source = -1; // invalid at the moment
	newGraph->ShortestDistance = (double*) malloc(NumVertices * sizeof(double));
	newGraph->Predecessor = (int*) malloc(NumVertices * sizeof(int));

	// initialize the elements of the adjMat matrix
	for (i = 0; i < NumVertices; i++) {
		newGraph->adjMat[i] = (double*) malloc(NumVertices * sizeof(double));
		for (j = 0; j < NumVertices; j++) {
			if (i == j) {
				newGraph->adjMat[i][j] = 0; // vertices are the same
			}
			else {
				newGraph->adjMat[i][j] = INF; // initialize as unconnected
			}
		}
	}

	return newGraph;
}

/* Frees the adjacency matrix for the graph, as well as the header block holding it.
 * 
 * G - the header block for the graph to be destroyed.
 */
void graph_destruct (graph_t *G) {
	int i = 0;

	// free the array for each vertice in the adjacency matrix first
	for (i = 0; i < G->vertCount; i++) {
		free(G->adjMat[i]);
	}

	// now free the main arrays
	free(G->adjMat);
	free(G->ShortestDistance);
	free(G->Predecessor);
	free(G);
}

/* Adds an edge between two vertices in a graph.
 *
 * G - the graph to be modified
 * link_src - the source vertice for the edge
 * link_dest - the destination vertice for the edge
 * link_weight - the weight that the edge will be
 */
void graph_add_edge (graph_t *G, int link_src, int link_dest, double link_weight) {
	G->adjMat[link_src][link_dest] = link_weight;
}

/* Removes an edge between two vertices in a graph.
 *
 * G - the graph to be modified
 * link_src - the source vertice for the edge to be removed
 * link_dest - the destination vertice for the edge to be removed
 */
void graph_remove_edge (graph_t *G, int link_src, int link_dest) {
	G->adjMat[link_src][link_dest] = INF;
}

/* Implements Dijkstra's algorithm to find the shortest path between the given
 * 	source vertex and each other vertice in the graph.
 * 
 * Inputs:
 *     source:  the source vertex in the set V of vertices
 *     G:       a graph data structure that includes at least
 *         a.  count of number of vertices in the set V
 *         b.  either an adjacency matrix or adjacency lists
 *
 *           The code below assumes G contains a pointer to the matrix 
 *           T[ link_source ] [ link_destination ]
 *           but modifying the code to use adjacency lists is easy
 *
 * Outputs (also passed as inputs because function void):
 *     ShortestDistance[]: an array for the path cost to each vertex from the 
 *                         source on the shortest path
 *     Predecessor[]:  an array for the predecessor vertex (or the upsteam
 *                     neighbor) on the shortest path to each vertex
 */
  
void graph_shortest_path(graph_t *G, int source) {
	int *W;

    int count_added = 1;   // for verbose prints
	 double MinDistance = INF, cost_to_u_via_w = INF;
	 int w = 0, u = 0, v = 0;
	 int i = 0;

	 // makes clear what the ShortestDistance and Predecessor arrays within
	 // G are in reference to, not really necessary for operation
	 G->source = source;

	 // initialize W, the set of confirmed vertices
	 // 0 is unconfirmed, 1 is confirmed
	 W = (int*) malloc(G->vertCount * sizeof(int));

	 for (i = 0; i < G->vertCount; i++) {
		 W[i] = 0;
	 }

    if (Verbose) {
        printf("Starting at node %d\n", source);
    }

    // W is a set indicating which vertices have been confirmed, that is,
    //   the vertices for which we have found the shortest distance

    // Initialize W and ShortestDistance[u] as follows:
    W[source] = 1;
    
	 G->ShortestDistance[source] = 0;
    // for (each u in V - {source} )
	 for (u = 0; u < G->vertCount; u++) {
		 // it shouldn't matter what the values for the source 'u' are, they
		 // will be ignored anyway
       	G->ShortestDistance[u] = G->adjMat[source][u];
		   G->Predecessor[u] = source;
    }

    // repeatedly enlarge W until W includes all vertices in V 
    // while (W != V)
	 while (array_full(W, G->vertCount) == 0) { // W == V when its full
        // find the vertex w in V - W at the minimum distance from source
        MinDistance = INF; 
        w = -1; // w = invalid vertex
        // for (each v in V - W)		
		  for (v = 0; v < G->vertCount; v++) {
			  if (W[v] == 0) {
           	   if (G->ShortestDistance[v] < MinDistance) {
               	 MinDistance = G->ShortestDistance[v];
            	    w = v;
          	 	}
			  }
        }
		  if (w == -1) {
			  // w not found
			  break;
		  }

        // if a vertex w was found, add w to W, the confirmed set
        // W = W union {w};
		  	W[w] = 1;
        	if (Verbose) {
           	count_added++;
           	printf(" %d added with cost %g\n", w, MinDistance);
     		}

       	// update the shortest distances to vertices in V - W via w 
     		// for (each u in V - W) {
		  	for (u = 0; u < G->vertCount; u++) {
			  	if (W[u] == 0) {
        			// if vertex u is a neighbor of w
      	      if (G->adjMat[w][u] < INF) {
           	 	   cost_to_u_via_w = G->ShortestDistance[w] + G->adjMat[w][u];
              	   if (cost_to_u_via_w < G->ShortestDistance[u]) {
                 		G->ShortestDistance[u] = cost_to_u_via_w;
							G->Predecessor[u] = w;
                 	   if (Verbose) {
                    	   printf("\t%d has lower cost %g with predecessor %d\n", 
									u, cost_to_u_via_w, w);
                    	}
                	}
            	}
			  }
        }
    }

    if (Verbose) {
        printf("Found %d nodes, including source\n", count_added);
    }

	 free(W);
	 W = NULL;
}

/* Prints the adjacency matrix of the graph for debugging purposes.
 *
 * G - the graph to be printed
 */
void graph_debug_print (graph_t *G) {
	int i = 0, j = 0;

	printf("Adjacency matrix for graph of %d vertices:\n\n", G->vertCount);
	printf("\t");
	// print row listing all vertices
	for (i = 0; i < G->vertCount; i++) {
		printf("%d\t", i);
	}
	puts("");
	
	// make new row for each vertice, and print the weight of each edge
	// with every other vertice in the graph
	for (i = 0; i < G->vertCount; i++) {
		printf("%d\t", i);
		for (j = 0; j < G->vertCount; j++) {
			if (G->adjMat[i][j] == INF) {
				// looks bad if INF printed normally
				printf("INF\t");
			}
			else {
				printf("%0.3f\t", G->adjMat[i][j]);
			}
		}
		puts("");
	}
}

/* Determines if a given array is full or not. Assumes that for an array to be
 * full, all values must be nonzero. The presence of a zero indicates the array
 * is not full.
 *
 * array - the array to be analyzed.
 * size - the size of the array.
 *
 * Returns the status of whether the array is full or not as an int.
 * 	0 - not full
 * 	1 - full
 */
int array_full (int array[], int size) {
	int i = 0;

	for (i = 0; i < size; i++) {
		if (array[i] == 0) {
			// not full if any zeros contained, return
			return 0;
		}
	}
	// no zeros found, is full
	return 1;
}




