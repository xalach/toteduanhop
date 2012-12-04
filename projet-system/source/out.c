#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
 #include <errno.h>


#include "out.h"

void write_verbose(char * message)
{
	if( verbose == 1)
		printf("%s\n", message);
}

void afficher_file(struct file_info * file)
{

	printf("******** %s *********\n", file->name);
	printf("*   Path : %s\n", file->path);

	time_t t = ntohl(atoi(&file->create_time));
	printf("*   date creation : %s", ctime(&t));
	printf("*   size : %ld\n", ntohl(atol(&file->size)));
	printf("*   Access mode 0%i\n", ntohs(atoi(&file->mode)));
	printf("**********************\n", file->name);
}

void create_file(struct file_info * file)
{



}

void create_directory(struct file_info * dir)
{
	mode_t dirmod = ntohs(atoi(&dir->mode));

	if ( mkdir("test", NULL) != 0 )
	{
		printf("erreur dans la creation dossier\n");
		if(errno == EEXIST)
			printf("le nom existe deja\n");
	}
	/*
	 * si le dossier existe dejà
	 * 	 chmod(dir->path, dirmod);
	 */

	struct utimbuf chgtm;
	chgtm.modtime = ntohl(atoi(&dir->create_time));
	if ( utime(dir->path, NULL) != 0 )
		printf("erreur dans le changement de date");
	printf("dossier créer\n");
}
