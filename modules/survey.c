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
	survey->surveyVersion = NULL;
	survey->version = NULL;
	survey->name = NULL;
	survey->repo = NULL;
	survey->install = NULL;
	survey->makefile = NULL;
	survey->license = NULL;
	vec_void_t src;
	vec_init(&src);
	survey->src = src;
	vec_void_t keywords;
	vec_init(&keywords);
	survey->keywords = keywords;
	vec_void_t dependencies;
	vec_init(&dependencies);
	vec_void_t development;
	vec_init(&development);
	survey->development = development;
	srvyr_set_survey_survey_version(survey, "1.0");
	srvyr_set_survey_version(survey, version);
	srvyr_set_survey_name(survey, name);
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

// Set the repo of the survey.
void srvyr_set_survey_repo(SurveyFile_t* survey, char* repo)
{
	// If the Buffer already exists free it. 
	if(survey->repo != NULL)
	{
		buffer_free(survey->repo);
	}

	//Set the repo to a new buffer.
	survey->repo = buffer_new_with_copy(repo);

	return;
}

// Set the surveyVersion of the survey.
void srvyr_set_survey_survey_version(SurveyFile_t* survey, char* surveyVersion)
{
	// If the Buffer already exists free it. 
	if(survey->surveyVersion != NULL)
	{
		buffer_free(survey->surveyVersion);
	}

	//Set the surveyVersion to a new buffer.
	survey->surveyVersion = buffer_new_with_copy(surveyVersion);

	return;
}

// Set the install of the survey.
void srvyr_set_survey_install(SurveyFile_t* survey, char* install)
{
	// If the Buffer already exists free it. 
	if(survey->install != NULL)
	{
		buffer_free(survey->install);
	}

	//Set the new buffer.
	survey->install = buffer_new_with_copy(install);

	return;
}

// Set the uninstall of the survey.
void srvyr_set_survey_uninstall(SurveyFile_t* survey, char* uninstall)
{
	// If the Buffer already exists free it. 
	if(survey->uninstall != NULL)
	{
		buffer_free(survey->uninstall);
	}

	//Set the new buffer.
	survey->uninstall = buffer_new_with_copy(uninstall);

	return;
}


// Set the makefile of the survey.
void srvyr_set_survey_makefile(SurveyFile_t* survey, char* makefile)
{
	// If the Buffer already exists free it. 
	if(survey->makefile != NULL)
	{
		buffer_free(survey->makefile);
	}

	//Set the new buffer.
	survey->makefile = buffer_new_with_copy(makefile);

	return;
}

// Set the license of the survey.
void srvyr_set_survey_license(SurveyFile_t* survey, char* license)
{
	// If the Buffer already exists free it. 
	if(survey->license != NULL)
	{
		buffer_free(survey->license);
	}

	//Set the new buffer.
	survey->license = buffer_new_with_copy(license);

	return;
}

// Load Survey
void srvyr_load_survey(SurveyFile_t* survey, char* content)
{
	return;	
}

