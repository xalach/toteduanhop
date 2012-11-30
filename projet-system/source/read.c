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

struct file_info * get_file_info(char * path) // add parameter : xmlNodePtr ( repetoire courant )
{
	printf("-   - ficher : %s \n", path);
	struct stat statfile;
	stat(path, &statfile);

	struct file_info * newfile;
	newfile = (struct file_info *)malloc(sizeof(struct file_info));
	newfile->path = path;
	newfile->name = path;
	//newfile->create_time = statfile.st_mtime;  	// se compile mal depuis eclipse
	newfile->mode = statfile.st_mode;
	newfile->size = htonl(statfile.st_size);

	return newfile;
}

void get_files_directory(char * path)	  // add parameter : xmlNodePtr ( repetoire courant )
{
	printf("ouverture du dossier : %s \n", path);
	begin_dir(path);
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
			//get_files_directory(fname,addFolder(char* NewFolderName, xmlNodePtr repertoireCourant));
		}
		else
		{
			printf("   - fichier : %s - \n", fname);
			// get_file_info(fname);
			//xml a.ddFile(nomFichier,get_file_info(files[i]),repertoireCourant,DATA(char *)); //getata(file[i]);
		}
	}
	end_dir(path);
	closedir(d);
}


// lis tous
void read_files(int nb_files, char * files[]) 
{
	// xmlNodePtr repetoire courant = xmlCreate(".");

	struct stat statfile;
	int i;
	for(i=0; i<nb_files; i++)
	{
		stat(files[i], &statfile);
		if (S_ISREG(statfile.st_mode))
		{
			get_file_info(files[i]);
			//xml addFile(nomFichier,get_file_info(files[i]),repertoireCourant,DATA(char *)); //getata(file[i]);
		}
		if (S_ISDIR (statfile.st_mode))
		{
			//addFolder(char* NewFolderName, xmlNodePtr repertoireCourant)
			get_files_directory(files[i]/*AddFolder*/); 	// passé en parametre
		}
	}
}

void begin_dir(char * dir_name)
{
	// à compléter par Pierre
}

void end_dir(char * dir_name)
{
	// à completer par Pierre
}
