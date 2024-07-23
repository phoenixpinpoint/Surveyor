/** @file file.c
 * 
 * @brief The file module is a wrapper around jwerle/fs.c
 *
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>

#include <cwalk/cwalk.h>
#include <vec/vec.h>
#include <buffer/buffer.h>

//Looks in the deps/ directory and grabs files/folders
//Returns a vector of buffer_t's
vec_void_t srvyr_get_files_in_directory(char* dirPath)
{
    //Create a vector to store the fileNames as buffer_t's
    vec_void_t fileNames;
    vec_init(&fileNames);

    //Initialize the DIR d and dirent struct dir    
    DIR *d;
    struct dirent *dir;

    //open the dirpath
    //Ex: ./deps
    d = opendir(dirPath);

    if(d) {//If the directory is actually open
        while((dir = readdir(d)) != NULL)//For all files in directory
        {
            //If the its isn't . or ..
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                buffer_t* dirNameBuffer = buffer_new_with_copy(dir->d_name);//Create buffer
                vec_push(&fileNames, (void*)dirNameBuffer);//Add the buffer to the vector.
            }   
        }
    }

    //Close and return.
    closedir(d);
    return fileNames;
}

//Takes an vector of files and returns all the source files
//Returns a vector of buffer_t's
vec_void_t srvyr_get_source_files(vec_void_t files)
{
	vec_void_t sourceFiles;
	vec_init(&sourceFiles);
	buffer_t* filename;
	int i;
	if (files.length > 0)
	{	
		vec_foreach(&files, filename, i)
		{
			//Get the extension for the file
			const char* extension;
			size_t extLen;
			if(cwk_path_has_extension(filename->data))
			{
				cwk_path_get_extension(filename->data, &extension, &extLen);
					
				//If it ends in .c then add it to the vector.
				if(strcmp(extension, ".c") == 0)
				{
					vec_push(&sourceFiles, (void*)filename);
				}
				else if (strcmp(extension, ".cpp") == 0)
				{
					vec_push(&sourceFiles, (void*)filename);
				}
				else if (strcmp(extntion, ".cxx") == 0)
				{
					vec_push(&sourceFiles, (void*)filename);	
				}
			}
			
		}
	}
	return sourceFiles;
}


