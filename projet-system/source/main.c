#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "record.h"
#include "global.h"
#include "out.h"
#include "read.h"

int main( int argc, char* argv[] )
{	
	verbose = 1;
	/*list_file = (struct pile_file *)malloc(sizeof (struct pile_file));
	list_file->nb_file = 0;
	list_file->first_file = NULL;*/

	get_file_info("/home/arnaud/test.tar");
	get_file_info("/home/arnaud/test1");
	get_file_info("/home/arnaud/test.tar");
	extern int optind, optopt;
	extern char *optarg;
	int opt;
	
	tar_path = "blabal/bibi";

// le string "abc:d:" représente les paramètre qu'on veut reconnaitre
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
