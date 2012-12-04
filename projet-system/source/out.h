#ifndef OUT_H_
#define OUT_H_

#include "global.h"

void write_verbose(char * message);

void afficher_file(struct file_info * file);

void create_file(struct file_info * file);

void create_directory(struct file_info * dir);

// MEMO
/*
 * char * d = "/home/arnaud/toteduanhop/projet-system/source/Debug";
	char * p = "/home/arnaud/toteduanhop/projet-system/source/Debug/Test/subdir.mk";
	int sd = strlen(d);
	int sp = strlen(p);
	//strncpy(p, &p[sd], sp-sd);
	printf("resultat : %s\n\n", strndup(p+sd+1, sp));
 *  */

#endif /* OUT_H_ */
