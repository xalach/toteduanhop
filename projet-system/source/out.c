#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <errno.h>
#include <fcntl.h>

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

void afficher_erreur(char * info)
{
	perror(info);
	exit(1);
}

void afficher_help()
{

}

char * default_tar_name()
{
	time_t n = time(NULL);
	struct tm * t = localtime(&n);
	char * date = malloc(sizeof(char)*33);
	//char date[33];			// marche pas et c'est inexplicable
	strftime(date, 33, "Archive_%Y-%m-%d_%H-%M-%S.tarx", t);
	return date;
}


void create_file(char * parent, struct file_info * file)
{
	mode_t fmod = ntohs(atoi(&file->mode));
	int fd = open(file->name, O_WRONLY | O_CREAT, fmod);
	if (fd < 0 )
		afficher_erreur(file->name);

	FILE * fw = fdopen(fd, "w");
	if (fw == NULL)
		afficher_erreur(file->name);
	long fsize = ntohl(atol(&file->size));
	fwrite(get_data_tar_file(parent, file->name),fsize-1, fsize, fw);

	struct utimbuf chgtm;
	chgtm.modtime = ntohl(atoi(&file->create_time));
	if ( utime(file->name, &chgtm) != 0 )
		afficher_erreur(file->name);
	printf("fichier créer\n");
	fclose(fw);
	close(fd);
}

void create_directory(struct file_info * dir)
{
	mode_t dirmod = ntohs(atoi(&dir->mode));

	if ( mkdir(dir->name, NULL) != 0 )
		afficher_erreur(dir->name);

	struct utimbuf chgtm;
	chgtm.modtime = ntohl(atoi(&dir->create_time));
	if ( utime(dir->name, NULL) != 0 )
		afficher_erreur(dir->name);
	printf("dossier créer\n");
}

void create_folder_files(char * parent, char * dirpath)
{
	struct file_info flist[512];
	int n;
	n = tar_folder_files(parent, dirpath);
	if ( n > 0 )
	{
	   chdir(dirpath);
	   int i=0;
	   while ( i < n)
	   {
		   mode_t mf = ntohs(atoi(files[i].mode));
		   if (S_ISREG(mf))
			{
			   create_file(parent,&files[i]);
			}
			if (S_ISDIR (mf))
			{
				create_directory(&files[i]);
				create_folder_files(basename(dirpath), files[i].name);
			}
			i++;
	   }
	   chdir("..");
	}
}

void create_tar_files(char * tarpath)
{
	open_tar(tarpath);
	struct file_info flist[512];
	int n = tar_root_files();
	if ( n > 0 )
	{
	   int i=0;
	   while ( i < n)
	   {
			mode_t mf = ntohs(atoi(files[i].mode));
			printf("out : %s - %s - %s - %s\n",files[i].name, files[i].size, files[i].create_time, files[i].mode);
			printf("%d\n",mf);
			if (S_ISREG(mf))
			{
				create_file("root", &files[i]);
			}
			if (S_ISDIR (mf))
			{
				create_directory(&files[i]);
				create_folder_files(basename(tarpath), files[i].name);
			}
			i++;
	   }
	}
	//free(flist);
}
