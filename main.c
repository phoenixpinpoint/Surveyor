#include "surveyor.h"

#include <buffer/buffer.c>
#include <parson/parson.c>
#include <cwalk/cwalk.c>
#include <vec/vec.c>
#include <fs/fs.c>

#include "modules/file.c"
#include "surveyor.c"

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

    printf("writing to survey.c");

    //If the file opens
    if (survey)
    {
        //For each src file
        for(int i = 0; i < srcPaths.length; i++)
        {
            //Build the #include <{src/src.c}> line
            buffer_t* source = srcPaths.data[i];
            buffer_prepend(source, "#include <");
            buffer_append(source, ">\n");

            //Write it to the file.
            fputs(source->data, survey);

            buffer_free(source);

        }
        fclose(survey);
        printf("....success\n");
    }
    else {//write failure.
        printf("....failed\n");
    }

    //Clean-up
    vec_deinit(&srcPaths);

    return 0;
}
