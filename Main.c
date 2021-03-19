/*This program receives names of files from the user as arguments to the main program. The files will consist different numbers from 0-28. The program will
read through the numbers from the different files and then, will print out the instances of these numbers in the different files - that is, for each number
that appeared in a file, the program will specify how many times it appeared in each file and the names of the specific files in which the number was found.
The program will print this summary for the numbers in ascending order. */


#include "hash.h"



int main( int argc, char *argv[] )  {

	FILE *fp;
	int file_no, number,i;
	ptr ptr_array[RANGE]={0};
	
	

	if(argc<2) { /*If the user didn't enter file names, the program will end after a short message */
		fprintf(stderr,"%s","Not enough arguments\n");
		exit(0);
	}
	
	for(file_no=1;file_no<argc;file_no++) {/*each file given will be open once, processed and then closed before opening the next file */

		fp = fopen(argv[file_no], "r");
		
		if (fp == NULL) {/*If the opening has failed the program will end after a short message*/
    		
			fprintf(stderr,"%s","Cannot open file because there is a problem with the file, or it doesn't exist\n"); 
      		exit(0); 
  		} 
		
		
		while(fscanf(fp, "%d", &number) > 0 ) {/* for every number scanned in the file, we will call the function count_inst */
            count_inst(&ptr_array[number],argv[file_no]);
   		}

		fclose(fp);

	}
	

	for (i=0;i<RANGE;i++){/*for each pointer in the array which is not null, we will print the list it points to */
		if(ptr_array[i]!=0)
			print_lists(ptr_array[i],i);
	}
	
	for (i=0;i<RANGE;i++){/*for each pointer in the array which is not null, we will free the memory for the list it points to */
		if(ptr_array[i]!=0)
			free_lists(&ptr_array[i]);
	}
	printf("\n");
	return 0;

}




void count_inst(ptr *hptr, char* name) {/*creating the lists */
	
	ptr p1,p2,t;
    
	if (!(*hptr)) {/*if the list is empty */
		t= (ptr) malloc(sizeof(hash_struct));
		if(!t) {/*if the allocation failed */
			printf("\n Cannot allocate memory \n");
			exit(0);
		}
		/*updating the node's data*/
		t->file_name = name;
		t->count=1;
		t->next=NULL;
		*hptr = t;
		
		return;
		
	}
	p1=*hptr;
	 /*if the list is not empty, we'll add a node at the tail of the list */
	while(p1) {
		if(strcmp(p1->file_name,name)!=0){/*if the file name is different, p1 moves ahead */
			p2=p1;
			p1= p1->next;
		}
		else {/*if the file name is the same, add 1 to count */
			p1->count+=1;
			return;
		}
	}
	/*if we arrived at the end of the list, we'll create a new node and update the correct data */
	if (p1==NULL) {
		t= (ptr) malloc(sizeof(hash_struct));
		if(!t) {
			printf("\n Cannot allocate memory \n");
			exit(0);
		}
		t->file_name =name;
		t->count=1;
		p2->next = t;
		t->next=NULL;
		return;
	}
	
}	

void print_lists(ptr h, int i) {/*printing the lists information*/
	
	ptr curr= h;

	printf("\n %d appears in ", i);
	
	while (curr!=NULL) {	
	
		if(curr->count==1){/*if the number appears only once, we'll print "1 time" */
			if(curr==h)/*if it's the first node, there's no need for a comma */
				printf("file %s - 1 time", curr->file_name);
			else/*otherwise, print a comma before "file" */
				printf(", file %s - 1 time",curr->file_name);
		}
		else{/*if the number appears more than once, we'll print the number of instances and the word "times" */
			if(curr==h)
				printf("file %s - %d times", curr->file_name, curr->count);
			else
				printf(", file %s - %d times", curr->file_name, curr->count);

		}
		curr =curr->next;
	}

}



void free_lists(ptr *hptr) {/*Freeing the allocated memory for the lists */
	ptr p;
	/*while the list is not empty, p becomes the current node, the head of the list goes next and then p is freed  */
	while(*hptr) {
		p = *hptr;
		*hptr = p->next;
		free(p);
	}
}















































