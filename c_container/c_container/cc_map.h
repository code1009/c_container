#ifndef cc_map_h
#define cc_map_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_map.h
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
typedef struct _cc_map_t
{
	cc_equal_t equal;
	cc_less_t less;
	cc_pair_container_t container;
}
cc_map_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_map_initialize(cc_map_t* ctx, cc_equal_t equal, cc_less_t less, cc_pair_t* elements, size_t max_count, uintptr_t param);
cc_api uintptr_t cc_map_param(cc_map_t* ctx);

cc_api void cc_map_clear(cc_map_t* ctx);
cc_api bool cc_map_erase(cc_map_t* ctx, size_t index);
cc_api bool cc_map_add(cc_map_t* ctx, void* first, void* second);

cc_api cc_pair_t* cc_map_at(cc_map_t* ctx, size_t index);
cc_api size_t cc_map_find(cc_map_t* ctx, void* first);
cc_api void* cc_map_get(cc_map_t* ctx, void* first);

cc_api size_t cc_map_count(cc_map_t* ctx);
cc_api bool cc_map_empty(cc_map_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_map_h

