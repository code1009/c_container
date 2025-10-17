/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _data_t
{
	int first;
	int second;
} data_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define data_max_count 10





/////////////////////////////////////////////////////////////////////////////
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
typedef struct _key_memory_pool_t
{
	cc_simple_segregated_storage_t storage;
	uintptr_t memory[data_max_count];
	cc_allocator_t allocator;
}
key_memory_pool_t;

//===========================================================================
static key_memory_pool_t _key_memory_pool;

//===========================================================================
static bool key_memory_pool_initialize()
{
	bool rv;
	rv = cc_simple_segregated_storage_allocator_initialize(
		&_key_memory_pool.allocator,
		&_key_memory_pool.storage, &_key_memory_pool.memory[0], sizeof(_key_memory_pool.memory), sizeof(int), data_max_count
	);
	if (rv == false)
	{
		test_out << "cc_simple_segregated_storage_allocator_initialize() failed (key)" << test_tendl;
		test_assert(0);
		return false;
	}
	return true;
}

static void key_memory_pool_uninitialize()
{
	test_out << "key storage count: " << cc_simple_segregated_storage_count(&_key_memory_pool.storage) << test_tendl;
}

static int* key_memory_pool_alloc()
{
	int* key_pointer = (int*)_key_memory_pool.allocator.alloc(&_key_memory_pool.storage);
	if (key_pointer == NULL)
	{
		test_out << "_key_memory_pool.allocator.alloc() failed" << test_tendl;
		//test_assert(0);
	}
	return key_pointer;
}

static void key_memory_pool_free(int* key)
{
	bool rv;

	rv = _key_memory_pool.allocator.free(&_key_memory_pool.storage, key);
	if (rv == false)
	{
		test_out << "_key_memory_pool.allocator.free() failed" << test_tendl;
		test_assert(0);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _data_container_t
{
	cc_pair_t elements[data_max_count];
	cc_map_t container;
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

	rv = key_memory_pool_initialize();
	if (rv == false)
	{
		data_memory_pool_uninitialize();
		return false;
	}

	cc_map_initialize(&_data_container.container, cc_equal_pvalue_int32_t, cc_less_pvalue_int32_t, _data_container.elements, data_max_count, sizeof(data_t));

	return true;
}

static void data_container_uninitialize()
{
	test_out << "elements count:" << cc_map_count(&_data_container.container) << test_tendl;

	key_memory_pool_uninitialize();
	data_memory_pool_uninitialize();
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void add(void)
{
	size_t i;
	size_t count;
	bool rv;
	data_t* data_pointer;
	int* key_pointer;


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = data_memory_pool_alloc();
		if (data_pointer)
		{
			data_pointer->first = 10 - (int)i;
			data_pointer->second = 20 - (int)i;
		}
		else
		{
			test_out << "data_memory_pool_alloc() failed:" << test_tindex(i) << test_tendl;
			test_assert(i == 10);
			break;
		}

		key_pointer = key_memory_pool_alloc();
		if (key_pointer)
		{
			*key_pointer = data_pointer->first;
		}
		else
		{
			test_out << "key_memory_pool_alloc() failed:" << test_tindex(i) << test_tendl;
			test_assert(0);
			data_memory_pool_free(data_pointer);
			break;
		}


		test_out << "add:" << test_tindex(i) << data_pointer->first << ", " << data_pointer->second << test_tendl;
		rv = cc_map_add(&_data_container.container, key_pointer, data_pointer);
		if (false == rv)
		{
			test_out << "add failed:" << test_tindex(i) << test_tendl;
			data_memory_pool_free(data_pointer);
			key_memory_pool_free(key_pointer);
			test_assert(0);
			break;
		}
	}
}

static void print(void)
{
	size_t i;
	size_t count;
	cc_pair_t* element_pointer;
	data_t* data_pointer;


	count = cc_map_count(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		element_pointer = (cc_pair_t*)cc_map_at(&_data_container.container, i);
		test_assert(element_pointer != NULL);

		data_pointer = (data_t*)element_pointer->second.pointer;
		test_assert(data_pointer != NULL);

		test_out
			<< test_tindex(i)
			<< " = "
			<< data_pointer->first
			<< ", "
			<< data_pointer->second
			<< test_tendl
			;
	}
}

static void release(void)
{
	size_t i;
	size_t count;
	int* key_pointer;
	data_t* data_pointer;


	count = cc_map_count(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		key_pointer = (int*)cc_map_element_first(&_data_container.container, i);
		test_assert(key_pointer != NULL);

		data_pointer = (data_t*)cc_map_element_second(&_data_container.container, i);
		test_assert(data_pointer != NULL);

		key_memory_pool_free(key_pointer);
		data_memory_pool_free(data_pointer);
	}

	cc_map_clear(&_data_container.container);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void run(void)
{
	add();

	print();
	release();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_case_cc_map_1()
{
	if (!data_container_initialize())
	{
		return;
	}

	run();

	data_container_uninitialize();
}