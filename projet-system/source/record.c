#include "record.h"
#include <unistd.h>

int compress_archive()
{
	if( fork() == 0)
	{
		execlp("gzip", "gzip", "fichiertar");
		ajouter_flag(1);
	}
}

void ajouter_flag(int bit)
{
}
