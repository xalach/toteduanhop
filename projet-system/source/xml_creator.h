#include "global.h"


xmlNodePtr createXml(char*rootFolder, xmlDocPtr doc);

void addFile(char *name,struct file_info infos, xmlNodePtr currentNode,char *data);

xmlNodePtr addFolder(char *folderName, xmlNodePtr currentNode);

void printXml(xmlDocPtr doc);

void printElements(xmlNodePtr a_node);
