#include "mystring.h"
#include <stdio.h>
#include <stdlib.h> //added library

/*
 *   Implement the following functions: 
 * 
 *   You are NOT allowed to use any standard string functions such as 
 *   strlen, strcpy or strcmp or any other string function.
 */

/*
 *  mystrlen() calculates the length of the string s, 
 *  not including the terminating character '\0'.
 *  Returns: length of s.
 */

//DONE-04/02
int mystrlen (const char *s) 
{
	/* Complete the body of the function */
	int length = 0; //variable length 
	for(int i=0; ; i++)
	{
		if(s[i] != '\0') 
		{
			length++;
		}
		else
		{
			break;
		}
	
	}
	return length; 
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating 
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
//DONE-04/02
char  *mystrcpy (char *dst, const char *src)
{
	/* Complete the body of the function */
	//FIRST TAKE LENGTH OF STRING
	int len_str = mystrlen(src);

	//COPY WHOLE STRING <=
	for(int i=0;i<=len_str;i++)
	{ 
		dst[i] = src[i]; //make destination to be the string
	}

	return dst;
	
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns: 
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
//DONE-04/02
int mystrcmp(const char *s1, const char *s2)
{

	/* Complete the body of the function */
	int s1_len = mystrlen(s1);
	int s2_len = mystrlen(s2);
	int maximum_len_str;

	//STEP 1: COMPARE THE LENGTHS-DONE
	if(s1_len < s2_len)
	{
		maximum_len_str = s2_len;
	}

	//s1_len is greatest
	// s1 >= s2
	else
	{
		maximum_len_str = s1_len;
	}

	//STEP 2: LOOP AND COMPARE THE STRINGS
	for (int i = 0; i < maximum_len_str; ++i)
	{
		/* code */
		//s1 ==s2
		if(s1[i] == s2[i])
		{
			continue; //can't return otherwise would stop.
		}

		//s1 > s2
		else if (s1[i] > s2[i])
		{
			return 1;
				
		}
		//s1 < s2
		else if (s1[i] < s2[i])
		{
			return -1;
		}
	}

	//END-RETURN IF SAME
	return 0; //both are equal 
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s. 
 * The space for the new string is obtained using malloc.  
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate) 
 	     or null If the new string could not be created for 
	     any reason such as insufficient memory.
 */
//DONE-04/02
char *mystrdup(const char *s1)
{
	/* Complete the body of the function */
	int length_string = mystrlen(s1); 


	char *duplicate = (char *) malloc(sizeof(char)*(length_string+1)); //+1 for the null character. Reserve space for each char*numberofcharacter_including null

	if(duplicate == NULL) 
	{
		printf("New string cannot be created.Malloc failed! \n");
		return NULL; // not created- return NULL
	}

	//loop through string length(<=!!!) to create duplicate
	for(int i=0;i<=length_string;i++)
	{
		duplicate[i] = s1[i]; //copies all the letter in the string to the duplicate 
 	}

	return duplicate;
}

