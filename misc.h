#include<stdio.h>
#include<stdlib.h>

#ifndef INC_E_MISC_
#define INC_E_MISC_


/*  CONVENTIONS:  All data structures for red-black trees have the prefix */
/*                "rb_" to prevent name conflicts. */
/*                                                                      */
/*                Function names: Each word in a function name begins with */
/*                a capital letter.  An example funcntion name is  */
/*                CreateRedTree(a,b,c). Furthermore, each function name */
/*                should begin with a capital letter to easily distinguish */
/*                them from variables. */
/*                                                                     */
/*                Variable names: Each word in a variable name begins with */
/*                a capital letter EXCEPT the first letter of the variable */
/*                name.  For example, int newLongInt.  Global variables have */
/*                names beginning with "g".  An example of a global */
/*                variable name is gNewtonsConstant. */
struct __memory_monitor{
	size_t totalAlloc;			
	void** pArr;		
} __global_memory_monitor;
void Assert(int assertion, char* error);
void * SafeMalloc(size_t size);
void SafeFree(void* p);
void PrintAllocCount();
void PrintAllocAddress();

#endif








