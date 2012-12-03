#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "out.h"

void write_verbose(char * message)
{
	if( verbose == 1)
		printf("%s\n", message);
}

void afficher_file(struct file_info * file)
{

	printf("******** %s *********\n", file->name);
	printf("*********************\n");
	printf("Path : %s\n", file->path);

	time_t t = atoi(&file->create_time);
	printf("date creation : %s\n", ctime(&t));

	printf("size : %ld\n", atol(&file->size));
	printf("Access mode 0%i\n", atoi(&file->mode));
	/*
	int i;
	   for(i = 6; i >= 0; i -=3)
		  printf("%s", right_values[(file->mode >> i) & 7]);
	   printf("\n");*/
}

