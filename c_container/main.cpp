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
	std::cout << "begin of test" << std::endl;
}

void test_end()
{
	std::cout << "end of test" << std::endl;
}

void test()
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

		{ "end", test_end }
	};



	size_t i = 0;
	size_t count = sizeof(tests) / sizeof(test_t);

	for (i = 0; i < count; i++)
	{
		std::cout << "==========================================================================" << std::endl;
		std::cout << "test: " << tests[i].name << std::endl;
		std::cout << "==========================================================================" << std::endl;
		
		tests[i].function();
		
		std::cout << std::endl;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int main()
{
	test();

	return 0;
}

