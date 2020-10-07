#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following are simple tests to help you.
 * You should develop more extensive tests to try and find bugs.
 */
int main()
{
	const int SIZE = 100;
	char buffer[SIZE];

	//LENGTH TESTS-DONE
	assert(mystrlen("") == 0);//TEST EMPTY STRING 29/01-yes
	assert(mystrlen("a") == 1); //works-01/02
	assert(mystrlen("cmpt 300") == 8); // This one works-yes
	assert(mystrlen("ilovecoding") == 11); //works
	assert(mystrlen("you're nice.") == 12); //works
	assert(mystrlen("@#!$%;") == 6 );//works


	//STRCPY AND CMP
	mystrcpy(buffer, "I am testing my string functions!"); //text->empty
	assert(strcmp(buffer, "I am testing my string functions!") == 0); //works 
	assert(mystrcmp(buffer, "ADDED THIS TEST") == 1); //added 1 as I > A   (-01/02)
	

	//COPY TEST
	int copy_size = 50;
	char copy[copy_size];
	mystrcpy(copy, "This course is fun!");
	printf("\nTest empty case: ");
	printf("%s\n",copy);
	
	//Overwrite
	mystrcpy(copy,"Added this for copy_again");
	assert(mystrcmp(copy,"Added this for copy_again") == 0); //overwrite works. 
	printf("\nOVERWRITE COPY AND TEST: \n%s\n",copy); //works

	
	//OTHER TESTS
	//strcpy
	char test_strcpy[30];
	mystrcpy(test_strcpy,"1230*&^%#$");
	assert(mystrcmp(test_strcpy,"1230*&^%#$")==0);


	//STRCMP
	assert(mystrcmp ("I love coding", "I love coding") == 0); //works
	assert(mystrcmp ("tauseef", "") == 1);//added test 29/01
	assert(mystrcmp("","") == 0); //test 01/02**
	assert(mystrcmp("ahmed","hmed") == -1); //differ by one letter in beg/end/middle(a<h)
	assert(mystrcmp("hmed","ahmed") == 1);

	assert(mystrcmp("ahmed","ahed") == 1); //works(m>e)



	//STRDUP(04/02)
	printf("\n%s\n",buffer);
	printf("\nDUPLICATE-TEST");
	mystrdup(buffer);
	printf("\nNEW STRING: ");
	printf("%s\n",buffer);

	//printf("\n");
	printf("\n%s\n",copy);

	//printf("Testing above\n");

	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));// Works
	assert (buffer != dupStr); //Works

	if (dupStr != NULL)
		free (dupStr);

	printf ("\nPassed VERY simple tests, remember to develop more tests.\n");

	return 0;
}

