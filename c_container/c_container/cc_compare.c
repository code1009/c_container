/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_compare.c
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
#include "cc_compare.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define cc_pointer_value_equal(T,a,b) \
	T* ap;                      \
	T* bp;                      \
	T  av;                      \
	T  bv;                      \
	                            \
	                            \
	cc_debug_assert((a)!=NULL); \
	cc_debug_assert((b)!=NULL); \
	                            \
	                            \
	ap = (T*)(a);               \
	bp = (T*)(b);               \
	av = *ap;                   \
	bv = *bp;                   \
	                            \
	                            \
	if (av == bv)               \
	{                           \
		return true;            \
	}                           \
	                            \
	return false

//===========================================================================
#define cc_pointer_value_less(T,a,b) \
	T* ap;                      \
	T* bp;                      \
	T  av;                      \
	T  bv;                      \
	                            \
	                            \
	cc_debug_assert((a)!=NULL); \
	cc_debug_assert((b)!=NULL); \
	                            \
	                            \
	ap = (T*)(a);               \
	bp = (T*)(b);               \
	av = *ap;                   \
	bv = *bp;                   \
	                            \
	                            \
	if (av < bv)                \
	{                           \
		return true;            \
	}                           \
	                            \
	return false






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_equal_pvalue_int32_t(void* left, void* right) { cc_pointer_value_equal(int32_t, left, right); }
cc_api bool cc_equal_pvalue_int16_t(void* left, void* right) { cc_pointer_value_equal(int16_t, left, right); }
cc_api bool cc_equal_pvalue_int8_t(void* left, void* right) { cc_pointer_value_equal(int8_t, left, right); }

cc_api bool cc_equal_pvalue_uint32_t(void* left, void* right) { cc_pointer_value_equal(uint32_t, left, right); }
cc_api bool cc_equal_pvalue_uint16_t(void* left, void* right) { cc_pointer_value_equal(uint16_t, left, right); }
cc_api bool cc_equal_pvalue_uint8_t(void* left, void* right) { cc_pointer_value_equal(uint8_t, left, right); }

cc_api bool cc_equal_pvalue_size_t(void* left, void* right) { cc_pointer_value_equal(size_t, left, right); }

cc_api bool cc_equal_pvalue_char(void* left, void* right) { cc_pointer_value_equal(char, left, right); }

cc_api bool cc_equal_c_str(void* left, void* right)
{
	char* ap;
	char* bp;


	cc_debug_assert(left  != NULL);
	cc_debug_assert(right != NULL);


	ap = (char*)left;
	bp = (char*)right;

	if (0==strcmp(ap, bp))
	{
		return true;
	}

	return false;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_less_pvalue_int32_t(void* left, void* right) { cc_pointer_value_less(int32_t, left, right); }
cc_api bool cc_less_pvalue_int16_t(void* left, void* right) { cc_pointer_value_less(int16_t, left, right); }
cc_api bool cc_less_pvalue_int8_t(void* left, void* right) { cc_pointer_value_less(int8_t, left, right); }

cc_api bool cc_less_pvalue_uint32_t(void* left, void* right) { cc_pointer_value_less(uint32_t, left, right); }
cc_api bool cc_less_pvalue_uint16_t(void* left, void* right) { cc_pointer_value_less(uint16_t, left, right); }
cc_api bool cc_less_pvalue_uint8_t(void* left, void* right) { cc_pointer_value_less(uint8_t, left, right); }

cc_api bool cc_less_pvalue_size_t(void* left, void* right) { cc_pointer_value_less(size_t, left, right); }

cc_api bool cc_less_pvalue_char(void* left, void* right) { cc_pointer_value_less(char, left, right); }

cc_api bool cc_less_c_str(void* left, void* right)
{
	char* ap;
	char* bp;


	cc_debug_assert(left != NULL);
	cc_debug_assert(right != NULL);


	ap = (char*)left;
	bp = (char*)right;

	if (0 > strcmp(ap, bp))
	{
		return true;
	}

	return false;
}



