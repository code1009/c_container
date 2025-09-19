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
#include "cc_container.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void CC_API cc_container_initialize(cc_container_t* ctx, cc_element_t* data, size_t capacity, size_t chunk)
{
	ctx->data = data;
	ctx->capacity = capacity;
	ctx->chunk = chunk;
	ctx->count = 0;

	memset(ctx->data, 0, sizeof(cc_element_t) * ctx->capacity);
}

void CC_API cc_container_clear(cc_container_t* ctx)
{
	ctx->count = 0;
}

bool CC_API cc_container_add(cc_container_t* ctx, void* ptr)
{
	if (ctx->count < ctx->capacity)
	{
		ctx->data[ctx->count].ptr = ptr;
		ctx->count++;
		return true;
	}

	return false;
}

bool CC_API cc_container_erase(cc_container_t* ctx, size_t index)
{
	if (index < ctx->count)
	{
		for (size_t i = index; i < ctx->count - 1; i++)
		{
			ctx->data[i] = ctx->data[i + 1];
		}
		ctx->count--;

		return true;
	}

	return false;
}

bool CC_API cc_container_insert(cc_container_t* ctx, size_t index, void* ptr)
{
	if (index <= ctx->count && ctx->count < ctx->capacity)
	{
		for (size_t i = ctx->count; i > index; i--)
		{
			ctx->data[i] = ctx->data[i - 1];
		}
		ctx->data[index].ptr = ptr;
		ctx->count++;
		return true;
	}
	return false;
}

CC_API void* cc_container_at(cc_container_t* ctx, size_t index)
{
	if (index < ctx->count)
	{
		return ctx->data[index].ptr;
	}
	return NULL;
}

size_t CC_API cc_container_count(cc_container_t* ctx)
{
	return ctx->count;
}

bool CC_API cc_container_is_empty(cc_container_t* ctx)
{
	return (ctx->count == 0);
}
