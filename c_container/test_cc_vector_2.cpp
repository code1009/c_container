/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_vector_2()
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
		cc_debug_assert(0);
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
		cc_debug_assert(0);
		return;
	}
#endif


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));
	cc_element_t* element_pointer;


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
			cc_debug_assert(i == 10);
			break;
		}

		rv = cc_vector_add(&container, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			cc_debug_assert(i==10);
			break;
		}
	}


	i = 9;
	element_pointer = cc_vector_at(&container, i);
	cc_debug_assert(element_pointer != NULL);
	data_pointer = (data_t*)element_pointer->pointer;
	cc_debug_assert(data_pointer != NULL);
	rv = cc_vector_erase(&container, i);
	if (false == rv)
	{
		std::cout << "erase failed:" << index_string(i) << std::endl;
		cc_debug_assert(0);
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
		element_pointer = cc_vector_at(&container, i);
		cc_debug_assert(element_pointer != NULL);

		data_pointer = (data_t*)element_pointer->pointer;
		cc_debug_assert(data_pointer != NULL);

		std::cout << index_string(i) << data_pointer->first << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_element(&container, i);
		cc_debug_assert(data_pointer != NULL);

		data_allocator.free(&data_storage, data_pointer);
	}


	cc_vector_clear(&container);


	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
}
