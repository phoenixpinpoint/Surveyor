#include "surveyor.h"

#include <buffer/buffer.c>
#include <parson/parson.c>

#include <cwalk.c>

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path)
{
    printf("Opening %s", path);
    //Open clibs.json
    FILE *clib = fopen(path, "r");
    
    if(clib != NULL)//File is open.
    {
        printf("....success\n");
    }
    else {//File is not open.
        printf("....failed\n");
        return -1;
    }
}

int main() 
{
    printf("Surveyor v1.0\n");
    printf("=============\n");

    parseClib("clib.json\0");

    return 0;
}