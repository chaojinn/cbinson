#include "BinsonArray.h"
void** cBSON_array_insert(void** pOldArray,void* newValue,size_t oldSize)
{
	void** newBuf=(void**)SafeMalloc((oldSize+1)*sizeof(void*));
	
	if(pOldArray)
	{
		memcpy(newBuf,pOldArray,oldSize*sizeof(void*));
	}
	
	memcpy(&newBuf[oldSize],&newValue,sizeof(void*));
	
	
	SafeFree(pOldArray);
	return newBuf;
	
}

void** cBSON_array_remove(void** pOldArray,size_t oldSize,size_t idx)
{
	void** newBuf=(void**)SafeMalloc((oldSize-1)*sizeof(void*));
	memcpy(newBuf,pOldArray,idx*sizeof(void*));
	if(idx!=oldSize-1)
		memcpy(&newBuf[idx],&pOldArray[idx+1],(oldSize-idx-1)*sizeof(void*));
	SafeFree(pOldArray);
	return newBuf;
	
}

BinsonArray* cBSON_create_array()
{
	BinsonArray* pArray=(BinsonArray*)SafeMalloc(sizeof(BinsonArray));
	if(pArray==NULL)
	{
		return NULL;
	}
	memset(pArray,0,sizeof(BinsonArray));
	return pArray;
}

void cBSON_free_array(BinsonArray* pArray)
{
	for(size_t i=0;i<pArray->arrayLength;i++)
	{
		BinsonField* field=pArray->arrData[i];
		if(field->fieldName!=NULL)
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
	SafeFree(pArray->arrData);
	SafeFree(pArray);
}

BinsonField* cBSON_array_get_item(BinsonArray* pArray,size_t idx)
{
	
	if(idx>=0&&idx<pArray->arrayLength)
	{
		
		return pArray->arrData[idx];
	}
	return NULL;
}

size_t cBSON_array_get_size(BinsonArray* pArray)
{
	return pArray->arrayLength;
}

BinsonField* cBSON_array_put_integer(BinsonArray* pArray,int64_t value)
{
	
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_INTEGER;
	pField->integerValue=value;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_double(BinsonArray* pArray,double value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_DOUBLE;
	pField->doubleValue=value;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_bool(BinsonArray* pArray,bool value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_BOOLEAN;
	pField->booleanValue=value;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_string(BinsonArray* pArray,const char* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	size_t len=strlen(value);
	char* buf=(char*)SafeMalloc(len+1);
	if(!pField||!buf)
	{
		SafeFree(pField);
		SafeFree(buf);
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	strcpy(buf,value);
	pField->fieldType=BSON_TYPE_STRING;
	pField->stringValue=buf;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_byte(BinsonArray* pArray,const BYTE* value,size_t nArrayLength)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	BYTE* buf=(BYTE*)SafeMalloc(nArrayLength);
	if(!pField||!buf)
	{
		SafeFree(pField);
		SafeFree(buf);
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_BYTES;
	pField->byteValue=buf;
	memcpy(buf,value,nArrayLength);
	pField->byteArrayLen=nArrayLength;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_object(BinsonArray* pArray,BinsonObject* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_OBJECT;
	pField->objectValue=value;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

BinsonField* cBSON_array_put_array(BinsonArray* pArray,BinsonArray* value)
{
	BinsonField* pField=(BinsonField*)SafeMalloc(sizeof(BinsonField));
	if(!pField)
	{
		return NULL;
	}
	memset(pField,0,sizeof(BinsonField));
	pField->fieldType=BSON_TYPE_ARRAY;
	pField->arrayValue=value;
	pArray->arrData=(BinsonField**)cBSON_array_insert((void**)pArray->arrData,(void*)pField,pArray->arrayLength);
	pArray->arrayLength++;
	return pField;
}

int cBSON_array_remove_item(BinsonArray* pArray,size_t idx)
{
	if(idx<0||idx>pArray->arrayLength-1)
		return 1;
	BinsonField* pField=pArray->arrData[idx];
	pArray->arrData=(BinsonField**)cBSON_array_remove((void**)pArray->arrData,pArray->arrayLength,idx);
	pArray->arrayLength--;
	if(pField->fieldName!=NULL)
	{
		SafeFree(pField->fieldName);
	}
	if(pField->stringValue!=NULL)
	{
		SafeFree(pField->stringValue);
	}
	if(pField->byteValue!=NULL)
	{
		SafeFree(pField->byteValue);
	}
	if(pField->arrayValue!=NULL)
	{  
		cBSON_free_array(pField->arrayValue);
	}
	if(pField->objectValue!=NULL)
	{
		cBSON_free_binson_object(pField->objectValue);
	}
	if(pField)
	{
		SafeFree(pField);
	}
	return 0;
}