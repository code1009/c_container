/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_vector.c
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
#include "cc_vector.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_vector_initialize(cc_vector_t* ctx, cc_element_t* elements, size_t max_count, uintptr_t param)
{
	cc_container_initialize(&ctx->container, elements, max_count, param);
}

cc_api void cc_vector_clear(cc_vector_t* ctx)
{
	cc_container_clear(&ctx->container);
}

cc_api bool cc_vector_add(cc_vector_t* ctx, void* pointer)
{
	return cc_container_add(&ctx->container, pointer);
}

cc_api bool cc_vector_erase(cc_vector_t* ctx, size_t index)
{
	return cc_container_erase(&ctx->container, index);
}

cc_api bool cc_vector_insert(cc_vector_t* ctx, size_t index, void* pointer)
{
	return cc_container_insert(&ctx->container, index, pointer);
}

cc_api void* cc_vector_at(cc_vector_t* ctx, size_t index)
{
	return cc_container_at(&ctx->container, index);
}

cc_api size_t cc_vector_count(cc_vector_t* ctx)
{
	return cc_container_count(&ctx->container);
}

cc_api bool cc_vector_empty(cc_vector_t* ctx)
{
	return cc_container_empty(&ctx->container);
}

cc_api uintptr_t cc_vector_param(cc_vector_t* ctx)
{
	return cc_container_param(&ctx->container);
}
