#include <check.h>
#include "../modules/survey.h"

#include <buffer/buffer.h>

START_TEST(init_survey)
{	
	printf("%s\n", "CHECKING SURVEY INIT");

	//Create a survey file
	SurveyFile_t* survey = srvyr_survey_init("1.0", "SOMETESTPACKAGE");

	ck_assert_ptr_nonnull(survey);
	ck_assert_str_eq("1.0", survey->version->data);
	ck_assert_str_eq("SOMETESTPACKAGE", survey->name->data);

	buffer_free(survey->version);
	buffer_free(survey->name);
	free(survey);
}
END_TEST

START_TEST(set_name)
{
	printf("%s\n", "CHECKING SET NAME");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");
	buffer_free(survey->name);
	survey->name = NULL;

	//Set the name for the first time
	srvyr_set_survey_name(survey, "FIRSTNAME");
	ck_assert_str_eq(survey->name->data, "FIRSTNAME");

	//Set the name the second time
	srvyr_set_survey_name(survey, "SECONDNAME");
	ck_assert_str_eq(survey->name->data, "SECONDNAME");

	buffer_free(survey->name);
	buffer_free(survey->version);
	free(survey);
}
END_TEST

START_TEST(set_version)
{
	printf("%s\n", "CHECKING SET VERSION");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");
	buffer_free(survey->version);
	survey->version = NULL;

	//Set the name for the first time
	srvyr_set_survey_version(survey, "1.0");
	ck_assert_str_eq(survey->version->data, "1.0");

	//Set the name the second time
	srvyr_set_survey_version(survey, "2.0");
	ck_assert_str_eq(survey->version->data, "2.0");

	buffer_free(survey->name);
	buffer_free(survey->version);
	free(survey);
	
}
END_TEST


START_TEST(set_repo)
{
	printf("%s\n", "CHECKING SET REPO");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");

	//Set the name for the first time
	srvyr_set_survey_repo(survey, "https://example.com/repo");
	ck_assert_str_eq(survey->repo->data,"https://example.com/repo");

	//Set the name the second time
	srvyr_set_survey_repo(survey, "https://example.com/repo2");
	ck_assert_str_eq(survey->repo->data,"https://example.com/repo2");

	buffer_free(survey->version);
	buffer_free(survey->name);
	buffer_free(survey->repo);
	free(survey);
	
}
END_TEST

START_TEST(set_surveyVersion)
{
	printf("%s\n", "CHECKING SET SURVEYVERSION");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");
	buffer_free(survey->surveyVersion);
	survey->surveyVersion = NULL;

	//Set the first time
	srvyr_set_survey_survey_version(survey, "1.0");
	ck_assert_str_eq(survey->surveyVersion->data,"1.0");

	//Set the name the second time
	srvyr_set_survey_survey_version(survey, "1.1");
	ck_assert_str_eq(survey->surveyVersion->data,"1.1");

	buffer_free(survey->name);
	buffer_free(survey->version);
	buffer_free(survey->surveyVersion);
	free(survey);
}
END_TEST

START_TEST(set_install)
{
	printf("%s\n", "CHECKING SET INSTALL");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");

	//Set the first time
	srvyr_set_survey_install(survey, "INS1");
	ck_assert_str_eq(survey->install->data,"INS1");

	//Set the name the second time
	srvyr_set_survey_install(survey, "INS2");
	ck_assert_str_eq(survey->install->data,"INS2");

	buffer_free(survey->name);
	buffer_free(survey->version);
	buffer_free(survey->install);
	free(survey);
}
END_TEST

START_TEST(set_uninstall)
{
	printf("%s\n", "CHECKING SET UNINSTALL");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");

	//Set the first time
	srvyr_set_survey_uninstall(survey, "UNINS1");
	ck_assert_str_eq(survey->uninstall->data,"UNINS1");

	//Set the name the second time
	srvyr_set_survey_uninstall(survey, "UNINS2");
	ck_assert_str_eq(survey->uninstall->data,"UNINS2");

	buffer_free(survey->name);
	buffer_free(survey->version);
	buffer_free(survey->uninstall);
	free(survey);
}
END_TEST

START_TEST(set_makefile)
{
	printf("%s\n", "CHECKING SET MAKEFILE");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");

	//Set the first time
	srvyr_set_survey_makefile(survey, "MakeFile");
	ck_assert_str_eq(survey->makefile->data,"MakeFile");

	//Set the name the second time
	srvyr_set_survey_makefile(survey, "Makefile");
	ck_assert_str_eq(survey->makefile->data,"Makefile");

	buffer_free(survey->name);
	buffer_free(survey->version);
	buffer_free(survey->makefile);
	free(survey);
}
END_TEST

START_TEST(set_license)
{
	printf("%s\n", "CHECKING SET LICENSE");
	
	//Create a blank Survey File
	SurveyFile_t* survey = srvyr_survey_init("1.0", "name");

	//Set the first time
	srvyr_set_survey_license(survey, "ISC");
	ck_assert_str_eq(survey->license->data,"ISC");

	//Set the name the second time
	srvyr_set_survey_license(survey, "GPL");
	ck_assert_str_eq(survey->license->data,"GPL");

	buffer_free(survey->name);
	buffer_free(survey->version);
	buffer_free(survey->license);
	free(survey);
}
END_TEST


Suite* survey_suite(void)
{
	Suite *s;
	TCase *tc_survey;
	
	s = suite_create("survey");

	tc_survey = tcase_create("Survey");
	tcase_add_test(tc_survey, init_survey);
	tcase_add_test(tc_survey, set_name);
	tcase_add_test(tc_survey, set_version);
	tcase_add_test(tc_survey, set_repo);
	tcase_add_test(tc_survey, set_surveyVersion);
	tcase_add_test(tc_survey, set_install);
	tcase_add_test(tc_survey, set_uninstall);
	tcase_add_test(tc_survey, set_makefile);
	tcase_add_test(tc_survey, set_license);
	suite_add_tcase(s, tc_survey);
	
	return s;
}
