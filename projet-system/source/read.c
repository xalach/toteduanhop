#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#include "read.h"
#include "out.h"
#include "global.h"
#include "xml_creator.h"

int is_compress(char * path)
{
	int bit = 0;
	int fd = open(path, O_RDONLY);
	if ( read(fd, &bit, 1) != 1 )
		exit(1);
	printf("le bit lu est : %d\n", bit);
	return bit;
}

struct file_info * get_file_info(char * path)
{

	struct stat statfile;
	stat(path, &statfile);

	struct file_info * newfile;
	newfile = (struct file_info *)malloc(sizeof(struct file_info));

	newfile->path = path;
	newfile->name = basename(path);
	newfile->create_time = ctime(&statfile.st_mtime);  	// se compile mal depuis eclipse
	sprintf(&newfile->mode, "%i", (int)statfile.st_mode);
	sprintf(&newfile->size,"%ld", htonl(statfile.st_size));	// plante niveau mémoire

	return newfile;
}

void get_files_directory(char * path, xmlNodePtr repcourant)	  // add parameter : xmlNodePtr ( repetoire courant )
{
	printf("ouverture du dossier : %s \n", path);
	struct stat statfile;
	DIR * d = opendir(path);
	struct dirent * infodir;

	while( (infodir = readdir(d)) != NULL)
	{
		char * fname = &infodir->d_name;
		stat(fname, &statfile);
		if (S_ISDIR (statfile.st_mode))
		{
			//if ( strcmp(fname,".") != 0 || strcmp(fname,"..") != 0 )
			printf("   * sous dossier : %s - \n", fname);
			//get_files_directory(fname, addFolder(fname, repcourant));
		}
		else
		{
			printf("   - fichier : %s - \n", fname);
			//addFile(fname,get_file_info(fname),repcourant,""); //get_data(file[i]);
		}
	}
	closedir(d);
}


// lis tous les fichiers passé en parametre par l'utilisateur
// lis recursivement les dossiers
void read_files(int nb_files, char * files[]) 
{
	//xmlNodePtr repcourant = createXml(".");

	struct stat statfile;
	int i;
	for(i=0; i<nb_files; i++)
	{
		stat(files[i], &statfile);
		if (S_ISREG(statfile.st_mode))
		{
			//addFile(basename(files[i]),get_file_info(files[i]),repcourant,""); //get_data(file[i]);
		}
		if (S_ISDIR (statfile.st_mode))
		{
			//addFolder("name", repcourant);
			//get_files_directory(files[i], repcourant);
		}
	}
}

char * get_data(struct file_info * file)
{
	long s = ntohl(atoi(file->size));
	FILE * fr = fopen(file->path, "r");
	char * data = malloc(s);
	if( fread(data, s, s, fr) < s )
		perror("erreur dans la récupération des donnés");
	fclose(fr);
	return data;
}
