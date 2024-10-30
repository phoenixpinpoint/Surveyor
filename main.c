#include "surveyor.h"

#include "modules/file.c"
#include "surveyor.c"

#include "survey.c"

file_logger *fhl;

int main() 
{
    fhl = new_file_logger("surveyor.log", false);
    fLOG_INFO(fhl, "Surveyor v1.0");

    //vec_init(&dependencies);
    vec_init(&srcPaths);

    //Begin Parsing the Root clib.json
    fLOG_INFO(fhl, "Parsing initial clib.json");
    parseClib("clib.json\0");
    
    //Open survey.c
    FILE* survey = fopen("./survey.c", "w+");
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
        fclose(survey);

        if (fputsErrorFlag < 0)
        {
            fLOG_ERROR(fhl, "Failed to write to survey.c");
            return -1;
        }
        else
        {
            fLOG_INFO(fhl, "Successfully wrote to survey.c");
        }
        //printf("....success\n");
    }
    else {//write failure.
        fLOG_ERROR(fhl, "Failed to open survey.c");
        return -1;
    }

    //Clean-up
    vec_deinit(&srcPaths);

    return 0;
}
