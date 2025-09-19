#ifndef cc_element_h
#define cc_element_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_element.h
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

//===========================================================================
typedef struct _cc_elements_t
{
	cc_element_t* data;
	size_t capacity;
	size_t chunk;
	size_t count;
}
cc_elements_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void cc_elements_initialize(cc_elements_t* ctx, cc_element_t* data, size_t capacity, size_t chunk);
void cc_elements_clear(cc_elements_t* ctx);

bool cc_elements_erase(cc_elements_t* ctx, size_t index);
bool cc_elements_add(cc_elements_t* ctx, void* ptr);
bool cc_elements_insert(cc_elements_t* ctx, size_t index, void* ptr);

void* cc_elements_at(cc_elements_t* ctx, size_t index);

size_t cc_elements_count(cc_elements_t* ctx);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // cc_element_h

