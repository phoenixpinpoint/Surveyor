#ifndef SURVEYOR_H
#define SURVEYOR_H

#include <stdio.h>
#include <dirent.h> 

#include <buffer/buffer.h>
#include <parson/parson.h>
#include <vec/vec.h>
#include <fs/fs.h>

#include <cwalk/cwalk.h>

//Parses a JSON_Object(clib dependencies object)
//Adds each dependency to the vector.
vec_str_t getDependencies(vec_str_t dependencies, JSON_Object *dependencyObject);

//Looks in the deps/} directory and grabs files/folders
//Returns a vector of buffer_t's
vec_void_t getFilesInDirectory(char* dirPath);

//Looks in the deps/{dependency} directory and grabs all .c files. 
//Returns a vector of buffer_t's
vec_void_t getSourceFilesInDirectory(char* dirPath);

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path);

#endif
