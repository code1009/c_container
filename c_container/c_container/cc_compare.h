#ifndef cc_compare_h
#define cc_compare_h

/////////////////////////////////////////////////////////////////////////////
// 
// # File: cc_compare.h
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
#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*cc_equal_t)(void* left, void* right);
typedef bool (*cc_less_t )(void* left, void* right);

#ifdef __cplusplus
}
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_equal_pvalue_int32_t (void* left, void* right);
cc_api bool cc_equal_pvalue_int16_t (void* left, void* right);
cc_api bool cc_equal_pvalue_int8_t  (void* left, void* right);

cc_api bool cc_equal_pvalue_uint32_t(void* left, void* right);
cc_api bool cc_equal_pvalue_uint16_t(void* left, void* right);
cc_api bool cc_equal_pvalue_uint8_t (void* left, void* right);

cc_api bool cc_equal_pvalue_size_t  (void* left, void* right);

cc_api bool cc_equal_pvalue_char    (void* left, void* right);

cc_api bool cc_equal_c_str          (void* left, void* right);

//===========================================================================
cc_api bool cc_less_pvalue_int32_t  (void* left, void* right);
cc_api bool cc_less_pvalue_int16_t  (void* left, void* right);
cc_api bool cc_less_pvalue_int8_t   (void* left, void* right);

cc_api bool cc_less_pvalue_uint32_t(void* left, void* right);
cc_api bool cc_less_pvalue_uint16_t(void* left, void* right);
cc_api bool cc_less_pvalue_uint8_t  (void* left, void* right);

cc_api bool cc_less_pvalue_size_t   (void* left, void* right);

cc_api bool cc_less_pvalue_char     (void* left, void* right);

cc_api bool cc_less_c_str           (void* left, void* right);





#endif




