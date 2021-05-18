/* MP6perfScript.c
 * Judson Cooper
 * C14711807
 * MP6
 * ECE 2230, Fall 2018
 *
 * This script runs the commands for the performance evaluation.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	// 1a
	system("./lab6 -g 2 -h 1 -n 15000 -s 0 -d 14999"); 
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 2 -h 1 -n 7500 -s 0 -d 7499"); 
	puts("\n \n \n "); fflush(stdin);

	// 1b
	system("./lab6 -g 3 -h 1 -n 15000 -s 0 -d 14999 -a 20"); 
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 1 -n 7500 -s 0 -d 7499 -a 20"); 
	puts("\n \n \n "); fflush(stdin);

	// 2
	system("./lab6 -g 3 -h 2 -n 250 -a 20");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 500 -a 20");
	puts("\n \n \n "); fflush(stdin);

	// 3
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 1");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 2");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 3");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 4");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 5");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 6");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 7");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 8");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 9");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 7 -r 10");
	puts("\n \n \n "); fflush(stdin);
	
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 1");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 2");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 3");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 4");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 5");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 6");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 7");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 8");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 9");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 2 -n 100 -a 20 -r 10");
	puts("\n \n \n "); fflush(stdin);

	// 4a
	system("./lab6 -g 2 -h 3 -n 15 -s 14 -d 0");
	puts("\n \n \n "); fflush(stdin);

	// 4b
	system("./lab6 -g 3 -h 3 -n 1000 -s 0 -d 999 -a 10");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 3 -n 1000 -s 0 -d 999 -a 20");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 3 -n 1000 -s 0 -d 999 -a 50");
	puts("\n \n \n "); fflush(stdin);
	system("./lab6 -g 3 -h 3 -n 1000 -s 0 -d 999 -a 100");
	puts("\n \n \n "); fflush(stdin);
	
	return 0;
}




