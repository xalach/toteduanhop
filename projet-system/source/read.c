#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "read.h"
#include "out.h"
#include "global.h"

int is_compress(char * path)
{
	int bit = 0;
	int fd = open(path, O_RDONLY);
	read(fd, &bit, 1);
	printf("le bit lu est : %d\n", bit);
	return bit;
}

void get_file_info(char * path)
{
	stat(path, &file_info);
}
