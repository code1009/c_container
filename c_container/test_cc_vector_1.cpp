/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _data_t
{
	int value;
} data_t;




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define data_max_count 32





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static data_t* data_memory_pool_alloc()
{
	return new(std::nothrow)data_t();
}

static void data_memory_pool_free(data_t* data)
{
	delete data;
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
	cc_vector_initialize(&_data_container.container, _data_container.elements, data_max_count, sizeof(data_t));

	return true;
}

static void data_container_uninitialize()
{
	std::cout << "elements count: " << cc_vector_count(&_data_container.container) << std::endl;
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
			data_pointer->value = (int)i;
		}
		else
		{
			std::cout << "data_memory_pool_alloc() failed:" << index_string(i) << std::endl;
			break;
		}

		rv = cc_vector_add(&_data_container.container, data_pointer);
		if (false == rv)
		{
			std::cout << "add failed:" << index_string(i) << std::endl;
			data_memory_pool_free(data_pointer);
			break;
		}
	}
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
		std::cout << "erase failed:" << index_string(i) << std::endl;
		test_assert(0);
	}
	else
	{
		std::cout << "erase success:" << index_string(i) << data_pointer->value << std::endl;
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
		data_pointer->value = 10;
		rv = cc_vector_insert(&_data_container.container, i, data_pointer);
		if (rv)
		{
			std::cout << "insert success:" << index_string(i) << std::endl;
		}
		else
		{
			std::cout << "insert failed:" << index_string(i) << std::endl;
			data_memory_pool_free(data_pointer);
		}
	}
	else
	{
		std::cout << "data_memory_pool_alloc() failed:" << index_string(i) << std::endl;
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
			std::cout
				<< index_string(i)
				<< " = "
				<< data_pointer->value
				<< std::endl
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
void test_cc_vector_1()
{
	if (!data_container_initialize())
	{
		return;
	}

	run();

	data_container_uninitialize();
}
