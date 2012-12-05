#ifndef OUT_H_
#define OUT_H_

#include "global.h"

void write_verbose(char * message);

void afficher_file(struct file_info * file);

// créer un fichier à partir d'un file info
void create_file(struct file_info * file);
// créer un dossier à partir d'un file info
void create_directory(struct file_info * dir);

void create_folder_files(char * dirpath);
void create_tar_files(char * tarfile);

// MEMO
/*
 * char * d = "/home/arnaud/toteduanhop/projet-system/source/Debug";
	char * p = "/home/arnaud/toteduanhop/projet-system/source/Debug/Test/subdir.mk";
	int sd = strlen(d);
	int sp = strlen(p);
	//strncpy(p, &p[sd], sp-sd);
	printf("resultat : %s\n\n", strndup(p+sd+1, sp));
 *  */

#endif /* OUT_H_ */
