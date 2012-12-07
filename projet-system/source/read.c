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
#include <limits.h>


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

struct file_info get_file_info(char * path)
{

	struct stat statfile;
	if ( stat(path, &statfile) == -1 )
		afficher_erreur(path);

	struct file_info newfile;
	newfile.name = basename(path);
	sprintf(&newfile.create_time, "%i", htonl(statfile.st_mtime));	// se compile mal depuis eclipse
	sprintf(&newfile.mode, "%i", htons(statfile.st_mode));
	sprintf(&newfile.size,"%ld", htonl(statfile.st_size));			// plante niveau mémoire

	return newfile;
}

void get_files_directory(char * path, xmlNodePtr repcourant)
{
// Récupère un tableau contenant la liste des fichiers et dossiers
// celon un ordre alphabétique pour retier "." et ".."
	struct dirent **flist;
	struct stat statfile;
	int n;

	n = scandir(path, &flist, 0, alphasort);
	if (n > 0)
	{
// changement de répétoire pour récupére fichiers et dossiers
		chdir(path);
		int i = 2;
		while ( i < n)
		{
		   char * fname = flist[i]->d_name;
		   if( stat(fname, &statfile) == 0)
		   {
				struct file_info fi = get_file_info(fname);
				if (S_ISDIR (statfile.st_mode))
					get_files_directory(fname, addFolder(fname, &fi, repcourant));
				else if (S_ISREG(statfile.st_mode))
					addFile(fname, &fi, repcourant, get_data(&fi));
		   }
		   else
			   afficher_erreur(fname);

		   free(flist[i]);
		   i++;
	   }
	   free(flist);
	   chdir("..");
// retour au répértoir précédent
   }

}


// lis tous les fichiers passé en parametre par l'utilisateur
// appel la lecture recursif lors d'un dossier
void read_files(int nb_files, char * files[]) 
{
	xmlNodePtr repcourant = createXml(".");

	struct stat statfile;
	int i;
	for(i=0; i<nb_files; i++)
	{
		stat(files[i], &statfile);
		if (S_ISREG(statfile.st_mode))
		{
			struct file_info fi = get_file_info(files[i]);
			//addFile(basename(files[i]),fi , repcourant, get_data(files[i]));
		}
		if (S_ISDIR (statfile.st_mode))
		{
		  //addFolder("name", repcourant);
			get_files_directory(files[i], repcourant);
		}
	}
}

char * get_data(struct file_info * file)
{
	long s = ntohl(atoi(file->size));
	FILE * fr = fopen(file->name, "r");
	if (fr == NULL)
		afficher_erreur(file->name);
	char * data = malloc(s);
	fread(data, s-1, 1, fr);
	fclose(fr);
	return data;
}

int is_more_recent(char * path1, char * path2)
{
	struct stat statfile;

	stat(path1, &statfile);
	time_t f1 = statfile.st_mtime;
	stat(path2, &statfile);
	time_t f2 = statfile.st_mtime;

	return f1-f2 > 0 ? 1 : 0;
}
