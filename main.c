#include "modules/surveyor.h"

#include "modules/file.c"
#include "modules/survey.c"
#include "modules/surveyor.c"

#include "survey.c"

file_logger *fhl;

int main(int argc, char *argv[]) 
{
    fhl = new_file_logger("surveyor.log", false);
    fLOG_INFO(fhl, "Surveyor v0.3.0");

    if (argc == 1)
    {
        fLOG_INFO(fhl, "Running Default Survey Generation");
        srvyr_generate_survey();

    }
    else if (argc == 2)
    {
        //Valid completions:
        //install
        //uninstall
        if (strncmp(argv[1], "install", 7) == 0)
        {
            fLOG_INFO(fhl, "Running Install");
            //If Deps Folder doesn't exist create it.
            if (fs_exists("./deps") == -1)
            {
                fs_mkdir("./deps", 0777);
            }

            //Get a list of all the dependencies
            //Load the Root Survey/Clib File into the surveyor.
            //Look in the current directory for clib.json or survey.json
            int clibExists = fs_exists("./clib.json");
            int surveyExists = fs_exists("./survey.json");
            char* fileContents = 0;
            survey_file_t* survey_struct = 0;
            //If survey.json exists
            if(surveyExists != -1)
            {
                fLOG_INFO(fhl, "survey.json exists using Surveyor format");
                FILE* survey_fd = fs_open("./survey.json", "r");
                fileContents = fs_fread(survey_fd);
                fs_close(survey_fd);
                survey_struct = srvyr_load_survey(survey_struct, fileContents);
                survey_struct->clibFlag = 0;
            }
            else if (clibExists != -1 && surveyExists == -1)
            {
                fLOG_INFO(fhl, "clib.json exists using legacy Clib format");
                FILE* clib_fd = fs_open("./clib.json", "r");
                fileContents = fs_fread(clib_fd);
                fs_close(clib_fd);
                survey_struct = srvyr_load_survey(survey_struct, fileContents);
                survey_struct->clibFlag = 1;
            }
            else
            {
                fLOG_ERROR(fhl, "No survey.json or clib.json found");
                return -1;
            }

            if(survey_struct->clibFlag == 1)
            {
                fLOG_INFO(fhl, "Getting Dependencies");
                //printf("Size of dependencies %d\n", survey_struct->dependencies.length);
                int dependency_count = survey_struct->dependencies.length;
                survey_file_t** dependency_files = (survey_file_t**)malloc(survey_struct->dependencies.length*sizeof(survey_file_t*));
                for (int i = 0; i < survey_struct->dependencies.length; i++)
                {
                    survey_file_t* dep_file = srvyr_get_dependency_survey(dep_file, (dependency_t*)survey_struct->dependencies.data[i]);
                    if (dep_file)
                    {
                        dependency_files[i] = dep_file;
                    }
                    else
                    {
                        fLOG_ERROR(fhl, "Failed to get dependency");
                    }
                }
            }

            


            char* res = srvyr_get_github_file("phoenixpinpoint", "fido", "clib.json", "*");
            printf("%s\n", res);
        }
        else if (strncmp(argv[1], "uninstall", 9) == 0)
        {
            fLOG_INFO(fhl, "Running Uninstall");
            //If Deps Folder exists delete it.
            if (fs_exists("./deps") != -1)
            {
                fs_rmdir("./deps");
            }
        }
        else
        {
            fLOGF_ERROR(fhl, "%s is not a valid command", argv[1]);
            return -1;
        }
    }
    else if (argc == 3)
    {
        //fLOGF_INFO(fhl, "Running Survey Generation for %s", argv[1]);
    }
    else
    {
        fLOG_ERROR(fhl, "Invalid number of arguments");
        return -1;
    }

    //Load the Root Survey/Clib File into the surveyor.
    //Look in the current directory for clib.json or survey.json
    int clibExists = fs_exists("./clib.json");
    int surveyExists = fs_exists("./survey.json");
    char* fileContents = 0;
    survey_file_t* survey_struct = 0;
    //If survey.json exists
    if(surveyExists != -1)
    {
        fLOG_INFO(fhl, "survey.json exists using Surveyor format");
        FILE* survey_fd = fs_open("./survey.json", "r");
        fileContents = fs_fread(survey_fd);
        fs_close(survey_fd);
        survey_struct = srvyr_load_survey(survey_struct, fileContents);
        survey_struct->clibFlag = 0;
    }
    else if (clibExists != -1 && surveyExists == -1)
    {
        fLOG_INFO(fhl, "clib.json exists using legacy Clib format");
        FILE* clib_fd = fs_open("./clib.json", "r");
        fileContents = fs_fread(clib_fd);
        fs_close(clib_fd);
        survey_struct = srvyr_load_survey(survey_struct, fileContents);
        survey_struct->clibFlag = 1;
    }
    else
    {
        fLOG_ERROR(fhl, "No survey.json or clib.json found");
        return -1;
    }

    return 0;
}
