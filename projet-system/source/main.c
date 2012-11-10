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
	
	while( (rtn = getopt(argc, argv, "abcd:")) != -1 )
	{
		printf( "%c : %s\n", rtn, optarg+1);
	}
	return 0;
}
