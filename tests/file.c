#include <check.h>
#include <file.h>

#include <fs/fs.h>
#include <buffer/buffer.h>

START_TEST(get_files)
{	
	printf("%s\n\0", "CHECKING GET_FILES.");
	//Create the test directory and files
	ck_assert_int_eq(fs_mkdir("getfilestest", 0777), 0);
	FILE *testcfile = fs_open("getfilestest/main.c", "w");
	FILE *testjsonfile = fs_open("getfilestest/main.json", "w");
	ck_assert_int_eq(fs_exists("getfilestest/main.c"), 0);
	ck_assert_int_eq(fs_exists("getfilestest/main.json"), 0);

	//Check output
	vec_void_t files;
	int i;
	buffer_t *buffer;

	files = srvyr_get_files_in_directory("getfilestest");
	ck_assert_int_eq(files.length, 2);
	/*
	*vec_foreach(&files, buffer, i)
	*{
	*	printf("%s\n", (buffer_t*)buffer->data);
	*}
	*/
	
	//Close files and cleanup
	fs_close(testcfile);
	fs_close(testjsonfile);
	vec_deinit(&files);
}
END_TEST

Suite* file_suite(void)
{
	Suite *s;
	TCase *tc_file;
	
	s = suite_create("file");

	tc_file = tcase_create("File");
	tcase_add_test(tc_file, get_files);
	suite_add_tcase(s, tc_file);
	
	return s;
}
