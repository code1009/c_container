/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_snode_collection.c
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
#include "cc_snode.h"

//===========================================================================
#include "cc_snode_collection.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_snode_collection_initialize(cc_snode_collection_t* ctx, cc_snode_t* elements, size_t max_count, uintptr_t param)
{
	cc_debug_assert(ctx != NULL);
	cc_debug_assert(elements != NULL);
	cc_debug_assert(max_count != 0);


	ctx->elements = elements;
	ctx->max_count = max_count;
	ctx->param = param;

	ctx->count = 0;

	for (size_t i = 0; i < ctx->max_count; i++)
	{
		cc_snode_initialize(&ctx->elements[i]);
	}
}

cc_api uintptr_t cc_snode_collection_param(cc_snode_collection_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->param;
}

//===========================================================================
cc_api void cc_snode_collection_clear(cc_snode_collection_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	ctx->count = 0;
}

cc_api bool cc_snode_collection_erase(cc_snode_collection_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->count)
	{
		for (size_t i = index; i < ctx->count - 1; i++)
		{
			cc_snode_copy(&ctx->elements[i], &ctx->elements[i + 1]);
		}
		ctx->count--;

		return true;
	}

	return false;
}

cc_api bool cc_snode_collection_add(cc_snode_collection_t* ctx, cc_snode_t* next, void* element)
{
	cc_debug_assert(ctx != NULL);


	size_t index = ctx->count;
	if (index < ctx->max_count)
	{
		cc_snode_set(&ctx->elements[index], next, element);
		ctx->count++;
		return true;
	}

	return false;
}

cc_api bool cc_snode_collection_insert(cc_snode_collection_t* ctx, size_t index, cc_snode_t* next, void* element)
{
	cc_debug_assert(ctx != NULL);


	if (index <= ctx->count && ctx->count < ctx->max_count)
	{
		for (size_t i = ctx->count; i > index; i--)
		{
			cc_snode_copy(&ctx->elements[i], &ctx->elements[i - 1]);
		}
		cc_snode_set(&ctx->elements[index], next, element);
		ctx->count++;

		return true;
	}

	return false;
}

//===========================================================================
cc_api cc_snode_t* cc_snode_collection_at(cc_snode_collection_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->count)
	{
		return &ctx->elements[index];
	}
	return NULL;
}

cc_api void* cc_snode_collection_next(cc_snode_collection_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->count)
	{
		return cc_snode_next(&ctx->elements[index]);
	}
	return NULL;
}

cc_api void* cc_snode_collection_element(cc_snode_collection_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	if (index < ctx->count)
	{
		return cc_snode_element(&ctx->elements[index]);
	}
	return NULL;
}

//===========================================================================
cc_api size_t cc_snode_collection_count(cc_snode_collection_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return ctx->count;
}

cc_api bool cc_snode_collection_empty(cc_snode_collection_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return (ctx->count == 0) ? true : false;
}
