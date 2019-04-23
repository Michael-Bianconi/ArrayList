/**
 * @author Michael Bianconi
 * @since 04-02-2019
 *
 * Source code for ArrayList.h.
 */
#include "arraylist.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <stdarg.h> // valist
#include <string.h> // strcpy

void ArrayList_add(ArrayList list, char* item)
{
    // Copy the item into a buffer
    char* data = malloc(strlen(item) + 1);
    strcpy(data, item);

    // ArrayList memory allocation reached, double allocation
    if (list->size == list->buffer) ArrayList_expand(list, list->buffer);

    // Add the item to the list
    list->items[list->size] = data;
    list->size++;   
}


void ArrayList_addAll(ArrayList list, int argc, ...)
{
    // initialize variable arguments list
    va_list valist;
    va_start(valist, argc);

    // add each to the list
    for (int i = 0; i < argc; i++)
    {
        ArrayList_add(list, va_arg(valist, char*));
    }
}


void ArrayList_addArray(ArrayList dest, size_t n, char** items)
{
    // add each item in the array to the list
    for (size_t i = 0; i < n; i++)
    {
        ArrayList_add(dest, items[i]);
    }
}


void ArrayList_addList(ArrayList dest, ArrayList src)
{
    for (size_t i = 0; i < src->size; i++)
    {
        ArrayList_add(dest, ArrayList_get(src, i));
    }   
}


void ArrayList_clear(ArrayList list)
{
    // remove the first element from list until list is empty.
    while (list->size != 0)
    {
        ArrayList_remove(list, 0);
    }  
}


unsigned short ArrayList_contains(ArrayList list, char* item)
{
    // check each item
    for (size_t n = 0; n < list->size; n++)
    {
        if (!strcmp(list->items[n], item)) return 1;
    }

    return 0;
}


ArrayList ArrayList_copy(ArrayList list)
{

    ArrayList copy = ArrayList_create(list->buffer);
    for (size_t i = 0; i < list->size; i++)
    {
        ArrayList_add(copy, ArrayList_get(list, i));
    }

    
    return copy;
}


ArrayList ArrayList_create(size_t size)
{
    // Size cannot be 0
    if (size == 0) return NULL;

    // Construct list and allocate memory
    ArrayList list = malloc(sizeof(struct ArrayList_s));
    list->size = 0;
    list->buffer = size;
    list->items = malloc(list->buffer * sizeof(char*));

    return list;
}


ArrayList ArrayList_createFromArray(size_t n, char** array)
{
    // always allocate space for at least one item
    ArrayList list = ArrayList_create(n==0 ? 1 : n);
    ArrayList_addArray(list, n, array);

    return list;
}


unsigned short ArrayList_equals(ArrayList a, ArrayList b)
{
    // lists must be same size
    if (a->size != b->size) return 0;

    // check each item
    for (size_t n = 0; n < a->size; n++)
    {
        if (strcmp(a->items[n], b->items[n])) return 0;
    }

    return 1;
}


void ArrayList_expand(ArrayList list, size_t amount)
{
    list->buffer += amount;
    list->items = realloc(list->items, list->buffer * sizeof(char*));
}


void ArrayList_free(ArrayList list)
{
    // Free all items held by the list
    for (size_t i = 0; i < list->size; i++)
    {
        free(list->items[i]);
    }

    // Free the parent array
    free(list->items);

    // Free the list itself
    free(list);
}


char* ArrayList_get(ArrayList list, size_t n)
{
    // Index out of bounds
    if (n >= list->size) return NULL;

    return list->items[n];
}


void ArrayList_insert(ArrayList list, char* item, size_t idx)
{
    // index out of bounds (may be in range [0,list->size])
    if (idx > list->size) return;

    // new item will exceed memory allocation
    if (list->size == list->buffer) ArrayList_expand(list, list->buffer);

    char* copy = malloc(strlen(item)+1);
    strcpy(copy, item);

    // shift items up
    for (size_t n = list->size-1; n >= idx; n--)
    {
        list->items[n+1] = list->items[n];
    }

    // insert item
    list->items[idx] = copy;
    list->size++;
}


void ArrayList_print(ArrayList list)
{
    for (size_t i = 0; i < list->size; i++)
    {
        printf("[\"%s\"]", list->items[i]);
    }

    printf("\n");
}


ArrayList ArrayList_range(ArrayList list, size_t start, size_t end)
{
    ArrayList sublist = ArrayList_create(list->size);

    // add everything within the range
    while (start < end && start < list->size)
    {
        ArrayList_add(sublist, ArrayList_get(list, start));
        start++;
    }

    return sublist;
}


void ArrayList_remove(ArrayList list, size_t n)
{
    // index out of bounds
    if (n >= list->size) return;
    
    // free the removed item
    free(list->items[n]);

    // shift everything down to fill the gap
    for (size_t i = n + 1; i < list->size; i++)
    {
        list->items[i-1] = list->items[i];
    }

    list->size--;
}


void ArrayList_removeAllMatches(ArrayList list, char* match)
{
    size_t n = 0;
    while (n < list->size)
    {
        if (!strcmp(list->items[n], match)) ArrayList_remove(list, n);
        else n++;
    }   
}


void ArrayList_reverse(ArrayList list)
{
    // No reversing needed
    if (list->size <= 1) return;

    for (size_t i = 0; i < list->size/2; i++)
    {
        // Swap the two items
        char* temp = list->items[i];
        list->items[i] = list->items[list->size-1-i];
        list->items[list->size-1-i] = temp;
    }
}


void ArrayList_set(ArrayList list, char* item, size_t n)
{
    // index out of bounds
    if (n >= list->size) return;

    // copy new item
    list->items[n] = realloc(list->items[n], strlen(item) + 1);
    strcpy(list->items[n], item);
}


void ArrayList_shuffle(ArrayList list)
{
    // ASSUMES srand() has already been called!
    for (size_t i = list->size-1; i > 0; i--) 
    { 
        // Pick a random index
        size_t j = rand() % (i+1); 
  
        // swap
        ArrayList_swap(list, i, j); 
    }
}


static size_t ArrayList_sortPartition(ArrayList list, size_t low, size_t high)
{
    char* pivot = list->items[high];
    size_t i = low - 1;

    for (size_t j = low; j <= high-1; j++)
    {
        if (strcmp(list->items[j], pivot) < 0)
        {
            i++;
            ArrayList_swap(list,i,j);
        }
    }
    ArrayList_swap(list, i+1, high);

    return i+1;
}


static void ArrayList_sortWithArgs(ArrayList list, size_t low, size_t high)
{
    if (low < high)
    {
        size_t pivot = ArrayList_sortPartition(list, low, high);

        ArrayList_sortWithArgs(list, low, pivot-1);
        ArrayList_sortWithArgs(list, pivot+1, high);
    }
}


void ArrayList_sort(ArrayList list)
{
    ArrayList_sortWithArgs(list, 0, list->size-1);
}


void ArrayList_swap(ArrayList list, size_t i, size_t j)
{
    // Indices must be within bounds
    if (i >= list->size || j >= list->size) return;

    // Swap list[i] and list[j]
    char* a = list->items[i];
    list->items[i] = list->items[j];
    list->items[j] = a;
}


void ArrayList_trim(ArrayList list)
{
    // trim the buffer down to size + 1
    list->buffer = list->size + 1;
    list->items = realloc(list->items, list->buffer * sizeof(char*));
}
