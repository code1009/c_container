/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api cc_hash_key_t test1_cc_hash_key_generate(void* data)
{
	typedef struct _data_t
	{
		uint16_t key1;
		uint16_t key2;
		uint32_t value;
	} data_t;


	cc_debug_assert(data != NULL);


	data_t* data_pointer = (data_t*)data;

	return cc_hash_key_djb2(&data_pointer->key1, 4);
}

cc_api bool test1_cc_hash_equal(void* left, void* right)
{
	typedef struct _data_t
	{
		uint16_t key1;
		uint16_t key2;
		uint32_t value;
	} data_t;


	cc_debug_assert(left != NULL);
	cc_debug_assert(right != NULL);


	data_t* ldata_pointer = (data_t*)left;
	data_t* rdata_pointer = (data_t*)right;


	if ((ldata_pointer->key1 == rdata_pointer->key1) &&
		(ldata_pointer->key2 == rdata_pointer->key2))
	{
		return true;
	}


	return false;
}

void test_cc_hash_table_1()
{
	typedef struct _data_t
	{
		uint16_t key1;
		uint16_t key2;
		uint32_t value;
	} data_t;


	const size_t max_count = 256;
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


	cc_hash_entry_t elements[max_count];
	cc_hash_table_t container;
	cc_hash_table_initialize(&container, test1_cc_hash_key_generate, test1_cc_hash_equal, elements, max_count, sizeof(data_t));
	//cc_hash_entry_t* element_pointer;


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)data_allocator.alloc(&data_storage);
		if (data_pointer)
		{
			data_pointer->key1  = (uint16_t)i;
			data_pointer->key2  = (uint16_t)i + 10;
			data_pointer->value = (uint32_t)i + 1000;
		}
		else
		{
			std::cout << "data storage allocate failed:" << index_string(i) << std::endl;
			cc_debug_assert(i==16);
			break;
		}

		rv = cc_hash_table_add(&container, data_pointer);
		if (false == rv)
		{
			std::cout << "add failed:" << index_string(i) << std::endl;
			data_allocator.free(&data_storage, data_pointer);
			//cc_debug_assert(0);
			break;
		}
		

		cc_hash_key_t hash_key = test1_cc_hash_key_generate(data_pointer);
		std::cout << "add:" 
			<< index_string(i) 
			<< index_string(data_pointer->key1) << "-" 
			<< index_string(data_pointer->key2) << ": " 
			<< data_pointer->value << ", "

			<< "hash="
			<< index_string(cc_hash_probe(hash_key % max_count, 0, max_count))
			<< hash_key
			<< std::endl;
	}


	count = cc_hash_table_size(&container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_hash_table_element(&container, i);

		if (data_pointer != NULL)
		{
			cc_hash_key_t hash_key = test1_cc_hash_key_generate(data_pointer);

			std::cout
				<< index_string(cc_hash_probe(hash_key % max_count, 0, max_count))
				<< "->"
				<< index_string(i)
				<< " = "
				<< index_string(data_pointer->key1) << "-"
				<< index_string(data_pointer->key2) << ": "
				<< data_pointer->value
				<< std::endl
				;
		}
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_hash_table_element(&container, i);
		if (data_pointer != NULL)
		{
			data_allocator.free(&data_storage, data_pointer);
		}
	}


	cc_hash_table_clear(&container);


	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&data_storage) << std::endl;
}
