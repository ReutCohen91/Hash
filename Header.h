#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGE 29 /*this is the range of numbers the can appear in the files. (0-28 is a range of 29 numbers) */

typedef struct node * ptr; /*Defining the pointer type for the struct we'll use */


typedef struct node { /*Defining the struct for the hash table we'll use in this program */
	char* file_name;
	int count;
	ptr next;
} hash_struct;


void count_inst(ptr *hptr,char* name);/*This function configures the hash-table used for keeping track of all the instances of numbers in the different files. The function receives a ptr pointer which is the pointer to the struct we'll use and the name of the current opened file. The function does not return a value but simply creates different nodes in the list.*/
   
void print_lists(ptr h, int i); /*This function receives a ptr pointer and a number which is the index of the pointer in the pointer array and will print out the summary of the instances of numbers - how many instances were found in each file (unless none were found) */

void free_lists(ptr *hptr); /*This function frees the memory in which the lists are restored before the program ends.*/ 
