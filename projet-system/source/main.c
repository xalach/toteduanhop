#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <string.h>

#include "record.h"
#include "global.h"
#include "out.h"
#include "read.h"
#include "xml_creator.h"

int main( int argc, char* argv[] )
{

	tar_path = default_tar_name();
	printf("%d : tar name = %s\n",strlen (tar_path), tar_path);
	struct file_info fi = get_file_info("test.txt");

	doc = xmlNewDoc("1.0");
	xmlNodePtr rootNode = createXml(".");
	xmlNodePtr mynode = rootNode ;
	
	addFile("rootFile", &fi, mynode, "donneRoot");
	mynode = addFolder("folder1",&fi, mynode);
	addFile("testFile1", &fi, mynode, "donne1");
	addFile("testFile2", &fi, mynode, "donne2");
	addFile("testFile3", &fi, mynode, "donne3");
	mynode = addFolder("folder2",&fi,rootNode);
	addFile("testFile4", &fi, mynode, "donne4");
	addFile("testFile5", &fi, mynode, "donne5");
	
	//open_tar("test.xml");
	printXml();
	xmlSaveFormatFileEnc("toto.tar",doc,"utf-8",1);


// Gestion des options
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
