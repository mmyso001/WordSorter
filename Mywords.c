/*
*Meekaeel Mysorewala
* Description: This program takes a text file given from the command line and for the c s and f commands either counts the number 
* of words in the file, orders the words in ascii, or finds the amount of time a given substring appears. In order to parse from the command line, getopt is used.
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define YES 1
#define NO 0
#define n 10000
#define BUFFER_SIZE 1000

// method implemented to find how many words are in a file
int wordCount(char *str)
{
	int counter = 0;
	int s = NO;
	while(*str)
	{
		if(*str == '\n' || *str == '\t' || *str == ' ')
		{
			s = NO;
		}
		else if(s == NO)
		{
			s = YES;
			counter++;
		}
		str++;
	}
	return counter;
}

//breaks the file down into lines by string and sorts them into ascii order
void words(char *str, int numW)
{
	int i = 0;
	int j = 0;
	int a = 0;
	char temp[40];
	char *x;
	char strng[60][30];
	x = strtok(str, " ,.-");
	while(x != NULL)
	{
		strcpy(strng[a], x);
		x = strtok(NULL, " ,.-");
		a++;
	}
	for(i = 1; i < numW; i++)
	{
		for(j = 1; j <= numW - i; j ++)
		{
			if(strcmp(strng[j - 1] , strng[j]) > 0)
			{
				strcpy(temp, strng[j -1]);
				strcpy(strng[j -1], strng[j]);
				strcpy(strng[j], temp);
			}
		}
	}
	printf("\nThese are the words sorted in ASCII order\n");
	for(i = 0; i < numW; i++)
	{
		puts(strng[i]);
	}
	printf("\n\n");
}
// parses through the file and searches for the key word given on the terminal to find how many occurences there are
int numofTimes(FILE *file, const char *word)
{
	char str[BUFFER_SIZE];
    	char *pos;
	int index, count;
    
    	count = 0;

    
    	while ((fgets(str, BUFFER_SIZE, file)) != NULL)
    	{
        	index = 0;

        	while ((pos = strstr(str + index, word)) != NULL)
        	{
            		index = (pos - str) + 1;

            		count++;
        	}
    	}

    

		
	return count;
}
	
main (int argc, char *argv[])
{
	FILE *file;
	size_t numRead;
	int i = 0;
	int numberW = 0;
	char b[n];
	char s[100];
	int option;
	int subCount;
	file = fopen(argv[4], "r");
	if(file)
	{
		while((numRead = fread(b, 1, sizeof b, file)) > 0)
		{
			fwrite(b, 1, numRead, stdout);
		}
		if(ferror(file))
		{
			printf("There is an error reading the file");
		}
		
		
		fclose(file);
	}
	subCount = numofTimes(file,argv[3]);
	numberW = wordCount(b);
	while((option = getopt(argc, argv, "f:cs")) != -1)
	{
		switch(option)
		{
			case 's': 
				words(b, numberW);
				break;
			case 'c':
				printf("\nNumber of words in the text are: %d", numberW);
				break;
			case 'f':
				printf("\nKeyword appears %d times\n", subCount);
				break;
			case '?':
				printf("\nunknown command");
				break;
		}
	}
	return 0;
}
