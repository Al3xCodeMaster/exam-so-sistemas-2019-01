#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int searchFile(const char * file,const char*path)
{
    DIR *d;
    struct dirent *dir;
    char result[PATH_MAX];

    d = opendir(path);

    if(d)
    {   
        if(access(path,X_OK) == -1)
        {
	   fprintf(stderr,"Error, no se puede ejecutar el programa por problema de permisos\n");
  	   exit(EXIT_FAILURE);
        }
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name,file) == 0)
            {
                strcpy(result,path);
                strcat(result,"/");
                strcat(result,file);
		printf("%s\n",result);
                closedir(d);
		execl(result,file,NULL);
            }
        }
        closedir(d);
        return -1;   
    }else
    {
        return -1;
    }    
    
}



