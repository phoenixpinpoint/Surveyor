/** @file survey.c
 * 
 * @brief The basis of the survey module
 * 
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */

#include "survey.h"

// Initialize a SurveyFile Data Structure
SurveyFile_t* srvyr_survey_init(char* version, char* name)
{
	SurveyFile_t* survey = (SurveyFile_t*)malloc(1*sizeof(SurveyFile_t));
	survey->version =  buffer_new_with_copy(version);
	survey->name = buffer_new_with_copy(name);
	return survey;
}

// Set the name of the survey.
void srvyr_set_survey_name(SurveyFile_t* survey, char* name)
{
	// If the Buffer already exists free it. 
	if(survey->name != NULL)
	{
		buffer_free(survey->name);
	}

	//Set the name to a new buffer.
	survey->name = buffer_new_with_copy(name);

	return;
}

// Set the version of the survey.
void srvyr_set_survey_version(SurveyFile_t* survey, char* version)
{
	// If the Buffer already exists free it. 
	if(survey->version != NULL)
	{
		buffer_free(survey->version);
	}

	//Set the version to a new buffer.
	survey->version = buffer_new_with_copy(version);

	return;
}


