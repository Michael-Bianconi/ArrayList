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

	VERBOSE_MSG("added %s\n",data);
	VERBOSE_FUNC_END;
}


void ArrayList_addAll(ArrayList list, int argc, ...)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSG("adding %d items\n", argc);


	// initialize variable arguments list
	va_list valist;
	va_start(valist, argc);

	// add each to the list
	for (size_t i = 0; i < argc; i++)
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
	VERBOSE_MSG("adding %lu items\n", src->size);

	for (size_t i = 0; i < src->size; i++)
	{
		ArrayList_add(dest, ArrayList_get(src, i));
	}

	VERBOSE_FUNC_END;
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
		VERBOSE_ERR("ERROR: cannot create ArrayList of size %lu\n",size);
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


void ArrayList_expand(ArrayList list, size_t amount)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSG("expanding buffer from %lu to %lu\n",
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
		VERBOSE_MSG("freeing list[%lu]: %s\n", i, list->items[i]);
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
		VERBOSE_ERR("index %lu out of bounds\n", n);
		return NULL;
	}

	VERBOSE_MSG("retrieved list[%lu]: %s\n", n, list->items[n]);
	VERBOSE_FUNC_END;

	return list->items[n];
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
	VERBOSE_MSG("selecting range from %lu to %lu\n", start, end);

	ArrayList sublist = ArrayList_create(list->size);

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

	if (n >= list->size)
	{
		VERBOSE_ERR("index %lu out of bounds\n", n);
		return;
	}

	VERBOSE_MSG("removing list[%lu]: %s\n", n, list->items[n]);

	free(list->items[n]);

	for (size_t i = n + 1; i < list->size; i++)
	{
		list->items[i-1] = list->items[i];
	}

	list->size--;

	VERBOSE_FUNC_END;
}


void ArrayList_reverse(ArrayList list)
{
	VERBOSE_FUNC_START;

	// No reversing needed
	if (list->size <= 1) return;

	for (size_t i = 0; i < list->size/2; i++)
	{
		VERBOSE_MSG("reversing %s and %s\n",
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
		VERBOSE_ERR("index %lu out of bounds\n", n);
		return;
	}

	// copy new item
	list->items[n] = realloc(list->items[n], strlen(item) + 1);
	strcpy(list->items[n], item);

	VERBOSE_MSG("set list[%lu] to %s\n", n, item);
	VERBOSE_FUNC_END;
}


void ArrayList_trim(ArrayList list)
{
	VERBOSE_FUNC_START;
	VERBOSE_MSG("trimming buffer from %lu to %lu\n",
		list->buffer, list->size + 1);

	list->buffer = list->size  + 1;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
	VERBOSE_FUNC_END;
}
