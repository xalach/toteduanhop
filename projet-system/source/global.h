#ifndef GLOBAL_H_
#define GLOBAL_H_


struct tar_header
{
	double size;
	int filecount;
};

char* tar_path;
int verbose;

#endif /* GLOBAL_H_ */
