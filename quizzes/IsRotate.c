#include <stdio.h>
#include <string.h>
#include "IsRotate.h"

int IsRotate(const char *s1, const char *s2)
{
	unsigned int len = 0;
	unsigned int n = 0;
	const char *runner1 = s1;
	const char *runner2 = s2;
	
	len = strlen(runner1);
	n = len;

	if ( strlen(runner2) != len)
	{
		return false;
	}

	if (0 == strncmp(runner1, runner2, n))
	{	
		return true;
	}
	
	while ('\0' != *runner2)
	{
		++runner2;
		--n;

		if(0 == strncmp(runner1, runner2, n))
		{	
			runner2 = s2;
			runner1 = s1 + n;
			
			if (0 == strncmp(runner1, runner2, len-n))
			{
				return true;
			}
		}
	}
		
	return false;	
}
