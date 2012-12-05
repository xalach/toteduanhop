#ifndef READ_H_
#define READ_H_

#include <libxml/tree.h>

int is_compress(char * path);

// construit une structure file_info pour un path donné
struct file_info get_file_info(char * path);

// récupère tous les fichiers d'un dossier
// appel récursif pour lire tous la hiérarchie
void get_files_directory(char * path, xmlNodePtr repcourant)	;

// li tous les fichiers passé en paramêtre et effectue
// les actions appropriés
void read_files(int nb_files, char * files[]);

// retourne les donnée
char * get_data(struct file_info * file);

// test si le fichier path1 et plus récent que le fichier path2
int is_more_recent(char * path1, char * path2);

#endif /* READ_H_ */
