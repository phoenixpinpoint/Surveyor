/** @file survey.c
 * 
 * @brief The basis of the survey module
 * 
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */

#include <stdio.h>

#include "survey.h"

extern file_logger *fhl;

// Initialize a SurveyFile Data Structure
survey_file_t* srvyr_survey_init(char* version, char* name)
{
	survey_file_t* survey = (survey_file_t*)malloc(1*sizeof(survey_file_t));
	survey->surveyVersion = NULL;
	survey->version = NULL;
	survey->name = NULL;
	survey->repo = NULL;
	survey->install = NULL;
	survey->uninstall = NULL;
	survey->makefile = NULL;
	survey->license = NULL;
	survey->type = NULL;
	vec_void_t src;
	vec_init(&src);
	survey->src = src;
	vec_void_t keywords;
	vec_init(&keywords);
	survey->keywords = keywords;
	vec_void_t dependencies;
	vec_init(&dependencies);
	survey->dependencies = dependencies;
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
	fLOGF_DEBUG(fhl, "Name: %s", name);
	if (name != NULL)
	{
		survey->name = buffer_new_with_copy(name);
	}
	char* version = json_object_get_string(file, "version");
	fLOGF_DEBUG(fhl, "Version: %s", version);
	if (version != NULL)
	{
		survey->version = buffer_new_with_copy(version);
	}
	char* repo = json_object_get_string(file, "repo");
	fLOGF_DEBUG(fhl, "Repo: %s", repo);
	if (repo != NULL)
	{
		survey->repo = buffer_new_with_copy(repo);
	}
	char* type = json_object_get_string(file, "type");
	fLOGF_DEBUG(fhl, "Type: %s", type);
	if (type != NULL)
	{
		survey->type = buffer_new_with_copy(type);
	} else {
		survey->type = buffer_new_with_copy("clib\0");
	}
	char* surveyVersion = json_object_get_string(file, "surveyVersion");
	fLOGF_DEBUG(fhl, "Survey Version: %s", surveyVersion);
	if (surveyVersion != NULL)
	{
		survey->surveyVersion = buffer_new_with_copy(surveyVersion);
	}
	char* install = json_object_get_string(file, "install");
	fLOGF_DEBUG(fhl, "Install: %s", install);
	if (install != NULL)
	{
		survey->install = buffer_new_with_copy(install);
	}
	char* uninstall = json_object_get_string(file, "uninstall");
	fLOGF_DEBUG(fhl, "Uninstall: %s", uninstall);
	if (uninstall != NULL)
	{
		survey->uninstall = buffer_new_with_copy(uninstall);
	}
	char* makefile = json_object_get_string(file, "makefile");
	fLOGF_DEBUG(fhl, "Makefile: %s", makefile);
	if (makefile != NULL)
	{
		survey->makefile = buffer_new_with_copy(makefile);
	}
	char* license = json_object_get_string(file, "license");
	fLOGF_DEBUG(fhl, "License: %s", license);
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
	//Dpendencies is not an array but a JSON_Object
	JSON_Object* dependencies = json_object_get_object(file, "dependencies");
	if (dependencies != NULL)
	{		
		for (int i = 0; i < json_object_get_count(dependencies); i++)
		{
			if(type != NULL && strcmp(type, "survey") == 0)
			{
				char* name = json_object_get_name(dependencies, i);
				char* version = json_object_get_string(dependencies, name);
				char* type = "survey\0";
				dependency_t* dep = srvyr_dependency_init(
					name, 
					version, 
					type
				);
				vec_push(&survey->dependencies, dep);
			} else {

				char* name = json_object_get_name(dependencies, i);
				char* version = json_object_get_string(dependencies, name);
				char* type = "clib\0";
				dependency_t* dep = srvyr_dependency_init(
					name, 
					version, 
					type
				);
				vec_push(&survey->dependencies, dep);
			}
		}
	} 
	else {
		fLOG_DEBUG(fhl, "No dependencies found");
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

//Generate the survey.c file.
void srvyr_generate_survey()
{    
    vec_init(&srcPaths);
	
	//Begin Parsing the Root clib.json
    fLOG_INFO(fhl, "Parsing initial clib.json");
    int parseStatus = parseClib("clib.json\0");
    if (parseStatus < 0)
    {
        fLOG_ERROR(fhl, "Failed to parse clib.json");
        return;
    }
    else
    {
        fLOG_INFO(fhl, "Successfully parsed clib.json");
    }
    
    //Open survey.c
    FILE* survey = fs_open("./survey.c", "w+");
    //FILE* survey = fopen("./survey.c", "r");

    fLOG_INFO(fhl, "Writing to survey.c");

    //If the file opens
    if (survey)
    {
        //For each src file
        int fputsErrorFlag = 0;
        for(int i = 0; i < srcPaths.length; i++)
        {
            //Build the #include <{src/src.c}> line
            buffer_t* source = srcPaths.data[i];
            buffer_prepend(source, "#include <");
            buffer_append(source, ">\n");

            //Write it to the file.
            fputsErrorFlag = fputs(source->data, survey);

            buffer_free(source);

        }
        fs_close(survey);

        if (fputsErrorFlag < 0)
        {
            fLOG_ERROR(fhl, "Failed to write to survey.c");
            vec_deinit(&srcPaths);
            return;
        }
        else
        {
            fLOG_INFO(fhl, "Successfully wrote to survey.c");
        }
        //printf("....success\n");
    }
    else {//write failure.
        fLOG_ERROR(fhl, "Failed to open survey.c");
        vec_deinit(&srcPaths);
        return;
    }

    //Clean-up
    vec_deinit(&srcPaths);
}

dependency_t* srvyr_dependency_init(char* name, char* version, char* type)
{
	dependency_t* dependency = (dependency_t*)malloc(1*sizeof(dependency_t));
	dependency->name = buffer_new_with_copy(name);
	dependency->version = buffer_new_with_copy(version);
	dependency->type = buffer_new_with_copy(type);
	return dependency;
}

char* srvyr_json_serialize_survey(survey_file_t* survey)
{
	json_set_escape_slashes(0);	
	JSON_Value* root_value = json_value_init_object();
	JSON_Object* root_object = json_value_get_object(root_value);
	if (survey->name != NULL)
	{
		json_object_set_string(root_object, "name", survey->name->data);
	}
	if (survey->version != NULL)
	{
		json_object_set_string(root_object, "version", survey->version->data);
	}
	if (survey->repo != NULL)
	{
		json_object_set_string(root_object, "repo", survey->repo->data);
	}
	if (survey->type != NULL)
	{
		json_object_set_string(root_object, "type", survey->type->data);
	}
	if (survey->surveyVersion != NULL)
	{
		json_object_set_string(root_object, "surveyVersion", survey->surveyVersion->data);
	}
	if (survey->install != NULL)
	{
		json_object_set_string(root_object, "install", survey->install->data);
	}
	if (survey->uninstall != NULL)
	{
		json_object_set_string(root_object, "uninstall", survey->uninstall->data);
	}
	if (survey->makefile != NULL)
	{
		json_object_set_string(root_object, "makefile", survey->makefile->data);
	}
	if (survey->license != NULL)
	{
		json_object_set_string(root_object, "license", survey->license->data);
	}

	JSON_Value* src_value = json_value_init_array();
	if (survey->src.length > 0)
	{
		JSON_Array* src = json_value_get_array(src_value);
		for (int i = 0; i < survey->src.length; i++)
		{
			buffer_t* srcPath = survey->src.data[i];
			json_array_append_string(src, srcPath->data);
		}
		json_object_set_value(root_object, "src", src_value);
	}
	
	JSON_Value* keywords_value = json_value_init_array();
	if (survey->keywords.length > 0)
	{
		JSON_Array* keywords = json_value_get_array(keywords_value);
		for (int i = 0; i < survey->keywords.length; i++)
		{
			buffer_t* keyword = survey->keywords.data[i];
			json_array_append_string(keywords, keyword->data);
		}
		json_object_set_value(root_object, "keywords", keywords_value);
	}
	
	JSON_Value* dependencies_value = json_value_init_object();
	if (survey->dependencies.length > 0)
	{
		JSON_Object* dependencies = json_value_get_object(dependencies_value);
		for (int i = 0; i < survey->dependencies.length; i++)
		{
			dependency_t* dep = survey->dependencies.data[i];
			JSON_Value* dep_value = json_value_init_object();
			JSON_Object* dep_object = json_value_get_object(dep_value);
			json_object_set_string(dep_object, "name", dep->name->data);
			json_object_set_string(dep_object, "version", dep->version->data);
			json_object_set_string(dep_object, "type", dep->type->data);
			json_object_set_value(dependencies, dep->name->data, dep_value);
		}
		json_object_set_value(root_object, "dependencies", dependencies_value);
	}

	JSON_Value* development_value = json_value_init_array();
	if (survey->development.length > 0)
	{
		JSON_Array* development = json_value_get_array(development_value);
		for (int i = 0; i < survey->development.length; i++)
		{
			buffer_t* dev = survey->development.data[i];
			json_array_append_string(development, dev->data);
		}
		json_object_set_value(root_object, "development", development_value);
	}
	char* content = json_serialize_to_string_pretty(root_value);
	json_value_free(root_value);
	json_set_escape_slashes(1);
	return content;
}

void srvyr_dump_survey(char* content)
{
		
	printf("===Survey Dump===\n%s\n======\n",content);
	free(content);
}
