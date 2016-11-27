#include <stdio.h>
#include <stdlib.h>
#include "asciitable.h"
#include "dirscanner.h"


void saveChar (char *filename, char *text)
{
	FILE *fp;

	if (!(fp = fopen(filename, "w")))
	{
		printf("Please specify a valid file to save result to.\n");
		exit(-1);
	}

	fprintf(fp, "%s", text);

	fclose(fp);

	printf("Saved result to %s.\n", filename);
}

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please provide a directory with splitted ascii art (30x30 chars) to merge.\n");
		printf("Valid arguments are:\n");
		printf("1: Directory with names sort (Required)\n");
		printf("2: Directory to save result (Optional)\n");
		printf("If argument 2 is not provided result will be printed to the terminal.\n");
		exit(-1);
	}
	AsciiTable *table = scanDir(argv[1]);

	if (table == NULL)
	{
		printf("Please provide a valid directory with splitted ascii art (30x30 chars) to merge.\n");
		exit(-1);
	}

	char *ascii = mergeAsciiTable(table);

	if (argc > 2)
		saveChar(argv[2], ascii);
	else
		printf("%s", ascii);

	freeTable(table);
	free(ascii);
	return 0;
}
