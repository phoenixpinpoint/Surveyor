#include <stdlib.h>
#include <check.h>

#include <fs/fs.c>
#include <buffer/buffer.c>
#include <cwalk/cwalk.c>
#include <parson/parson.c>
#include <vec/vec.c>
#include <fido/response.c>
#include <fido/fido.c>
#include <fido/headers.h>
#include <fido/headers.c>
#include <fido/request.c>

#include "../src/file.c"
#include "../src/survey.c"

#include "file.c"
#include "survey.c"
#include "../src/surveyor.c"

file_logger *fhl;

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
	Suite *surveySuite;
	SRunner *surveyRunner;

    s = file_suite();
    sr = srunner_create(s);
	surveySuite = survey_suite();
	surveyRunner = srunner_create(surveySuite);

	printf("%s\n", "RUNNING ALL TESTS\n========================\0");
    srunner_run_all(sr, CK_NORMAL);
	srunner_run_all(surveyRunner, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
