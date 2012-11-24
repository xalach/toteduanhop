#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>

#include "read.h"
#include "out.h"
#include "global.h"

int is_compress(char * path)
{
	int bit = 0;
	int fd = open(path, O_RDONLY);
	if ( read(fd, &bit, 1) != 1 )
		exit(1);
	printf("le bit lu est : %d\n", bit);
	return bit;
}

void get_file_info(char * path)
{
	struct stat statfile;
	stat(path, &statfile);
	//long size = htonl(statfile.st_size);
	//empiler(list_file, path, "jose", (time_t *)&statfile.st_mtim, (ushort *)&statfile.st_mode, &size);
}
