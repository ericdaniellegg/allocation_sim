/* * * * * * * * * * * * * * * * * 
		ERIC DANIEL LEGG
		CS 450 FALL 2016
* * * * * * * * * * * * * * * * * */

#include <stdio.h>              
#include <stdbool.h>            
#include <stdint.h>             
#include <inttypes.h>           
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#include "file_in.h"
#include "allocation.h"

#define MEMORY_SIZE 1024

int memory[MEMORY_SIZE]; //global memory

info_struct *array_sort(info_struct *holes_info, int total_rows) {
	int i, j, k = 2, x;

	for(i = 0; i < total_rows; i++) 
	{
		for(j = i + 1; j < total_rows; j++) 
		{
			if(holes_info[i].size > holes_info[j].size)
			{
				int tmps = holes_info[i].size;
				int tmpb = holes_info[i].base;
				holes_info[i] = holes_info[j];
				holes_info[j].size = tmps;
				holes_info[j].base = tmpb;
			}
		}
	}
	
    return holes_info;
}

info_struct sort(info_struct* holes_info, int n) {
    int j,i;
	info_struct largest_hole;
	for (i = 0; i < MEMORY_SIZE; i++)
	{
		largest_hole.size = 0;
		largest_hole.base = 0;
	}

    for(i = 0;i < MEMORY_SIZE;i++) 
    {
        if (holes_info[i].size > largest_hole.size)
		{
			largest_hole.size = holes_info[i].size;
			largest_hole.base = holes_info[i].base;

		}
    }
	
	return largest_hole;
}

void
first_fit (int *information_block[], int rows) {
	int i, j, k, blah;
	bool current_process_fits = true;
	bool printsuccess = false;
	int dummy_counter = 0;
	int failed_process_number = -1;
	int failed_process_size = -1;
    int fragmentation = 0;
	
	process_info processes[rows+1];
	
	info_struct holes_info[MEMORY_SIZE];	//recyclable information struct array
	
	printf("First Fit simulation:\n");
	 
			
	for (i = 0; i < rows; i++)
	{
		processes[i].reference_number = information_block[0][i];
		
		if (information_block[1][i] == 1)
		{
			processes[i].allocate = true; //allocate
			processes[i].deallocate_number = -1;
			processes[i].process_size = information_block[2][i];
		} else {
			processes[i].allocate = false; //deallocate
			processes[i].process_size = -1; 
			processes[i].deallocate_number = information_block[2][i];
		}
		
	}
	
	for (i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0; 
	}
	
	while (current_process_fits == true) 
	{
		for (i = 0; i < rows; i++) 
		{

			int h = 0;

			for (k = 0; k < MEMORY_SIZE; k++) //holes struct array clean initiative
			{
				holes_info[k].size = 0;
				holes_info[k].base = -1;
			}
			
			
			for (j = 0; j < MEMORY_SIZE; j++) //iterating through every "byte" of memory
			{
				if (memory[j] == 0)
				{
					holes_info[h].size++; //finding the size of the hole				

					if (holes_info[h].base < 0)
					{
						holes_info[h].base = j; //setting the base for the hole
					}
				}
				if (memory[j] > 0 && j < MEMORY_SIZE && memory[j+1] == 0)
				{
					h++;	//start over and get info on next hole
				}
				

			}
			
			if (processes[i].allocate == true && current_process_fits == true)
			{
				info_struct largest_hole;
				largest_hole.size = 0;
				largest_hole.base = 0; 

				largest_hole = sort(holes_info, h); 

				if (largest_hole.size < processes[i].process_size) 
				{
					failed_process_number = processes[i].reference_number;
					failed_process_size = processes[i].process_size;
					current_process_fits = false;
				}
				if (current_process_fits == false)
				{
					break;
				}
			}

			if (processes[i].allocate == true && current_process_fits == true) 
			{
				for (j = 0; j < h + 1; j++) 
				{

					if (holes_info[j].size >= processes[i].process_size)
					{
						for (k = holes_info[j].base; k < (holes_info[j].base + processes[i].process_size); k++)
						{
							memory[k] = processes[i].reference_number; //allocating memory
						}
						break;
					}
				}
			}

			if (processes[i].allocate == false && current_process_fits == true)
			{
				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == processes[i].deallocate_number)
					{
						memory[j] = 0; //deallocating memory
					}
				}
			}
			
			dummy_counter++;
			
		}
		
		
		
		if (current_process_fits == false && printsuccess == false)
		{
			if (i != rows)
			{
				printf("Request %i failed trying to allocate %i bytes\n", failed_process_number, failed_process_size);
				
				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == 0)
					{
						fragmentation++;
					}
				}
				
				printf("External fragmentation is %i bytes\n", fragmentation);
			}
			break;
		}
		if (i == rows)
		{
			printsuccess = true;
		}
		if (dummy_counter == rows)
		{
			break;
		}
		
	}
	
	if (printsuccess == true)
	{
		printf("Success\n");
	}
}

void
worst_fit (int *information_block[], int rows) {
	int i, j, k, blah;
	bool current_process_fits = true;
	bool printsuccess = false;
	int dummy_counter = 0;
    int failed_process_number = -1;
	int failed_process_size = -1;
	int fragmentation = 0;
	
	process_info processes[rows+1];

	
	info_struct holes_info[MEMORY_SIZE];	
	 
	printf("Worst Fit simulation:\n");
			
	for (i = 0; i < rows; i++)
	{
		processes[i].reference_number = information_block[0][i];
		
		if (information_block[1][i] == 1)
		{
			processes[i].allocate = true; //allocate
			processes[i].deallocate_number = -1;
			processes[i].process_size = information_block[2][i];
		} else {
			processes[i].allocate = false; //deallocate
			processes[i].process_size = -1; 
			processes[i].deallocate_number = information_block[2][i];
		}
		
	}
	
	for (i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0; 
	}
	
	while (current_process_fits == true)
	{
		for (i = 0; i < rows; i++) 
		{	
			int h = 0; 
			
			for (k = 0; k < MEMORY_SIZE; k++) 
			{
				holes_info[k].size = 0;
				holes_info[k].base = -1;
			}
			
			
			for (j = 0; j < MEMORY_SIZE; j++) 
			{
				if (memory[j] == 0)
				{
					holes_info[h].size++; 

					if (holes_info[h].base < 0) 
					{
						holes_info[h].base = j; 
					}
				}
				if (memory[j] > 0 && j < MEMORY_SIZE && memory[j+1] == 0)
				{
					h++;
				}
				

			}
			
			if (processes[i].allocate == true) 
			{
				for (j = 0; j < h + 1; j++) 
				{

					info_struct largest_hole;
					largest_hole.size = 0;
					largest_hole.base = 0;

					largest_hole = sort(holes_info, h); 

					if (largest_hole.size < processes[i].process_size) 
					{
						failed_process_number = processes[i].reference_number;
						failed_process_size = processes[i].process_size;
						current_process_fits = false;
					}
				}
			}

			if (processes[i].allocate == true) 
			{
				info_struct largest_hole;
				largest_hole.size = 0;
				largest_hole.base = 0;

				largest_hole = sort(holes_info, h);

				if (largest_hole.size >= processes[i].process_size)
				{
					for (k = largest_hole.base; k < (largest_hole.base + processes[i].process_size); k++) 
					{

						memory[k] = processes[i].reference_number; //allocating memory
					}
				}
				
				if (current_process_fits == false)
				{
					break;
				}
			}

			if (processes[i].allocate == false)
			{

				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == processes[i].deallocate_number)
					{
						memory[j] = 0; //deallocating memory
					}
				}
			}
			
			dummy_counter++;
		}
		
		
		
		if (current_process_fits == false && printsuccess == false)
		{
			if (i != rows)
			{
				printf("Request %i failed trying to allocate %i bytes\n", failed_process_number, failed_process_size);
				
				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == 0)
					{
						fragmentation++;
					}
				}
				
				printf("External fragmentation is %i bytes\n", fragmentation);
			}
			break;
		}
		if (i == rows)
		{
			printsuccess = true;
		}
		if (dummy_counter == rows)
		{
			break;
		}
	}
	
	if (printsuccess == true)
	{
		printf("Success\n");
	}
}

void
best_fit (int *information_block[], int rows) {
	int i, j, k, blah, m;
	bool current_process_fits = true;
	bool printsuccess = false;
	int dummy_counter = 0;
	int failed_process_number = -1; 
	int failed_process_size = -1; 
    int fragmentation = 0;
	
	process_info processes[rows+1];
	
	info_struct holes_info[MEMORY_SIZE];
	
	printf("Best Fit simulation:\n");
			
	for (i = 0; i < rows; i++)
	{
		processes[i].reference_number = information_block[0][i];
		
		if (information_block[1][i] == 1)
		{
			processes[i].allocate = true; //allocate
			processes[i].deallocate_number = -1;
			processes[i].process_size = information_block[2][i];
		} else {
			processes[i].allocate = false; //deallocate
			processes[i].process_size = -1; 
			processes[i].deallocate_number = information_block[2][i];
		}
		
	}

	for (i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0; 
	}
	
	while (current_process_fits == true) 
	{
		for (i = 0; i < rows; i++) 
		{
			 
			int h = 0; 

			for (k = 0; k < MEMORY_SIZE; k++) 
			{
				holes_info[k].size = 0;
				holes_info[k].base = -1;
			}
			
			for (j = 0; j < MEMORY_SIZE; j++) 
			{
				if (memory[j] == 0)
				{
					holes_info[h].size++; 
					
					if (holes_info[h].base < 0) 
					{
						holes_info[h].base = j; 
					}
				}
				if (memory[j] > 0 && j < MEMORY_SIZE && memory[j+1] == 0)
				{
					h++;
				}

			}
			
			if (processes[i].allocate == true && current_process_fits == true)
			{
				info_struct largest_hole;
				largest_hole.size = 0;
				largest_hole.base = 0; 

				largest_hole = sort(holes_info, h); 

				if (largest_hole.size < processes[i].process_size) 
				{
					failed_process_number = processes[i].reference_number;
					failed_process_size = processes[i].process_size;
					current_process_fits = false;
				}
				
				if (current_process_fits == false)
				{
					break;
				}
			}

			if (processes[i].allocate == true && current_process_fits == true) 
			{ 
				info_struct *sort_yeah = array_sort(holes_info, h);
				
				for (j = 0; j < h + 1; j++)
				{			
					if (sort_yeah[j].size >= processes[i].process_size)
					{
						for (k = sort_yeah[j].base; k < (sort_yeah[j].base + processes[i].process_size); k++) 
						{

							memory[k] = processes[i].reference_number; //allocating memory
						}
						break;
					}
				}
			}

			if (processes[i].allocate == false && current_process_fits == true)
			{

				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == processes[i].deallocate_number)
					{
						memory[j] = 0; //deallocating memory
					}
				}
			}
			
			dummy_counter++;
			
		}
		
		if (current_process_fits == false && printsuccess == false)
		{
			if (i != rows)
			{
				printf("Request %i failed trying to allocate %i bytes\n", failed_process_number, failed_process_size);
				
				for (j = 0; j < MEMORY_SIZE; j++)
				{
					if (memory[j] == 0)
					{
						fragmentation++;
					}
				}
				
				printf("External fragmentation is %i bytes\n", fragmentation);
			}
			break;
		}
		if (i == rows)
		{
			printsuccess = true;
		}
			
		if (dummy_counter == rows)
		{
			break;
		}
		
	}
	
	if (printsuccess == true)
	{
		printf("Success\n");
	}
}