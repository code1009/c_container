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

typedef bool (*cc_equal_t)(cc_element_t* left, cc_element_t* right);
typedef bool (*cc_less_t )(cc_element_t* left, cc_element_t* right);

#ifdef __cplusplus
}
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cc_api bool cc_equal_int32_t (cc_element_t* left, cc_element_t* right);
cc_api bool cc_equal_int16_t (cc_element_t* left, cc_element_t* right);
cc_api bool cc_equal_int8_t  (cc_element_t* left, cc_element_t* right);

cc_api bool cc_equal_uint32_t(cc_element_t* left, cc_element_t* right);
cc_api bool cc_equal_uint16_t(cc_element_t* left, cc_element_t* right);
cc_api bool cc_equal_uint8_t (cc_element_t* left, cc_element_t* right);

cc_api bool cc_equal_size_t  (cc_element_t* left, cc_element_t* right);

cc_api bool cc_equal_char    (cc_element_t* left, cc_element_t* right);
cc_api bool cc_equal_c_str   (cc_element_t* left, cc_element_t* right);

//===========================================================================
cc_api bool cc_less_int32_t  (cc_element_t* left, cc_element_t* right);
cc_api bool cc_less_int16_t  (cc_element_t* left, cc_element_t* right);
cc_api bool cc_less_int8_t   (cc_element_t* left, cc_element_t* right);

cc_api bool cc_less_uint32_t (cc_element_t* left, cc_element_t* right);
cc_api bool cc_less_uint16_t (cc_element_t* left, cc_element_t* right);
cc_api bool cc_less_uint8_t  (cc_element_t* left, cc_element_t* right);

cc_api bool cc_less_size_t   (cc_element_t* left, cc_element_t* right);

cc_api bool cc_less_char     (cc_element_t* left, cc_element_t* right);
cc_api bool cc_less_c_str    (cc_element_t* left, cc_element_t* right);





#endif




