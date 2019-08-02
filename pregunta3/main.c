#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <linux/limits.h>
#include "search.h"

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr,"Error, no se suministro el nombre del programa a ejecutar\n");
        exit(EXIT_FAILURE);
    }

    char currentSearchPath[PATH_MAX];
    const char* PATH = getenv("PATH");
    
    strcpy(currentSearchPath,PATH);

    char *token = strtok(currentSearchPath,":");
    int status;
    while (token != NULL)
    {
        status = searchFile(argv[1],token);
        if(status == 0)
        {
            break;
        }
        token = strtok(NULL,":");
    }    
    
    fprintf(stderr,"Error, no se encuentra el programa en las rutas de PATH\n");
        
    return 0;
}
