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
	doc = xmlNewDoc("1.0");
	verbose = update = 0;
	char * currentdirectory = realpath(".",NULL);
	char * destpath; // chemin de destination du fichier tar

// Gestion des options
	extern int optind, optopt;
	extern char *optarg;
	int opt;
// le string "hvc:tr:u:x:f:zd:sm:" représente les paramètre qu'on veut reconnaitre
// un ":" signifie que le paramêtre prend une valeur après

	if (argc > 1)
	{
		while( (opt = getopt(argc, argv, "hvc:t:r:u:x:f::zd:sm:")) != -1 )
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
				{
					flist = &argv[optind-1];
					nbfile = argc - optind +1;
					read_files(destpath, nbfile, flist);
					if(destpath != NULL)
						xmlSaveFormatFileEnc(destpath,doc,"utf-8",1);
					else
					{
						FILE * fa = fdopen(1, "w");
						xmlDocDump(fa, doc);
					}
					return 0;
					break;
				}

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

	}
	return 0;
}
