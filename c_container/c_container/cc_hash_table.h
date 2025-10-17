#ifndef cc_hash_table_h
#define cc_hash_table_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_hash_table.h
// 
// # Created by: code1009
// # Created on: 09-18, 2025.
// 
// # Description:
//   @ open addressing hash table
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef size_t cc_hash_key_t;

typedef cc_hash_key_t (*cc_hash_key_generate_t)(const void* data);

typedef enum _cc_hash_entry_status_t
{
	cc_hash_entry_status_empty = 0,
	cc_hash_entry_status_removed,
	cc_hash_entry_status_filled
}
cc_hash_entry_status_t;

//===========================================================================
typedef struct _cc_hash_entry_t
{
	cc_hash_entry_status_t status;
	cc_element_t element;
}
cc_hash_entry_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_hash_table_t
{
	cc_hash_key_generate_t key_generate;
	cc_equal_t equal;
	cc_hash_entry_t* table;
	size_t max_count;
	uintptr_t param;

	size_t count;
}
cc_hash_table_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_hash_entry_initialize(cc_hash_entry_t* ctx);
cc_api void* cc_hash_entry_element(cc_hash_entry_t* ctx);
cc_api cc_hash_entry_status_t cc_hash_entry_status(cc_hash_entry_t* ctx);
cc_api void cc_hash_entry_fill(cc_hash_entry_t* ctx, void* element);
cc_api void cc_hash_entry_remove(cc_hash_entry_t* ctx);
cc_api void cc_hash_entry_clear(cc_hash_entry_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api cc_hash_key_t cc_hash_key_djb2(const void* data, const size_t length);

cc_api size_t cc_hash_probe(const size_t index, const size_t attempt, const size_t size);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api void cc_hash_table_initialize(cc_hash_table_t* ctx, cc_hash_key_generate_t key_generate, cc_equal_t equal, cc_hash_entry_t* table, size_t max_count, uintptr_t param);
cc_api uintptr_t cc_hash_table_param(cc_hash_table_t* ctx);

cc_api void cc_hash_table_clear(cc_hash_table_t* ctx);
cc_api bool cc_hash_table_erase(cc_hash_table_t* ctx, size_t index);
cc_api bool cc_hash_table_add(cc_hash_table_t* ctx, void* element);

cc_api cc_hash_entry_t* cc_hash_table_at(cc_hash_table_t* ctx, size_t index);
cc_api void* cc_hash_table_element(cc_hash_table_t* ctx, size_t index);

cc_api size_t cc_hash_table_find(cc_hash_table_t* ctx, void* element);
cc_api void* cc_hash_table_element_by_key(cc_hash_table_t* ctx, void* element);

cc_api size_t cc_hash_table_count(cc_hash_table_t* ctx);
cc_api bool cc_hash_table_empty(cc_hash_table_t* ctx);

cc_api size_t cc_hash_table_size(cc_hash_table_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_hash_table_h

