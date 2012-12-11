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
  xmlNodePtr filePtr = xmlAddChild(currentNode,xmlNewNode(NULL,name));
  xmlNewProp(filePtr,"Time",BAD_CAST infos->create_time);
  xmlNewProp(filePtr,"Mode",BAD_CAST infos->mode);
  xmlNewProp(filePtr,"Size",BAD_CAST infos->size);
  xmlNewProp(filePtr,"Data",BAD_CAST data);
}


//Ajoute un répertoire au répertoire courant(currentNode) et retourne un pointeur sur le nouveau répertoire.
xmlNodePtr addFolder(char *folderName, struct file_info *infos, xmlNodePtr currentNode)
{
  xmlNodePtr folderPtr = xmlAddChild(currentNode,xmlNewNode(NULL,folderName));
  xmlNewProp(folderPtr,"Time",BAD_CAST infos->create_time);
  xmlNewProp(folderPtr,"Mode",BAD_CAST infos->mode);
  xmlNewProp(folderPtr,"Size",BAD_CAST infos->size);
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
		if(xmlGetProp(a_node,"Data") == NULL) //répertoire
		{
		  char indent[100] ;
		sprintf(indent,"| %s",indentation);
		if(xmlStrcmp(a_node->name,(BAD_CAST "text")) != 0)
		{
		  printf("%s%s \n", indentation, a_node->name);
	  }
		  if(a_node->children != NULL )
		  {
				printElements(a_node->children,indent,i);
			}	
		  if (a_node->next != NULL)
		  {
			printElements(a_node->next,indentation,i);
		  }
		}
		else if(xmlGetProp(a_node,"Time")!=NULL) //fichier
		{
		 if(xmlStrcmp(a_node->name,(BAD_CAST "text")) != 0)
		{
		  printf("%s%s \n", indentation, a_node->name);
	  }
		  if (a_node->next != NULL)
		  {
			printElements(a_node->next,indentation,i);
		  }
}
     /* int j;
      xmlNodePtr currentNode = NULL;
      for (currentNode = a_node->children; currentNode; currentNode = currentNode->next) 
      {
        printf("%s%s \n", indentation, currentNode->name);
        if(currentNode->children != NULL) 
        {
          indentation = strcat(indentation,"| ");
          printElements(currentNode->children,indentation,i);
        }
      }*/
  }


int tar_root_files(struct file_info ** files) //retourne le nombre d'élément à la racine et remplit le tableau des files_infos
{
  xmlNodePtr rootNode = xmlDocGetRootElement(doc);
  struct file_info tmp[512];
  int i = 0;
  xmlNodePtr currentNode = NULL;
  for(currentNode = rootNode->children ; currentNode ; currentNode = currentNode->next)
  {
    if (xmlGetProp(currentNode,"Time")!=NULL)
    {
      tmp[i].name = currentNode->name;
      *(tmp[i].size) = (char *)xmlGetProp(currentNode,"Size");
      *(tmp[i].create_time) = (char *)xmlGetProp(currentNode,"Time");
      *(tmp[i].mode) = (char *)xmlGetProp(currentNode,"Mode");
        //printf("%s - %s - %s - %s\n",tmp[i].name, tmp[i].size, tmp[i].create_time, tmp[i].mode);
      i++;
    }
  }
  files = &tmp;
  return i;
}

xmlXPathObjectPtr getnodeset (xmlChar *xpath)
{
  xmlXPathContextPtr context;
  xmlXPathObjectPtr result;

  context = xmlXPathNewContext(doc);
  if (context == NULL) {
    printf("Error in xmlXPathNewContext\n");
    return NULL;
  }
  result = xmlXPathEvalExpression(xpath, context);
  xmlXPathFreeContext(context);
  if (result == NULL) {
    printf("Error in xmlXPathEvalExpression\n");
    return NULL;
  }
  if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
    xmlXPathFreeObject(result);
    printf("No result\n");
    return NULL;
  }
  return result;
}

int tar_folder_files(char *pere, char * folder, struct file_info ** files)
{
  xmlNodeSetPtr nodeset;
  xmlXPathObjectPtr result;
  xmlNodePtr nodePtr;
  char path[100] ;
  sprintf(path,"//%s/%s",pere,folder);
  
  xmlChar *xpath = (xmlChar*) path;

  result = getnodeset (xpath);

  int i;
  if (result) 
  {
    nodeset = result->nodesetval;
    nodePtr = nodeset->nodeTab[0];
    xmlXPathFreeObject (result);
  }


  xmlNodePtr rootNode = nodePtr ;
  struct file_info tmp[512];
  i = 0;
  xmlNodePtr currentNode = NULL;
  for(currentNode = rootNode->children ; currentNode ; currentNode = currentNode->next)
  {
    if (xmlGetProp(currentNode,"Time")!=NULL)
    {
      tmp[i].name = currentNode->name;
      *(tmp[i].size) = (char *)xmlGetProp(currentNode,"Size");
      *(tmp[i].create_time) = (char *)xmlGetProp(currentNode,"Time");
      *(tmp[i].mode) = (char *)xmlGetProp(currentNode,"Mode");
        //printf("%s - %s - %s - %s\n",tmp[i].name, *tmp[i].size, *tmp[i].create_time, *tmp[i].mode);
      i++;
    }
  }
  files = &tmp;
  return i;
}

void delete_file(char * pere , char * name)
{
  xmlNodeSetPtr nodeset;
  xmlXPathObjectPtr result;
  xmlNodePtr nodePtr;
  char path[100] ;
  sprintf(path,"//%s/%s",pere,name);
  xmlChar *xpath = (xmlChar*) path;

  result = getnodeset (xpath);

  int i;
  if (result) 
  {
    nodeset = result->nodesetval;
    nodePtr = nodeset->nodeTab[0];
    xmlXPathFreeObject (result);
  }
  xmlUnlinkNode(nodePtr);
}

int exist_at_root(char* name)
{
  xmlNodePtr rootNode = xmlDocGetRootElement(doc);
  xmlNodePtr currentNode = NULL;
  for(currentNode = rootNode->children ; currentNode ; currentNode = currentNode->next)
  {
    if (xmlStrEqual(currentNode->name,BAD_CAST(name)))
    {
      printf("Trouvé\n");
    }
  }
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

char * get_data_tar_file(char *pere, char * file)
{
  xmlNodeSetPtr nodeset;
  xmlXPathObjectPtr result;
  xmlNodePtr nodePtr;
  char path[100] ;
  sprintf(path,"//%s/%s",pere,file);
  
  xmlChar *xpath = (xmlChar*) path;

  result = getnodeset (xpath);

  int i;
  if (result) 
  {
    nodeset = result->nodesetval;
    nodePtr = nodeset->nodeTab[0];
    xmlXPathFreeObject (result);
  }
  return ((char*)xmlGetProp(nodePtr,"Data"));
}
