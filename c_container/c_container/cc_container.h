#ifndef cc_container_h
#define cc_container_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_container.h
// 
// # Created by: code1009
// # Created on: 09-18, 2005.
// 
// # Description:
//   @ code template
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_element_t
{
	void* ptr;
}
cc_element_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _cc_container_t
{
	cc_element_t* data;
	size_t capacity;
	size_t chunk;
	size_t count;
}
cc_container_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void cc_container_initialize(cc_container_t* ctx, cc_element_t* data, size_t capacity, size_t chunk);
void cc_container_clear(cc_container_t* ctx);

bool cc_container_erase(cc_container_t* ctx, size_t index);
bool cc_container_add(cc_container_t* ctx, void* ptr);
bool cc_container_insert(cc_container_t* ctx, size_t index, void* ptr);

void* cc_container_at(cc_container_t* ctx, size_t index);

size_t cc_container_count(cc_container_t* ctx);
bool cc_container_is_empty(cc_container_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_container_h

