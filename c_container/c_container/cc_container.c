/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_container.c
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
#include "cc_container.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_container_initialize(cc_container_t* ctx, cc_element_t* elements, size_t max_count, size_t data_size)
{
	ctx->elements = elements;
	ctx->max_count = max_count;
	ctx->data_size = data_size;
	ctx->count = 0;

	for (size_t i = 0; i < ctx->max_count; i++)
	{
		cc_element_initialize(&ctx->elements[i]);
	}
}

cc_api void cc_container_clear(cc_container_t* ctx)
{
	ctx->count = 0;
}

cc_api bool cc_container_add(cc_container_t* ctx, void* pointer)
{
	size_t index = ctx->count;
	if (index < ctx->max_count)
	{
		ctx->elements[index].pointer = pointer;
		ctx->count++;
		return true;
	}

	return false;
}

cc_api bool cc_container_erase(cc_container_t* ctx, size_t index)
{
	if (index < ctx->count)
	{
		for (size_t i = index; i < ctx->count - 1; i++)
		{
			ctx->elements[i] = ctx->elements[i + 1];
		}
		ctx->count--;

		return true;
	}

	return false;
}

cc_api bool cc_container_insert(cc_container_t* ctx, size_t index, void* pointer)
{
	if (index <= ctx->count && ctx->count < ctx->max_count)
	{
		for (size_t i = ctx->count; i > index; i--)
		{
			ctx->elements[i] = ctx->elements[i - 1];
		}
		ctx->elements[index].pointer = pointer;
		ctx->count++;

		return true;
	}

	return false;
}

cc_api void* cc_container_at(cc_container_t* ctx, size_t index)
{
	if (index < ctx->count)
	{
		return ctx->elements[index].pointer;
	}
	return NULL;
}

cc_api size_t cc_container_count(cc_container_t* ctx)
{
	return ctx->count;
}

cc_api bool cc_container_is_empty(cc_container_t* ctx)
{
	return (ctx->count == 0) ? true : false;
}
