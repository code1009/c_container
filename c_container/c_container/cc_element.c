/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_element.c
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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void cc_elements_initialize(cc_elements_t* ctx, cc_element_t* data, size_t capacity, size_t chunk)
{
	ctx->data = data;
	ctx->capacity = capacity;
	ctx->chunk = chunk;
	ctx->count = 0;

	memset(ctx->data, 0, sizeof(cc_element_t) * ctx->capacity);
}

void cc_elements_clear(cc_elements_t* ctx)
{
	ctx->count = 0;
}

bool cc_elements_add(cc_elements_t* ctx, void* ptr)
{
	if (ctx->count < ctx->capacity)
	{
		ctx->data[ctx->count].ptr = ptr;
		ctx->count++;
		return true;
	}

	return false;
}

bool cc_elements_erase(cc_elements_t* ctx, size_t index)
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

bool cc_elements_insert(cc_elements_t* ctx, size_t index, void* ptr)
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

void* cc_elements_at(cc_elements_t* ctx, size_t index)
{
	if (index < ctx->count)
	{
		return ctx->data[index].ptr;
	}
	return NULL;
}

size_t cc_elements_count(cc_elements_t* ctx)
{
	return ctx->count;
}
