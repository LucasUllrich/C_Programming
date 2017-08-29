
#include "03_somelib.h"

int main (int argc, char *argv[])
{
	char *token, *cpy;

	if (argc != 2) {
		printf ("Usage: %s <someString>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	cpy = (char *) malloc (sizeof (char) * strlen (argv[1]));
	token = getToken (2, 5, argv[1], cpy);
	printf ("-- %s --\n", token);
	free (cpy);

	return 0;
}

