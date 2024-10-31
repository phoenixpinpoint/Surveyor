#include "surveyor.h"

extern file_logger *fhl;

//Parses a JSON_Object(clib dependencies object)
//Adds each dependency to the vector.
vec_str_t getDependencies(vec_str_t dependencies, JSON_Object *dependencyObject)
{
    //The total number of dependency objects. 
    size_t depCount = json_object_get_count(dependencyObject);

    //For each object. 
    for (int keyIndex = 0; keyIndex < depCount; keyIndex++)
    {
        //Split the name to get the dependency name and not the repo.
        //Ex: phoenixpinpoint/fido ====> fido
        buffer_t* key = buffer_new_with_string(json_object_get_name(dependencyObject, keyIndex));
        size_t slashIndex = buffer_indexof(key, "/");
        key = buffer_slice(key, slashIndex+1, strlen(key->data));

        //Remove . from dependency names
        //Ex: fs.c ==> fs
        size_t dotIndex = buffer_indexof(key, ".");
        if (dotIndex != -1)
        {
            key = buffer_slice(key, 0, dotIndex);
        }
        
        //Add the dependency to the list
        vec_push(&dependencies, key->data);
    }

    //Return the list of dependencies.
    return dependencies;
}

//Opens a given clib.json and gets the dependencies.
//Returns 0 if completed successfully, -1 on error. 
int parseClib(char* path)
{
    //Open clibs.json
    //printf("Opening %s", path);
    FILE *clib = fs_open(path, "r");
    if(clib != NULL)//File is open.
    {
        //printf("....success\n");
    }
    else {//File is not open.
        //printf("....failed\n");
        fLOGF_ERROR(fhl, "File %s failed to open", path);
        return -1;
    }

    //Read file into buffer
    //printf("Reading %s", path);
    buffer_t* clibContents = buffer_new_with_copy(fs_fread(clib));

    //Check the length of contents
    if (strlen(clibContents->data) > 0)
    {
        //printf("....success\n");
    }
    else
    {
        //printf("....failed\n");
        fLOGF_ERROR(fhl, "Contents of %s are empty", path);
        return -1;
    }

    //Parse the JSON.
    //printf("Parsing %s", path);
    JSON_Value *root;
    JSON_Object *file;
    JSON_Object *dependenciesObject;
    JSON_Array *src;

    root = json_parse_string(clibContents->data);
    if (json_value_get_type(root) != JSONObject) 
    {
        fLOGF_ERROR(fhl, "Failed to parse JSON of %s", path);
        return -1;
    }
    else {
        //printf("....success\n");
    }

    file = json_value_get_object(root);

    //Determine the source files for all dependencies:
    //If this is not the root clib file.
    if (strcmp("clib.json", path) != 0)
    {
        //Get the name of the module
        buffer_t* dependencyName = buffer_new_with_copy(json_object_get_string(file, "name"));

        fLOGF_INFO(fhl, "Getting sources for %s", path);
        //Create a new buffer for the sourcePath. 
        buffer_t* sourcePath = buffer_new_with_copy(path);
        size_t lenOfDirPath;

        //Get the directory name
        cwk_path_get_dirname(sourcePath->data, &lenOfDirPath);
        sourcePath = buffer_slice(sourcePath, 0, lenOfDirPath);
        
        //Get all source files from that directory.
		vec_void_t allFiles = srvyr_get_files_in_directory(sourcePath->data); //Get all files within the directory
		vec_void_t sourceFiles = srvyr_get_source_files(allFiles); //Determine which files are source files

        //For each of the files
        for (int i = 0; i < sourceFiles.length; i++)
        {
            //Build the include path
            //Ex: buffer/buffer.c
            buffer_t* sourceFileIncludePath = buffer_new_with_copy(dependencyName->data);
            buffer_prepend(sourceFiles.data[i], "/");
            buffer_prepend(sourceFiles.data[i], sourceFileIncludePath->data);
            buffer_t* check = (buffer_t*)sourceFiles.data[i];
            buffer_t* copy = buffer_new_with_copy(check->data);

            //If the source file isn't already in the list
            int matchFoundFlag = 0;
            for(int i = 0; i < srcPaths.length; i++)
            {
                buffer_t* source = srcPaths.data[i];
                if (strcmp(source->data, copy->data) == 0){
                    matchFoundFlag = 1;
                }
            }

            //Add it to the srcPaths vector if flat is still 0
            if (matchFoundFlag == 0)
            {
                vec_push(&srcPaths, copy);
            }
            buffer_free(sourceFileIncludePath);
        }

        //Clean=-up
        buffer_free(sourcePath);
        buffer_free(dependencyName);
        vec_deinit(&sourceFiles);
        //printf("....success\n");
    }

    //Determine the source files for all dependencies:
    fLOGF_INFO(fhl, "Getting dependencies for %s", path);
    //Get the Dependencies object from the clib.json/package.json
    dependenciesObject = json_object_get_object(file, "dependencies");

    //Create a vector of string to store the moduleDependency names
    vec_str_t moduleDeps;
    vec_init(&moduleDeps);
    if (dependenciesObject != NULL)
    {
        //Call get getDepedencies to get the root deps.
        moduleDeps = getDependencies(moduleDeps, dependenciesObject);
    }

    //If there are dependencies for the module.
    if (moduleDeps.length > 0)
    {
        //Go through each depedency
        for (int i = 0; i < moduleDeps.length; i++)
        {
            //Create the folder path.
            buffer_t* libPath = buffer_new();
            buffer_append(libPath, "./deps/");
            buffer_append(libPath, moduleDeps.data[i]);

            //Get all the files in that directory
            vec_void_t filesInDepDir = srvyr_get_files_in_directory(libPath->data);
            for (int j = 0; j < filesInDepDir.length; j++)
            {
                //Find the clib.json or package.json
                buffer_t* fileAsBuff = (buffer_t*)filesInDepDir.data[j];
                if(strcmp(fileAsBuff->data, "clib.json") == 0 || strcmp(fileAsBuff->data, "package.json") == 0){
                    //Build the paht for it.
                    buffer_append(libPath, "/");
                    buffer_append(libPath, fileAsBuff->data);
                    //Call parseClib to get that modules dependencies
                    parseClib(libPath->data);
                }
                buffer_free(fileAsBuff);
            }
            vec_deinit(&filesInDepDir);
            buffer_free(libPath);
        }
    } 
    else 
    {
        //printf("....success\n");
    }
    

    //Clean-up
    vec_deinit(&moduleDeps);
    fs_close(clib);
    buffer_free(clibContents);
    json_value_free(root);

}