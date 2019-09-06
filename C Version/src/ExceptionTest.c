#include "Exception.h"
#include <stdio.h>
#include <stdlib.h>






int main(int argc, char const *argv[])
{
	int* v = NULL;

	try
	{
		//v = malloc(sizeof(unsigned));

		if(v == NULL)
		{
			throw(__NullPointerException__);
		}
	}
	catch(NullPointerException)
	{

		puts(NullPointerException.message);
	}


	
	return 0;
}