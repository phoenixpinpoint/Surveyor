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
	SurveyFile_t* survey = (SurveyFile_t*)malloc(1*sizeof(SurveyFile_t));
	ck_assert_ptr_nonnull(survey);

	//Set the name for the first time
	srvyr_set_survey_name(survey, "FIRSTNAME");
	ck_assert_str_eq(survey->name->data, "FIRSTNAME");

	//Set the name the second time
	srvyr_set_survey_name(survey, "SECONDNAME");
	ck_assert_str_eq(survey->name->data, "SECONDNAME");

	buffer_free(survey->name);
	free(survey);
	
}
END_TEST

START_TEST(set_version)
{
	printf("%s\n", "CHECKING SET VERSION");
	
	//Create a blank Survey File
	SurveyFile_t* survey = (SurveyFile_t*)malloc(1*sizeof(SurveyFile_t));
	ck_assert_ptr_nonnull(survey);

	//Set the name for the first time
	srvyr_set_survey_version(survey, "1.0");
	ck_assert_str_eq(survey->version->data, "1.0");

	//Set the name the second time
	srvyr_set_survey_version(survey, "2.0");
	ck_assert_str_eq(survey->version->data, "2.0");

	buffer_free(survey->version);
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
	suite_add_tcase(s, tc_survey);
	
	return s;
}
