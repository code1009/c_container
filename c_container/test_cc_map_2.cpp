/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_map_2()
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
		cc_debug_assert(0);
		return;
	}


	cc_pair_t elements[max_count];
	cc_map_t container;
	cc_map_initialize(&container, cc_equal_int32_t, cc_less_int32_t, elements, max_count, sizeof(data_t));
	cc_pair_t* element_pointer;


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)data_allocator.alloc(&data_storage);
		if (data_pointer)
		{
			data_pointer->first = 10 - (int)i;
			data_pointer->second = 20 - (int)i;
		}
		else
		{
			std::cout << "data storage allocate failed:" << index_string(i) << std::endl;
			cc_debug_assert(i==10);
			break;
		}

#if (1==cc_config_compiler_msvc)
#pragma warning(disable:4312)
		rv = cc_map_add(&container, (void*)data_pointer->first, data_pointer);
#pragma warning(default:4312)
#endif

		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			cc_debug_assert(0);
			break;
		}
	}


	size_t index = cc_map_find(&container, (void*)5);
	if(index != cc_invalid_index)
	{
		element_pointer = (cc_pair_t*)cc_map_at(&container, index);
		data_pointer = (data_t*)element_pointer->second.pointer;
		std::cout << "find:" << index_string(index) << data_pointer->first << ", " << data_pointer->second << std::endl;
		

		rv = cc_map_erase(&container, index);
		if (false == rv)
		{
			std::cout << "erase failed:" << index_string(index) << std::endl;
			cc_debug_assert(0);
		}
		else
		{
			std::cout << "erase success:" << index_string(index) << data_pointer->first << ", " << data_pointer->second << std::endl;
		}
		data_allocator.free(&data_storage, data_pointer);
	}
	else
	{
		std::cout << "not found" << std::endl;
		cc_debug_assert(0);
	}


	data_pointer = (data_t*)cc_map_element_second_by_first(&container, (void*)4);
	if (data_pointer)
	{
		std::cout << "element:" << data_pointer->first << ", " << data_pointer->second << std::endl;
	}
	else
	{
		std::cout << "not found" << std::endl;
		cc_debug_assert(0);
	}


	count = cc_map_count(&container);
	for (i = 0; i < count; i++)
	{
		element_pointer = (cc_pair_t*)cc_map_at(&container, i);
		cc_debug_assert(element_pointer != NULL);

		data_pointer = (data_t*)element_pointer->second.pointer;
		cc_debug_assert(data_pointer != NULL);

		std::cout << index_string(i) << data_pointer->first << ", " << data_pointer->second << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_map_element_second(&container, i);
		cc_debug_assert(data_pointer != NULL);

		data_allocator.free(&data_storage, data_pointer);
	}


	cc_map_clear(&container);


	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
}
