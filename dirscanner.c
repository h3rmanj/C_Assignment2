#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "asciitable.h"
#include "dirscanner.h"

char *dir;
char *filenames[100];
int files = 0;

void listFiles ()
{
	DIR *d;
	struct dirent *dirent;

	char *asciiname = malloc(sizeof(char*) * strlen(dir) - 1);
	strncpy(asciiname, dir, strlen(dir) - 1);

	if ((d = opendir(dir)))
	{
		while ((dirent = readdir(d)))
		{
			if ((strcmp(".", dirent->d_name)) == 0 || (strcmp("..", dirent->d_name)) == 0)
				continue;
			if ((strncmp("part", dirent->d_name, 4)) != 0 || (strncmp(asciiname, dirent->d_name + 9, strlen(asciiname))) != 0)
				continue;

			filenames[files] = malloc(sizeof(char) * 50);
			strcpy(filenames[files], dir);
			strcat(filenames[files], dirent->d_name);
			files++;
		}

		closedir(d);
	}

	free(asciiname);
}

int getRow (char *filename)
{
	int r = filename[strlen(dir) + 7] - '0';
	return r;
}

int getCol (char *filename)
{
	int c = filename[strlen(dir) + 5] - '0';
	return c;
}

void setRowsAndCols (AsciiTable *table)
{
	table->rows = 0;
	table->cols = 0;

	for (int i = 0; i < files; i++)
	{
		int r = getRow(filenames[i]);
		int c = getCol(filenames[i]);

		if (table->rows < r)
			table->rows = r;
		if (table->cols < c)
			table->cols = c;
	}

	table->rows += 1;
	table->cols += 1;
}

void mallocTableData (AsciiTable *table)
{
	table->data = malloc(sizeof(char**) * table->rows);
	for (int i = 0; i < table->rows; i++)
		table->data[i] = malloc(sizeof(char*) * table->cols);
}

char* readFile (char *filename)
{
	FILE *fp;
	char *content = 0;
	long length;

	if ((fp = fopen (filename, "rb")))
	{
 		fseek (fp, 0, SEEK_END);
 		length = ftell (fp);
		fseek (fp, 0, SEEK_SET);
		content = malloc (length);
		if (content)
			fread (content, 1, length, fp);
		fclose (fp);
	}
	return content;
}

void fillTable (AsciiTable *table)
{
	for (int i = 0; i < files; i++)
	{
		int row = getRow(filenames[i]);
		int col = getCol(filenames[i]);
		table->data[row][col] = readFile(filenames[i]);
	}
}

AsciiTable* scanDir (char *dire)
{
	dir = malloc(sizeof(char*) * strlen(dire) + 1);
	strcpy(dir, dire);

	char *lastdirchar = malloc(sizeof(char*));
	strcpy(lastdirchar, dir + strlen(dir) - 1);
	if (strcmp("/", lastdirchar) != 0)
		strcat(dir, "/");
	free(lastdirchar);
	
	listFiles();
	if (files == 0)
	{
		free(dir);
		return NULL;
	}

	AsciiTable *table = malloc(sizeof(AsciiTable));
	setRowsAndCols(table);
	mallocTableData(table);
	fillTable(table);
	free(dir);

	for (int i = 0; i < files; i++)
		free(filenames[i]);

	return table;
}

void freeTable (AsciiTable *table)
{
	for (int i = 0; i < table->rows; i++)
	{
		for(int j = 0; j < table->cols; j++)
			free(table->data[i][j]);
		free(table->data[i]);
	}
	free(table->data);
	free(table);
}
