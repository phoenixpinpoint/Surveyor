#include "surveyor.h"

#include <buffer/buffer.c>
#include <parson/parson.c>
#include <cwalk/cwalk.c>
#include <vec/vec.c>
#include <fs/fs.c>

vec_void_t srcPaths;

vec_str_t getDependencies(vec_str_t dependencies, JSON_Object *dependencyObject)
{
    size_t depCount = json_object_get_count(dependencyObject);

    for (int keyIndex = 0; keyIndex < depCount; keyIndex++)
    {
        buffer_t* key = buffer_new_with_string(json_object_get_name(dependencyObject, keyIndex));
        size_t slashIndex = buffer_indexof(key, "/");
        key = buffer_slice(key, slashIndex+1, strlen(key->data));

        //Remove . from dependency names
        size_t dotIndex = buffer_indexof(key, ".");
        if (dotIndex != -1)
        {
            key = buffer_slice(key, 0, dotIndex);
        }
        vec_push(&dependencies, key->data);
    }

    return dependencies;
}

vec_void_t getFilesInDirectory(char* dirPath)
{
    vec_void_t fileNames;
    vec_init(&fileNames);

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if(d) {
        while((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                buffer_t* dirNameBuffer = buffer_new_with_copy(dir->d_name);
                vec_push(&fileNames, (void*)dirNameBuffer);
            }   
        }
    }

    closedir(d);
    return fileNames;
}

vec_void_t getSourceFilesInDirectory(char* dirPath)
{
    vec_void_t fileNames;
    vec_init(&fileNames);

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if(d) {
        while((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                buffer_t* dirNameBuffer = buffer_new_with_copy(dir->d_name);
                char* extension;
                size_t extLen;
                cwk_path_get_extension(dirNameBuffer->data, &extension, &extLen);
                if(strcmp(extension, ".c") == 0)
                {
                    vec_push(&fileNames, (void*)dirNameBuffer);
                }
            }   
        }
    }

    closedir(d);
    return fileNames;
}

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path)
{
    //Open clibs.json
    printf("Opening %s", path);
    FILE *clib = fopen(path, "r");
    if(clib != NULL)//File is open.
    {
        printf("....success\n");
    }
    else {//File is not open.
        printf("....failed\n");
        return -1;
    }

    //Read file into buffer
    printf("Reading %s", path);
    buffer_t* clibContents = buffer_new_with_copy(fs_fread(clib));

    //Check the length of contents
    if (strlen(clibContents->data) > 0)
    {
        printf("....success\n");
    }
    else
    {
        printf("....failed\n");
        return -1;
    }

    //Parse the JSON.
    printf("Parsing %s", path);
    JSON_Value *root;
    JSON_Object *file;
    JSON_Object *dependenciesObject;
    JSON_Array *src;

    root = json_parse_string(clibContents->data);
    if (json_value_get_type(root) != JSONObject) 
    {
        printf("....failed\n");
        return -1;
    }
    else {
        printf("....success\n");
    }

    file = json_value_get_object(root);

    //If this is not the root clib file.
    if (strcmp("clib.json", path) != 0)
    {
        //Get the name of the module
        buffer_t* dependencyName = buffer_new_with_copy(json_object_get_string(file, "name"));

        printf("Getting sources for %s", path);
        //Create a new buffer for the sourcePath. 
        buffer_t* sourcePath = buffer_new_with_copy(path);
        size_t lenOfDirPath;

        //Get the directory name
        cwk_path_get_dirname(sourcePath->data, &lenOfDirPath);
        sourcePath = buffer_slice(sourcePath, 0, lenOfDirPath);
        
        //Get all source files from that directory.
        vec_void_t sourceFiles = getSourceFilesInDirectory(sourcePath->data);
        for (int i = 0; i < sourceFiles.length; i++)
        {
            buffer_t* sourceFileIncludePath = buffer_new_with_copy(dependencyName->data);
            buffer_prepend(sourceFiles.data[i], "/");
            buffer_prepend(sourceFiles.data[i], sourceFileIncludePath->data);
            buffer_t* check = (buffer_t*)sourceFiles.data[i];
            buffer_t* copy = buffer_new_with_copy(check->data);
            int matchFoundFlag = 0;
            for(int i = 0; i < srcPaths.length; i++)
            {
                buffer_t* source = srcPaths.data[i];
                if (strcmp(source->data, copy->data) == 0){
                    matchFoundFlag = 1;
                }
            }

            if (matchFoundFlag == 0)
            {
                vec_push(&srcPaths, copy);
            }
            buffer_free(sourceFileIncludePath);
        }

        buffer_free(sourcePath);
        buffer_free(dependencyName);
        vec_deinit(&sourceFiles);
        printf("....success\n");
    }

    printf("Getting dependencies for %s\n", path);
    
    dependenciesObject = json_object_get_object(file, "dependencies");
    vec_str_t moduleDeps;
    vec_init(&moduleDeps);
    if (dependenciesObject != NULL)
    {
        moduleDeps = getDependencies(moduleDeps, dependenciesObject);
    }

    if (moduleDeps.length > 0)
    {
        for (int i = 0; i < moduleDeps.length; i++)
        {
            buffer_t* libPath = buffer_new();
            buffer_append(libPath, "./deps/");
            buffer_append(libPath, moduleDeps.data[i]);
            vec_void_t filesInDepDir = getFilesInDirectory(libPath->data);
            for (int j = 0; j < filesInDepDir.length; j++)
            {
                buffer_t* fileAsBuff = (buffer_t*)filesInDepDir.data[j];
                if(strcmp(fileAsBuff->data, "clib.json") == 0 || strcmp(fileAsBuff->data, "package.json") == 0){
                    // printf("%s\n", libPath->data);
                    buffer_append(libPath, "/");
                    buffer_append(libPath, fileAsBuff->data);
                    parseClib(libPath->data);
                }
            }
        }
    } 
    else 
    {
        printf("....success\n");
    }
    

    //Clean-up
    fclose(clib);
    buffer_free(clibContents);
    json_value_free(root);

}

int main() 
{
    printf("Surveyor v1.0\n");
    printf("=============\n");

    //vec_init(&dependencies);
    vec_init(&srcPaths);

    //Begin Parsing the Root clib.json
    parseClib("clib.json\0");

    //Open survey.c
    FILE* survey = fopen("./survey.c", "w+");

    if (survey)
    {
        //For each src file
        for(int i = 0; i < srcPaths.length; i++)
        {
            buffer_t* source = srcPaths.data[i];
            buffer_prepend(source, "#include <");
            buffer_append(source, ">\n");
            fputs(source->data, survey);

        }
        fclose(survey);
    }
    else {
        printf("failed to write\n");
    }




    //Clean-up
    //vec_deinit(&dependencies);
    vec_deinit(&srcPaths);

    return 0;
}