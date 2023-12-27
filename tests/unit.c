#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "../surveyor.h"

START_TEST(openClib)
{
    FILE *clib = fopen("../clib.json", "r");
    ck_assert_ptr_nonnull(clib);
    fclose(clib);
}

Suite *unit_suite(void)
{
    Suite *s;
    TCase *tc_parse;

    s = suite_create("unit");

    tc_parse = tcase_create("parse");
    tcase_add_test(tc_parse, openClib);

    suite_add_tcase(s, tc_parse);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = unit_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS: EXIT_FAILURE;
}