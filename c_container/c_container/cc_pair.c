/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_pair.c
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
#include "cc_element.h"

//===========================================================================
#include "cc_pair.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_pair_initialize(cc_pair_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	cc_element_initialize(&ctx->first);
	cc_element_initialize(&ctx->second);
}

cc_api void cc_pair_copy(cc_pair_t* dst, cc_pair_t* src)
{
	cc_debug_assert(dst != NULL);
	cc_debug_assert(src != NULL);


	cc_element_copy(&dst->first, &src->first);
	cc_element_copy(&dst->second, &src->second);
}

cc_api void cc_pair_set(cc_pair_t* dst, void* first, void* second)
{
	cc_debug_assert(dst != NULL);


	cc_element_set(&dst->first, first);
	cc_element_set(&dst->second, second);
}

cc_api void* cc_pair_first(cc_pair_t* dst)
{
	cc_debug_assert(dst != NULL);


	return cc_element_get(&dst->first);
}

cc_api void* cc_pair_second(cc_pair_t* dst)
{
	cc_debug_assert(dst != NULL);


	return cc_element_get(&dst->second);
}
