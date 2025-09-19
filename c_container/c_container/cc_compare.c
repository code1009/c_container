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
#define cc_equal(T,a,b) \
	T* ap;                  \
	T* bp;                  \
	T  av;                  \
	T  bv;                  \
	                        \
	                        \
	ap = (T*)a;             \
	bp = (T*)b;             \
	av = *ap;               \
	bv = *bp;               \
	                        \
	                        \
	if (av == bv)           \
	{                       \
		return true;        \
	}                       \
	                        \
	return false


#define cc_less(T,a,b) \
	T* ap;                  \
	T* bp;                  \
	T  av;                  \
	T  bv;                  \
	                        \
	                        \
	ap = (T*)a;             \
	bp = (T*)b;             \
	av = *ap;               \
	bv = *bp;               \
	                        \
	                        \
	if (av < bv)            \
	{                       \
		return true;        \
	}                       \
	                        \
	return false






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool cc_equal_int32_t (void* left, void* right) { cc_equal(int32_t , left, right); }
bool cc_equal_int16_t (void* left, void* right) { cc_equal(int16_t , left, right); }
bool cc_equal_int8_t  (void* left, void* right) { cc_equal(int8_t  , left, right); }

bool cc_equal_uint32_t(void* left, void* right) { cc_equal(uint32_t, left, right); }
bool cc_equal_uint16_t(void* left, void* right) { cc_equal(uint16_t, left, right); }
bool cc_equal_uint8_t (void* left, void* right) { cc_equal(uint8_t , left, right); }

bool cc_equal_size_t(void* left, void* right) { cc_equal(size_t, left, right); }

bool cc_equal_char(void* left, void* right) { cc_equal(char, left, right); }

bool cc_equal_c_str(void* left, void* right)
{
	char** ap;
	char** bp;


	ap = (char**)left;
	bp = (char**)right;

	if (0==strcmp(*ap, *bp))
	{
		return true;
	}

	return false;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool cc_less_int32_t  (void* left, void* right) { cc_less(int32_t , left, right); }
bool cc_less_int16_t  (void* left, void* right) { cc_less(int16_t , left, right); }
bool cc_less_int8_t   (void* left, void* right) { cc_less(int8_t  , left, right); }

bool cc_less_uint32_t (void* left, void* right) { cc_less(uint32_t, left, right); }
bool cc_less_uint16_t (void* left, void* right) { cc_less(uint16_t, left, right); }
bool cc_less_uint8_t  (void* left, void* right) { cc_less(uint8_t , left, right); }

bool cc_less_size_t(void* left, void* right) { cc_less(size_t, left, right); }

bool cc_less_char(void* left, void* right) { cc_less(char, left, right); }

bool cc_less_c_str(void* left, void* right)
{
	char** ap;
	char** bp;


	ap = (char**)left;
	bp = (char**)right;

	if (0 > strcmp(*ap, *bp))
	{
		return true;
	}

	return false;
}



