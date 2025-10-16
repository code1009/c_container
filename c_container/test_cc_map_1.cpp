/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_map_1()
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


	cc_simple_segregated_storage_t key_storage;
	uintptr_t key_memory[max_count];

	cc_allocator_t key_allocator;

	rv = cc_simple_segregated_storage_allocator_initialize(
		&key_allocator,
		&key_storage, &key_memory[0], sizeof(key_memory), sizeof(int), max_count
	);
	if (rv == false)
	{
		std::cout << "key storage allocator initialize failed" << std::endl;
		cc_debug_assert(0);
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
			data_pointer->first = 10 - (int)i;
			data_pointer->second = 20 - (int)i;
		}
		else
		{
			std::cout << "data storage allocate failed:" << index_string(i) << std::endl;
			cc_debug_assert(i==10);
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
			cc_debug_assert(0);
			break;
		}


		std::cout << "add:" << index_string(i) << data_pointer->first << ", " << data_pointer->second << std::endl;
		rv = cc_map_add(&container, key_pointer, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			cc_debug_assert(0);
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

		key_pointer = (int*)pair_pointer->first.pointer;
		data_pointer = (data_t*)pair_pointer->second.pointer;
		key_allocator.free(&key_storage, key_pointer);
		data_allocator.free(&data_storage, data_pointer);
	}


	cc_map_clear(&container);


	std::cout << "key storage count: " << cc_simple_segregated_storage_count(&key_storage) << std::endl;
	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
}
