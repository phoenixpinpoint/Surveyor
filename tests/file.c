#include <check.h>
#include <file.h>

#include <fs/fs.h>
#include <buffer/buffer.h>

START_TEST(get_files)
{	
	printf("%s\n\0", "CHECKING GET FILES");
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
	
	//Close files and cleanup
	fs_close(testcfile);
	fs_close(testjsonfile);
	vec_deinit(&files);
}
END_TEST

START_TEST(get_sources)
{
	printf("%s\n\0", "CHECKING GET SOURCE");
	vec_void_t files = srvyr_get_files_in_directory("getfilestest");
	//printf("File Vector Count: %d\n", files.length);
	vec_void_t sourceFiles = srvyr_get_source_files(files);
	//printf("Source Files Vector Count: %d\n", sourceFiles.length);
	ck_assert_int_eq(sourceFiles.length, 1);
	int i;
	buffer_t* buffer;
	vec_foreach(&sourceFiles, buffer, i)
	{
		//printf("%s\n\0", buffer->data);
		buffer_free(buffer);	
	}	
	vec_deinit(&sourceFiles);
}


Suite* file_suite(void)
{
	Suite *s;
	TCase *tc_file;
	
	s = suite_create("file");

	tc_file = tcase_create("File");
	tcase_add_test(tc_file, get_files);
	tcase_add_test(tc_file, get_sources);
	suite_add_tcase(s, tc_file);
	
	return s;
}
