
#include "03_somelib.h"

char * getToken (int start, int end, char *src, char *dest)
{
	assert (start < end);
	assert (end <= strlen (src));
	strncpy (dest, src, strlen (src));
	* (dest + end + 1) = '\0';

	return dest + start;
}

