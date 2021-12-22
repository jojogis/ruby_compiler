#include "xml.h"


//Здесь надо выводить дерево, построенное после 
void printTag(char *tag,char *str)
{
	fprintf(stdout,"\n<%s>",tag);
	fprintf(stdout,"\'%s\'",str);
	fprintf(stdout,"</%s>",tag);
}

// Только открывающий тег
void openTag(char *openTag)
{
	fprintf(stdout,"\n<%s>", openTag);
}

// Только закрывающий тег
void closeTag(char *closeTag)
{
	fprintf(stdout,"\n</%s>",closeTag);
}
