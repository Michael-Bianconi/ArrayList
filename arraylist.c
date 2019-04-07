/**
 * @author Michael Bianconi
 * @since 04-02-2019
 *
 * Source code for ArrayList.h.
 */
#include "arraylist.h"
#include "verbose.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <stdarg.h> // valist
#include <string.h> // strcpy

void ArrayList_add(ArrayList list, char* item)
{
	VERBOSE_FUNC_START;

	// Copy the item into a buffer
	char* data = malloc(strlen(item) + 1);
	strcpy(data, item);

	// ArrayList memory allocation reached, double allocation
	if (list->size == list->buffer) ArrayList_expand(list, list->buffer);

	// Add the item to the list
	list->items[list->size] = data;
	list->size++;

	VERBOSE_MSGARGS("added %s\n",data);
	VERBOSE_FUNC_END;
}


void ArrayList_addAll(ArrayList list, int argc, ...)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("adding %d items\n", argc);


	// initialize variable arguments list
	va_list valist;
	va_start(valist, argc);

	// add each to the list
	for (int i = 0; i < argc; i++)
	{
		ArrayList_add(list, va_arg(valist, char*));
	}

	VERBOSE_FUNC_END;
}


void ArrayList_addArray(ArrayList dest, size_t n, char** items)
{
	VERBOSE_FUNC_START;

	// add each item in the array to the list
	for (size_t i = 0; i < n; i++)
	{
		ArrayList_add(dest, items[i]);
	}

	VERBOSE_FUNC_END;
}


void ArrayList_addList(ArrayList dest, ArrayList src)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("adding %lu items\n", src->size);

	for (size_t i = 0; i < src->size; i++)
	{
		ArrayList_add(dest, ArrayList_get(src, i));
	}

	VERBOSE_FUNC_END;
}


void ArrayList_clear(ArrayList list)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("clearing %lu items\n", list->size);

	// remove the first element from list until list is empty.
	while (list->size != 0)
	{
		ArrayList_remove(list, 0);
	}

	VERBOSE_FUNC_END;
}


unsigned short ArrayList_contains(ArrayList list, char* item)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("searching for %s\n", item);

	// check each item
	for (size_t n = 0; n < list->size; n++)
	{
		if (!strcmp(list->items[n], item)) {
			VERBOSE_MSGARGS("found out %lu\n", n);
			return 1;
		}
	}

	VERBOSE_MSG("not found\n");
	VERBOSE_FUNC_END;

	return 0;
}


ArrayList ArrayList_copy(ArrayList list)
{
	VERBOSE_FUNC_START;

	ArrayList copy = ArrayList_create(list->buffer);
	for (size_t i = 0; i < list->size; i++)
	{
		ArrayList_add(copy, ArrayList_get(list, i));
	}

	VERBOSE_FUNC_END;
	return copy;
}


ArrayList ArrayList_create(size_t size)
{
	VERBOSE_FUNC_START;

	// Size cannot be 0
	if (size == 0)
	{
		VERBOSE_ERRARGS("ERROR: cannot create ArrayList of size %lu\n", size);
		return NULL;
	}

	// Construct list and allocate memory
	ArrayList list = malloc(sizeof(struct ArrayList_s));
	list->size = 0;
	list->buffer = size;
	list->items = malloc(list->buffer * sizeof(char*));

	VERBOSE_FUNC_END;
	return list;
}


ArrayList ArrayList_createFromArray(size_t n, char** array)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("adding first %lu items from array\n", n);

	// always allocate space for at least one item
	ArrayList list = ArrayList_create(n==0 ? 1 : n);
	ArrayList_addArray(list, n, array);

	VERBOSE_FUNC_END;

	return list;
}


unsigned short ArrayList_equals(ArrayList a, ArrayList b)
{
	VERBOSE_FUNC_START;

	// lists must be same size
	if (a->size != b->size)
	{
		VERBOSE_MSG("lists not equal\n");
		return 0;
	}

	// check each item
	for (size_t n = 0; n < a->size; n++)
	{
		if (strcmp(a->items[n], b->items[n]))
		{
			VERBOSE_MSG("lists not equal\n");
			return 0;
		}
	}

	VERBOSE_MSG("lists are equal\n");
	VERBOSE_FUNC_END;

	return 1;
}


void ArrayList_expand(ArrayList list, size_t amount)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("expanding buffer from %lu to %lu\n",
		list->buffer, list->buffer + amount);

	list->buffer += amount;
	list->items = realloc(list->items, list->buffer * sizeof(char*));

	VERBOSE_FUNC_END;
}


void ArrayList_free(ArrayList list)
{
	VERBOSE_FUNC_START;

	// Free all items held by the list
	for (size_t i = 0; i < list->size; i++)
	{
		VERBOSE_MSGARGS("freeing list[%lu]: %s\n", i, list->items[i]);
		free(list->items[i]);
	}

	// Free the parent array
	free(list->items);

	// Free the list itself
	free(list);

	VERBOSE_FUNC_END;
}


char* ArrayList_get(ArrayList list, size_t n)
{
	VERBOSE_FUNC_START;

	// Index out of bounds
	if (n >= list->size)
	{
		VERBOSE_ERRARGS("index %lu out of bounds\n", n);
		return NULL;
	}

	VERBOSE_MSGARGS("retrieved list[%lu]: %s\n", n, list->items[n]);
	VERBOSE_FUNC_END;

	return list->items[n];
}


void ArrayList_insert(ArrayList list, char* item, size_t idx)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("inserting %s at %lu\n",item,idx);

	// index out of bounds (may be in range [0,list->size])
	if (idx > list->size)
	{
		VERBOSE_ERRARGS("index %lu out of bounds\n",idx);
		return;
	}

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

	VERBOSE_FUNC_END;
}


void ArrayList_print(ArrayList list)
{
	VERBOSE_FUNC_START;

	for (size_t i = 0; i < list->size; i++)
	{
		printf("[\"%s\"]", list->items[i]);
	}

	printf("\n");

	VERBOSE_FUNC_END;
}


ArrayList ArrayList_range(ArrayList list, size_t start, size_t end)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("selecting range from %lu to %lu\n", start, end);

	ArrayList sublist = ArrayList_create(list->size);

	// add everything within the range
	while (start < end && start < list->size)
	{
		ArrayList_add(sublist, ArrayList_get(list, start));
		start++;
	}

	VERBOSE_FUNC_END;

	return sublist;
}


void ArrayList_remove(ArrayList list, size_t n)
{
	VERBOSE_FUNC_START;

	// index out of bounds
	if (n >= list->size)
	{
		VERBOSE_ERRARGS("index %lu out of bounds\n", n);
		return;
	}

	VERBOSE_MSGARGS("removing list[%lu]: %s\n", n, list->items[n]);

	// free the removed item
	free(list->items[n]);

	// shift everything down to fill the gap
	for (size_t i = n + 1; i < list->size; i++)
	{
		list->items[i-1] = list->items[i];
	}

	list->size--;

	VERBOSE_FUNC_END;
}


void ArrayList_removeAllMatches(ArrayList list, char* match)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("removing all instances of %s\n",match);

	size_t n = 0;
	while (n < list->size)
	{
		if (!strcmp(list->items[n], match)) ArrayList_remove(list, n);
		else n++;
	}

	VERBOSE_FUNC_END;
}


void ArrayList_reverse(ArrayList list)
{
	VERBOSE_FUNC_START;

	// No reversing needed
	if (list->size <= 1) return;

	for (size_t i = 0; i < list->size/2; i++)
	{
		VERBOSE_MSGARGS("reversing %s and %s\n",
			list->items[i], list->items[list->size-1-i]);

		// Swap the two items
		char* temp = list->items[i];
		list->items[i] = list->items[list->size-1-i];
		list->items[list->size-1-i] = temp;
	}

	VERBOSE_FUNC_END;
}


void ArrayList_set(ArrayList list, char* item, size_t n)
{
	VERBOSE_FUNC_START;

	// index out of bounds
	if (n >= list->size)
	{
		VERBOSE_ERRARGS("index %lu out of bounds\n", n);
		return;
	}

	// copy new item
	list->items[n] = realloc(list->items[n], strlen(item) + 1);
	strcpy(list->items[n], item);

	VERBOSE_MSGARGS("set list[%lu] to %s\n", n, item);
	VERBOSE_FUNC_END;
}


void ArrayList_shuffle(ArrayList list)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSG("shuffling list");

	// ASSUMES srand() has already been called!
	for (size_t i = list->size-1; i > 0; i--) 
    { 
        // Pick a random index
        size_t j = rand() % (i+1); 
  
        // swap
        ArrayList_swap(list, i, j); 
    }

    VERBOSE_FUNC_END;
}


static size_t ArrayList_sortPartition(ArrayList list, size_t low, size_t high)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("pivoting on %lu and %lu\n", low, high);

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

	VERBOSE_FUNC_END;
	return i+1;
}


static void ArrayList_sortWithArgs(ArrayList list, size_t low, size_t high)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("sorting on %lu and %lu\n",low,high);

	if (low < high)
	{
		size_t pivot = ArrayList_sortPartition(list, low, high);

		ArrayList_sortWithArgs(list, low, pivot-1);
		ArrayList_sortWithArgs(list, pivot+1, high);
	}

	VERBOSE_FUNC_END;
}


void ArrayList_sort(ArrayList list)
{
	VERBOSE_FUNC_START;
	ArrayList_sortWithArgs(list, 0, list->size-1);
	VERBOSE_FUNC_END;
}


void ArrayList_swap(ArrayList list, size_t i, size_t j)
{
	VERBOSE_FUNC_START;

	// Indices must be within bounds
	if (i >= list->size || j >= list->size)
	{
		VERBOSE_ERRARGS("indices out of bounds: %lu, %lu\n",i,j);
		return;
	}

	// Swap list[i] and list[j]
	char* a = list->items[i];
	list->items[i] = list->items[j];
	list->items[j] = a;

	VERBOSE_MSGARGS("swapped %lu (%s) and %lu (%s)\n",
					i, list->items[j], j, list->items[i]);
	VERBOSE_FUNC_END;

}


void ArrayList_trim(ArrayList list)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSGARGS("trimming buffer from %lu to %lu\n",
		list->buffer, list->size + 1);

	// trim the buffer down to size + 1
	list->buffer = list->size + 1;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
	VERBOSE_FUNC_END;
}
