#include <stdio.h>
#include <dirent.h> 

#include <buffer/buffer.h>
#include <parson/parson.h>
#include <vec/vec.h>
#include <fs/fs.h>

#include <cwalk/cwalk.h>

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path);