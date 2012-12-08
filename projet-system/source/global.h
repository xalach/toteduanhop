#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>

const char * right_values[8];

char * tar_path;				// emplacement du tar à enregistrer
int verbose;				// booléen pour activité la verbose du logiciel
int update;					// booléen pour précisé si l'archive doit être mis à jours


xmlDocPtr doc;
xmlDocPtr doctest;

struct file_info
{
	char* name;
	char* create_time[sizeof(time_t)];		// converti en Char* via ctime(&create_time);
	char* mode[sizeof(mode_t)];				// converti en Char* via sprintf(%o)
	char* size[sizeof(off_t)];				// à convertir avec htonl, convertir en long avec atoi() et ntohl()
};



#endif /* GLOBAL_H_ */
