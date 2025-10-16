/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_map.c
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
#include "cc_compare.h"
#include "cc_pair.h"
#include "cc_pair_container.h"
#include "cc_map.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
size_t cc_map_lower_bound(cc_map_t* ctx, void* pointer)
{
	cc_debug_assert(ctx != NULL);


	size_t low;
	size_t high;
	size_t mid;

	void* e;


	low = 0u;
	high = cc_map_count(ctx);
	while (low < high)
	{
		// mid = (low + high) / 2u;
		// (x+y)/2 => x&y + (x^y)/2
		mid = (low & high) + ((low ^ high) / 2u);

		e = cc_pair_container_first(&ctx->container, mid);
		if (true == ctx->less(e, pointer))
		{
			low = mid + 1u;
		}
		else
		{
			high = mid;
		}
	}

	return low;
}

size_t cc_map_upper_bound(cc_map_t* ctx, void* pointer)
{
	cc_debug_assert(ctx != NULL);


	size_t low;
	size_t high;
	size_t mid;

	void* e;


	low = 0u;
	high = cc_map_count(ctx);
	while (low < high)
	{
		mid = (low & high) + ((low ^ high) / 2u);

		e = cc_pair_container_first(&ctx->container, mid);
		if (true == ctx->less(pointer, e))
		{
			high = mid;
		}
		else
		{
			low = mid + 1u;
		}
	}

	return low;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_map_initialize(cc_map_t* ctx, cc_equal_t equal, cc_less_t less, cc_pair_t* elements, size_t max_count, uintptr_t param)
{
	cc_debug_assert(ctx != NULL);
	cc_debug_assert(equal != NULL);
	cc_debug_assert(less != NULL);
	cc_debug_assert(elements != NULL);
	cc_debug_assert(max_count != 0);


	ctx->equal = equal;
	ctx->less = less;
	cc_pair_container_initialize(&ctx->container, elements, max_count, param);
}

cc_api uintptr_t cc_map_param(cc_map_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return cc_pair_container_param(&ctx->container);
}

//===========================================================================
cc_api void cc_map_clear(cc_map_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	cc_pair_container_clear(&ctx->container);
}

cc_api bool cc_map_erase(cc_map_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	return cc_pair_container_erase(&ctx->container, index);
}

cc_api bool cc_map_add(cc_map_t* ctx, void* first, void* second)
{
	cc_debug_assert(ctx != NULL);


	//return cc_pair_container_add(&ctx->container, pointer);
	return false;
}

//===========================================================================
cc_api cc_pair_t* cc_map_at(cc_map_t* ctx, size_t index)
{
	cc_debug_assert(ctx != NULL);


	//return cc_pair_container_at(&ctx->container, index);
	return NULL;
}

cc_api size_t cc_map_find(cc_map_t* ctx, void* first)
{
	cc_debug_assert(ctx != NULL);


	return cc_invalid_index;
}

cc_api void* cc_map_get(cc_map_t* ctx, void* first)
{
	cc_debug_assert(ctx != NULL);


	return NULL;
}

//===========================================================================
cc_api size_t cc_map_count(cc_map_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return cc_pair_container_count(&ctx->container);
}

cc_api bool cc_map_empty(cc_map_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	return cc_pair_container_empty(&ctx->container);
}
