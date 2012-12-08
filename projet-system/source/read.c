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
void read_files(char * tarpath, int nb_files, char * files[])
{
	xmlNodePtr repcourant = createXml("root");
	struct stat statfile;
	int i;
	for(i=0; i<nb_files; i++)
	{
		if( stat(files[i], &statfile) == 0)
		{
			struct file_info fi = get_file_info(files[i]);
			printf("basename : %s\n", basename(files[i]));
			if (S_ISREG(statfile.st_mode))
				addFile(basename(files[i]),&fi , repcourant, get_data(&fi));
			else if (S_ISDIR (statfile.st_mode))
				get_files_directory(basename(files[i]), addFolder(basename(files[i]), &fi, repcourant));
		}
		else
		   afficher_erreur(files[i]);
	}
}

char * get_data(struct file_info * file)
{
	long s = ntohl(atoi(file->size));
	printf("fichier à récup : %s\n", file->name);
	FILE * fr = fopen(file->name, "r");
	//if (fr == NULL)
		//afficher_erreur(file->name);
	char * data = malloc(s);
	fread(data, s-1, 1, fr);
	fclose(fr);
	return data;
}

void add_files_directory(char * path, xmlNodePtr repcourant)
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
		  /* if( stat(fname, &statfile) == 0)
		   {
				struct file_info fi = get_file_info(fname);
				if(file_exist(fname) == 0 ||
						( update == 1 && is_more_recent(&fi,get_info_tar(fname)) ) )
				{
					if (S_ISDIR (statfile.st_mode))
						add_files_directory(fname, addFolder(fname, &fi, repcourant));
					else if (S_ISREG(statfile.st_mode))
						addFile(fname, &fi, repcourant, get_data(&fi));
				}
		   }
		   else
			   afficher_erreur(fname);

		   free(flist[i]);*/
		   i++;
	   }
	   free(flist);
	   chdir("..");
// retour au répértoir précédent
   }
}

void add_files(char * tarpath, int nb_files, char * files[])
{
	open_tar(tarpath);
	xmlNodePtr repcourant = createXml(basename(tarpath));
	struct stat statfile;
	int i;
	for(i=0; i<nb_files; i++)
	{
		if( stat(files[i], &statfile) == 0)
		{
			struct file_info fi = get_file_info(files[i]);
// si le fichier à ajouter n'est pas déjà dans l'archive
// ou l'option update est présent et il s'ajoute seulement si plus récent
		/*	if(file_exist(files[i]) == 0 ||
					( update == 1 && is_more_recent(&fi,get_info_tar(files[i])) ) )
			{
				if (S_ISREG(statfile.st_mode))
					addFile(basename(files[i]),fi , repcourant, get_data(files[i]));
				if (S_ISDIR (statfile.st_mode))
					add_files_directory(basename(files[i]), addFolder(basename(files[i]), &fi, repcourant));
			}*/
		}
		else
			afficher_erreur(files[i]);
	}
}

int is_more_recent(struct file_info * file1, struct file_info * file2)
{
	//time_t f1 = ntohl(atoi(&file1->create_time));
	//time_t f2 = ntohl(atoi(&file2->create_time));
	//return f1-f2 > 0 ? 1 : 0;
	return 0;
}
