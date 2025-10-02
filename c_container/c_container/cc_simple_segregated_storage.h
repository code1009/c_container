#ifndef cc_simple_segregated_storage_h
#define cc_simple_segregated_storage_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_simple_segregated_storage.h
// 
// # Created by: code1009
// # Created on: 09-18, 2025.
// 
// # Description:
//   @ code template
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_simple_segregated_storage_free_chunk_t
{
	struct _cc_simple_segregated_storage_free_chunk_t* next;
}
cc_simple_segregated_storage_free_chunk_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_simple_segregated_storage_t
{
	uint8_t* memory_pointer;
	size_t memory_size;

	size_t data_size;
	size_t max_count;

	size_t chunk_size;
	cc_simple_segregated_storage_free_chunk_t* free_chunk_head;
	signed long int count;
}
cc_simple_segregated_storage_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
size_t cc_simple_segregated_storage_calc_chunk_size(size_t data_size);
size_t cc_simple_segregated_storage_calc_memory_size(size_t data_size, size_t max_count);
bool   cc_simple_segregated_storage_validate_pointer(cc_simple_segregated_storage_t* ctx, void* pointer);

bool cc_simple_segregated_storage_initialize(cc_simple_segregated_storage_t* ctx, void* memory_pointer, size_t memory_size, size_t data_size, size_t max_count);

void* cc_simple_segregated_storage_allocate(cc_simple_segregated_storage_t* ctx);
bool  cc_simple_segregated_storage_release(cc_simple_segregated_storage_t* ctx, void* pointer);

size_t cc_simple_segregated_storage_count(cc_simple_segregated_storage_t* ctx);





#endif




