#include "misc.h"
#include <string.h>

/***********************************************************************/
/*  FUNCTION:  void Assert(int assertion, char* error)  */
/**/
/*  INPUTS: assertion should be a predicated that the programmer */
/*  assumes to be true.  If this assumption is not true the message */
/*  error is printed and the program exits. */
/**/
/*  OUTPUT: None. */
/**/
/*  Modifies input:  none */
/**/
/*  Note:  If DEBUG_ASSERT is not defined then assertions should not */
/*         be in use as they will slow down the code.  Therefore the */
/*         compiler will complain if an assertion is used when */
/*         DEBUG_ASSERT is undefined. */
/***********************************************************************/


void Assert(int assertion, char* error) {
  if(!assertion) {
    printf("Assertion Failed: %s\n",error);
    exit(-1);
  }
}



/***********************************************************************/
/*  FUNCTION:  SafeMalloc */
/**/
/*    INPUTS:  size is the size to malloc */
/**/
/*    OUTPUT:  returns pointer to allocated memory if succesful */
/**/
/*    EFFECT:  mallocs new memory.  If malloc fails, prints error message */
/*             and terminates program. */
/**/
/*    Modifies Input: none */
/**/
/***********************************************************************/

void * SafeMalloc(size_t size) {
  void * result;

  if ( (result = malloc(size)) ) 
  { /* assignment intentional */
#ifdef CBINSON_DEBUG_MEMORY
	void* pNewArr=(void**)malloc((__global_memory_monitor.totalAlloc+1)*sizeof(void*));
	
	if(__global_memory_monitor.totalAlloc!=0)
	{
		memcpy(pNewArr,__global_memory_monitor.pArr,__global_memory_monitor.totalAlloc*sizeof(void*));
	}
	memcpy(pNewArr+__global_memory_monitor.totalAlloc*sizeof(void*),&result,sizeof(void*));
	if(__global_memory_monitor.pArr)
		free(__global_memory_monitor.pArr);
	__global_memory_monitor.pArr=pNewArr;
	__global_memory_monitor.totalAlloc++;
#endif	
    return(result);
  } else {
    printf("memory overflow: malloc failed in SafeMalloc.");
    printf("  Exiting Program.\n");
    exit(-1);
    return(0);
  }
}

void SafeFree(void* p)
{
#ifdef CBINSON_DEBUG_MEMORY	
	size_t i;
	for(i=0;i<__global_memory_monitor.totalAlloc;i++)
	{
		
		if(__global_memory_monitor.pArr[i]==p)
		{
			void* pNewArr=(void**)malloc((__global_memory_monitor.totalAlloc-1)*sizeof(void*));
			memcpy(pNewArr,__global_memory_monitor.pArr,i*sizeof(void*));
			if(i<__global_memory_monitor.totalAlloc-1)
			{
				memcpy(pNewArr+i*sizeof(void*),&__global_memory_monitor.pArr[i+1],(__global_memory_monitor.totalAlloc-i-1)*sizeof(void*));
			}
			free(__global_memory_monitor.pArr);
			__global_memory_monitor.pArr=pNewArr;
			__global_memory_monitor.totalAlloc--;
			break;
		}
	}
#endif		
	if(p)
	{
		free(p);
		p=NULL;
	}
}
void PrintAllocCount()
{
	printf("count: %zu\n",__global_memory_monitor.totalAlloc);
}
void PrintAllocAddress()
{
	size_t i;
	for(i=0;i<__global_memory_monitor.totalAlloc;i++)
	{
		printf("addr: %p\n",__global_memory_monitor.pArr[i]);
	}
}
/*  NullFunction does nothing it is included so that it can be passed */
/*  as a function to RBTreeCreate when no other suitable function has */
/*  been defined */

void NullFunction(void * junk) { ; }
