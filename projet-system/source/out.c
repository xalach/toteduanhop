#include <stdio.h>
#include "out.h"
#include "global.h"

void write_verbose(char * message)
{
	if( verbose == 1)
		printf("%s\n", message);
}
