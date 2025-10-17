/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test_c_container/test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_case_cc_code_template();
void test_case_cc_assert_1();
void test_case_cc_assert_2();
void test_case_cc_vector_1();
void test_case_cc_vector_2();
void test_case_cc_map_1();
void test_case_cc_map_2();
void test_case_cc_hash_table_1();





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void test_suite_cc_code_template()
{
	test_case_t test_cases[] =
	{
		{ "test_case_cc_code_template", test_case_cc_code_template },
		{ NULL, NULL }
	};


	test_suite_t test_suite;
	test_suite.name = "test_suite_cc_code_template";
	test_suite.items = test_cases;
	test_suite.count = sizeof(test_cases) / sizeof(test_case_t) - 1;
	test_runner(&test_suite);
}

static void test_suite_cc_assert()
{
	test_case_t test_cases[] =
	{
		{ "test_case_cc_assert_1", test_case_cc_assert_1 },
		{ "test_case_cc_assert_2", test_case_cc_assert_2 },
		{ NULL, NULL }
	};


	test_suite_t test_suite;
	test_suite.name = "test_suite_cc_assert";
	test_suite.items = test_cases;
	test_suite.count = sizeof(test_cases) / sizeof(test_case_t) - 1;
	test_runner(&test_suite);
}

static void test_suite_cc_vector()
{
	test_case_t test_cases[] =
	{
		{ "test_case_cc_vector_1", test_case_cc_vector_1 },
		{ "test_case_cc_vector_2", test_case_cc_vector_2 },
		{ NULL, NULL }
	};


	test_suite_t test_suite;
	test_suite.name = "test_suite_cc_vector";
	test_suite.items = test_cases;
	test_suite.count = sizeof(test_cases) / sizeof(test_case_t) - 1;
	test_runner(&test_suite);
}

static void test_suite_cc_map()
{
	test_case_t test_cases[] =
	{
		{ "test_case_cc_map_1", test_case_cc_map_1 },
		{ "test_case_cc_map_2", test_case_cc_map_2 },
		{ NULL, NULL }
	};


	test_suite_t test_suite;
	test_suite.name = "test_suite_cc_map";
	test_suite.items = test_cases;
	test_suite.count = sizeof(test_cases) / sizeof(test_case_t) - 1;
	test_runner(&test_suite);
}

static void test_suite_cc_hash_table()
{
	test_case_t test_cases[] =
	{
		{ "test_case_cc_hash_table_1", test_case_cc_hash_table_1 },
		{ NULL, NULL }
	};


	test_suite_t test_suite;
	test_suite.name = "test_suite_cc_hash_table";
	test_suite.items = test_cases;
	test_suite.count = sizeof(test_cases) / sizeof(test_case_t) - 1;
	test_runner(&test_suite);
}

//===========================================================================
static void test_run()
{
//	test_suite_cc_code_template();
//	test_suite_cc_assert();
	test_suite_cc_vector();
	test_suite_cc_map();
	test_suite_cc_hash_table();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int main()
{
	test_run();

	return 0;
}

