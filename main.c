#include <stdio.h>
#include "createTree.h"
#include "treePrint.h"

int main(int argc, char *argv[])
{
	FILE* tree;
	if(create_tree("test.txt") == -1)
	{
		printf("cannot open file!");
	}
	else
	{
		tree = freopen("tree.xml","w",stdout);
		tree_print();
	}
	return 0;
}
