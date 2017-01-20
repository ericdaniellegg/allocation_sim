/* * * * * * * * * * * * * * * * * 
		ERIC DANIEL LEGG
		CS 450 FALL 2016
* * * * * * * * * * * * * * * * * */

#include <stdio.h>              
#include <stdbool.h>           
#include <stdint.h>            
#include <inttypes.h>           
#include <stdlib.h>

#include "file_in.h"
#include "allocation.h"


bool read_file(char* name) {		
	

	int number;
	int lines = 0; 

	int i, j;
	int row = 0;
	int column = 0;
	int number_count = 0;
	
	FILE *f = fopen(name, "r");

	if (f == 0)
    {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

	
	 while (!feof(f))
        {
            fscanf(f, "%i", &number);

            number_count++;
        }
		
    lines = number_count/3;
	
	int *info_array[3];
    
	for (i = 0; i < 3; i++)
	{
		info_array[i] = (int*)malloc(lines*sizeof(int));
	}

	if (fseek(f, 0, SEEK_SET)) 
    {
		puts("Error.");
		return 1;
    }

	int *n;
	while (!feof(f))
        {
            fscanf(f, "%i", &number);
			if(column < 3 && row < lines)
			{
				info_array[column][row] = number;

			}
			column++;

			if(column > 2){
				column = 0;

				row++;
			}

        }

	fclose(f);

    first_fit(info_array, row);
	best_fit(info_array, row);
	worst_fit(info_array, row);

	for(int i = 0; i < 3; i++)
	{
		free(info_array[i]);
	}

	return 0;
}

