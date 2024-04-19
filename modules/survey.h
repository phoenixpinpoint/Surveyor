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

//Local Headers

//Variables and Data Structures
typedef struct SurveyFile {
	buffer_t* version;
	buffer_t* name;
	buffer_t* repo;
	buffer_t* install;
	buffer_t* makefile;
	buffer_t* license;
	buffer_t* src;
    buffer_t* keywords;
	vec_void_t dependencies;
	vec_void_t development;
} SurveyFile_t;

//Function Prototypes

// Intialize a SurveyFile Data Structure
SurveyFile_t* srvyr_survey_init(char* surveyVersion, char* name);

// Set the name of the survey.
void srvyr_set_survey_name(SurveyFile_t* survey, char* name);

// Set the version of the survey.
void srvyr_set_survey_version(SurveyFile_t* survey, char* version);

#endif