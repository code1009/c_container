/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_code_template();

void test_cc_assert_1();
void test_cc_assert_2();

void test_cc_vector_1();
void test_cc_vector_2();

void test_cc_map_1();
void test_cc_map_2();

void test_cc_hash_table_1();





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _test_t
{
	const char* name;
	void (*function)(void);
} test_t;

//===========================================================================
void test_begin()
{
	test::out << "begin of test" << test::tendl;
}

void test_end()
{
	test::out << "end of test" << test::tendl;
}

void test_run()
{
	test_t tests[] =
	{
		{ "begin", test_begin },
		
		{ "cc_code_template", test_cc_code_template },
		
//		{ "cc_assert_1", test_cc_assert_1 },
//		{ "cc_assert_2", test_cc_assert_2 },

		{ "cc_vector_1", test_cc_vector_1 },
		{ "cc_vector_2", test_cc_vector_2 },

		{ "cc_map_1", test_cc_map_1 },
		{ "cc_map_2", test_cc_map_2 },

		{ "cc_hash_table_1", test_cc_hash_table_1 },

		{ "end", test_end }
	};



	size_t i = 0;
	size_t count = sizeof(tests) / sizeof(test_t);

	for (i = 0; i < count; i++)
	{
		test::out << "==========================================================================" << test::tendl;
		test::out << "test: " << tests[i].name << test::tendl;
		test::out << "==========================================================================" << test::tendl;
		
		tests[i].function();
		
		test::out << test::tendl;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int main()
{
	test_run();

	return 0;
}

