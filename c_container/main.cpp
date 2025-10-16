/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>

//===========================================================================
#include "c_container/cc.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::string index_string(size_t index)
{
	char buffer[32];
	sprintf_s(buffer, " [%zu] ", index);
	return std::string(buffer);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_code_template()
{
	cc_code_template_t code_template;
	code_template.field = cc_code_template_macro;
	cc_code_template_function(&code_template);
}

void test_cc_assert1()
{
	cc_assert(0 != 0);
}

void test_cc_assert2()
{
	cc_debug_assert(0 != 0);
}

void test_cc_vector1()
{
	typedef struct _data_t
	{
		int value;
	} 
	data_t;


	const size_t max_count = 10;
	size_t i;
	size_t count;
	bool rv;
	data_t* pointer;


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));


	count = 20;
	for (i = 0; i < count; i++)
	{
		pointer = new data_t();
		pointer->value = (int)i;

		rv = cc_vector_add(&container, pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			delete pointer;
			break;
		}
	}


	i = 9;
	pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << index_string(i) << std::endl;
	}
	else
	{
		std::cout << "erase success:" << index_string(i) << pointer->value << std::endl;
		delete pointer;
	}


	i = 5;
	pointer = new data_t();
	if (pointer)
	{
		pointer->value = 10;
		cc_vector_insert(&container, i, pointer);
	}


	count = cc_vector_count(&container);
	for (i = 0; i < count; i++)
	{
		pointer = (data_t*)cc_vector_at(&container, i);
		std::cout << index_string(i) << pointer->value << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		pointer = (data_t*)cc_vector_at(&container, i);
		delete pointer;
	}


	cc_vector_clear(&container);
}

void test_cc_vector2()
{
	typedef struct _data_t
	{
		int first;
		int second;
	} data_t;


	const size_t max_count = 10;
	size_t i;
	size_t count;
	bool rv;
	data_t* pointer;


#if 0
	cc_simple_segregated_storage_t data_storage;
	data_t data_memory[max_count];

	rv = cc_simple_segregated_storage_initialize(&data_storage, &data_memory[0], sizeof(data_memory), sizeof(data_t), max_count);
	if (rv == false)
	{
		std::cout << "storage initialize failed" << std::endl;
		return;
	}


	cc_allocator_t allocator;
	cc_allocator_initialize(&allocator, &data_storage, (cc_alloc_t)cc_simple_segregated_storage_allocate, (cc_free_t)cc_simple_segregated_storage_free);
#else
	cc_simple_segregated_storage_t data_storage;
	data_t data_memory[max_count];

	cc_allocator_t allocator;

	rv = cc_simple_segregated_storage_allocator_initialize(
		&allocator,
		&data_storage, &data_memory[0], sizeof(data_memory), sizeof(data_t), max_count
	);
	if (rv == false)
	{
		std::cout << "storage allocator initialize failed" << std::endl;
		return;
	}
#endif


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));


	count = 20;
	for (i = 0; i < count; i++)
	{
		pointer = (data_t*)allocator.alloc(&data_storage);
		if (pointer)
		{
			pointer->first = (int)i;
			pointer->second = (int)i;
		}
		else
		{
			std::cout << "storage allocate failed:" << index_string(i) << std::endl;
			break;
		}

		rv = cc_vector_add(&container, pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			allocator.free(&data_storage, pointer);
			break;
		}
	}


	i = 9;
	pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << index_string(i) << std::endl;
	}
	else
	{
		std::cout << "erase success:" << index_string(i) << pointer->first << std::endl;
		allocator.free(&data_storage, pointer);
	}


	i = 5;
	pointer = (data_t*)allocator.alloc(&data_storage);
	if (pointer)
	{
		pointer->first = 10;
		cc_vector_insert(&container, i, pointer);
	}


	count = cc_vector_count(&container);
	for (i = 0; i < count; i++)
	{
		pointer = (data_t*)cc_vector_at(&container, i);
		std::cout << index_string(i) << pointer->first << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		pointer = (data_t*)cc_vector_at(&container, i);
		allocator.free(&data_storage, pointer);
	}


	cc_vector_clear(&container);


	std::cout << "storage count: " << data_storage.count << std::endl;
}





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
		
		{ "cc_assert1", test_cc_assert1 },
		{ "cc_assert2", test_cc_assert2 },

		{ "cc_vector1", test_cc_vector1 },
		{ "cc_vector2", test_cc_vector2 },

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

