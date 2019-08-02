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
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name,file) == 0)
            {
                strcpy(result,path);
                strcat(result,"/");
                strcat(result,file);
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



