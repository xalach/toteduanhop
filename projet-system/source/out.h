#ifndef OUT_H_
#define OUT_H_

#include "global.h"

void write_verbose(char * message);
void afficher_file(struct file_info * file);
void afficher_erreur(char * info);
void afficher_help();
char * default_tar_name();

// créer un fichier à partir d'un file info
void create_file(char * parent, struct file_info * file);
// créer un dossier à partir d'un file info
void create_directory(struct file_info * dir);

void create_folder_files(char * parent, char * dirpath);
void create_tar_files(char * tarfile);

#endif /* OUT_H_ */
