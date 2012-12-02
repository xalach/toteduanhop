#ifndef READ_H_
#define READ_H_

#include <libxml/tree.h>

int is_compress(char * path);

// construit une structure file_info pour un path donné
struct file_info * get_file_info(char * path);

// récupère tous les fichiers d'un dossier
// appel récursif pour lire tous la hiérarchie
void get_files_directory(char * path, xmlNodePtr repcourant)	;

// li tous les fichiers passé en paramêtre et effectue
// les actions appropriés
void read_files(int nb_files, char * files[]);

// marque le début et la fin de lecture d'un dossier
// utiliser pour construire la hiérarchie dans le fichier XML
void begin_dir(char * dir_name);
void end_dir(char * dir_name);

#endif /* READ_H_ */
