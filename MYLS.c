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

		while ((entry = readdir(dir)) != NULL)
		{
			if( strcoll(entry->d_name , ".") != 0 && strcoll(entry->d_name , "..") != 0 )
			{
				printf("%s\n",entry->d_name);
			}
		}
	}


	closedir(dir);
