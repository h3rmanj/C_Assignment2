#include <stdlib.h>
#include <string.h>
#include "asciitable.h"

char* mergeAsciiTable (AsciiTable *table)
{
	char *result = malloc(sizeof(char) * table->rows * table->cols * 901 + table->rows * 30 + 1);
	result[0] = '\0';
	for (int i = 0; i < table->rows; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < table->cols; k++)
			{
				char temp[31];
				int offset = j * 30;
				strncpy(temp, table->data[i][k] + offset, 30);
				temp[30] = '\0';
				strcat(result, temp);
			}
			strcat(result, "\n");
		}
	}
	return result;
}
