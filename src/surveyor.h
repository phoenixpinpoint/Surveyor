#ifndef SURVEYOR_H
#define SURVEYOR_H

#include <stdio.h>
#include <dirent.h> 
#include <stdbool.h>

#include <buffer/buffer.h>
#include <parson/parson.h>
#include <vec/vec.h>
#include <fs/fs.h>
#include <ulog/logger.h>
#include <cwalk/cwalk.h>

#include "file.h"
#include "survey.h"

//Parses a JSON_Object(clib dependencies object)
//Adds each dependency to the vector.
vec_str_t getDependencies(vec_str_t dependencies, JSON_Object *dependencyObject);

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path);

//Gets a given file from a github repo.
char* srvyr_get_github_file(char* user, char* repo, char* file, char* version);

//Get Dependency Clib or Survey
survey_file_t* srvyr_get_dependency_survey(survey_file_t* survey, dependency_t* dependency);

//Install a given dependency
//int srvyr_install_dependency(char* dependency);

#endif
