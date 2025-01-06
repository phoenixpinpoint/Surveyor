#include <check.h>
#include "../src/file.h"

#include <fs/fs.h>
#include <buffer/buffer.h>
#include <vec/vec.h>

#ifdef STANDALONE
#include <fs/fs.c>
#include <buffer/buffer.c>
#include <vec/vec.c>
#include <cwalk/cwalk.c>

#include "../src/file.c"
#endif

START_TEST(get_files)
{	
	printf("%s\n", "CHECKING GET FILES");
	//Create the test directory and files
	ck_assert_int_eq(fs_mkdir("getfilestest", 0777), 0);
	FILE *testcfile = fs_open("getfilestest/main.c", "w");
	FILE *testjsonfile = fs_open("getfilestest/main.json", "w");
	FILE *testcppfile = fs_open("getfilestest/test.cpp", "w");
	FILE *testcxxfile = fs_open("getfilestest/test.cxx", "w");
	ck_assert_int_eq(fs_exists("getfilestest/main.c"), 0);
	ck_assert_int_eq(fs_exists("getfilestest/main.json"), 0);
	ck_assert_int_eq(fs_exists("getfilestest/test.cpp"),0);
	ck_assert_int_eq(fs_exists("getfilestest/test.cxx"),0);

	//Check output
	vec_void_t files;
	int i;

	files = srvyr_get_files_in_directory("getfilestest");
	ck_assert_int_eq(files.length, 4);
	
	//Close files and cleanup
	fs_close(testcfile);
	fs_close(testjsonfile);
	fs_close(testcppfile);
	fs_close(testcxxfile);
	vec_deinit(&files);
}
END_TEST

START_TEST(get_sources)
{
	printf("%s\n", "CHECKING GET SOURCE");
	vec_void_t files = srvyr_get_files_in_directory("getfilestest");
	vec_void_t sourceFiles = srvyr_get_source_files(files);
	ck_assert_int_eq(sourceFiles.length, 3);
	int i;
	buffer_t* buffer;
	vec_foreach(&sourceFiles, buffer, i)
	{
		buffer_free(buffer);	
	}	
	vec_deinit(&sourceFiles);
}

START_TEST(issue_1_included_a_make_file)
{
	printf("%s\n", "CHECKING 1-included-a-makefile");
	FILE *testmakefile = fs_open("getfilestest/Makefile", "w");
	ck_assert_int_eq(fs_exists("getfilestest/Makefile"), 0);
	
	//Check output
	vec_void_t files;
	int i;
	buffer_t *buffer;

	files = srvyr_get_files_in_directory("getfilestest");
	ck_assert_int_eq(files.length, 5);

	vec_void_t sourceFiles = srvyr_get_source_files(files);
	ck_assert_int_eq(sourceFiles.length, 3);
}
END_TEST

START_TEST(check_for_inline_includes)
{
	buffer_t* test = buffer_new_with_copy("#include <buffer/buffer.h>\n");
	buffer_append(test, "#include <vec/vec.c>\n");
	buffer_append(test, "#include <parson/parson.cpp>\n");
	buffer_append(test, "#include <fs/fs.cxx>\n");
	buffer_append(test, "#include <ulog/logger.h>\n");
	buffer_append(test, "#include <cwalk/cwalk.h>\n");
	buffer_append(test, "#include \"fido.c\"\n");

	//printf("Example: %s\n", test->data);

	vec_void_t sourceFiles = srvyr_get_included_source_files(test);

	ck_assert_int_eq(sourceFiles.length, 4);
	// printf("Source Files: %d\n", sourceFiles.length);
	// printf("1: %s\n", ((buffer_t*)sourceFiles.data[0])->data);
	// printf("2: %s\n", ((buffer_t*)sourceFiles.data[1])->data);
	// printf("3: %s\n", ((buffer_t*)sourceFiles.data[2])->data);
	// printf("4: %s\n", ((buffer_t*)sourceFiles.data[3])->data);
}
END_TEST

Suite* file_suite(void)
{
	Suite *s;
	TCase *tc_file;
	
	s = suite_create("file");

	tc_file = tcase_create("File");
	tcase_add_test(tc_file, get_files);
	tcase_add_test(tc_file, get_sources);
	tcase_add_test(tc_file, issue_1_included_a_make_file);
	tcase_add_test(tc_file, check_for_inline_includes);
	suite_add_tcase(s, tc_file);
	
	return s;
}

#ifdef STANDALONE

int main(void)
{
    int number_failed;
    Suite *s;
	SRunner *sr;

    s = file_suite();
    sr = srunner_create(s);

	printf("%s\n", "RUNNING FILE TESTS\n========================\0");
	srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif
