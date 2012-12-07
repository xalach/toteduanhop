#include <stdio.h>
#include <string.h>

#include "xml_creator.h"


xmlNodePtr createXml(char *rootFolder) //Créer le document xml(!= d'un fichier) et retourne un pointeur sur le répertoire racine de l'archive
{
  xmlNodePtr nodePtr = xmlNewNode(NULL,rootFolder);
  xmlDocSetRootElement(doc, nodePtr);
  return (nodePtr);
}


//Ajoute un fichier au répertoire courant(currentNode) avec les attribut de file_info correspondants.
void addFile(char *name, struct file_info *infos, xmlNodePtr currentNode, char *data)
{
  printf("ADD fichier %s\n",name);
  xmlNodePtr filePtr = xmlAddChild(currentNode,xmlNewNode(NULL,name));
  xmlNewProp(filePtr,"Time",infos->create_time);
  xmlNewProp(filePtr,"Mode",infos->mode);
  xmlNewProp(filePtr,"Size",infos->size);
  xmlNewProp(filePtr,"Data",data);
}


//Ajoute un répertoire au répertoire courant(currentNode) et retourne un pointeur sur le nouveau répertoire.
xmlNodePtr addFolder(char *folderName, struct file_info *infos, xmlNodePtr currentNode)
{
  xmlNodePtr folderPtr = xmlAddChild(currentNode,xmlNewNode(NULL,folderName));
  xmlNewProp(folderPtr,"Time",infos->create_time);
  xmlNewProp(folderPtr,"Mode",infos->mode);
  xmlNewProp(folderPtr,"Size",infos->size);
  return folderPtr ;
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
void printXml()
{
    xmlNodePtr rootNode = NULL;
    char indentation[100]= "";
    
    rootNode = xmlDocGetRootElement(doc); //récupère la node root
    printf("Archive : \n");
    printf("---------\n");
    printElements(rootNode,indentation,0);
    printf("\n");

    xmlCleanupParser();
}

void printElements(xmlNodePtr a_node, char *indentation, int i) 
{
  indentation = strcat(indentation,"| ");
  int j;
    xmlNodePtr currentNode = NULL;
    if(a_node->children != NULL) //C'est un répertoire
      {
	for (currentNode = a_node->children; currentNode; currentNode = currentNode->next) 
	  {
	    printf("%s%s \n", indentation, currentNode->name);
	    if(currentNode->children != NULL)
	      {
		printElements(currentNode->children,indentation,i);
	      }
	  }
      }
    else
      {
	printf("%s%s \n", indentation, a_node->name);
      }
}

int tar_root_files(struct file_info ** files)
{
  xmlNodePtr rootNode = xmlDocGetRootElement(doc);
  printf("%s\n",rootNode->name);
  xmlNodePtr currentNode = NULL;
  for(currentNode = rootNode->children ; currentNode ; currentNode = currentNode->next)
    {
      if(xmlGetProp(currentNode,"Data") != NULL)
	printf("%s\n",xmlGetProp(currentNode, "Data"));
    }
}

int tar_folder_files(char * folder, struct file_info ** files)
{
	return 0;
}

void open_tar(char * tarfile)
{
  doc = xmlParseFile(tarfile);
	
  if (doc == NULL ) 
    {
      fprintf(stderr,"Document not parsed successfully. \n");
      return;
    }

  xmlNodePtr cur = xmlDocGetRootElement(doc);
	
  if (cur == NULL) 
    {
      fprintf(stderr,"empty document\n");
      xmlFreeDoc(doc);
      return;
    }
}

char * get_data_tar_file(char * file)
{
	return "";
}
