#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

int verbose;				// booléen pour activité la verbose du logiciel
int update;					// booléen pour précisé si l'archive doit être mis à jours

xmlDocPtr doc;

struct file_info
{
	char* name;
	char* create_time[100];//sizeof(time_t)];		// converti en Char* via ctime(&create_time);
	char* mode[100];//sizeof(mode_t)];				// converti en Char* via sprintf(%o)
	char* size[100];//sizeof(off_t)];				// à convertir avec htonl, convertir en long avec atoi() et ntohl()
};

struct file_info files[512];

#endif /* GLOBAL_H_ */
