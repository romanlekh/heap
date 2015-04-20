#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
/*
*   Suffix 'g' with variable name means "global".
*   Suffix 'p' with variable name means "pointer".
*
*
*/

// Structure for saving info about blocked memory
typedef struct
{
    // Pointer to user-memory block
    char *res_ptr;
    // Number of used bytes
    size_t mem_length;
    // Memory accessibility (0 - free, 1 - locked)
    char bool_use;
} Memory_info;


// Pointers for begin and end of reserve memory.
static char *gp_res_end;
static char *gp_res_beg;

// Pointers for begin of user-available memory.
// End of memory - gp_res_beg.
static char *gp_beg;

// Below "move"-pointers
// Pointer for next free user-memory
// (position of pointer is included).
static char *gp_next;

// Pointer for next free reserve-memory
// (position of pointer is included).
static Memory_info *gp_res_next;

// Part of reserve memory.
static const float gres_part = 0.20;

void SetMemory(void *ptr1, void *ptr2)
{
    gp_beg = (char*)ptr1;
    gp_res_end = (char*)ptr2;

    // Separate user and reserve memory
    gp_res_beg = gp_res_end - (int)( (gp_res_end - gp_beg) * gres_part );

    // Set "next" pointers
    gp_next = gp_beg;
    gp_res_next = (Memory_info*)(gp_res_end - sizeof(Memory_info));

    // Initialization first block of memory info;
    // this block will every time move to left
    gp_res_next->mem_length = gp_res_beg - gp_beg;
    gp_res_next->res_ptr = gp_beg;
    gp_res_next->bool_use = 0;
}

// Try to try to unite adjacent memory blocks.
// Using only in function MemLoc().
char* UniteFreeMem(size_t mem_size);

void* MemLoc(size_t mem_size)
{
    /*// In first case looking already free memory (second-hand memory)
    Memory_info *temp_res_next = gp_res_next;
    Memory_info *temp_res_end = (Memory_info*)gp_res_end;
    while( temp_res_next < temp_res_end )
    {
        if( temp_res_next->bool_use == 0 &&
           temp_res_next->mem_length == mem_size )
        {
            temp_res_next->bool_use = 1;
            return temp_res_next->res_ptr;
        }
        ++temp_res_next;
    }*/

    // In first case looking already free memory (second-hand memory);
    // try to unite adjacent memory blocks

    // Set position of location
    char* ptr_loc = UniteFreeMem( mem_size );
    if( ptr_loc )
        return (void*)ptr_loc;

    printf("\nSECOND\n");
    // Second case - no free second-hand memory

    // Check if enough free reserve-memory
    if( (char*)gp_res_next - gp_res_beg <  sizeof(Memory_info) )
        return NULL;
    // Check if enough free user-memory
    if( gp_res_beg - gp_next < mem_size )
        return NULL;

    // Set position of location from gp_next
    ptr_loc = gp_next;

    // Move to the next memory block
    // and write info about this block to reserve memory
    // by using Memory_info structure
    gp_next += mem_size;
    Memory_info mem_info_new = {ptr_loc, mem_size, 1};
    Memory_info mem_info_next ={NULL, gp_res_next->mem_length - mem_size, 0};
    *gp_res_next = mem_info_new;
    *--gp_res_next = mem_info_next;

    return (void*)ptr_loc;
}

char* UniteFreeMem(size_t mem_size)
{
    Memory_info *temp_res_next = gp_res_next + 1;
    Memory_info *temp_res_end = (Memory_info*)gp_res_end - 1;

    // Counter for bool_use; need for check free memory
    size_t cout_bool_use = 0;
    // Counter for total previous free memory
    size_t cout_prev_mem = 0;

    // Pointer to start of unite block
    Memory_info *unite_start = temp_res_end;
    while( temp_res_next < temp_res_end )
    {
        // Check if memory available
        cout_bool_use += temp_res_end->bool_use;
        if( cout_bool_use == 0 )
        {
            cout_prev_mem += temp_res_end->mem_length;
            if( cout_prev_mem == mem_size )
            {
                unite_start->bool_use = 1;
                unite_start->mem_length = mem_size;
                //while( unite_start == temp_res_next )
                    printf("\nFIRST\n");
                return unite_start->res_ptr;
            }
        }
        else
        {
            cout_bool_use = 0;
            cout_prev_mem = 0;
            unite_start = temp_res_end - 1;
        }
        --temp_res_end;
    }
    return NULL;
}

void FreeMem(void *ptr)
{
    Memory_info *temp_res_next = gp_res_next + 1;
    Memory_info *temp_res_end = (Memory_info*)gp_res_end;
    char *temp_ptr = (char*)ptr;

    // Searching until end of reserve memory
    // (in next release will be binary-mod of heap
    // and search will be faster)
    while( temp_res_next < temp_res_end )
    {
        if( temp_res_next->res_ptr == temp_ptr )
        {
            temp_res_next->bool_use = 0;
            break;
        }
        ++temp_res_next;
    }
}




