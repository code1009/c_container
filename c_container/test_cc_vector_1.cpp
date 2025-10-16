/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "test.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_cc_vector_1()
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
	data_t* data_pointer;


	cc_element_t elements[max_count];
	cc_vector_t container;
	cc_vector_initialize(&container, elements, max_count, sizeof(data_t));
	cc_element_t* element_pointer;


	count = 20;
	for (i = 0; i < count; i++)
	{
		data_pointer = new data_t();
		data_pointer->value = (int)i;

		rv = cc_vector_add(&container, data_pointer);
		if (false == rv)
		{
			std::cout << "full:" << index_string(i) << std::endl;
			delete data_pointer;
			cc_debug_assert(i==10);
			break;
		}
	}


	i = 9;
	element_pointer = cc_vector_at(&container, i);
	cc_debug_assert(element_pointer!=NULL);
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
		std::cout << "erase success:" << index_string(i) << data_pointer->value << std::endl;
		delete data_pointer;
	}


	i = 5;
	data_pointer = new data_t();
	if (data_pointer)
	{
		data_pointer->value = 10;
		cc_vector_insert(&container, i, data_pointer);
	}


	count = cc_vector_count(&container);
	for (i = 0; i < count; i++)
	{
		element_pointer = cc_vector_at(&container, i);
		cc_debug_assert(element_pointer != NULL);

		data_pointer = (data_t*)element_pointer->pointer;
		cc_debug_assert(data_pointer != NULL);

		std::cout << index_string(i) << data_pointer->value << std::endl;
	}
	for (i = 0; i < count; i++)
	{
		data_pointer = (data_t*)cc_vector_element(&container, i);
		cc_debug_assert(data_pointer != NULL);

		delete data_pointer;
	}


	cc_vector_clear(&container);
}
