/*! \file BinsonObject.h*/ 
#ifndef BINSON_OBJECT_H
#define BINSON_OBJECT_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "red_black_tree.h"
typedef int8_t BYTE;
typedef struct BinsonField BinsonField;
typedef struct BinsonArray BinsonArray;


/** Enumation BinsonValueType
	\b Enumation for Binson field types
     */
typedef enum {
	BSON_TYPE_BOOLEAN,   /**< enum value for boolean type */
	BSON_TYPE_INTEGER,   /**< enum value for integer type */
	BSON_TYPE_DOUBLE,    /**< enum value for double type */
	BSON_TYPE_STRING,    /**< enum value for string type */
	BSON_TYPE_BYTES,     /**< enum value for byte array type */
	BSON_TYPE_ARRAY,     /**< enum value for array type */
	BSON_TYPE_OBJECT     /**< enum value for object type */
} BinsonValueType;

typedef enum {
	INT_TYPE_NORMAL,   				/**< enum value for boolean type */
	INT_TYPE_STRING_LENGTH,   		/**< enum value for integer type */
	INT_TYPE_BYTEARR_LENGTH,    	/**< enum value for double type */
} IntValueType;

/*! \struct BinsonObject
    \brief struct to represent a binson object
*/
typedef struct {
  rb_red_blk_tree* tree;		/**< red black tree to store all the fields, allow quick access and sorted with field name */
} BinsonObject;

/*! \struct BinsonArray
    \brief struct to represent a binson array
*/
struct BinsonArray{
	size_t arrayLength;			/**< array length */
	BinsonField** arrData;		/**< pointer to the array data*/
} ;

/*! \struct BinsonField
    \brief struct to represent a binson field
*/
struct BinsonField{
	char* fieldName;						/**< field name */
	BinsonValueType fieldType;				/**< field type */
	bool booleanValue;						/**< boolean value, if field type is boolean , otherwise false */
	int64_t integerValue;					/**< integer value, if field type is integer , otherwise 0 */
	double doubleValue;						/**< double value, if field type is double , otherwise 0 */
	char* stringValue;						/**< string value, if field type is string , otherwise NULL */
	BYTE* byteValue;						/**< byte array value, if field type is byte array , otherwise NULL */
	size_t byteArrayLen;					/**< byte array length, if field type is not byte array , it is 0*/
	BinsonArray* arrayValue;				/**< binson array value, if field type is binson array , otherwise NULL */
	BinsonObject* objectValue;				/**< binson object value, if field type is binson object , otherwise NULL */
} ;

/** @brief function to allocate memory to create a binson object.
    @return The pointer to the new created object
*/
BinsonObject* cBSON_create_binson_object();

/** @brief function to free memory allocated for a binson object.
	@param pObj The pointer to the new created object
*/
void cBSON_free_binson_object(BinsonObject* pObj);

/** @brief function to return a list of BinsonField pointers, allow linear access to all the fields
    @return a list of BinsonField pointers.
*/
BinsonField** cBSON_get_fields(BinsonObject* pObj,size_t* size);

/** @brief function to check if certain field exists in this binson object
    @return true if field exists, false if not
*/
bool cBSON_has_value(BinsonObject* pObj, const char* strName);

/** @brief function to get a specific field from a binson object
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
    @return a pointer to the binson field object, if not found then NULL
*/
BinsonField* cBSON_get_field(BinsonObject* pObj, const char* strName);

/** @brief function to get a specific binson object field by name, if the field is not an object type field, return NULL
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
    @return a pointer to the binson object.
*/
BinsonObject* cBSON_get_object(BinsonObject* pObj, const char* strName);

/** @brief function to get a specific binson array field by name, if the field is not an array type field, return NULL
	@param pObj The pointer to the binson array.
	@param strName zero terminated string represents the field name.
    @return a pointer to the binson array .
*/
BinsonArray* cBSON_get_array(BinsonObject* pObj, const char* strName);

/** @brief function to create/set a boolean binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value boolean value for this field.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_bool(BinsonObject* pObj, const char* strName, bool value);

/** @brief function to create/set a integer binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value integer value for this field.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_integer(BinsonObject* pObj, const char* strName, int64_t value);

/** @brief function to create/set a double binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value double value for this field.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_double(BinsonObject* pObj, const char* strName, double value);

/** @brief function to create/set a string binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value string value for this field.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_string(BinsonObject* pObj, const char* strName, const char* value);

/** @brief function to create/set a byte array binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value byte array value for this field.
	@param length byte length of the byte array
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_byte(BinsonObject* pObj, const char* strName, const BYTE* value,size_t length);

/** @brief function to create/set an array binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value pointer to the binson array object.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_array(BinsonObject* pObj, const char* strName, BinsonArray* value);

/** @brief function to create/set an object binson field
	@param pObj The pointer to the binson object.
	@param strName zero terminated string represents the field name.
	@param value pointer to the binson object.
    @return 0 if successful, otherwise failed.
*/
int cBSON_put_object(BinsonObject* pObj, const char* strName, BinsonObject* value);


/** @brief function to serialize a binson object to byte array, please free the byte after use
	@param pObj The pointer to the binson object.
    @return the byte array contains the serialized object. NULL if failed.
*/
BYTE* cBSON_to_bytes(BinsonObject* pObj,size_t* size);

/** @brief function to create a binson object from a byte array
	@param rawData byte array contains the binson data
	@param pObj The pointer to the binson object pointer.
    @return 0 if successful, 1 if failed to parse the object
*/
BinsonObject* cBSON_from_bytes(BYTE* rawData,size_t byteSize);

/** @brief function to convert a binson object to a json string
	@param pObj The pointer to the binson object.
    @return string buffer which contains the json string, please free this buffer after use.
*/
char* cBSON_to_JSON_string(const BinsonObject* pObj);

/** @brief function to create a binson object by parsing a json string
	@param rawData byte array contains the json string
	@param pObj The pointer to the binson object pointer.
    @return 0 if successful, 1 if failed to parse the object
*/
int cBSON_from_JSON_string(char* rawJSONData,BinsonObject** pObj);

/** @brief function to print byte array to std out
	@param arr the byte array 
	@param length length of the byte array
*/
void cBSON_print_byte_array(BYTE* arr, size_t length);
#endif