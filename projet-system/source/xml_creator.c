#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>
#include "global.h"
#include <stdio.h>
#include <string.h>


xmlNodePtr createXml(char *rootFolder) //Créer le document xml(!= d'un fichier) et retourne un pointeur sur le répertoire racine de l'archive
{
  xmlNodePtr nodePtr = xmlNewNode(NULL,rootFolder);
  xmlDocSetRootElement(xmlNewDoc("1.0"), nodePtr);
  return (nodePtr);
}


//Ajoute un fichier au répertoire courant(currentNode) avec les attribut de file_info correspondants.
void addFile(char *name, struct file_info infos, xmlNodePtr currentNode, char *data)
{
  xmlNodePtr filePtr = xmlAddChild(currentNode,xmlNewNode(NULL,name));
  xmlNewChild(filePtr,NULL,"Time",infos.create_time);
  xmlNewChild(filePtr,NULL,"Mode",infos.mode);
  xmlNewChild(filePtr,NULL,"Size",infos.size);
  xmlNewChild(filePtr,NULL,"Data",data);
}


//Ajoute un répertoire au répertoire courant(currentNode) et retourne un pointeur sur le nouveau répertoire.
xmlNodePtr addFolder(char *folderName, xmlNodePtr *currentNode)
{
  //xmlNodePtr currentNode =  
  return(xmlAddChild(currentNode,xmlNewNode(NULL,folderName)));
}
