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
survey_file_t* srvyr_survey_init(char* version, char* name)
{
	survey_file_t* survey = (survey_file_t*)malloc(1*sizeof(survey_file_t));
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
void srvyr_set_survey_name(survey_file_t* survey, char* name)
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
void srvyr_set_survey_version(survey_file_t* survey, char* version)
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
void srvyr_set_survey_repo(survey_file_t* survey, char* repo)
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

// Set the type of the survey.
void srvyr_set_survey_type(survey_file_t* survey, char* type)
{
	// If the Buffer already exists free it. 
	if(survey->type != NULL)
	{
		buffer_free(survey->type);
	}

	//Set the type to a new buffer.
	survey->type = buffer_new_with_copy(type);

	return;
}

// Set the surveyVersion of the survey.
void srvyr_set_survey_survey_version(survey_file_t* survey, char* surveyVersion)
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
void srvyr_set_survey_install(survey_file_t* survey, char* install)
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
void srvyr_set_survey_uninstall(survey_file_t* survey, char* uninstall)
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
void srvyr_set_survey_makefile(survey_file_t* survey, char* makefile)
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
void srvyr_set_survey_license(survey_file_t* survey, char* license)
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
survey_file_t* srvyr_load_survey(survey_file_t* survey, char* content)
{
	survey = srvyr_survey_init("", "");
	//Parse the JSON
	JSON_Value* root = json_parse_string(content);
	JSON_Object* file = json_value_get_object(root);
	char* name = json_object_get_string(file, "name");
	if (name != NULL)
	{
		survey->name = buffer_new_with_copy(name);
	}
	char* version = json_object_get_string(file, "version");
	if (version != NULL)
	{
		survey->version = buffer_new_with_copy(version);
	}
	char* repo = json_object_get_string(file, "repo");
	if (repo != NULL)
	{
		survey->repo = buffer_new_with_copy(repo);
	}
	char* type = json_object_get_string(file, "type");
	if (type != NULL)
	{
		survey->type = buffer_new_with_copy(type);
	}
	char* surveyVersion = json_object_get_string(file, "surveyVersion");
	if (surveyVersion != NULL)
	{
		survey->surveyVersion = buffer_new_with_copy(surveyVersion);
	}
	char* install = json_object_get_string(file, "install");
	if (install != NULL)
	{
		survey->install = buffer_new_with_copy(install);
	}
	char* uninstall = json_object_get_string(file, "uninstall");
	if (uninstall != NULL)
	{
		survey->uninstall = buffer_new_with_copy(uninstall);
	}
	char* makefile = json_object_get_string(file, "makefile");
	if (makefile != NULL)
	{
		survey->makefile = buffer_new_with_copy(makefile);
	}
	char* license = json_object_get_string(file, "license");
	if (license != NULL)
	{
		survey->license = buffer_new_with_copy(license);
	}
	JSON_Array* src = json_object_get_array(file, "src");
	if (src != NULL)
	{
		for (int i = 0; i < json_array_get_count(src); i++)
		{
			buffer_t* srcPath = buffer_new_with_copy(json_array_get_string(src, i));
			vec_push(&survey->src, srcPath);
		}
	}
	JSON_Array* keywords = json_object_get_array(file, "keywords");
	if (keywords != NULL)
	{
		for (int i = 0; i < json_array_get_count(keywords); i++)
		{
			buffer_t* keyword = buffer_new_with_copy(json_array_get_string(keywords, i));
			vec_push(&survey->keywords, keyword);
		}
	}
	JSON_Array* dependencies = json_object_get_array(file, "dependencies");
	if (dependencies != NULL)
	{
		for (int i = 0; i < json_array_get_count(dependencies); i++)
		{
			buffer_t* dependency = buffer_new_with_copy(json_array_get_string(dependencies, i));
			vec_push(&survey->dependencies, dependency);
		}
	}
	JSON_Array* development = json_object_get_array(file, "development");
	if (development != NULL)
	{
		for (int i = 0; i < json_array_get_count(development); i++)
		{
			buffer_t* dev = buffer_new_with_copy(json_array_get_string(development, i));
			vec_push(&survey->development, dev);
		}
	}
	return survey;
}