#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>

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
	printf("date creation : %s\n", ctime(&file->create_time));
	printf("size : %d\n", ntohl(file->size));

	printf(" Access mode 0%o: ", file->mode);
	int i;
	   for(i = 6; i >= 0; i -=3)
		  printf("%s", right_values[(file->mode >> i) & 7]);
	   printf("\n");
}
