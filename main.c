/* * * * * * * * * * * * * * * * * 
		ERIC DANIEL LEGG
		CS 450 FALL 2016
* * * * * * * * * * * * * * * * * */

/* Library includes here.  */
#include <stdio.h>              
#include <stdlib.h>             
#include <stdbool.h>            
#include <stdint.h>             
#include <unistd.h>             
#include <ctype.h>              
#include <string.h>             
#include <malloc.h>

#include "file_in.h"
#include "allocation.h"

bool parse_command_line (int, char *[]);

int
main(int argc, char *argv[])
{
	bool success = parse_command_line (argc, argv);
}

bool
parse_command_line (int argc, char *argv[])
{
  int option;
  char* file;
  
  while ((option = getopt (argc, argv, "f:")) != -1)
    {
      switch (option)
        {
          case 'f':
            file = argv[2];		  
			read_file(file); 
            exit (0);
            break;
		  default:
            /* invalid flag */
              {
                fprintf (stderr, "Unknown option -%c\n", optopt);
                return false;
              }
            break;
        }
    }
  return true;
}