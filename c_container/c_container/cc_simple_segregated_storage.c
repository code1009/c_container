/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_simple_segregated_storage.c
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

//===========================================================================
#include "cc_simple_segregated_storage.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api size_t cc_simple_segregated_storage_calc_chunk_size(size_t data_size)
{
	size_t aligned_size;
	size_t aligned_count;

	size_t chunk_size;


	aligned_size = sizeof(void*);
	aligned_count = data_size / aligned_size;
	if (0U != (data_size % aligned_size))
	{
		aligned_count++;
	}


	chunk_size = aligned_size * aligned_count;


	return chunk_size;
}

cc_api size_t cc_simple_segregated_storage_calc_memory_size(size_t data_size, cc_ssize_t max_count)
{
	size_t chunk_size;
	size_t memory_size;


	chunk_size = cc_simple_segregated_storage_calc_chunk_size(data_size);


	memory_size = chunk_size * max_count;


	return memory_size;
}

cc_api bool cc_simple_segregated_storage_validate_pointer(cc_simple_segregated_storage_t* ctx, void* pointer)
{
	cc_debug_assert(ctx != NULL);


	uintptr_t first;
	uintptr_t last;
	uintptr_t current;


	first = (uintptr_t)(ctx->memory_pointer);
	last = first + ctx->chunk_size * ctx->max_count;
	current = (uintptr_t)pointer;

	if (first > current)
	{
		return false;
	}
	if (last < current)
	{
		return false;
	}
	if (0 != (current % ctx->chunk_size))
	{
		return false;
	}

	return true;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_simple_segregated_storage_initialize(cc_simple_segregated_storage_t* ctx, void* memory_pointer, size_t memory_size, size_t data_size, cc_ssize_t max_count)
{
	//-----------------------------------------------------------------------
	cc_debug_assert(ctx != NULL);
	cc_debug_assert(memory_pointer != NULL);
	cc_debug_assert(memory_size != 0);
	cc_debug_assert(data_size != 0);
	cc_debug_assert(max_count != 0);


	//-----------------------------------------------------------------------
	ctx->memory_pointer = (uint8_t*)memory_pointer;
	ctx->memory_size = memory_size;


	//-----------------------------------------------------------------------
	ctx->data_size = data_size;
	ctx->max_count = max_count;


	//-----------------------------------------------------------------------
	ctx->chunk_size = cc_simple_segregated_storage_calc_chunk_size(data_size);
	ctx->free_chunk_head = NULL;
	ctx->count = 0;


	//-----------------------------------------------------------------------
	if (ctx->memory_size < cc_simple_segregated_storage_calc_memory_size(data_size, max_count))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	cc_simple_segregated_storage_free_chunk_t* free_chunk_head;
	cc_simple_segregated_storage_free_chunk_t* free_chunk;

	uint8_t* pointer;

	cc_ssize_t i;
	cc_ssize_t count;


	pointer = ctx->memory_pointer;
	free_chunk_head = (cc_simple_segregated_storage_free_chunk_t*)(ctx->memory_pointer);
	count = ctx->max_count;


	free_chunk = free_chunk_head;
	for (i = 1; i < count; i++)
	{
		free_chunk->next = (cc_simple_segregated_storage_free_chunk_t*)(pointer + (i * ctx->chunk_size));
		free_chunk = free_chunk->next;
	}
	free_chunk->next = NULL;


	//-----------------------------------------------------------------------
	ctx->free_chunk_head = free_chunk_head;


	return true;
}

//===========================================================================
cc_api void* cc_simple_segregated_storage_allocate(cc_simple_segregated_storage_t* ctx)
{
	//-----------------------------------------------------------------------
	cc_debug_assert(ctx != NULL);


	//-----------------------------------------------------------------------
	if (NULL == ctx->free_chunk_head)
	{
		return NULL;
	}


	//-----------------------------------------------------------------------
	void* pointer;


	pointer = ctx->free_chunk_head;
	ctx->free_chunk_head = ctx->free_chunk_head->next;
	ctx->count++;


	return pointer;
}

cc_api bool cc_simple_segregated_storage_free(cc_simple_segregated_storage_t* ctx, void* pointer)
{
	//-----------------------------------------------------------------------
	cc_debug_assert(ctx != NULL);
	cc_debug_assert(pointer != NULL);


	//-----------------------------------------------------------------------
	if (false == cc_simple_segregated_storage_validate_pointer(ctx, pointer))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	cc_simple_segregated_storage_free_chunk_t* free_chunk;


	free_chunk = ctx->free_chunk_head;
	ctx->free_chunk_head = (cc_simple_segregated_storage_free_chunk_t*)(pointer);
	ctx->free_chunk_head->next = free_chunk;
	ctx->count--;


	return true;
}

cc_api cc_ssize_t cc_simple_segregated_storage_count(cc_simple_segregated_storage_t* ctx)
{
	//-----------------------------------------------------------------------
	cc_debug_assert(ctx != NULL);


	//-----------------------------------------------------------------------
	return ctx->count;
}
