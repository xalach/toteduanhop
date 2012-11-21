#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <string.h>

//Ajoute un fichier à l'endroit du pointeur de writer donnée en paramètre
// -1 si erreur
int addFile(char *name, file_info infos, xmlTextWriterPtr writer)
{
  int rc ; //gestion des erreur de xml
  rc = xmlTextWriterStartElement(writer,name);
  // rc += xmlTetWriterWriteAttribut(writer,"time",infos.
}


//Ajoute un node de repertoire à l'endroit du pointeur writer 
int addFolder(char *name, xmlTextWriterPtr writer)
{

}
