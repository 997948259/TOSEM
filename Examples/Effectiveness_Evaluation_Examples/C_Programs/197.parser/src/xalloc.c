 /***************************************************************************/
 /*                                                                         */
 /* This link grammar system is copyright (C) 1991-1997 by Daniel Sleator   */
 /* (sleator@cs.cmu.edu) and Davy Temperley.  This is work in progress.     */
 /* See http://www.cs.cmu.edu/~sleator for announcements of the latest      */
 /* version, detailed documentation, and rules for commercial use.          */
 /*                                                                         */
 /***************************************************************************/
 
#include "header.h"

#if 1

/* This simple allocator takes time O(number of allocs + number of frees). 
   It works by maintaining the location of the rightmost alloced block
   that is still in use.  xalloc simply gives you space right after the
   last block that's still in use.  When you free a block, it marks it
   free.  If you're freeing the last block it walks back through the
   list looking for the new last block in use.

   This works best for "stack-like" operations.   
 */

typedef unsigned int SIZET;
typedef struct {
    SIZET size;
} Nuggie;

/* before every block of allocated space is a Nuggie */

/* You're given a pointer to an allocated block.
   You want to determine 2 things:  is it in use,
   and you want to find a pointer to the previous
   block.  This information is stored in the Nuggie
   before the beginning of the current block */


#define size_lval(x)    (((Nuggie *)(((char *)x) - sizeof(Nuggie)))->size)
#define prev_block(x)   (((char *) x) - (size_lval(x) & (~1)))
#define in_use(x)       (size_lval(x) & (1))
#define set_use(x)      (size_lval(x) |= (1))
#define clear_use(x)    (size_lval(x) &= (~1))
#define toggle_use(x)   (size_lval(x) ^= (1))

SIZET largest_block;  /* the largest size block you're allowed to allocate */
int max_space_in_use;
int space_in_use;

char * end_of_array;   /* the next place in the array where we will alloc */
char * start_of_array; /* where the array begins */
char * last_block;      /* the rightmost block currently allocated */

#define MEMORY_LIMIT  ((30*1024*1024 * sizeof(char *))/4)
		      /* this is the maximum amount
			 of memory we can use.  For machines
			 with 64 bit pointers we have to increase it */

typedef double Align;
#define MEMORY_ALIGNMENT sizeof(Align)
#define ALIGNMENT_MASK (~(MEMORY_ALIGNMENT-1))

void initialize_memory(void) {
    SIZET i, j;
    if ((MEMORY_ALIGNMENT & (MEMORY_ALIGNMENT-1)) != 0) {
	fprintf(stderr, "sizeof(Align) is not a power of 2.\n");
	exit(1);	
    }
    for (i=0, j=1; i < j; i = j, j = (2*j+1)) largest_block = i;
    largest_block &= ALIGNMENT_MASK;
    largest_block += -sizeof(Nuggie); /* must have room for a nuggie too */
    
    start_of_array = (void *) malloc(MEMORY_LIMIT);
    if (start_of_array == NULL) {
	fprintf(stderr, "Not enough memory for base pool.\n");
	exit(1);
    }

    end_of_array = start_of_array + ((sizeof(Nuggie) + MEMORY_ALIGNMENT-1) & ALIGNMENT_MASK);
    size_lval(end_of_array) = 0;
    max_space_in_use = 0;
    space_in_use = 0;
    last_block = NULL;
}

void * xalloc(int size) {
    char * old_end_of_array;
    if (((unsigned int) size) > largest_block) {
	fprintf(stderr, "Attempt to allocate too big a block (more than %d bytes)\n", largest_block);
	abort();
	exit(1);
    }
    old_end_of_array = end_of_array;
    end_of_array += ((size+sizeof(Nuggie)) + MEMORY_ALIGNMENT-1) & ALIGNMENT_MASK;
    size_lval(end_of_array) = end_of_array - old_end_of_array;
    clear_use(end_of_array);  /* this is not necessary, cause it will be zero */
    set_use(old_end_of_array);
    last_block = old_end_of_array;

    if (((unsigned int)(end_of_array-start_of_array)) > MEMORY_LIMIT) {
	fprintf(stderr, "Ran out of space.  Memory requested so far: %d bytes\n",
	       (end_of_array - start_of_array));
	exit(1);
    }
    space_in_use += size;
    if (space_in_use > max_space_in_use) max_space_in_use = space_in_use;
    return old_end_of_array;
}

void xfree(char * p, int size) {
    char * q;
    /* At this point we could check that the in_use bit for this block
       is set, and also check that the size is right */
    clear_use(p);  /* mark this block as unused */
    if (p == last_block) {
	while (1) {
	    q = prev_block(p);
	    if (q == p) {
		last_block = NULL;
		end_of_array = p;
		break;  /* only happens when we get to the beginning */
	    }
	    if (in_use(q)) {
		last_block = q;
		end_of_array = p;
		break;
	    }
	    p = q;
	}
    }
    space_in_use -= size;
}
/*
void mark_allocation_point(void) {
}
void reset_allocation_point(void) {
}
*/
#endif


#if 0
int max_space_in_use;
int space_in_use;

#define MEMORY_LIMIT 32*1024*1024        /* this is the maximum amount
					    of memory we can use */
/* NOTE: THE FOLLOWING MUST BE A POWER OF 2 */
/* This should be at least equal to the alignment that malloc follows */
#define MEMORY_ALIGNMENT 0x8
char    *memory_array;                  /* this will be aligned base */
int     memory_array_pointer = 0;        /* initialize the pointer */
static int memory_array_marker=0;

void initialize_memory() {
  memory_array = (char *) malloc(MEMORY_LIMIT);
  if (memory_array==NULL) {
    fprintf(stderr, "Not enough memory for base pool.\n");
    exit(1);
  }
}

void mark_allocation_point() {
  memory_array_marker = memory_array_pointer;
}

void reset_allocation_point() {
  memory_array_pointer = memory_array_marker;
}

void * xalloc(int size) {

  /* To allow printing of a nice error message, and keep track of the
     space allocated.
     */   
  
  int temp_pointer;
  
  temp_pointer = memory_array_pointer & (~(MEMORY_ALIGNMENT-1));
  if ((memory_array_pointer & (MEMORY_ALIGNMENT-1)) != 0) {
    temp_pointer += MEMORY_ALIGNMENT;
  }
  memory_array_pointer = temp_pointer + size;
  
  if (memory_array_pointer > MEMORY_LIMIT) {
    fprintf(stderr, "Ran out of space.  Memory requested so far: %d bytes\n",
	   memory_array_pointer);
    exit(1);
  }
  space_in_use += size;
  if (space_in_use > max_space_in_use) max_space_in_use = space_in_use;
  /*  printf("Received request for %d bytes.  Pointer is now at %d\n",
	 size, memory_array_pointer); */
  return (void *) (memory_array+temp_pointer);
}

void xfree(char * p, int size) {
  /* this routine does nothing now */
  if (p == NULL) return;   /* this is to avoid a non-used parameter compiler warning */
  space_in_use -= size;
}

#endif

