#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("mode : %d\n", statfile.st_mode);
	printf("date : %s\n", ctime(&statfile.st_mtim));
	long test = htonl(statfile.st_size);
	printf("size : %d\n", ntohl(test));

	ushort mode = statfile.st_mode;
	//char * modestring = atoi(mode);
	char * accesses[] = {"...", "..x", ".w.", ".wx", "r..", "r.x", "rw.", "rwx"};
	//printf(" Access mode 0%s: ", modestring);
	printf(" Access mode 0%o: ", mode);
	int i;
	   for(i = 6; i >= 0; i -=3)
	      printf("%s", accesses[(mode >> i) & 7]);
	   printf("\n");
}
