#include <stdlib.h>
#include <check.h>

#include <fs/fs.c>
#include <buffer/buffer.c>
#include <cwalk/cwalk.c>
#include <parson/parson.c>
#include <vec/vec.c>

#include "../modules/file.c"

#include "file.c"
#include "../surveyor.c"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = file_suite();
    sr = srunner_create(s);

	printf("%s\n", "RUNNING ALL TESTS\n========================\0");
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
