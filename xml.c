#include "xml.h"


//����� ���� �������� ������, ����������� ����� 
void printTag(char *tag,char *str)
{
	fprintf(stdout,"\n<%s>",tag);
	fprintf(stdout,"\'%s\'",str);
	fprintf(stdout,"</%s>",tag);
}

// ������ ����������� ���
void openTag(char *openTag)
{
	fprintf(stdout,"\n<%s>", openTag);
}

// ������ ����������� ���
void closeTag(char *closeTag)
{
	fprintf(stdout,"\n</%s>",closeTag);
}
