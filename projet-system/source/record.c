#include "record.h"
#include <unistd.h>

int compress_archive()
{
  execlp("gzip", "gzip", "fichiertar");
}

void ajouter_flag(int bit)
{
}
