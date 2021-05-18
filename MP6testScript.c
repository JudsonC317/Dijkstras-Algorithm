/* MP6testScript.c
 * Judson Cooper
 * MP6
 *
 * This file is a test script to quickly test the functionality of MP6. It
 * automatically runs several test cases using different sets of command line
 * options for the program to verify that the output is correct.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	// test graph building
	printf("Verify adjacency matrix is correct for graph 1:\n\n");
	system("./lab6 -g 1 -t"); 
	puts("\n \n \n ");
	
	printf("Verify edge between every vertice pair for graph 2:\n\n");
	system("./lab6 -g 2 -n 5 -t"); 
	puts("\n \n \n ");
	
	
	printf("Verify average adjacent vertices close to 5:\n\n");
	system("./lab6 -g 3 -n 1000 -a 5"); 
	puts("\n \n \n ");

	// test Dijkstra's
	printf("Verify cost is 11 and path is 1--2--3--5:\n\n");
	system("./lab6 -g 1 -h 1 -s 1 -d 5"); 
	puts("\n \n \n ");

	printf("Verify a path does not exist between these vertices\n\n");
	system("./lab6 -g 1 -h 1 -s 5 -d 1");
	puts("\n \n \n ");

	printf("Verify cost is 2172 and 11 vertices in path\n\n");
	system("./lab6 -g 2 -n 100 -h 1 -s 0 -d 99");
	puts("\n \n \n ");

	// test network diameter
	printf("Verfiy diameter is 21 and graph is not connected\n\n");
	system("./lab6 -g 1 -h 2");

	printf("Verify graph connected (no 'pair of vertices without a path' message\n\n");
	system("./lab6 -g 2 -n 100 -h 2");

	// test multiple link-disjoint paths
	printf("Verify 1--2--3--5 with cost 11 found first, and\n"
		"then 1--6--4--5 with cost 20\n");
	system("./lab6 -g 1 -h 3 -s 1 -d 5");

	return 0;
}




