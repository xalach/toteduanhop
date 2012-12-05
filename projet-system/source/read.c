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
	stat(path, &statfile);

	struct file_info newfile;
	//newfile = (struct file_info *)malloc(sizeof(struct file_info));

	newfile.path = realpath(path,NULL);
	newfile.name = basename(path);
	sprintf(&newfile.create_time, "%i", htonl(statfile.st_mtime));	// se compile mal depuis eclipse
	sprintf(&newfile.mode, "%i", htons(statfile.st_mode));
	sprintf(&newfile.size,"%ld", htonl(statfile.st_size));			// plante niveau mémoire

	return newfile;
}

void get_files_directory(char * path, xmlNodePtr repcourant)	  // add parameter : xmlNodePtr ( repetoire courant )
{
	//printf("\n dossier courant : %s\n", get_current_dir_name());
	//printf("ouverture du dossier : %s \n", path);

// UNE AUTRE APPROCHE POUR PARCOURIR UN DOSSIER
// 		plus haut niveau mais retire bien le "." et le ".."
//		un tri alphabetique permet de les exclure
//
//		pour le parcours recursif : deux solutions
   struct dirent **namelist;
   struct stat statfile;
   int n;

   n = scandir(path, &namelist, 0, alphasort);
   if (n < 0)
	   perror("scandir");
   else
   {
	   int i = 2;
	   chdir(path);
	   while ( i < n)
	   {
		   char * fname = namelist[i]->d_name;
		   if( stat(fname, &statfile) == 0)
		   {
			   if (S_ISDIR (statfile.st_mode))
				{
					///printf("   * sous dossier : %s - \n", fname);
				   struct file_info fi = get_file_info(fname);
				   afficher_file(&fi);
				   //get_files_directory(fname, addFolder(fname, repcourant));
					//get_files_directory(fname, addFolder(fname, fi, repcourant));

				}
				else //if (S_ISREG(statfile.st_mode))
				{
					//printf("   - fichier : %s -\n", fname);
					struct file_info fi = get_file_info(fname);
					afficher_file(&fi);
					//addFile(fname, fi, repcourant, "TOTO"); //get_data(file[i]);
				}
		   }
		   else
			   perror(fname);

		   free(namelist[i]);
		   i++;
	   }
	   free(namelist);
	   chdir("..");
   }

}


// lis tous les fichiers passé en parametre par l'utilisateur
// lis recursivement les dossiers
void read_files(int nb_files, char * files[]) 
{
  
  xmlNodePtr repcourant = createXml(".",doc);

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
	/*long s = ntohl(atoi(file->size));
	FILE * fr = fopen(file->path, "r");
	char * data;
	fgets(data, s, fr);
	//printf("data = %s\n", data);
		//perror("erreur dans la récupération des donnés");
	fclose(fr);
	return data;*/
	return "";
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
