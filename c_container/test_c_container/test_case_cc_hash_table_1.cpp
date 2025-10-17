/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _data_t
{
	uint16_t key1;
	uint16_t key2;
	uint32_t value;
} data_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api static cc_hash_key_t cc_hash_key_generate(const void* data)
{
	test_assert(data != NULL);


	return cc_hash_key_djb2(data, 4);
}

cc_api static bool cc_hash_equal(const void* left, const void* right)
{
	test_assert(left != NULL);
	test_assert(right != NULL);


	data_t* ldata_pointer = (data_t*)left;
	data_t* rdata_pointer = (data_t*)right;


	if ((ldata_pointer->key1 == rdata_pointer->key1) &&
		(ldata_pointer->key2 == rdata_pointer->key2))
	{
		return true;
	}


	return false;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define data_max_count 32

//===========================================================================
typedef struct _data_memory_pool_t
{
	cc_simple_segregated_storage_t storage;
	data_t memory[data_max_count];
	cc_allocator_t allocator;
}
data_memory_pool_t;

//===========================================================================
static data_memory_pool_t _data_memory_pool;

//===========================================================================
static bool data_memory_pool_initialize()
{
	bool rv;
	rv = cc_simple_segregated_storage_allocator_initialize(
		&_data_memory_pool.allocator,
		&_data_memory_pool.storage, &_data_memory_pool.memory[0], sizeof(_data_memory_pool.memory), sizeof(data_t), data_max_count
	);
	if (rv == false)
	{
		test_out << "cc_simple_segregated_storage_allocator_initialize() failed" << test_tendl;
		test_assert(0);
		return false;
	}
	return true;
}

static void data_memory_pool_uninitialize()
{
	test_out << "data storage count:" << cc_simple_segregated_storage_count(&_data_memory_pool.storage) << test_tendl;
}

static data_t* data_memory_pool_alloc()
{
	data_t* data_pointer = (data_t*)_data_memory_pool.allocator.alloc(&_data_memory_pool.storage);
	if (data_pointer == NULL)
	{
		test_out << "_data_memory_pool.allocator.alloc() failed" << test_tendl;
		//test_assert(0);
	}
	return data_pointer;
}

static void data_memory_pool_free(data_t* data)
{
	bool rv;
	
	rv = _data_memory_pool.allocator.free(&_data_memory_pool.storage, data);
	if (rv == false)
	{
		test_out << "_data_memory_pool.allocator.free() failed" << test_tendl;
		test_assert(0);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _data_container_t
{
	cc_hash_entry_t elements[data_max_count];
	cc_hash_table_t container;
}
data_container_t;

//===========================================================================
static data_container_t _data_container;

//===========================================================================
static bool data_container_initialize()
{
	bool rv;

	rv = data_memory_pool_initialize();
	if (rv == false)
	{
		return false;
	}

	cc_hash_table_initialize(
		&_data_container.container,
		cc_hash_key_generate, cc_hash_equal, _data_container.elements, data_max_count, sizeof(data_t));

	return true;
}

static void data_container_uninitialize()
{
	test_out << "elements count:" << cc_hash_table_count(&_data_container.container) << test_tendl;

	data_memory_pool_uninitialize();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static size_t cc_hash_calc_key_index(data_t* data_pointer)
{
	cc_hash_key_t key = cc_hash_key_generate(data_pointer);

	size_t table_size = cc_hash_table_size(&_data_container.container);
	test_assert(table_size != 0);


	size_t index = key % table_size;


	return index;
}

static size_t cc_hash_calc_attempt(data_t* data_pointer, size_t target)
{
	cc_hash_key_t key = cc_hash_key_generate(data_pointer);

	size_t table_size = cc_hash_table_size(&_data_container.container);
	test_assert(table_size != 0);


	size_t index = key % table_size;


	size_t attemp = 0;

	for (attemp = 0; attemp < table_size; attemp++)
	{
		if (cc_hash_probe(index, attemp, table_size) == target)
		{
			return attemp;
		}
	}

	if (attemp >= table_size)
	{
		return cc_invalid_index;
	}

	return attemp;
}

//===========================================================================
static void add(void)
{
	size_t i;
	size_t count;
	bool rv;
	data_t* data_pointer;


	count = 512;
	for (i = 0; i < count; i++)
	{
		data_pointer = data_memory_pool_alloc();
		if (data_pointer)
		{
			data_pointer->key1 = (uint16_t)i;
			data_pointer->key2 = (uint16_t)i + 10;
			data_pointer->value = (uint32_t)i + 1000;
		}
		else
		{
			test_out << "data_memory_pool_alloc() failed:" << test_tindex(i) << test_tendl;
			break;
		}

		rv = cc_hash_table_add(&_data_container.container, data_pointer);
		if (false == rv)
		{
			test_out << "add failed:" << test_tindex(i) << test_tendl;
			data_memory_pool_free(data_pointer);
			break;
		}
	}
}

static void print(void)
{
	size_t i;
	size_t count;
	data_t* data_pointer;


	count = cc_hash_table_size(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_hash_table_element(&_data_container.container, i);

		if (data_pointer != NULL)
		{
			test_out
				<< test_tindex(cc_hash_calc_key_index(data_pointer))
				<< "+"
				<< cc_hash_calc_attempt(data_pointer, i)
				<< " ->"
				<< test_tindex(i)
				<< " = "
				<< test_tindex(data_pointer->key1) << "-"
				<< test_tindex(data_pointer->key2) << ":"
				<< data_pointer->value
				<< ", hash="
				<< cc_hash_key_generate(data_pointer)
				<< test_tendl
				;
		}
	}
}

static void release(void)
{
	size_t i;
	size_t count;
	data_t* data_pointer;


	count = cc_hash_table_size(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_hash_table_element(&_data_container.container, i);
		if (data_pointer != NULL)
		{
			data_memory_pool_free(data_pointer);
		}
	}
}

static void run(void)
{
	add();



	print();
	release();
}

//===========================================================================
void test_case_cc_hash_table_1()
{
	if (!data_container_initialize())
	{
		return;
	}

	run();

	data_container_uninitialize();
}
