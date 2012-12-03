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
	char* create_time[sizeof(time_t)];		// converti en Char* via ctime(&create_time);
	char* mode[sizeof(mode_t)];				// converti en Char* via sprintf(%o)
	char* size[sizeof(off_t)];				// à convertir avec htonl, convertir en long avec atoi() et ntohl()
};

struct dir_info
{
	char* name;
	time_t create_time;		// convertible en Char* via ctime(&create_time);
	ushort mode;			// convertible en Char* via la fonction mode_view(mode) dans out.h
};

xmlDocPtr doc;


#endif /* GLOBAL_H_ */
