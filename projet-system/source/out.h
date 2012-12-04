#ifndef OUT_H_
#define OUT_H_

#include "global.h"

void write_verbose(char * message);

void afficher_file(struct file_info * file);

void create_file(struct file_info * file);

void create_directory(struct file_info * dir);

#endif /* OUT_H_ */
