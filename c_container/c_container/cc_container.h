#ifndef cc_container_h
#define cc_container_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_container.h
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
typedef struct _cc_container_t
{
	cc_element_t* elements;
	size_t max_count;
	uintptr_t param;

	size_t count;
}
cc_container_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_container_initialize(cc_container_t* ctx, cc_element_t* elements, size_t max_count, uintptr_t param);
cc_api void cc_container_clear(cc_container_t* ctx);

cc_api bool cc_container_erase(cc_container_t* ctx, size_t index);
cc_api bool cc_container_add(cc_container_t* ctx, void* pointer);
cc_api bool cc_container_insert(cc_container_t* ctx, size_t index, void* pointer);

cc_api void* cc_container_at(cc_container_t* ctx, size_t index);

cc_api size_t cc_container_count(cc_container_t* ctx);
cc_api bool cc_container_empty(cc_container_t* ctx);

cc_api uintptr_t cc_container_param(cc_container_t* ctx);




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_container_h

