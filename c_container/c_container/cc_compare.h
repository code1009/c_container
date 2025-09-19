#ifndef cc_compare_h
#define cc_compare_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_compare.h
// 
// # Created by: code1009
// # Created on: 09-18, 2005.
// 
// # Description:
//   @ 
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef bool (*cc_equal_t)(void* left, void* right);
typedef bool (*cc_less_t )(void* left, void* right);


//===========================================================================
CC_API bool cc_equal_int32_t (void* left, void* right);
CC_API bool cc_equal_int16_t (void* left, void* right);
CC_API bool cc_equal_int8_t  (void* left, void* right);

CC_API bool cc_equal_uint32_t(void* left, void* right);
CC_API bool cc_equal_uint16_t(void* left, void* right);
CC_API bool cc_equal_uint8_t (void* left, void* right);

CC_API bool cc_equal_size_t  (void* left, void* right);

CC_API bool cc_equal_char    (void* left, void* right);
CC_API bool cc_equal_c_str   (void* left, void* right);

//===========================================================================
CC_API bool cc_less_int32_t  (void* left, void* right);
CC_API bool cc_less_int16_t  (void* left, void* right);
CC_API bool cc_less_int8_t   (void* left, void* right);

CC_API bool cc_less_uint32_t (void* left, void* right);
CC_API bool cc_less_uint16_t (void* left, void* right);
CC_API bool cc_less_uint8_t  (void* left, void* right);

CC_API bool cc_less_size_t   (void* left, void* right);

CC_API bool cc_less_char     (void* left, void* right);
CC_API bool cc_less_c_str    (void* left, void* right);





#endif




