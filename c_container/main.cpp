/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>

//===========================================================================
#include "c_container/cc.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_code_template()
{
	cc_code_template_t code_template;
	code_template.field = cc_code_template_macro;
	cc_code_template_function(&code_template);
}

void test_cc_assert()
{
	cc_assert(0 != 0);
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
			std::cout << "full:" << " [" << i << "] " << std::endl;
			delete pointer;
			break;
		}
	}


	i = 9;
	pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << " [" << i << "] " << std::endl;
	}
	else
	{
		std::cout << "erase success:" << " [" << i << "] " << pointer->value << std::endl;
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
		std::cout <<" [" << i << "] " << pointer->value << std::endl;
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
			std::cout << "storage allocate failed:" << " [" << i << "] " << std::endl;
			break;
		}

		rv = cc_vector_add(&container, pointer);
		if (false == rv)
		{
			std::cout << "full:" << " [" << i << "] " << std::endl;
			allocator.free(&data_storage, pointer);
			break;
		}
	}


	i = 9;
	pointer = (data_t*)cc_vector_at(&container, i);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << " [" << i << "] " << std::endl;
	}
	else
	{
		std::cout << "erase success:" << " [" << i << "] " << pointer->first << std::endl;
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
		std::cout << "[" << i << "] " << pointer->first << std::endl;
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
int main()
{
	test_cc_code_template();
	//test_cc_assert();
	test_cc_vector1();
	test_cc_vector2();

	return 0;
}

