#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "record.h"
#include "global.h"

int main( int argc, char* argv[] )
{	
	extern int optind, optopt;
	extern char *optarg;
	int rtn;
	
// le string "abc:d:" représente les paramètre qu'on veut reconnaitre
// un ":" signifie que le paramêtre prend une valeur
	while( (rtn = getopt(argc, argv, "abc:d:")) != -1 )
	{
		printf( "%c : %s\n", rtn, optarg);
	}
	return 0;
}
