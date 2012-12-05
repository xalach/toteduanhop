#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
 #include <errno.h>

#include "out.h"
#include "xml_creator.h"


void write_verbose(char * message)
{
	if( verbose == 1)
		printf("%s\n", message);
}

void afficher_file(struct file_info * file)
{

	printf("******** %s *********\n", file->name);
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
	if ( utime(dir->name, NULL) != 0 )
		printf("erreur dans le changement de date");
	printf("dossier créer\n");
}

void create_folder_files(char * dirpath)
{
	struct file_info **flist;
	int n;
	n = tar_folder_files(dirpath, &flist);
	if ( n > 0 )
	{
	   chdir(dirpath);
	   int i=0;
	   while ( i < n)
	   {
		   mode_t mf = ntohs(atoi(&flist[i]->mode));
		   if (S_ISREG(mf))
			{
			   create_file(flist[i]);
			}
			if (S_ISDIR (mf))
			{
				create_directory(flist[i]);
				create_folder_files(flist[i]->name);
			}
	   }
	   chdir("..");
	}
}

void create_tar_files(char * tarfile)
{
	open_tar(tarfile);
	struct file_info **flist;
	int n = tar_root_files(&flist);
	if ( n > 0 )
	{
	   int i=0;
	   while ( i < n)
	   {
		   mode_t mf = ntohs(atoi(&flist[i]->mode));
		   if (S_ISREG(mf))
			{
			   create_file(flist[i]);
			}
			if (S_ISDIR (mf))
			{
				create_directory(flist[i]);
				create_folder_files(flist[i]->name);
			}
	   }
	}
	// else le tar est vide
}
