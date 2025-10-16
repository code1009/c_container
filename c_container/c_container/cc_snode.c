/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_snode.c
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

//===========================================================================
#include "cc_snode.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_snode_initialize(cc_snode_t* ctx)
{
	cc_debug_assert(ctx != NULL);


	ctx->next = NULL;
	cc_element_initialize(&ctx->element);
}

cc_api void cc_snode_copy(cc_snode_t* dst, cc_snode_t* src)
{
	cc_debug_assert(dst != NULL);
	cc_debug_assert(src != NULL);


	dst->next = src->next;
	cc_element_copy(&dst->element, &src->element);
}

cc_api void cc_snode_set(cc_snode_t* dst, cc_snode_t* next, void* element)
{
	cc_debug_assert(dst != NULL);


	dst->next = next;
	cc_element_set(&dst->element, element);
}

cc_api cc_snode_t* cc_snode_next(cc_snode_t* dst)
{
	cc_debug_assert(dst != NULL);


	return dst->next;
}

cc_api void* cc_snode_element(cc_snode_t* dst)
{
	cc_debug_assert(dst != NULL);


	return cc_element_get(&dst->element);
}

