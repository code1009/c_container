#ifndef cc_pair_container_h
#define cc_pair_container_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_pair_container.h
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
typedef struct _cc_pair_container_t
{
	cc_pair_t* elements;
	size_t max_count;
	uintptr_t param;

	size_t count;
}
cc_pair_container_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_pair_container_initialize(cc_pair_container_t* ctx, cc_pair_t* elements, size_t max_count, uintptr_t param);
cc_api uintptr_t cc_pair_container_param(cc_pair_container_t* ctx);

cc_api void cc_pair_container_clear(cc_pair_container_t* ctx);
cc_api bool cc_pair_container_erase(cc_pair_container_t* ctx, size_t index);
cc_api bool cc_pair_container_add(cc_pair_container_t* ctx, void* first, void* second);
cc_api bool cc_pair_container_insert(cc_pair_container_t* ctx, size_t index, void* first, void* second);

cc_api cc_pair_t* cc_pair_container_at(cc_pair_container_t* ctx, size_t index);
cc_api void* cc_pair_container_first(cc_pair_container_t* ctx, size_t index);
cc_api void* cc_pair_container_second(cc_pair_container_t* ctx, size_t index);

cc_api size_t cc_pair_container_count(cc_pair_container_t* ctx);
cc_api bool cc_pair_container_empty(cc_pair_container_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_pair_container_h

