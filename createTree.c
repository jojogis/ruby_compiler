#include "createTree.h"

int create_tree(char* filename)
{
	yyin = fopen(filename, "r");
	
	if(yyin == NULL)
		return -1;

	yyparse();
	fclose(yyin);
	return 0;
}
