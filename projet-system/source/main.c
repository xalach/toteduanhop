#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>

#include "record.h"
#include "global.h"
#include "out.h"
#include "read.h"
#include "xml_creator.h"

int main( int argc, char* argv[] )
{	
	doc = xmlNewDoc("1.0");
	/*struct file_info fi = get_file_info("Test");
	afficher_file(&fi);
	create_directory(&fi);*/

	is_more_recent("read.o", "record.o");
	is_more_recent("Test", "/home/arnaud");
	is_more_recent("Test", "read.o");

	xmlNodePtr mynode = createXml("unnom");
	//get_files_directory("Test", mynode);

	/*
	//get_files_directory("Test");
	xmlNodePtr mynode = createXml("unnom", doc);
	mynode = addFolder("folder1", mynode);
	int i;
	for (i=0; i<5; i++)
	{
		addFile("file", fi, mynode, "donne");
	}
	printXml(doc);
	*/

		//struct file_info * fi = get_file_info("read.d");
		//afficher_file(fi);
		//free(fi);

	extern int optind, optopt;
	extern char *optarg;
	int opt;
// le string "hvc:tr:u:x:f:zd:sm:" représente les paramètre qu'on veut reconnaitre
// un ":" signifie que le paramêtre prend une valeur après
	if (argc > 1)
	{
		while( (opt = getopt(argc, argv, "hvc:tr:u:x:f:zd:sm:")) != -1 )
		{
			printf( "%c - %d - %d : %s\n", opt, optind, optopt, optarg);
			switch(opt)
			{
				case 'h':
					//afficher l'aide (présent dans un fichier)
					return 0;
				case 'v':
					verbose = 1;
					break;
				case 'c':
					//créer une archive tar avec les fichier dans "optarg" 
					break;
				case 't':
					//afficher l'archive
					break;
				case 'r':
					//add_tar(optarg);
					break;
				case 'u':
					//update_tar(optarg);
					break;
				case 'x':
					//extract_tar(optarg);
					break;
				case 'f':
					//add_file_tar(optar
					break;
				case 'z':
					//compress_tar();
					break;
				case 'd':
					//delete_tar(optarg);
					break;
				case 's':
					//save_space();
					break;
				case 'm':
					//get_diff();
					break;
				default:
					break;
			}
		}
		write_verbose("ceci est un test");

	}
	return 0;
}
