#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void list_dir(const char *path)
	{
		DIR *dir = opendir(path);
		struct dirent *entry ;

		if (dir == NULL)
	       	{
       		 perror("opendir");
  	    	 return;
		}
	}

