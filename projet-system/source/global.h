#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char * right_values[8];

struct tar_header
{
	double size;
	int filecount;
};

char* tar_path;				// chemin de sortie du fichier tar, NULL sinon
int verbose;				// booléen pour activité la verbose du logiciel

struct file_info
{
	char* path;
	char* name;
	time_t create_time;		// convertible en Char* via ctime(&create_time);
	ushort mode;			// convertible en Char* via la fonction mode_view(mode) dans out.h
	long size;				// converti avec htonl
};

/**********************************************************************
 * 	PILE
 **********************************************************************/

/*
 // definir la structure de base d'une pile

struct element_pile
{
	struct file_info info;
	struct element_pile * next;
};

// la pile de fichier
struct pile_file
{
	int nb_file; 							// le nombre d'élément dans la pile
	struct element_pile * first_file;		// pointeur vers le premier fichier
};

struct element_pile * entete_pile(struct pile_file * pile);
struct file_info * info_element(struct element_pile * element);
struct element_pile * next_element(struct element_pile * element);
void empiler(struct pile_file * pile, char * p, char * n, time_t * ct, ushort * mode, long * size);
struct element_pile * depiler(struct pile_file * pile);
void liberer_pile(struct pile_file * pile);

struct pile_file * list_file; */


#endif /* GLOBAL_H_ */
