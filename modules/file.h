/** @file file.h
 * 
 * @brief The file module is a wrapper around jwerle/fs.c
 
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */

#ifndef SURVEYOR_FILE_H
#define SURVEYOR_FILE_H

//Build Path Header Includes
//ie #include <stdlib.h>
#include<vec/vec.h>

//Local Headers
//ie #include "somefile.h"

//Variables


//Function Prototypes

//Looks in the deps/ directory and grabs files/folders
//Returns a vector of buffer_t's
vec_void_t srvyr_get_files_in_directory(char* dirPath);



#endif
