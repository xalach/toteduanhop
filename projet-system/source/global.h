#ifndef GLOBAL_H
#define GLOBAL_H


struct tar_header
{
	double size;
	int filecount;
};

char* tar_path;
const char * tar_ext = "tar";
int verbose;

#endif
