#include "global.h"
#include "out.h"

/**********************************************************************
 * 	PILE
 **********************************************************************/

struct element_pile * entete_pile(struct pile_file * pile)
{
	return pile->first_file;
}

struct file_info * info_element(struct element_pile * element)
{
	return &(element->info);
}

struct element_pile * next_element(struct element_pile * element)
{
	return element->next;
}

void empiler(struct pile_file * pile, char * p, char * n, time_t * ct, ushort * mode, long * size)
{
	struct element_pile * newfile;
	newfile = (struct element_pile *)malloc(sizeof(struct element_pile));
	newfile->info.path = *p;
	newfile->info.name = *n;
	newfile->info.create_time = *ct;
	newfile->info.mode = *mode;
	newfile->info.size = *size;

	newfile->next = pile->first_file;
	pile->first_file = newfile;

	pile->nb_file++;

	write_verbose("nouveau fichier empiler");
}


struct element_pile * depiler(struct pile_file * pile)
{
	struct element_pile * entete = entete_pile(pile);
	pile->first_file = next_element(entete);
	free(entete);
	return entete_pile(pile);
}

void liberer_pile(struct pile_file * pile)
{
	while( depiler(pile) != NULL );
}
