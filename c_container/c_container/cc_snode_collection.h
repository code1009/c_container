#ifndef cc_snode_collection_h
#define cc_snode_collection_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_snode_collection.h
// 
// # Created by: code1009
// # Created on: 09-18, 2025.
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_snode_collection_t
{
	cc_snode_t* elements;
	size_t max_count;
	uintptr_t param;

	size_t count;
}
cc_snode_collection_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_snode_collection_initialize(cc_snode_collection_t* ctx, cc_snode_t* elements, size_t max_count, uintptr_t param);
cc_api uintptr_t cc_snode_collection_param(cc_snode_collection_t* ctx);

cc_api void cc_snode_collection_clear(cc_snode_collection_t* ctx);
cc_api bool cc_snode_collection_erase(cc_snode_collection_t* ctx, size_t index);
cc_api bool cc_snode_collection_add(cc_snode_collection_t* ctx, cc_snode_t* next, void* element);
cc_api bool cc_snode_collection_insert(cc_snode_collection_t* ctx, size_t index, cc_snode_t* next, void* element);

cc_api cc_snode_t* cc_snode_collection_at(cc_snode_collection_t* ctx, size_t index);
cc_api void* cc_snode_collection_next(cc_snode_collection_t* ctx, size_t index);
cc_api void* cc_snode_collection_element(cc_snode_collection_t* ctx, size_t index);

cc_api size_t cc_snode_collection_count(cc_snode_collection_t* ctx);
cc_api bool cc_snode_collection_empty(cc_snode_collection_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_snode_collection_h

