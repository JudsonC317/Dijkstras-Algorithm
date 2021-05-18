/* dijkstra.h
 * Judson Cooper
 * MP6
 */

#include <float.h>

#define TRUE 1
#define FALSE 0
#define INF FLT_MAX

typedef struct graph_tag {
	int vertCount;
	double** adjMat;
	
	// these are to be used for the implementation of Dijkstra's algorithm
	int source;
	double* ShortestDistance;
	int* Predecessor;
} graph_t;

graph_t* graph_construct (int NumVertices);
void graph_destruct (graph_t *G);
void graph_add_edge (graph_t *G, int link_src, int link_dest, double link_weight);
void graph_remove_edge (graph_t *G, int link_src, int link_dest);
void graph_shortest_path (graph_t *G, int path_src);

void graph_debug_print (graph_t *G);
