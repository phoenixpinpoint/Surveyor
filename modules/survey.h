/** @file survey.h
 * 
 * @brief The basis of the survey module
 *
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */

#ifndef SURVEYOR_SURVEY_H
#define SURVEYOR_SURVEY_H

//Build Path Header Includes
#include <buffer/buffer.h>
#include <vec/vec.h>
#include <parson/parson.h>
#include <ulog/logger.h>

//Local Headers

//Variables and Data Structures
typedef struct survey_file {
	int clibFlag;
	buffer_t* surveyVersion;
	buffer_t* version;
	buffer_t* name;
	buffer_t* repo;
	buffer_t* type;
	buffer_t* install;
	buffer_t* uninstall;
	buffer_t* makefile;
	buffer_t* license;
	vec_void_t src;
    vec_void_t keywords;
	vec_void_t dependencies;
	vec_void_t development;
} survey_file_t;

typedef struct dependency {
	buffer_t* name;
	buffer_t* version;
} dependency_t;


//Vector to store the paths
vec_void_t srcPaths;


//Function Prototypes

// Intialize a SurveyFile Data Structure
survey_file_t* srvyr_survey_init(char* surveyVersion, char* name);

// Set the name of the survey.
void srvyr_set_survey_name(survey_file_t* survey, char* name);

// Set the version of the survey.
void srvyr_set_survey_version(survey_file_t* survey, char* version);

// Set the repo of the survey.
void srvyr_set_survey_repo(survey_file_t* survey, char* repo);

// Set the type of the survey.
void srvyr_set_survey_type(survey_file_t* survey, char* type);

// Set the surveyVersion of the survey.
void srvyr_set_survey_survey_version(survey_file_t* survey, char* surveyVersion);

// Set the install of the survey.
void srvyr_set_survey_install(survey_file_t* survey, char* install);

// Set the uninstall of the survey.
void srvyr_set_survey_uninstall(survey_file_t* survey, char* uninstall);

// Set the makefile of the survey.
void srvyr_set_survey_makefile(survey_file_t* survey, char* makefile);

// Set the license of the survey.
void srvyr_set_survey_license(survey_file_t* survey, char* license);

// Load Survey
survey_file_t* srvyr_load_survey(survey_file_t* survey, char* content);

//Generate the survey.c file.
void srvyr_generate_survey();

#endif
