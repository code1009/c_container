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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_assert1()
{
	cc_assert(0 != 0);
}

void test_cc_assert2()
{
	cc_debug_assert(0 != 0);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
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
	data_t* data_pointer;


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = new data_t();
		data_pointer->value = (int)i;

		rv = cc_vector_add(&container, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			delete data_pointer;
			break;
		}
	}


	i = 9;
	data_pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << index_string(i) << std::endl;
	}
	else
	{
		std::cout << "erase success:" << index_string(i) << data_pointer->value << std::endl;
		delete data_pointer;
	}


	i = 5;
	data_pointer = new data_t();
	if (data_pointer)
	{
		data_pointer->value = 10;
		cc_vector_insert(&container, i, data_pointer);
	}


	count = cc_vector_count(&container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_at(&container, i);
		std::cout << index_string(i) << data_pointer->value << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_at(&container, i);
		delete data_pointer;
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
	data_t* data_pointer;


#if 0
	cc_simple_segregated_storage_t data_storage;
	data_t data_memory[max_count];

	rv = cc_simple_segregated_storage_initialize(&data_storage, &data_memory[0], sizeof(data_memory), sizeof(data_t), max_count);
	if (rv == false)
	{
		std::cout << "data storage initialize failed" << std::endl;
		return;
	}


	cc_allocator_t data_allocator;
	cc_allocator_initialize(&data_allocator, &data_storage, (cc_alloc_t)cc_simple_segregated_storage_allocate, (cc_free_t)cc_simple_segregated_storage_free);
#else
	cc_simple_segregated_storage_t data_storage;
	data_t data_memory[max_count];

	cc_allocator_t data_allocator;

	rv = cc_simple_segregated_storage_allocator_initialize(
		&data_allocator,
		&data_storage, &data_memory[0], sizeof(data_memory), sizeof(data_t), max_count
	);
	if (rv == false)
	{
		std::cout << "data storage allocator initialize failed" << std::endl;
		return;
	}
#endif


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)data_allocator.alloc(&data_storage);
		if (data_pointer)
		{
			data_pointer->first = (int)i;
			data_pointer->second = (int)i;
		}
		else
		{
			std::cout << "data storage allocate failed:" << index_string(i) << std::endl;
			break;
		}

		rv = cc_vector_add(&container, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			break;
		}
	}


	i = 9;
	data_pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << index_string(i) << std::endl;
	}
	else
	{
		std::cout << "erase success:" << index_string(i) << data_pointer->first << std::endl;
		data_allocator.free(&data_storage, data_pointer);
	}


	i = 5;
	data_pointer = (data_t*)data_allocator.alloc(&data_storage);
	if (data_pointer)
	{
		data_pointer->first = 10;
		cc_vector_insert(&container, i, data_pointer);
	}


	count = cc_vector_count(&container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_at(&container, i);
		std::cout << index_string(i) << data_pointer->first << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_at(&container, i);
		data_allocator.free(&data_storage, data_pointer);
	}


	cc_vector_clear(&container);


	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_map1()
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
	data_t* data_pointer;


	cc_simple_segregated_storage_t data_storage;
	data_t data_memory[max_count];

	cc_allocator_t data_allocator;

	rv = cc_simple_segregated_storage_allocator_initialize(
		&data_allocator,
		&data_storage, &data_memory[0], sizeof(data_memory), sizeof(data_t), max_count
	);
	if (rv == false)
	{
		std::cout << "data storage allocator initialize failed" << std::endl;
		return;
	}


	cc_simple_segregated_storage_t key_storage;
	int key_memory[max_count*2];

	cc_allocator_t key_allocator;

	rv = cc_simple_segregated_storage_allocator_initialize(
		&key_allocator,
		&key_storage, &key_memory[0], sizeof(key_memory), sizeof(int), max_count
	);
	if (rv == false)
	{
		std::cout << "key storage allocator initialize failed" << std::endl;
		return;
	}


	cc_pair_t elements[max_count];
	cc_map_t container;
	cc_map_initialize(&container, cc_equal_pvalue_int32_t, cc_less_pvalue_int32_t, elements, max_count, sizeof(data_t));
	int* key_pointer;
	cc_pair_t* pair_pointer;


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)data_allocator.alloc(&data_storage);
		if (data_pointer)
		{
			data_pointer->first = 20 - (int)i;
			data_pointer->second = 20 - (int)i;
		}
		else
		{
			std::cout << "data storage allocate failed:" << index_string(i) << std::endl;
			break;
		}

		key_pointer = (int*)key_allocator.alloc(&key_storage);
		if (key_pointer)
		{
			*key_pointer = data_pointer->first;
		}
		else
		{
			std::cout << "key storage allocate failed:" << index_string(i) << std::endl;
			break;
		}

		rv = cc_map_add(&container, key_pointer, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			break;
		}
	}


	count = cc_map_count(&container);
	for (i = 0; i < count; i++)
	{
		pair_pointer = (cc_pair_t*)cc_map_at(&container, i);
		data_pointer = (data_t*)pair_pointer->second.pointer;

		std::cout << index_string(i) << data_pointer->first << ", " << data_pointer->second << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		pair_pointer = (cc_pair_t*)cc_map_at(&container, i);
		key_allocator.free(&key_storage, pair_pointer->first.pointer);
		data_allocator.free(&data_storage, pair_pointer->second.pointer);
	}


	cc_map_clear(&container);


	std::cout << "key storage count: " << cc_simple_segregated_storage_count(&key_storage) << std::endl;
	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
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
		
//		{ "cc_assert1", test_cc_assert1 },
//		{ "cc_assert2", test_cc_assert2 },

		{ "cc_vector1", test_cc_vector1 },
		{ "cc_vector2", test_cc_vector2 },

		{ "cc_map1", test_cc_map1 },

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

