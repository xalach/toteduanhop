#include "global.h"

/* j'ai fait une variable global doctest, et ça fonction. est toujours utile le passage en parametre ? */

xmlNodePtr createXml(char*rootFolder);

void addFile(char *name,struct file_info *infos, xmlNodePtr currentNode,char *data);

xmlNodePtr addFolder(char *folderName, struct file_info *infos, xmlNodePtr currentNode);

void printXml();

void printElements(xmlNodePtr a_node, char *indentation,int i);

/***************************************************
 * Fonction à faire pour Desarchiver
 ****************************************************/

int tar_root_files(struct file_info ** files);
// 		- files : tableau de structure file_info pour chaque fichiers et dossier à la racine
// 		- retourne la taille du tableau
// --> comme fait la fonction scandir

int tar_folder_files(char * folder, struct file_info ** files);
// 		-folder : le dossier à explorer
// 		-files : tableau de structure file_info pour chaque fichiers et dossier du "folder"
// 		- retourne la taille du tableau

void open_tar(char * tarfile);
// 		- ouvre le fichier "tarfile" et le place dans doc

char * get_data_tar_file(char * file);
// 		- retourne les donné du fichier "file"

// 	limite on peut retiré la fonction tar_root_files si tu me donne le nom du root

