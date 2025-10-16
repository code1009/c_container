/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_hash_table.c
// 
// # Created by: code1009
// # Created on: 09-18, 2025.
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "cc_export.h"

//===========================================================================
#include "cc_element.h"
#include "cc_compare.h"
#include "cc_pair.h"
#include "cc_pair_collection.h"

//===========================================================================
#include "cc_hash_table.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_hash_entry_initialize(cc_hash_entry_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	cc_hash_entry_clear(ctx);
}

cc_api void* cc_hash_entry_element(cc_hash_entry_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->element.pointer;
}

cc_api cc_hash_entry_status_t cc_hash_entry_status(cc_hash_entry_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->status;
}

cc_api void cc_hash_entry_fill(cc_hash_entry_t* ctx, void* element)
{
	cc_debug_assert(ctx != NULL);

	
	ctx->status = cc_hash_entry_status_filled;
	ctx->element.pointer = element;
}

cc_api void cc_hash_entry_remove(cc_hash_entry_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	ctx->status = cc_hash_entry_status_removed;
	ctx->element.pointer = NULL;
}

cc_api void cc_hash_entry_clear(cc_hash_entry_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	ctx->status = cc_hash_entry_status_empty;
	ctx->element.pointer = NULL;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api hash_key_t cc_hash_key_djb2(void* data, size_t length)
{
	cc_debug_assert(data != NULL);
	cc_debug_assert(length != 0);


	hash_key_t hash = 5381;
	uint8_t* ptr = (uint8_t*)data;
	for (size_t i = 0; i < length; i++)
	{
		hash = ((hash << 5) + hash) + ptr[i]; // hash * 33 + c
	}

	return hash;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static inline size_t cc_hash_linear_probe(size_t index, size_t attempt, size_t size)
{
	return (index + attempt) % size;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_hash_table_initialize(cc_hash_table_t* ctx, cc_equal_t equal, cc_hash_key_generate_t key_generate, cc_hash_entry_t* table, size_t max_count, uintptr_t param)
{
	cc_debug_assert(ctx != NULL);
	cc_debug_assert(equal != NULL);
	cc_debug_assert(key_generate != NULL);
	cc_debug_assert(table != NULL);
	cc_debug_assert(max_count != 0);


	ctx->equal = equal;
	ctx->key_generate = key_generate;
	ctx->table = table;
	ctx->max_count = max_count;
	ctx->param = param;

	ctx->count = 0;


	size_t i;
	for(i = 0; i < ctx->max_count; i++)
	{
		cc_hash_entry_initialize(&ctx->table[i]);
	}
}

cc_api uintptr_t cc_hash_table_param(cc_hash_table_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->param;
}

//===========================================================================
cc_api void cc_hash_table_clear(cc_hash_table_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	ctx->count = 0;


	size_t i;
	for (i = 0; i < ctx->max_count; i++)
	{
		cc_hash_entry_clear(&ctx->table[i]);
	}
}

cc_api bool cc_hash_table_erase(cc_hash_table_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->max_count)
	{
		cc_hash_entry_t* entry = &ctx->table[index];

		if (cc_hash_entry_status(entry) == cc_hash_entry_status_filled)
		{
			cc_hash_entry_remove(entry);
			ctx->count--;

			return true;
		}

		return false;
	}

	return false;
}

cc_api bool cc_hash_table_add(cc_hash_table_t* ctx, void* element)
{
	cc_debug_assert(ctx != NULL);


	if (ctx->count >= ctx->max_count)
	{
		return false;
	}


	hash_key_t key = ctx->key_generate(element);
	size_t index = key % ctx->max_count;


	size_t attempt;
	for(attempt = 0; attempt < ctx->max_count; attempt++)
	{
		size_t probe_index = cc_hash_linear_probe(index, attempt, ctx->max_count);
		cc_hash_entry_t* entry = &ctx->table[probe_index];
		cc_hash_entry_status_t status = cc_hash_entry_status(entry);


		if ( (status == cc_hash_entry_status_empty) ||
			 (status == cc_hash_entry_status_removed) )
		{
			cc_hash_entry_fill(entry, element);
			ctx->count++;

			return true;
		}
		else if(status == cc_hash_entry_status_filled)
		{
			void* existing_element = cc_hash_entry_element(entry);
			if(ctx->equal(existing_element, element))
			{
				// already exists, do not add
				return false;
			}

			continue;
		}
		else
		{
			return false;
		}
	}

	return false;
}

//===========================================================================
cc_api cc_hash_entry_t* cc_hash_table_at(cc_hash_table_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->max_count)
	{
		return &ctx->table[index];
	}

	return NULL;
}

cc_api void* cc_hash_table_element(cc_hash_table_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->max_count)
	{
		return cc_hash_entry_element(&ctx->table[index]);
	}

	return NULL;
}

cc_api size_t cc_hash_table_find(cc_hash_table_t* ctx, void* element)
{
	cc_debug_assert(ctx != NULL);


	hash_key_t key = ctx->key_generate(element);
	size_t index = key % ctx->max_count;


	size_t attempt;
	for (attempt = 0; attempt < ctx->max_count; attempt++)
	{
		size_t probe_index = cc_hash_linear_probe(index, attempt, ctx->max_count);
		cc_hash_entry_t* entry = &ctx->table[probe_index];
		cc_hash_entry_status_t status = cc_hash_entry_status(entry);


		if (status == cc_hash_entry_status_filled)
		{
			void* existing_element = cc_hash_entry_element(entry);
			if (ctx->equal(existing_element, element))
			{
				return probe_index;
			}
		}
		else if (status == cc_hash_entry_status_removed)
		{
			continue;
		}
		/*
		else if (status == cc_hash_entry_status_empty)
		{
			return cc_invalid_index;
		}
		*/
		else
		{
			return cc_invalid_index;
		}
	}


	return cc_invalid_index;
}

cc_api void* cc_hash_table_element_by_key(cc_hash_table_t* ctx, void* element)
{
	cc_debug_assert(ctx != NULL);


	size_t index = cc_hash_table_find(ctx, element);
	if (index != cc_invalid_index)
	{
		return cc_hash_entry_element(&ctx->table[index]);
	}


	return NULL;
}

//===========================================================================
cc_api size_t cc_hash_table_count(cc_hash_table_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->count;
}

cc_api bool cc_hash_table_empty(cc_hash_table_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return (ctx->count == 0) ? true : false;
}
