/* * * * * * * * * * * * * * * * * 
		ERIC DANIEL LEGG
		CS 450 FALL 2016
* * * * * * * * * * * * * * * * * */

#ifndef scheduling_h
#define scheduling_h

extern void first_fit(int* [], int);
extern void worst_fit(int* [], int);
extern void best_fit(int* [], int);

typedef struct holes_info_struct {
	int size;
	int base;
} info_struct;

typedef struct process_info_type {
	int reference_number;
	bool allocate;
	int process_size;
	int deallocate_number; 
} process_info;

#endif
