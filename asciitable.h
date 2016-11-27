#ifndef ASCIITABLE_H
#define ASCIITABLE_H

typedef struct AsciiTable
{
	int rows;
	int cols;
	char ***data;
} AsciiTable;

char* mergeAsciiTable (AsciiTable *table);

#endif
