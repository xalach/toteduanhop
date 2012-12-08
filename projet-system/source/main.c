#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <string.h>

#include "record.h"
#include "global.h"
#include "out.h"
#include "read.h"
#include "xml_creator.h"

int main( int argc, char* argv[] )
{
	verbose = update = 0;
	char * currentdirectory = realpath(".",NULL);
	char * destpath; // chemin de destination du fichier tar
/*
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
	xmlSaveFormatFileEnc("toto.tar",doc,"utf-8",1);*/


// Gestion des options
	extern int optind, optopt;
	extern char *optarg;
	int opt;
// le string "hvc:tr:u:x:f:zd:sm:" représente les paramètre qu'on veut reconnaitre
// un ":" signifie que le paramêtre prend une valeur après

	printf("argc = %d\n", argc);

	if (argc > 1)
	{
		while( (opt = getopt(argc, argv, "hvc:tr:u:x:f::zd:sm:")) != -1 )
		{
			char ** flist;
			int nbfile;
			printf( "%c - %d - %d : %s\n", opt, optind, optopt, optarg);
			switch(opt)
			{
				case 'h':
					afficher_help();
					return 0;
				case 'v':
					verbose = 1;
					break;

		// Creation archive
				case 'c':
					flist = &argv[optind-1];
					nbfile = argc - optind +1;
					read_files(destpath, nbfile, flist);
					//xmlDocDump(File* f, doc);
					break;

		// Affichage archive
				case 't':
					open_tar(optarg);
					printXml();
					return 0;
					break;

		// Ajouter fichiers à une archive
				case 'r':
					flist = &argv[optind];
					nbfile = argc - optind +2;
					add_files(optarg, nbfile, flist);
					break;

		// Ajouter l'option update
				case 'u':
						update = 1;
					break;

		// Extraire l'archive
				case 'x':
					nbfile = argc - optind +1;
			// destination précisé ?
					if ( nbfile > 1)
						chdir(argv[optind]);
					create_tar_files(optarg);
					chdir(currentdirectory);
					return 0;
					break;

		// Choisir un fichier de sortie
				case 'f':
					if (optarg != NULL)
						destpath = argv[optind-1];
					else
						destpath = default_tar_name();
					break;

		// Compression de l'archive
				case 'z':
					//compress_tar();
					break;

		// Supression d'un fichier
				case 'd':
					//delete_tar(optarg);
					break;

		// Retirer des "0" en trop
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
