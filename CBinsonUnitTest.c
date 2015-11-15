#include "BinsonObject.h"
#include "BinsonArray.h"
#include "misc.h"
#include <math.h>
#include <string.h>

bool compareByteArr(BYTE* arr1,BYTE*arr2, size_t size)
{
	for(size_t i=0;i<size;i++)
	{
		if(arr1[i]!=arr2[i])
			return false;
	}
	return true;
}

bool cBSON_test_integer_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[128]={0X40,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X31,0X10,0X80,0X14,0X09,0X69,0X6E,0X74,0X46,
		0X69,0X65,0X6C,0X64,0X32,0X10,0X7F,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X33,0X11,0X00,
		0X80,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X34,0X11,0XFF,0X7F,0X14,0X09,0X69,0X6E,0X74,
		0X46,0X69,0X65,0X6C,0X64,0X35,0X12,0X00,0X00,0X00,
		0X80,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X36,0X12,0XFF,0XFF,0XFF,0X7F,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X37,0X13,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X38,0X13,0XFF,
		0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X41};
	cBSON_put_integer(pBinsonObj,"intField1",-128);
	cBSON_put_integer(pBinsonObj,"intField2",127);
	cBSON_put_integer(pBinsonObj,"intField3",-32768);
	cBSON_put_integer(pBinsonObj,"intField4", 32767);
	cBSON_put_integer(pBinsonObj,"intField5", -2147483648l);
	cBSON_put_integer(pBinsonObj,"intField6", 2147483647l);
	cBSON_put_integer(pBinsonObj,"intField7", -9223372036854775808ull);
	cBSON_put_integer(pBinsonObj,"intField8", 9223372036854775807ull);
	
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,128);
	SafeFree(byteArr);
	return result;
}
bool cBSON_test_double_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[140]={0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X46 ,0X76 ,0X3B ,0X77 ,0X30 ,
		0XD1 ,0X42 ,0XEE ,0XFF ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,
		0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X76 ,
		0X3B ,0X77 ,0X30 ,0XD1 ,0X42 ,0XEE ,0X7F ,0X14 ,0X0C ,0X64 ,
		0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
		0X33 ,0X46 ,0XC9 ,0X76 ,0XBE ,0X9F ,0X1A ,0XC7 ,0X5B ,0X40 ,
		0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X34 ,0X46 ,0X58 ,0XCA ,0X32 ,0XC4 ,0X71 ,
		0X5C ,0XA1 ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,
		0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X35 ,0X46 ,0X19 ,0XAD ,
		0XA3 ,0XAA ,0XAA ,0X46 ,0XE0 ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,
		0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,
		0X46 ,0XF4 ,0X53 ,0X1C ,0XC7 ,0X71 ,0X20 ,0X1B ,0X41 ,0X41 ,};
	cBSON_put_double(pBinsonObj,"doubleField1",-1.7E+308);
	cBSON_put_double(pBinsonObj,"doubleField2",1.7E+308);
	cBSON_put_double(pBinsonObj,"doubleField3",111.111);
	cBSON_put_double(pBinsonObj,"doubleField4",2222.2222);
	cBSON_put_double(pBinsonObj,"doubleField5",33333.33333);
	cBSON_put_double(pBinsonObj,"doubleField6",444444.444444);
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,140);
	SafeFree(byteArr);
	return result;
}

bool cBSON_test_boolean_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[80]={0X40 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X31 ,0X44 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,
		0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X44 ,0X14 ,0X0A ,0X62 ,
		0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X45 ,
		0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,
		0X64 ,0X34 ,0X45 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X35 ,0X44 ,0X14 ,0X0A ,0X62 ,0X6F ,
		0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,0X45 ,0X41 ,};
	cBSON_put_bool(pBinsonObj,"boolField1",true);
	cBSON_put_bool(pBinsonObj,"boolField2",true);
	cBSON_put_bool(pBinsonObj,"boolField3",false);
	cBSON_put_bool(pBinsonObj,"boolField4",false);
	cBSON_put_bool(pBinsonObj,"boolField5",true);
	cBSON_put_bool(pBinsonObj,"boolField6",false);
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,80);
	SafeFree(byteArr);
	return result;
}

bool cBSON_test_string_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[158]={0X40 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X14 ,0X03 ,0X61 ,0X73 ,0X64 ,
		0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X32 ,0X14 ,0X05 ,0X61 ,0X66 ,0X73 ,0X64 ,
		0X66 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,0X77 ,
		0X71 ,0X61 ,0X73 ,0X6A ,0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X34 ,0X14 ,0X16 ,0X61 ,0X6A ,0X73 ,0X68 ,0X66 ,
		0X6B ,0X6A ,0X73 ,0X61 ,0X68 ,0X6B ,0X6B ,0X64 ,0X6B ,0X73 ,
		0X6B ,0X6B ,0X73 ,0X64 ,0X66 ,0X6A ,0X6B ,0X14 ,0X0C ,0X73 ,
		0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
		0X35 ,0X14 ,0X06 ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA5 ,0XBD ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X36 ,0X14 ,0X0C ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA4 ,
		0XA7 ,0XE7 ,0X88 ,0XB7 ,0XE7 ,0X9A ,0X84 ,0X41 ,};
	cBSON_put_string(pBinsonObj,"stringField1","asd");
	cBSON_put_string(pBinsonObj,"stringField2","afsdf");
	cBSON_put_string(pBinsonObj,"stringField3","eewqasjdflkj");
	cBSON_put_string(pBinsonObj,"stringField4","ajshfkjsahkkdkskksdfjk");
	cBSON_put_string(pBinsonObj,"stringField5","你好");
	cBSON_put_string(pBinsonObj,"stringField6","你大爷的");
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,158);
	SafeFree(byteArr);
	return result;
}

bool cBSON_test_byte_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[358]={0X40 ,0X14 ,0X0A ,0X62 ,0X79 ,0X74 ,0X65 ,0X46 ,0X69 ,0X65 ,
	0X6C ,0X64 ,0X31 ,0X19 ,0X2A ,0X01 ,0X40 ,0X14 ,0X0C ,0X73 ,
	0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
	0X31 ,0X14 ,0X03 ,0X61 ,0X73 ,0X64 ,0X14 ,0X0C ,0X73 ,0X74 ,
	0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,
	0X14 ,0X05 ,0X61 ,0X66 ,0X73 ,0X64 ,0X66 ,0X14 ,0X0C ,0X73 ,
	0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
	0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,0X77 ,0X71 ,0X61 ,0X73 ,0X6A ,
	0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,
	0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X34 ,0X14 ,
	0X16 ,0X61 ,0X6A ,0X73 ,0X68 ,0X66 ,0X6B ,0X6A ,0X73 ,0X61 ,
	0X68 ,0X6B ,0X6B ,0X64 ,0X6B ,0X73 ,0X6B ,0X6B ,0X73 ,0X64 ,
	0X66 ,0X6A ,0X6B ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,
	0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X35 ,0X14 ,0X06 ,0XE4 ,
	0XBD ,0XA0 ,0XE5 ,0XA5 ,0XBD ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,
	0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,0X14 ,
	0X0C ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA4 ,0XA7 ,0XE7 ,0X88 ,0XB7 ,
	0XE7 ,0X9A ,0X84 ,0X41 ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,
	0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X46 ,
	0X76 ,0X3B ,0X77 ,0X30 ,0XD1 ,0X42 ,0XEE ,0XFF ,0X14 ,0X0C ,
	0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,
	0X64 ,0X32 ,0X46 ,0X76 ,0X3B ,0X77 ,0X30 ,0XD1 ,0X42 ,0XEE ,
	0X7F ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,
	0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X46 ,0XC9 ,0X76 ,0XBE ,0X9F ,
	0X1A ,0XC7 ,0X5B ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,
	0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X34 ,0X46 ,0X58 ,
	0XCA ,0X32 ,0XC4 ,0X71 ,0X5C ,0XA1 ,0X40 ,0X14 ,0X0C ,0X64 ,
	0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
	0X35 ,0X46 ,0X19 ,0XAD ,0XA3 ,0XAA ,0XAA ,0X46 ,0XE0 ,0X40 ,
	0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,
	0X65 ,0X6C ,0X64 ,0X36 ,0X46 ,0XF4 ,0X53 ,0X1C ,0XC7 ,0X71 ,
	0X20 ,0X1B ,0X41 ,0X41 ,0X14 ,0X0A ,0X62 ,0X79 ,0X74 ,0X65 ,
	0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X18 ,0X0A ,0X40 ,0X14 ,
	0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X14 ,0X0A ,
	0X62 ,0X79 ,0X74 ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,
	0X18 ,0X05 ,0X40 ,0X14 ,0X0C ,0X73 ,0X74 ,0X41 ,};
	BYTE data1[298]={0X40 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X14 ,0X03 ,0X61 ,0X73 ,0X64 ,
		0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X32 ,0X14 ,0X05 ,0X61 ,0X66 ,0X73 ,0X64 ,
		0X66 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,0X77 ,
		0X71 ,0X61 ,0X73 ,0X6A ,0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X34 ,0X14 ,0X16 ,0X61 ,0X6A ,0X73 ,0X68 ,0X66 ,
		0X6B ,0X6A ,0X73 ,0X61 ,0X68 ,0X6B ,0X6B ,0X64 ,0X6B ,0X73 ,
		0X6B ,0X6B ,0X73 ,0X64 ,0X66 ,0X6A ,0X6B ,0X14 ,0X0C ,0X73 ,
		0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
		0X35 ,0X14 ,0X06 ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA5 ,0XBD ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X36 ,0X14 ,0X0C ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA4 ,
		0XA7 ,0XE7 ,0X88 ,0XB7 ,0XE7 ,0X9A ,0X84 ,0X41 ,
		0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X46 ,0X76 ,0X3B ,0X77 ,0X30 ,
		0XD1 ,0X42 ,0XEE ,0XFF ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,
		0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X76 ,
		0X3B ,0X77 ,0X30 ,0XD1 ,0X42 ,0XEE ,0X7F ,0X14 ,0X0C ,0X64 ,
		0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
		0X33 ,0X46 ,0XC9 ,0X76 ,0XBE ,0X9F ,0X1A ,0XC7 ,0X5B ,0X40 ,
		0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X34 ,0X46 ,0X58 ,0XCA ,0X32 ,0XC4 ,0X71 ,
		0X5C ,0XA1 ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,0X75 ,0X62 ,0X6C ,
		0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X35 ,0X46 ,0X19 ,0XAD ,
		0XA3 ,0XAA ,0XAA ,0X46 ,0XE0 ,0X40 ,0X14 ,0X0C ,0X64 ,0X6F ,
		0X75 ,0X62 ,0X6C ,0X65 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,
		0X46 ,0XF4 ,0X53 ,0X1C ,0XC7 ,0X71 ,0X20 ,0X1B ,0X41 ,0X41 ,};
	BYTE data2[10]={0X40 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 };
	BYTE data3[5]={0X40 ,0X14 ,0X0C ,0X73 ,0X74 };
	cBSON_put_byte(pBinsonObj,"byteField1",(BYTE*)data1,298);
	cBSON_put_byte(pBinsonObj,"byteField2",(BYTE*)data2,10);
	cBSON_put_byte(pBinsonObj,"byteField3",(BYTE*)data3,5);
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,358);
	SafeFree(byteArr);
	return result;
	//return true;
}


bool cBSON_test_object_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[77]={0X40 ,0X14 ,0X05 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X40 ,0X14 ,
		0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X11 ,0X39 ,0X30 ,
		0X14 ,0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X14 ,
		0XAE ,0X47 ,0XE1 ,0X7A ,0X54 ,0X36 ,0X40 ,0X14 ,0X06 ,0X66 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X40 ,0X14 ,0X06 ,0X66 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X31 ,0X11 ,0X4D ,0X01 ,0X14 ,0X06 ,0X66 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X00 ,0X00 ,0X00 ,0X00 ,
		0X00 ,0XC0 ,0X7B ,0X40 ,0X41 ,0X41 ,0X41 ,};
	BinsonObject* pChildObj1=cBSON_create_binson_object();
	BinsonObject* pChildObj2=cBSON_create_binson_object();
	cBSON_put_integer(pChildObj1,"field1",12345l);
	cBSON_put_double(pChildObj1,"field2",22.33);
	cBSON_put_integer(pChildObj2,"field1",333);
	cBSON_put_double(pChildObj2,"field2",444);
	cBSON_put_object(pChildObj1,"field3",pChildObj2);
	cBSON_put_object(pBinsonObj,"field",pChildObj1);
	
	size_t bLen=0;
	
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,77);
	SafeFree(byteArr);
	return result;
}

bool cBSON_test_array_encode(BinsonObject* pBinsonObj)
{
	BYTE expectedResult[75]={0X40,0X14,0X08,0X61,0X72,0X72,0X46,0X69,0X65,0X6C,
		0X64,0X42,0X10,0X7B,0X46,0X2D,0XB2,0X9D,0XEF,0XA7,
		0XCA,0X6B,0X40,0X44,0X14,0X05,0X68,0X65,0X6C,0X6C,
		0X6F,0X18,0X0A,0X40,0X14,0X08,0X61,0X72,0X72,0X46,
		0X69,0X65,0X6C,0X40,0X14,0X06,0X66,0X69,0X65,0X6C,
		0X64,0X31,0X11,0X39,0X30,0X14,0X06,0X66,0X69,0X65,
		0X6C,0X64,0X32,0X46,0X14,0XAE,0X47,0XE1,0X7A,0X54,
		0X36,0X40,0X41,0X43,0X41,
	};
	BYTE bArray[10]={0X40,0X14,0X08,0X61,0X72,0X72,0X46,0X69,0X65,0X6C,};
	BinsonObject* pChildObj1=cBSON_create_binson_object();
	cBSON_put_integer(pChildObj1,"field1",12345l);
	cBSON_put_double(pChildObj1,"field2",22.33);
	
	BinsonArray* pArray=cBSON_create_array();
	
	cBSON_array_put_integer(pArray,123);
	cBSON_array_put_double(pArray,222.333);
	cBSON_array_put_bool(pArray,true);
	cBSON_array_put_string(pArray,"hello");
	cBSON_array_put_byte(pArray,bArray,10);
	cBSON_array_put_object(pArray,pChildObj1);
	
	
	cBSON_put_array(pBinsonObj,"arrField",pArray);
	
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,expectedResult,75);
	SafeFree(byteArr);
	return result;
}
bool cBSON_test_array_remove()
{
	BinsonArray* pArray=cBSON_create_array();
	BYTE bArray[10]={0X40,0X14,0X08,0X61,0X72,0X72,0X46,0X69,0X65,0X6C,};
	cBSON_array_put_integer(pArray,123);
	cBSON_array_put_double(pArray,222.333);
	cBSON_array_put_bool(pArray,true);
	cBSON_array_put_string(pArray,"hello");
	cBSON_array_put_byte(pArray,bArray,10);
	int t=cBSON_array_remove_item(pArray,0);
	if(t!=0)
	{
		cBSON_free_array(pArray);
		return false;
	}
	if(pArray->arrayLength!=4||pArray->arrData[0]->doubleValue!=222.333)
	{
		cBSON_free_array(pArray);
		return false;
	}
	t=cBSON_array_remove_item(pArray,3);
	t=cBSON_array_remove_item(pArray,2);
	if(t!=0)
	{
		cBSON_free_array(pArray);
		return false;
	}
	if(pArray->arrayLength!=2||pArray->arrData[1]->booleanValue!=true)
	{
		cBSON_free_array(pArray);
		return false;
	}
	cBSON_free_array(pArray);
	return true;
}

bool cBSON_test_double_decode()
{
	BYTE bArray[44]={0X40,0X14,0X0A,0X66,0X69,0X65,0X6C,0X64,0X4E,0X61,
		0X6D,0X65,0X31,0X46,0XAF,0X94,0X65,0X88,0XE3,0X5C,
		0X91,0X40,0X14,0X0A,0X66,0X69,0X65,0X6C,0X64,0X4E,
		0X61,0X6D,0X65,0X32,0X46,0XDD,0XB5,0X84,0X7C,0XC8,
		0XB4,0XE5,0X40,0X41,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,44);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	bool pass=true;
	float epsilon = 0.000000001;
	for(int i=0;i<nFields;i++)
	{
		if(i==0&&(strcmp("fieldName1",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_DOUBLE||abs(pFields[i]->doubleValue-1111.222)>epsilon))
		{
			
			pass=false;
			break;
		}
		if(i==1&&(strcmp("fieldName2",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_DOUBLE||abs(pFields[i]->doubleValue-44454.2652)>epsilon))
		{
			pass=false;
			break;
		}	
	}
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return pass;
}

bool cBSON_test_integer_decode()
{
	BYTE bArray[128]={0X40,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X31,0X10,0X80,0X14,0X09,0X69,0X6E,0X74,0X46,
		0X69,0X65,0X6C,0X64,0X32,0X10,0X7F,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X33,0X11,0X00,
		0X80,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X34,0X11,0XFF,0X7F,0X14,0X09,0X69,0X6E,0X74,
		0X46,0X69,0X65,0X6C,0X64,0X35,0X12,0X00,0X00,0X00,
		0X80,0X14,0X09,0X69,0X6E,0X74,0X46,0X69,0X65,0X6C,
		0X64,0X36,0X12,0XFF,0XFF,0XFF,0X7F,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X37,0X13,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X14,0X09,0X69,
		0X6E,0X74,0X46,0X69,0X65,0X6C,0X64,0X38,0X13,0XFF,
		0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X41};
	BinsonObject* pObj=cBSON_from_bytes(bArray,128);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	if(pFields==NULL||nFields!=8)
	{
		SafeFree(pFields);
		return false;
	}
	bool pass=true;
	
	for(int i=0;i<nFields;i++)
	{
		if(i==0&&(strcmp("intField1",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=-128))
		{
			pass=false;
			break;
		}
		if(i==1&&(strcmp("intField2",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=127))
		{
			pass=false;
			break;
		}	
		if(i==2&&(strcmp("intField3",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=-32768))
		{
			pass=false;
			break;
		}	
		if(i==3&&(strcmp("intField4",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=32767))
		{
			pass=false;
			break;
		}	
		if(i==4&&(strcmp("intField5",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=-2147483648l))
		{
			pass=false;
			break;
		}	
		if(i==5&&(strcmp("intField6",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=2147483647l))
		{
			pass=false;
			break;
		}	
		if(i==6&&(strcmp("intField7",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=-9223372036854775808ull))
		{
			
			pass=false;
			break;
		}	
		if(i==7&&(strcmp("intField8",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_INTEGER||pFields[i]->integerValue!=9223372036854775807ull))
		{
			
			pass=false;
			break;
		}	
	}
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return pass;

}

bool cBSON_test_boolean_decode()
{
	BYTE bArray[80]={0X40 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X31 ,0X44 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,
		0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X44 ,0X14 ,0X0A ,0X62 ,
		0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X45 ,
		0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,
		0X64 ,0X34 ,0X45 ,0X14 ,0X0A ,0X62 ,0X6F ,0X6F ,0X6C ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X35 ,0X44 ,0X14 ,0X0A ,0X62 ,0X6F ,
		0X6F ,0X6C ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,0X45 ,0X41 ,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,80);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	if(pFields==NULL||nFields!=6)
	{
		SafeFree(pFields);
		return false;
	}
	bool pass=true;
	
	for(int i=0;i<nFields;i++)
	{
		if(i==0&&(strcmp("boolField1",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=true))
		{
			pass=false;
			break;
		}
		if(i==1&&(strcmp("boolField2",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=true))
		{
			pass=false;
			break;
		}
		if(i==2&&(strcmp("boolField3",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=false))
		{
			pass=false;
			break;
		}
		if(i==3&&(strcmp("boolField4",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=false))
		{
			pass=false;
			break;
		}
		if(i==4&&(strcmp("boolField5",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=true))
		{
			pass=false;
			break;
		}
		if(i==5&&(strcmp("boolField6",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BOOLEAN||pFields[i]->booleanValue!=false))
		{
			pass=false;
			break;
		}
	}
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return pass;
}

bool cBSON_test_string_decode()
{
	BYTE bArray[158]={0X40 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X14 ,0X03 ,0X61 ,0X73 ,0X64 ,
		0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X32 ,0X14 ,0X05 ,0X61 ,0X66 ,0X73 ,0X64 ,
		0X66 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,0X77 ,
		0X71 ,0X61 ,0X73 ,0X6A ,0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X34 ,0X14 ,0X16 ,0X61 ,0X6A ,0X73 ,0X68 ,0X66 ,
		0X6B ,0X6A ,0X73 ,0X61 ,0X68 ,0X6B ,0X6B ,0X64 ,0X6B ,0X73 ,
		0X6B ,0X6B ,0X73 ,0X64 ,0X66 ,0X6A ,0X6B ,0X14 ,0X0C ,0X73 ,
		0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,
		0X35 ,0X14 ,0X06 ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA5 ,0XBD ,0X14 ,
		0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
		0X6C ,0X64 ,0X36 ,0X14 ,0X0C ,0XE4 ,0XBD ,0XA0 ,0XE5 ,0XA4 ,
		0XA7 ,0XE7 ,0X88 ,0XB7 ,0XE7 ,0X9A ,0X84 ,0X41 ,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,158);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	if(pFields==NULL||nFields!=6)
	{
		SafeFree(pFields);
		return false;
	}
	bool pass=true;
	
	for(int i=0;i<nFields;i++)
	{
		if(i==0&&(strcmp("stringField1",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"asd")!=0))
		{
			pass=false;
			break;
		}
		if(i==1&&(strcmp("stringField2",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"afsdf")!=0))
		{
			pass=false;
			break;
		}
		if(i==2&&(strcmp("stringField3",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"eewqasjdflkj")!=0))
		{
			pass=false;
			break;
		}
		if(i==3&&(strcmp("stringField4",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"ajshfkjsahkkdkskksdfjk")!=0))
		{
			pass=false;
			break;
		}
		if(i==4&&(strcmp("stringField5",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"你好")!=0))
		{
			pass=false;
			break;
		}
		if(i==5&&(strcmp("stringField6",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_STRING||strcmp(pFields[i]->stringValue,"你大爷的")!=0))
		{
			pass=false;
			break;
		}
	}
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return pass;
}

bool cBSON_test_byte_decode()
{
	BYTE bArray[93]={0X40 ,0X14 ,0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X18 ,
		0X0A ,0X66 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,
		0X46 ,0X14 ,0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X18 ,
		0X14 ,0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,
		0X77 ,0X71 ,0X61 ,0X73 ,0X6A ,0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,
		0X14 ,0X14 ,0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X18 ,
		0X05 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X14 ,0X06 ,0X66 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X34 ,0X18 ,0X10 ,0X0C ,0X73 ,0X74 ,0X72 ,
		0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,0X6C ,0X64 ,0X36 ,0X14 ,
		0X0C ,0XE4 ,0X41 ,};
	BYTE arr1[10]={0X66 ,0X14 ,0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,};
	BYTE arr2[20]={0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X14 ,0X0C ,0X65 ,0X65 ,0X77 ,
				0X71 ,0X61 ,0X73 ,0X6A ,0X64 ,0X66 ,0X6C ,0X6B ,0X6A ,0X14 ,};
	BYTE arr3[5]={0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,};
	BYTE arr4[16]={0X0C ,0X73 ,0X74 ,0X72 ,0X69 ,0X6E ,0X67 ,0X46 ,0X69 ,0X65 ,
				0X6C ,0X64 ,0X36 ,0X14 ,0X0C ,0XE4 ,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,93);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	if(pFields==NULL||nFields!=4)
	{
		SafeFree(pFields);
		return false;
	}
	bool pass=true;
	
	for(int i=0;i<nFields;i++)
	{
		if(i==0&&(strcmp("field1",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BYTES||!compareByteArr(arr1,pFields[i]->byteValue,pFields[i]->byteArrayLen)))
		{
			cBSON_print_byte_array(pFields[i]->byteValue,pFields[i]->byteArrayLen);
			pass=false;
			break;
		}
		if(i==1&&(strcmp("field2",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BYTES||!compareByteArr(arr2,pFields[i]->byteValue,pFields[i]->byteArrayLen)))
		{
			pass=false;
			break;
		}
		if(i==2&&(strcmp("field3",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BYTES||!compareByteArr(arr3,pFields[i]->byteValue,pFields[i]->byteArrayLen)))
		{
			pass=false;
			break;
		}
		if(i==3&&(strcmp("field4",pFields[i]->fieldName)!=0||pFields[i]->fieldType!=BSON_TYPE_BYTES||!compareByteArr(arr4,pFields[i]->byteValue,pFields[i]->byteArrayLen)))
		{
			pass=false;
			break;
		}
	}
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return pass;
}
bool cBSON_test_object_decode()
{
	BYTE bArray[77]={0X40 ,0X14 ,0X05 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X40 ,0X14 ,
		0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X31 ,0X11 ,0X39 ,0X30 ,
		0X14 ,0X06 ,0X66 ,0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X14 ,
		0XAE ,0X47 ,0XE1 ,0X7A ,0X54 ,0X36 ,0X40 ,0X14 ,0X06 ,0X66 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X33 ,0X40 ,0X14 ,0X06 ,0X66 ,0X69 ,
		0X65 ,0X6C ,0X64 ,0X31 ,0X11 ,0X4D ,0X01 ,0X14 ,0X06 ,0X66 ,
		0X69 ,0X65 ,0X6C ,0X64 ,0X32 ,0X46 ,0X00 ,0X00 ,0X00 ,0X00 ,
		0X00 ,0XC0 ,0X7B ,0X40 ,0X41 ,0X41 ,0X41 ,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,77);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	if(pFields==NULL||nFields!=1||pFields[0]->fieldType!=BSON_TYPE_OBJECT||pFields[0]->objectValue==NULL||strcmp(pFields[0]->fieldName,"field")!=0)
	{
		SafeFree(pFields);
		return false;
	}
	float epsilon = 0.000000001;
	BinsonField** pFields1=cBSON_get_fields(pFields[0]->objectValue,&nFields);
	if(pFields1==NULL||nFields!=3
		||pFields1[0]->fieldType!=BSON_TYPE_INTEGER
		||pFields1[0]->integerValue!=12345l
		||strcmp(pFields1[0]->fieldName,"field1")!=0
		||pFields1[1]->fieldType!=BSON_TYPE_DOUBLE
		||abs(pFields1[1]->doubleValue-22.33)>epsilon
		||strcmp(pFields1[1]->fieldName,"field2")!=0
		||pFields1[2]->fieldType!=BSON_TYPE_OBJECT
		||pFields1[2]->objectValue==NULL
		||strcmp(pFields1[2]->fieldName,"field3")!=0)
	{
		SafeFree(pFields);
		return false;
	}
	BinsonField** pFields2=cBSON_get_fields(pFields1[2]->objectValue,&nFields);
	if(pFields2==NULL||nFields!=2
		||pFields2[0]->fieldType!=BSON_TYPE_INTEGER
		||pFields2[0]->integerValue!=333
		||strcmp(pFields2[0]->fieldName,"field1")!=0
		||pFields2[1]->fieldType!=BSON_TYPE_DOUBLE
		||abs(pFields2[1]->doubleValue-444)>epsilon
		||strcmp(pFields2[1]->fieldName,"field2")!=0
		)
	{
		SafeFree(pFields);
		return false;
	}
	SafeFree(pFields2);
	SafeFree(pFields1);
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return true;
}

bool cBSON_test_array_decode()
{
	BYTE bArray[75]={0X40,0X14,0X08,0X61,0X72,0X72,0X46,0X69,0X65,0X6C,
		0X64,0X42,0X10,0X7B,0X46,0X2D,0XB2,0X9D,0XEF,0XA7,
		0XCA,0X6B,0X40,0X44,0X14,0X05,0X68,0X65,0X6C,0X6C,
		0X6F,0X18,0X0A,0X40,0X14,0X08,0X61,0X72,0X72,0X46,
		0X69,0X65,0X6C,0X40,0X14,0X06,0X66,0X69,0X65,0X6C,
		0X64,0X31,0X11,0X39,0X30,0X14,0X06,0X66,0X69,0X65,
		0X6C,0X64,0X32,0X46,0X14,0XAE,0X47,0XE1,0X7A,0X54,
		0X36,0X40,0X41,0X43,0X41,
	};
	BYTE bt[10]={0X40,0X14,0X08,0X61,0X72,0X72,0X46,0X69,0X65,0X6C,};
	BinsonObject* pObj=cBSON_from_bytes(bArray,75);
	if(pObj==NULL)
		return false;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	
	if(nFields!=1)
	{
		SafeFree(pFields);
		cBSON_free_binson_object(pObj);
		return false;
	}
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pObj,&bLen);
	
	if(bLen!=75)
	{
		SafeFree(pFields);
		SafeFree(byteArr);
		cBSON_free_binson_object(pObj);
		return false;
	}
	//cBSON_print_byte_array(byteArr,bLen);
	bool result=compareByteArr(byteArr,bArray,bLen);
	SafeFree(byteArr);
	
	SafeFree(pFields);
	cBSON_free_binson_object(pObj);
	return result;
}

int main ( int arc, char **argv ) 
{
	printf("test started\n");
	BinsonObject* pBinsonObj=NULL;
	bool r=false;
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_integer_encode(pBinsonObj);
	printf("\tcBSON_test_integer_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_double_encode(pBinsonObj);
	printf("\tcBSON_test_double_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_boolean_encode(pBinsonObj);
	printf("\tcBSON_test_boolean_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_string_encode(pBinsonObj);
	printf("\tcBSON_test_string_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_byte_encode(pBinsonObj);
	printf("\tcBSON_test_byte_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_object_encode(pBinsonObj);
	printf("\tcBSON_test_object_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	pBinsonObj=cBSON_create_binson_object();
	r=cBSON_test_array_encode(pBinsonObj);
	printf("\tcBSON_test_array_encode result:%s\n",r?"Passed":"Failed");
	cBSON_free_binson_object(pBinsonObj);
	
	r=cBSON_test_array_remove();
	printf("\tcBSON_test_array_remove result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_double_decode();
	printf("\tcBSON_test_double_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_integer_decode();
	printf("\tcBSON_test_integer_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_boolean_decode();
	printf("\tcBSON_test_boolean_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_string_decode();
	printf("\tcBSON_test_string_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_byte_decode();
	printf("\tcBSON_test_byte_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_object_decode();
	printf("\tcBSON_test_object_decode result:%s\n",r?"Passed":"Failed");
	
	r=cBSON_test_array_decode();
	printf("\tcBSON_test_array_decode result:%s\n",r?"Passed":"Failed");
	
	printf("test finished\n");
	PrintAllocCount();
	PrintAllocAddress();
	
	return 0;
}