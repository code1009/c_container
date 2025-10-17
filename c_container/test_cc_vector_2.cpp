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
#define data_max_count 32





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
typedef struct _data_container_t
{
	cc_element_t elements[data_max_count];
	cc_vector_t container;
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

	cc_vector_initialize(&_data_container.container, _data_container.elements, data_max_count, sizeof(data_t));

	return true;
}

static void data_container_uninitialize()
{
	test_out << "elements count:" << cc_vector_count(&_data_container.container) << test_tendl;

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


	count = 512;
	for (i = 0; i < count; i++)
	{
		data_pointer = data_memory_pool_alloc();
		if (data_pointer)
		{
			data_pointer->first = (int)i;
			data_pointer->second = 10+(int)i;
		}
		else
		{
			test_out << "data_memory_pool_alloc() failed:" << test_tindex(i) << test_tendl;
			break;
		}

		rv = cc_vector_add(&_data_container.container, data_pointer);
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


	count = cc_vector_count(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_element(&_data_container.container, i);

		if (data_pointer != NULL)
		{
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
}

static void release(void)
{
	size_t i;
	size_t count;
	data_t* data_pointer;


	count = cc_vector_count(&_data_container.container);
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_element(&_data_container.container, i);
		if (data_pointer != NULL)
		{
			data_memory_pool_free(data_pointer);
		}
	}

	cc_vector_clear(&_data_container.container);
}

static void erase(void)
{
	size_t i;
	data_t* data_pointer;
	bool rv;

	cc_element_t* element_pointer;


	i = 9;


	element_pointer = cc_vector_at(&_data_container.container, i);
	test_assert(element_pointer != NULL);

	data_pointer = (data_t*)element_pointer->pointer;
	test_assert(data_pointer != NULL);


	rv = cc_vector_erase(&_data_container.container, i);
	if (false == rv)
	{
		test_out << "erase failed:" << test_tindex(i) << test_tendl;
		test_assert(0);
	}
	else
	{
		test_out << "erase success:" << test_tindex(i) << data_pointer->first << test_tendl;
		data_memory_pool_free(data_pointer);
	}
}

static void insert(void)
{
	size_t i;

	bool rv;
	data_t* data_pointer;


	i = 5;
	data_pointer = data_memory_pool_alloc();
	if (data_pointer)
	{
		data_pointer->first = 99;
		data_pointer->second = 99;
		rv = cc_vector_insert(&_data_container.container, i, data_pointer);
		if(rv)
		{
			test_out << "insert success:" << test_tindex(i) << test_tendl;
		}
		else
		{
			test_out << "insert failed:" << test_tindex(i) << test_tendl;
			data_memory_pool_free(data_pointer);
		}
	}
	else
	{
		test_out << "data_memory_pool_alloc() failed:" << test_tindex(i) << test_tendl;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void run(void)
{
	add();

	erase();
	insert();

	print();
	release();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_vector_2()
{
	if (!data_container_initialize())
	{
		return;
	}

	run();

	data_container_uninitialize();
}
