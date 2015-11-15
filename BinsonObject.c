#include "BinsonObject.h"
#include "BinsonArray.h"

BYTE* cBSONInteger_to_bytes(int64_t value,IntValueType type,size_t* size);
BYTE* cBSONField_to_bytes(BinsonField* pObj,size_t* size);
BinsonField*  cBSON_parse_field(BYTE* rawData,size_t startIdx,size_t* pEndIdx,size_t byteSize,bool skipFielname);
//function to compare 2 binson fields
int BinsonFieldComp(const void* a,const void* b) 
{
  
  char* fieldName1=(char*)a;
  char* fieldName2=(char*)b;
  int result=strcmp(fieldName1,fieldName2);
  if(result<0)
	  return -1;
  else if(result>0)
	  return 1;
  //printf("compare %s vs %s, result:%d\n",fieldName1,fieldName2,result);
  return result;
}

void KeyDest(void* keyString) 
{
  if(keyString)
  {
	SafeFree((char*)keyString);
  }
}


void reverse_byte_array(BYTE* arr, int length)
{
    int i, temp;
    for (i=0; i<length/2; i++)
    {
        temp = arr[i];
        arr[i] = arr[length-i-1];
        arr[length-i-1] = temp;
    }
}

void cBSON_print_byte_array(BYTE* arr, size_t length)
{
	for(int i=0;i<length;i++)
	{
		if(i%10==0&&i!=0)
		{
			printf("\n");
		}
		printf("%02X,",(uint8_t)arr[i]);
	}
	printf("\n");
}


void IntPrint(const void* a) 
{
  printf("%s",(char*)a);
}

void InfoPrint(void* a) 
{
  ;
}

void InfoDest(void *a)
{
	BinsonField* field=(BinsonField*)a;
	if(field->fieldName)
	{
		SafeFree(field->fieldName);
	}
	if(field->stringValue!=NULL)
	{
		SafeFree(field->stringValue);
	}
	if(field->byteValue!=NULL)
	{
		SafeFree(field->byteValue);
	}
	if(field->arrayValue!=NULL)
	{  
		cBSON_free_array(field->arrayValue);
	}
	if(field->objectValue!=NULL)
	{
		cBSON_free_binson_object(field->objectValue);
	}
	if(field)
	{
		SafeFree(field);
	}
}

BinsonObject* cBSON_create_binson_object()
{
	BinsonObject* pObject=(BinsonObject*)SafeMalloc(sizeof(BinsonObject));
	memset(pObject,0,sizeof(BinsonObject));
	if(pObject)
		pObject->tree=RBTreeCreate(BinsonFieldComp,KeyDest,InfoDest,IntPrint,InfoPrint);
	if(pObject!=NULL&&pObject->tree!=NULL)
		return pObject;
	return (BinsonObject*)NULL;
}

void cBSON_free_binson_object(BinsonObject* pObj)
{	
	if(pObj!=NULL&&pObj->tree!=NULL)
	{
		RBTreeDestroy(pObj->tree);
	}
	if(pObj!=NULL)
	{
		SafeFree(pObj);	
	}
	
}

int cBSON_put_integer(BinsonObject* pObj, const char* strName, int64_t value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_INTEGER;
	pField->integerValue=value;
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_bool(BinsonObject* pObj, const char* strName, bool value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_BOOLEAN;
	pField->booleanValue=value;
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_double(BinsonObject* pObj, const char* strName, double value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_DOUBLE;
	pField->doubleValue=value;
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_string(BinsonObject* pObj, const char* strName, const char* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_STRING;
	pField->stringValue=(char*)SafeMalloc(strlen(value)+1);
	strcpy(pField->stringValue,value);
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_byte(BinsonObject* pObj, const char* strName, const BYTE* value,size_t length)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_BYTES;
	pField->byteValue=(BYTE*)SafeMalloc(length);
	pField->byteArrayLen=length;
	memcpy(pField->byteValue,value,length);
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_array(BinsonObject* pObj, const char* strName, BinsonArray* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_ARRAY;
	pField->arrayValue=value;
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}

int cBSON_put_object(BinsonObject* pObj, const char* strName, BinsonObject* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return 1;
	}
	memset(pField,0,sizeof(BinsonField));
	char *keyName=(char*)SafeMalloc(strlen(strName)+1);
	pField->fieldName=(char*)SafeMalloc(strlen(strName)+1);
	if(!pField->fieldName||!keyName)
	{
		return 1;
	}
	strcpy(keyName,strName);
	strcpy(pField->fieldName,strName);
	pField->fieldType=BSON_TYPE_OBJECT;
	pField->objectValue=value;
	RBTreeInsert(pObj->tree,keyName,(void*)pField);
	return 0;
}


BinsonField** cBSON_get_fields(BinsonObject* pObj,size_t* size)
{
	rb_red_blk_node* pNode=NULL;
	BinsonField** pFieldArray=NULL;
	stk_stack *fieldStack = RBGetAllNodes(pObj->tree);
	(*size)=fieldStack->stackSize-1;
	
	size_t allocSize=sizeof(BinsonField*)*(fieldStack->stackSize-1);
	pFieldArray=(BinsonField**)SafeMalloc(allocSize);
	if(pFieldArray==NULL)
	{
		(*size)=0;
		return NULL;
	}
	int i=0;
	
	while ( true) 
	{
		pNode =(rb_red_blk_node*)StackPop(fieldStack);
		if(pNode==NULL)
		{
			break;
		}
		if(pNode->info==NULL) //skip tree root
			continue;
		BinsonField* pField=(BinsonField*)(pNode->info);
		
	    pFieldArray[i]=pField;
		i++;
	}
	
	SafeFree(fieldStack);
	return pFieldArray;
}

BinsonField* cBSON_get_field(BinsonObject* pObj, const char* strName)
{
	rb_red_blk_node* pNode=NULL;
	pNode=RBExactQuery(pObj->tree, (void*)strName);
	if(pNode!=NULL&&pNode->info!=NULL)
	{
		return (BinsonField*)pNode->info;
	}
	return NULL;
}

bool cBSON_has_value(BinsonObject* pObj, const char* strName)
{
	if(cBSON_get_field(pObj,strName)==NULL)
		return false;
	return true;
}

BinsonObject* cBSON_get_object(BinsonObject* pObj, const char* strName)
{
	BinsonField* pField=cBSON_get_field(pObj,strName);
	if(pField!=NULL&&pField->fieldType==BSON_TYPE_OBJECT&&pField->objectValue!=NULL)
	{
		return pField->objectValue;
	}
	return NULL;
}

BinsonArray* cBSON_get_array(BinsonObject* pObj, const char* strName)
{
	BinsonField* pField=cBSON_get_field(pObj,strName);
	if(pField!=NULL&&pField->fieldType==BSON_TYPE_ARRAY&&pField->arrayValue!=NULL)
	{
		return pField->arrayValue;
	}
	return NULL;
}

BYTE* cBSONInteger_to_bytes(int64_t value,IntValueType type,size_t* size) //0 normal int,1 string len,2 byte len
{
	BYTE* fieldBuf=NULL;
	size_t arrLength=0;
	
	if(value>=-0x80l&&value<=0x7Fl)
	{
		arrLength=2;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		if(type==INT_TYPE_NORMAL)
			fieldBuf[0]=0x10;
		else if(type==INT_TYPE_STRING_LENGTH)
			fieldBuf[0]=0x14;
		else if(type==INT_TYPE_BYTEARR_LENGTH)
			fieldBuf[0]=0x18;
		memcpy(fieldBuf+1,&value,1);
	}
	else if(value>=-0x8000l&&value<=0x7FFFl)
	{
		arrLength=3;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		if(type==INT_TYPE_NORMAL)
			fieldBuf[0]=0x11;
		else if(type==INT_TYPE_STRING_LENGTH)
			fieldBuf[0]=0x15;
		else if(type==INT_TYPE_BYTEARR_LENGTH)
			fieldBuf[0]=0x19;
		memcpy(fieldBuf+1,&value,2);
	}
	else if(value>=-0x80000000l&&value<=0x7FFFFFFFl)
	{
		arrLength=5;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		if(type==INT_TYPE_NORMAL)
			fieldBuf[0]=0x12;
		else if(type==INT_TYPE_STRING_LENGTH)
			fieldBuf[0]=0x16;
		else if(type==INT_TYPE_BYTEARR_LENGTH)
			fieldBuf[0]=0x1a;
		memcpy(fieldBuf+1,&value,4);
	}
	else 
	{
		arrLength=9;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		if(type==INT_TYPE_NORMAL)
			fieldBuf[0]=0x13;
		else
		{
			*size=0;
			return NULL;
		}
		memcpy(fieldBuf+1,&value,8);
	}
	*size=arrLength;
	return fieldBuf;
}

BYTE* cBSONField_to_bytes(BinsonField* pField,size_t* size)
{
	BYTE* fieldBuf=NULL;
	size_t arrLength=0;
	if(pField->fieldType==BSON_TYPE_INTEGER)
	{
		fieldBuf=cBSONInteger_to_bytes(pField->integerValue,INT_TYPE_NORMAL,&arrLength);
	}
	else if(pField->fieldType==BSON_TYPE_BOOLEAN)
	{
		arrLength=1;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		fieldBuf[0]=pField->booleanValue?0x44:0x45;
	}
	else if(pField->fieldType==BSON_TYPE_DOUBLE)
	{
		arrLength=9;
		fieldBuf=(BYTE*)SafeMalloc(arrLength);
		if(fieldBuf==NULL)
			return NULL;
		fieldBuf[0]=0x46;
		memcpy(fieldBuf+1,&(pField->doubleValue),8);
	}
	else if(pField->fieldType==BSON_TYPE_STRING)
	{
		size_t fieldLengthSize=0;
		size_t fieldSize=strlen(pField->stringValue);
		BYTE* pFL=cBSONInteger_to_bytes(fieldSize,INT_TYPE_STRING_LENGTH,&fieldLengthSize);
		if(pFL==NULL)
			return NULL;
		fieldBuf=(BYTE*)SafeMalloc(fieldLengthSize+fieldSize);
		if(fieldBuf==NULL)
		{
			SafeFree(pFL);
			return NULL;
		}
		memcpy(fieldBuf,pFL,fieldLengthSize);
		memcpy(fieldBuf+fieldLengthSize,pField->stringValue,fieldSize);
		arrLength=fieldLengthSize+fieldSize;
		SafeFree(pFL);
	}
	else if(pField->fieldType==BSON_TYPE_BYTES)
	{
		size_t fieldLengthSize=0;
		BYTE* pFL=cBSONInteger_to_bytes(pField->byteArrayLen,INT_TYPE_BYTEARR_LENGTH,&fieldLengthSize);
		if(pFL==NULL)
			return NULL;
		fieldBuf=(BYTE*)SafeMalloc(fieldLengthSize+pField->byteArrayLen);
		if(fieldBuf==NULL)
		{
			SafeFree(pFL);
			return NULL;
		}
		memcpy(fieldBuf,pFL,pField->byteArrayLen);
		memcpy(fieldBuf+fieldLengthSize,pField->byteValue,pField->byteArrayLen);
		arrLength=fieldLengthSize+pField->byteArrayLen;
		SafeFree(pFL);
	}
	else if(pField->fieldType==BSON_TYPE_OBJECT)
	{
		fieldBuf=cBSON_to_bytes(pField->objectValue,&arrLength);
		if(fieldBuf==NULL||arrLength==0)
			return NULL;
	}
	else if(pField->fieldType==BSON_TYPE_ARRAY)
	{
		arrLength=0;
		fieldBuf=NULL;
		
		for(size_t i=0;i<pField->arrayValue->arrayLength;i++)
		{
			
			size_t tBufSize=0;
			BYTE* tBuf=NULL;
			tBuf=cBSONField_to_bytes(pField->arrayValue->arrData[i],&tBufSize);
			if(tBuf==NULL||tBufSize==0)
			{
				return NULL;
			}
			
			BYTE* newBuf=(BYTE*)SafeMalloc(arrLength+tBufSize);
			if(newBuf==NULL)
				return NULL;
			if(fieldBuf!=NULL)
				memcpy(newBuf,fieldBuf,arrLength);
			memcpy(newBuf+arrLength,tBuf,tBufSize);
			arrLength+=tBufSize;
			if(fieldBuf!=NULL)
				SafeFree(fieldBuf);
			SafeFree(tBuf);
			fieldBuf=newBuf;
		}
		BYTE* newBuf=(BYTE*)SafeMalloc(arrLength+2);
		newBuf[0]=0x42;
		memcpy(newBuf+1,fieldBuf,arrLength);
		newBuf[arrLength+1]=0x43;
		arrLength+=2;
		SafeFree(fieldBuf);
		fieldBuf=newBuf;
	}
	
	if(pField->fieldName!=NULL)
	{
		size_t fieldnameSize=strlen(pField->fieldName);
		{
			BYTE* newFieldBuf=(BYTE*)SafeMalloc(arrLength+fieldnameSize);
			if(newFieldBuf==NULL)
				return NULL;
			
			memcpy(newFieldBuf,pField->fieldName,fieldnameSize);
			memcpy(newFieldBuf+fieldnameSize,fieldBuf,arrLength);
			if(fieldBuf)
			{
				SafeFree(fieldBuf);	
			}
			fieldBuf=newFieldBuf;
			arrLength=arrLength+fieldnameSize;
		}
		
		{
			size_t fieldLengthSize=0;
			BYTE* pFL=cBSONInteger_to_bytes(fieldnameSize,1,&fieldLengthSize);
			if(pFL==NULL||fieldLengthSize==0)
				return NULL;
			BYTE* newFieldBuf=(BYTE*)SafeMalloc(arrLength+fieldLengthSize);
			if(newFieldBuf==NULL)
				return NULL;
			memcpy(newFieldBuf,pFL,fieldLengthSize);
			memcpy(newFieldBuf+fieldLengthSize,fieldBuf,arrLength);
			SafeFree(pFL);
			SafeFree(fieldBuf);
			fieldBuf=newFieldBuf;
			arrLength=arrLength+fieldLengthSize;
		}
	}
	
	*size=arrLength;
	return fieldBuf;
}

BYTE* cBSON_to_bytes(BinsonObject* pObj,size_t* size)
{
	BYTE* arr=NULL;
	int currentByteArrSize=0;
	size_t nFields=0;
	BinsonField** pFields=cBSON_get_fields(pObj,&nFields);
	for(int i=0;i<nFields;i++)
	{
		BYTE* newArr=NULL;
		BYTE* newValueArr=NULL;
		size_t newLength=0;
		newValueArr=cBSONField_to_bytes(pFields[i],&newLength);
		if(newValueArr==NULL||newLength==0)
		{
			return NULL;
		}
		newArr =(BYTE*)SafeMalloc(currentByteArrSize+newLength);
		if(newArr==NULL)
			return NULL;
		if(currentByteArrSize>0)
		{
			memcpy(newArr,arr,currentByteArrSize);
		}
		memcpy(newArr+currentByteArrSize,newValueArr,newLength);
		currentByteArrSize+=newLength;
		if(arr!=NULL)
			SafeFree(arr);
		if(newValueArr!=NULL)
			SafeFree(newValueArr);
		arr=newArr;
	}
	
	SafeFree(pFields);
	BYTE* newArr=(BYTE*)SafeMalloc(currentByteArrSize+2);
	newArr[0]=0x40;
	if(arr!=NULL)
		memcpy(newArr+1,arr,currentByteArrSize);
	newArr[currentByteArrSize+1]=0x41;
	if(arr!=NULL)
	{
		SafeFree(arr);
	}
	arr=newArr;
	currentByteArrSize+=2;
	*size=currentByteArrSize;
	return arr;
}
char*  cBSON_parse_field_name(BYTE* rawData,size_t startIdx,size_t* pEndIdx,size_t byteSize)
{
	if(startIdx+1>=byteSize-1)
	{
		return NULL;
	}
	BYTE typeLength=rawData[startIdx];
	if(typeLength!=0x14&&typeLength!=0x15&&typeLength!=0x16)
		return NULL;
	int32_t fieldLen=0;
	size_t nBytes=0;
	if(typeLength==0x14)
	{
		nBytes=1;
		if(startIdx+1+nBytes>=byteSize-1)
		{
			return NULL;
		}
		memcpy(&fieldLen,rawData+startIdx+1,nBytes);
		if(startIdx+1+nBytes+fieldLen>byteSize-1)
		{
			return NULL;
		}
	}
	else if(typeLength==0x15)
	{
		nBytes=2;
		if(startIdx+1+nBytes>=byteSize-1)
			return NULL;
		memcpy(&fieldLen,rawData+startIdx+1,nBytes);
		if(startIdx+1+nBytes+fieldLen>byteSize-1)
			return NULL;
	}
	else if(typeLength==0x16)
	{
		nBytes=4;
		if(startIdx+1+nBytes>=byteSize-1)
			return NULL;
		memcpy(&fieldLen,rawData+startIdx+1,nBytes);
		if(startIdx+1+nBytes+fieldLen>byteSize-1)
			return NULL;
	}
	char* pFieldName=(char*)SafeMalloc(fieldLen+1);
	
	memset(pFieldName,0,fieldLen+1);
	if(pFieldName==NULL)
		return NULL;
	memcpy(pFieldName,rawData+startIdx+1+nBytes,fieldLen);
	//printf("field name:%s, %d\n",pFieldName,pFieldName);
	*pEndIdx=startIdx+1+nBytes+fieldLen;
	return pFieldName;
	
}

BinsonObject*  cBSON_parse_object(BYTE* rawData,size_t startIdx,size_t* pEndIdx,size_t byteSize)
{
	if(startIdx+1>=byteSize-1)
	{
		return NULL;
	}
	if(byteSize-startIdx<2)
		return NULL;
	if(rawData[startIdx]!=0x40)
	{
		return NULL;
	}
	BinsonObject* pBinsonObj=cBSON_create_binson_object();
	if(pBinsonObj==NULL)
		return NULL;
	size_t endIdx=startIdx+1;
	startIdx=endIdx;
	
	while(rawData[endIdx]!=0x41&&endIdx<byteSize-1)
	{
		
		BinsonField* pField=cBSON_parse_field(rawData,startIdx,&endIdx,byteSize,false);
		if(pField==NULL)
		{
			cBSON_free_binson_object(pBinsonObj);
			return NULL;
		}
		char* key=(char*)SafeMalloc(strlen(pField->fieldName)+1);
		
		if(key==NULL)
		{
			InfoDest(pField);
			cBSON_free_binson_object(pBinsonObj);
			return NULL;
		}
		strcpy(key,pField->fieldName);
		RBTreeInsert(pBinsonObj->tree,key,pField);
		startIdx=endIdx;
	}
	if(rawData[endIdx]==0x41&&endIdx<byteSize-1)
	{
		*pEndIdx=endIdx+1;
		return pBinsonObj;	
	}
	else
	{
		return NULL;
	}
}

BinsonArray*  cBSON_parse_array(BYTE* rawData,size_t startIdx,size_t* pEndIdx,size_t byteSize)
{
	if(startIdx+1>=byteSize-1)
	{
		return NULL;
	}
	if(byteSize-startIdx<2)
		return NULL;
	if(rawData[startIdx]!=0x42)
	{
		return NULL;
	}
	BinsonArray* pBinsonArray=cBSON_create_array();
	if(pBinsonArray==NULL)
		return NULL;
	size_t endIdx=startIdx+1;
	startIdx=endIdx;
	
	while(rawData[endIdx]!=0x43&&endIdx<byteSize-1)
	{
		BinsonField* pField=cBSON_parse_field(rawData,startIdx,&endIdx,byteSize,true);
		if(pField==NULL)
		{
			cBSON_free_array(pBinsonArray);
			return NULL;
		}
		if(pField->fieldType==BSON_TYPE_INTEGER)
			cBSON_array_put_integer(pBinsonArray,pField->integerValue);
		else if(pField->fieldType==BSON_TYPE_DOUBLE)
			cBSON_array_put_double(pBinsonArray,pField->doubleValue);
		else if(pField->fieldType==BSON_TYPE_BOOLEAN)
			cBSON_array_put_bool(pBinsonArray,pField->booleanValue);
		else if(pField->fieldType==BSON_TYPE_STRING)
			cBSON_array_put_string(pBinsonArray,pField->stringValue);
		else if(pField->fieldType==BSON_TYPE_BYTES)
			cBSON_array_put_byte(pBinsonArray,pField->byteValue,pField->byteArrayLen);
		else if(pField->fieldType==BSON_TYPE_ARRAY)
			cBSON_array_put_array(pBinsonArray,pField->arrayValue);
		else if(pField->fieldType==BSON_TYPE_OBJECT)
			cBSON_array_put_object(pBinsonArray,pField->objectValue);
		if(pField->fieldName)
			SafeFree(pField->fieldName);
		if(pField->stringValue)
			SafeFree(pField->stringValue);
		if(pField->byteValue)
			SafeFree(pField->byteValue);
		if(pField)
			SafeFree(pField);
		startIdx=endIdx;
	}
	if(rawData[endIdx]==0x43&&endIdx<byteSize-1)
	{
		*pEndIdx=endIdx+1;
		return pBinsonArray;	
	}
	else
	{
		return NULL;
	}
	return NULL;
}

BinsonField*  cBSON_parse_field(BYTE* rawData,size_t startIdx,size_t* pEndIdx,size_t byteSize,bool skipFielname)
{
	BinsonField* pField=NULL;
	char* pFieldName=NULL;
	size_t endIdx=0;
	
	if(!skipFielname)
	{
		pFieldName=cBSON_parse_field_name(rawData,startIdx,&endIdx,byteSize);
		
		if(pFieldName==NULL)
		{
			return NULL;
		}
		startIdx=endIdx;
		if(startIdx>=byteSize-1)
		{
			SafeFree(pFieldName);
			return NULL;
		}
	}
	
	BYTE byteType=rawData[startIdx];
	if(byteType==0x10||byteType==0x11||byteType==0x12||byteType==0x13) //integer
	{
		int64_t value=0;
		size_t nBytes=0;
		if(byteType==0x10)
		{
			nBytes=1;
			int8_t t=0;
			if(startIdx+1+nBytes>byteSize-1)
				return NULL;
			memcpy(&t,rawData+startIdx+1,nBytes);
			value=(int64_t)t;
		}
		else if(byteType==0x11)
		{
			nBytes=2;
			int16_t t=0;
			if(startIdx+1+nBytes>byteSize-1)
				return NULL;
			memcpy(&t,rawData+startIdx+1,nBytes);
			value=(int64_t)t;
		}
		else if(byteType==0x12)
		{
			nBytes=4;
			int32_t t=0;
			if(startIdx+1+nBytes>byteSize-1)
				return NULL;
			memcpy(&t,rawData+startIdx+1,nBytes);
			value=(int64_t)t;
		}
		else if(byteType==0x13)
		{
			nBytes=8;
			
			if(startIdx+1+nBytes>byteSize-1)
				return NULL;
			memcpy(&value,rawData+startIdx+1,nBytes);
			
		}
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_INTEGER;
		pField->integerValue=value;
		*pEndIdx=startIdx+nBytes+1;
	}
	else if(byteType==0x46) //double
	{
		if(startIdx+1+8>byteSize-1)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		double value=0;
		memcpy(&value,rawData+1+startIdx,8);
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_DOUBLE;
		pField->doubleValue=value;
		*pEndIdx=startIdx+8+1;
	}
	else if(byteType==0x44||byteType==0x45) //boolean
	{
		if(startIdx+1>byteSize-1)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_BOOLEAN;
		pField->booleanValue=(byteType==0x44)?true:false;
		*pEndIdx=startIdx+1;
	}
	else if(byteType==0x14||byteType==0x15||byteType==0x16) //string
	{
		if(startIdx+1>byteSize-1)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		
		char* pStringValue=NULL;
		size_t endIdx=0;
		pStringValue=cBSON_parse_field_name(rawData,startIdx,&endIdx,byteSize);
		if(pStringValue==NULL)
		{
			return NULL;
		}
		
		if(startIdx>=byteSize-1)
		{
			SafeFree(pStringValue);
			return NULL;
		}
		
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			SafeFree(pStringValue);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_STRING;
		pField->stringValue=pStringValue;
		*pEndIdx=endIdx;
		
	}
	else if(byteType==0x18||byteType==0x19||byteType==0x1a) //byteArray
	{
		if(startIdx+1>=byteSize-1)
		{
			return NULL;
		}
		BYTE typeLength=rawData[startIdx];
		if(typeLength!=0x18&&typeLength!=0x19&&typeLength!=0x1a)
			return NULL;
		int32_t fieldLen=0;
		size_t nBytes=0;
		if(typeLength==0x18)
		{
			nBytes=1;
			if(startIdx+1+nBytes>=byteSize-1)
			{
				return NULL;
			}
			memcpy(&fieldLen,rawData+startIdx+1,nBytes);
			if(startIdx+1+nBytes+fieldLen>byteSize-1)
			{
				return NULL;
			}
		}
		else if(typeLength==0x19)
		{
			nBytes=2;
			if(startIdx+1+nBytes>=byteSize-1)
			{
				return NULL;
			}
			memcpy(&fieldLen,rawData+startIdx+1,nBytes);
			if(startIdx+1+nBytes+fieldLen>byteSize-1)
			{
				return NULL;
			}
		}
		else if(typeLength==0x1a)
		{
			nBytes=4;
			if(startIdx+1+nBytes>=byteSize-1)
			{
				return NULL;
			}
			memcpy(&fieldLen,rawData+startIdx+1,nBytes);
			if(startIdx+1+nBytes+fieldLen>byteSize-1)
			{
				return NULL;
			}
		}
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_BYTES;
		pField->byteArrayLen=fieldLen;
		pField->byteValue=(BYTE*)SafeMalloc(fieldLen);
		if(pField->byteValue==NULL)
			return NULL;
		memcpy(pField->byteValue,rawData+startIdx+1+nBytes,fieldLen);
		*pEndIdx=startIdx+1+nBytes+fieldLen;
	}
	else if(byteType==0x42) //Array
	{
		
		if(startIdx+1>byteSize-1)
		{
			return NULL;
		}
		
		BinsonArray* pArray=cBSON_parse_array(rawData,startIdx,pEndIdx,byteSize);
		
		if(pArray==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			cBSON_free_array(pArray);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_ARRAY;
		pField->arrayValue=pArray;
		
	}
	else if(byteType==0x40) //object
	{
		if(startIdx+1>byteSize-1)
		{
			return NULL;
		}
		
		BinsonObject* pObj=cBSON_parse_object(rawData,startIdx,pEndIdx,byteSize);
		if(pObj==NULL)
		{
			SafeFree(pFieldName);
			return NULL;
		}
		pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
		if(pField==NULL)
		{
			SafeFree(pFieldName);
			cBSON_free_binson_object(pObj);
			return NULL;
		}
		memset(pField,0,sizeof(BinsonField));
		pField->fieldName=pFieldName;
		pField->fieldType=BSON_TYPE_OBJECT;
		pField->objectValue=pObj;
	}
	return pField;
}

BinsonObject* cBSON_from_bytes(BYTE* rawData,size_t byteSize)
{
	if(byteSize<2)
		return NULL;
	if(rawData[0]!=0x40||rawData[byteSize-1]!=0x41)
	{
		return NULL;
	}
	BinsonObject* pBinsonObj=cBSON_create_binson_object();
	if(pBinsonObj==NULL)
		return NULL;
	if(byteSize==2)
		return pBinsonObj;
	size_t startIdx=1;
	size_t endIdx=0;
	BinsonField* pField=cBSON_parse_field(rawData,startIdx,&endIdx,byteSize,false);
	if(pField!=NULL)
	{
		char* key=(char*)SafeMalloc(strlen(pField->fieldName)+1);		
		if(key==NULL)
		{
			InfoDest(pField);
			cBSON_free_binson_object(pBinsonObj);
			return NULL;
		}
		strcpy(key,pField->fieldName);
		RBTreeInsert(pBinsonObj->tree,key,pField);
	}
	while(endIdx!=byteSize-1)
	{
		
		if(pField==NULL)
		{
			cBSON_free_binson_object(pBinsonObj);
			pBinsonObj=NULL;
			break;
		}
		
		startIdx=endIdx;
		pField=cBSON_parse_field(rawData,startIdx,&endIdx,byteSize,false);
		char* key=(char*)SafeMalloc(strlen(pField->fieldName)+1);
		
		if(key==NULL)
		{
			InfoDest(pField);
			cBSON_free_binson_object(pBinsonObj);
			return NULL;
		}
		strcpy(key,pField->fieldName);
		RBTreeInsert(pBinsonObj->tree,key,pField);
	}
	return pBinsonObj;
}
/*int main ( int arc, char **argv ) 
{
	BinsonObject* pBinsonObj=cBSON_create_binson_object();
	cBSON_put_integer(pBinsonObj,"intKey",1111222333l);
	cBSON_put_double(pBinsonObj,"doubleKey",222.33);
	cBSON_put_bool(pBinsonObj,"boolKey",true);
	cBSON_put_string(pBinsonObj,"stringField","hello world");
	
	

	size_t size=0;
	BinsonField** pFields=cBSON_get_fields(pBinsonObj,&size);
	printf("total fields:%d\n",size,pFields);
	for(int i=0;i<size;i++)
	{
		if(pFields[i]!=NULL&&pFields[i]->fieldType==BSON_TYPE_INTEGER)
			printf("value %d %s: %d\n",i,pFields[i]->fieldName,pFields[i]->integerValue);
		else if(pFields[i]!=NULL&&pFields[i]->fieldType==BSON_TYPE_BOOLEAN)
			printf("value %d %s: %d\n",i,pFields[i]->fieldName,pFields[i]->booleanValue);
		else if(pFields[i]!=NULL&&pFields[i]->fieldType==BSON_TYPE_DOUBLE)
			printf("value %d %s: %f\n",i,pFields[i]->fieldName,pFields[i]->doubleValue);
		else if(pFields[i]!=NULL&&pFields[i]->fieldType==BSON_TYPE_STRING)
			printf("value %d %s: %s\n",i,pFields[i]->fieldName,pFields[i]->stringValue);
		else 
			printf("null node\n");
	}
	SafeFree(pFields);
	
	size_t bLen=0;
	BYTE* byteArr=cBSON_to_bytes(pBinsonObj,&bLen);
	printf("len:%d\n",bLen);
	print_byte_array(byteArr,bLen);
	cBSON_free_binson_object(pBinsonObj);
	printf("test done\n");
	
    return 0; // Indicates that everything vent well.
}*/