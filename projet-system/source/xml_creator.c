#include "xml_creator.h"
#include <stdio.h>
#include <string.h>


xmlNodePtr createXml(char *rootFolder, xmlDocPtr doc) //Créer le document xml(!= d'un fichier) et retourne un pointeur sur le répertoire racine de l'archive
{
  xmlNodePtr nodePtr = xmlNewNode(NULL,rootFolder);
  xmlDocSetRootElement(doc, nodePtr);
  return (nodePtr);
}


//Ajoute un fichier au répertoire courant(currentNode) avec les attribut de file_info correspondants.
void addFile(char *name, struct file_info infos, xmlNodePtr currentNode, char *data)
{
  printf("ADD fichier %s\n",name);
  xmlNodePtr filePtr = xmlAddChild(currentNode,xmlNewNode(NULL,name));
  xmlNewChild(filePtr,NULL,"Time",infos.create_time);
  xmlNewChild(filePtr,NULL,"Mode",&infos.mode);
  xmlNewChild(filePtr,NULL,"Size",&infos.size);
  xmlNewChild(filePtr,NULL,"Data",data);
  printf("END fichier\n");
}


//Ajoute un répertoire au répertoire courant(currentNode) et retourne un pointeur sur le nouveau répertoire.
xmlNodePtr addFolder(char *folderName, xmlNodePtr currentNode)
{
  return(xmlAddChild(currentNode,xmlNewNode(NULL,folderName)));
}
/*
xmlNodePtr getNode(char *name, xmlDocPtr doc)
{
  xmlNodePtr currentNode = xmlDocGetRootElement(doc); //récupère la node root
  xmlNodePtr resultNode = parcoursNode(currentNoden,name);
}

xmlNodePtr parcoursNode(xmlNodePtr a_node, char *name)
{
  xmlNodePtr currentNode = NULL;
    for (currentNode = a_node; currentNode; currentNode = currentNode->next) 
      {
	parcoursNode(currentNode->children,name);
      }
}*/


//Affiche l'arborescence du document xml passé en entrée
void printXml(xmlDocPtr doc)
{
    xmlNodePtr rootNode = NULL;
    
    rootNode = xmlDocGetRootElement(doc); //récupère la node root
    printf("ROOT = %s\n", rootNode->name);
    printElements(rootNode);

    xmlCleanupParser();
}

void printElements(xmlNodePtr  a_node)
{
    xmlNodePtr currentNode = NULL;
    printf("currentNode = %s\n",a_node->name);
    for (currentNode = a_node; currentNode; currentNode = currentNode->next) 
      {
	printf("Name: %s\n", currentNode->name);
	printf("Content : %s\n", currentNode->content);
	if(currentNode->children != NULL)
	  printElements(currentNode->children);
      }
    printf("----------\n");
}
