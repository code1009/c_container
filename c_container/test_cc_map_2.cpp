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
		std::cout << "cc_simple_segregated_storage_allocator_initialize() failed" << std::endl;
		test_assert(0);
		return false;
	}
	return true;
}

static void data_memory_pool_uninitialize()
{
	std::cout << "data storage count: " << cc_simple_segregated_storage_count(&_data_memory_pool.storage) << std::endl;
}

static data_t* data_memory_pool_alloc()
{
	data_t* data_pointer = (data_t*)_data_memory_pool.allocator.alloc(&_data_memory_pool.storage);
	if (data_pointer == NULL)
	{
		std::cout << "_data_memory_pool.allocator.alloc() failed" << std::endl;
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
		std::cout << "_data_memory_pool.allocator.free() failed" << std::endl;
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

	cc_map_initialize(&_data_container.container, cc_equal_int32_t, cc_less_int32_t, _data_container.elements, data_max_count, sizeof(data_t));

	return true;
}

static void data_container_uninitialize()
{
	std::cout << "elements count: " << cc_map_count(&_data_container.container) << std::endl;

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


	count = 10;
	for (i = 0; i < count; i++)
	{
		data_pointer = data_memory_pool_alloc();
		if (data_pointer)
		{
			data_pointer->first = (int)i;
			data_pointer->second = 10 + (int)i;
		}
		else
		{
			std::cout << "data_memory_pool_alloc() failed:" << index_string(i) << std::endl;
			break;
		}

#if (1==cc_config_compiler_msvc)
#pragma warning(disable:4312)
		rv = cc_map_add(&_data_container.container, (void*)data_pointer->first, data_pointer);
#pragma warning(default:4312)
#else
		rv = cc_map_add(&_data_container.container, (void*)data_pointer->first, data_pointer);
#endif

		if (false == rv)
		{
			std::cout << "add failed:" << index_string(i) << std::endl;
			data_memory_pool_free(data_pointer);
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

		std::cout
			<< index_string(i)
			<< " = "
			<< data_pointer->first
			<< ", "
			<< data_pointer->second
			<< std::endl
			;
	}
}

static void release(void)
{
	size_t i;
	size_t count;
	data_t* data_pointer;


	count = cc_map_count(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_map_element_second(&_data_container.container, i);
		if (data_pointer != NULL)
		{
			data_memory_pool_free(data_pointer);
		}
	}

	cc_map_clear(&_data_container.container);
}

static void lbound(void)
{
	size_t index;
	index = cc_map_lower_bound(&_data_container.container, (void*)11);
	std::cout << "lower bound of 11: " << index_string(index) << std::endl;
	test_assert(index == cc_map_count(&_data_container.container));
}

static void find_and_erase(void)
{
	cc_pair_t* element_pointer;
	data_t* data_pointer;
	bool rv;


	size_t index = cc_map_find(&_data_container.container, (void*)5);
	if (index != cc_invalid_index)
	{
		element_pointer = (cc_pair_t*)cc_map_at(&_data_container.container, index);
		data_pointer = (data_t*)element_pointer->second.pointer;
		std::cout << "find:" << index_string(index) << data_pointer->first << ", " << data_pointer->second << std::endl;


		rv = cc_map_erase(&_data_container.container, index);
		if (false == rv)
		{
			std::cout << "erase failed:" << index_string(index) << std::endl;
			test_assert(0);
		}
		else
		{
			std::cout << "erase success:" << index_string(index) << data_pointer->first << ", " << data_pointer->second << std::endl;
		}
		data_memory_pool_free(data_pointer);
	}
	else
	{
		std::cout << "not found" << std::endl;
		test_assert(0);
	}


	data_pointer = (data_t*)cc_map_element_second_by_first(&_data_container.container, (void*)4);
	if (data_pointer)
	{
		std::cout << "element:" << data_pointer->first << ", " << data_pointer->second << std::endl;
	}
	else
	{
		std::cout << "not found" << std::endl;
		test_assert(0);
	}
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void run(void)
{
	add();

	lbound();
	find_and_erase();

	print();
	release();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_map_2()
{
	if (!data_container_initialize())
	{
		return;
	}

	run();

	data_container_uninitialize();
}
