/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_allocator_helper.c
// 
// # Created by: code1009
// # Created on: 09-18, 2025.
// 
// # Description:
//   @ 
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "cc_export.h"
#include "cc_element.h"
#include "cc_allocator.h"
#include "cc_simple_segregated_storage.h"
#include "cc_allocator_helper.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_simple_segregated_storage_allocator_initialize(
	cc_allocator_t* allocator,
	cc_simple_segregated_storage_t* simple_segregated_storage, void* memory_pointer, size_t memory_size, size_t data_size, cc_ssize_t max_count
)
{
	bool rv;
	rv = cc_simple_segregated_storage_initialize(simple_segregated_storage, memory_pointer, memory_size, data_size, max_count);
	if (rv == false)
	{
		allocator->handle = NULL;
		allocator->alloc = NULL;
		allocator->free = NULL;
		return false;
	}

	cc_allocator_initialize(allocator, simple_segregated_storage, (cc_alloc_t)cc_simple_segregated_storage_allocate, (cc_free_t)cc_simple_segregated_storage_free);
	return true;
}
