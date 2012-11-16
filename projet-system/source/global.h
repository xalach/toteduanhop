#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct tar_header
{
	double size;
	int filecount;
};

char* tar_path;
int verbose;

struct stat file_info;

#endif /* GLOBAL_H_ */
