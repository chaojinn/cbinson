/*! \file BinsonArray.h*/ 
#ifndef BINSON_ARRAY_H
#define BINSON_ARRAY_H
#include "BinsonObject.h"

/** @brief function to allocate memory to create a binson array.
    @return The pointer to the new created array
*/
BinsonArray* cBSON_create_array();
/** @brief function to free memory allocated for a binson array.
	@param pArray The pointer to the array
*/
void cBSON_free_array(BinsonArray* pArray);

/** @brief function to put a integer to binson array
	@param pArray The pointer to the binson array.
	@param value integer value for this field.
    @return the binson filed of that inserted integer object.
*/
BinsonField* cBSON_array_put_integer(BinsonArray* pArray,int64_t value);

/** @brief function to put a double to binson array
	@param pArray The pointer to the binson array.
	@param value double value for this field.
    @return the binson filed of that inserted double object.
*/
BinsonField* cBSON_array_put_double(BinsonArray* pArray,double value);
/** @brief function to put a boolean value to binson array
	@param pArray The pointer to the binson array.
	@param value boolean value for this field.
    @return the binson filed of that inserted boolean object.
*/
BinsonField* cBSON_array_put_bool(BinsonArray* pArray,bool value);
/** @brief function to put a null terminated string to binson array
	@param pArray The pointer to the binson array.
	@param value null terminated string for this field.
    @return the binson filed of that inserted null terminated string.
*/
BinsonField* cBSON_array_put_string(BinsonArray* pArray,const char* value);
/** @brief function to put a byte array to binson array
	@param pArray The pointer to the binson array.
	@param value the byte array.
	@param nArrayLength length for this byte array.
    @return the binson filed of that byte array.
*/
BinsonField* cBSON_array_put_byte(BinsonArray* pArray,const BYTE* value,size_t nArrayLength);
/** @brief function to put a binson object to binson array
	@param pArray The pointer to the binson array.
	@param value pointer to the binson object you want to instert
    @return the binson filed of that inserted binson object
*/
BinsonField* cBSON_array_put_object(BinsonArray* pArray,BinsonObject* value);
/** @brief function to put a binson array to binson array
	@param pArray The pointer to the binson array.
	@param value pointer to the binson array you want to instert
    @return the binson filed of that inserted binson array
*/
BinsonField* cBSON_array_put_array(BinsonArray* pArray,BinsonArray* value);
/** @brief function to get an item from binson array
	@param pArray The pointer to the binson array.
	@param idx the index of the item
    @return the binson filed of that item
*/
BinsonField* cBSON_array_get_item(BinsonArray* pArray,size_t idx);
/** @brief function to remove one item from the binson array
	@param pArray The pointer to the binson array.
	@param idx the index of the item you want to remoev
    @return 0 successful, 1 failed
*/
int cBSON_array_remove_item(BinsonArray* pArray,size_t idx);
/** @brief function to get array size
	@param pArray The pointer to the binson array.
    @return array size
*/
size_t cBSON_array_get_size(BinsonArray* pArray);

#endif