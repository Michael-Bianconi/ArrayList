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

	if (list->__verbose__)
	{
		printf("ArrayList_add(): added %s, list now size %lu\n",
			   data, list->size);
	}
}


void ArrayList_addAll(ArrayList list, int argc, ...)
{
	if (ArrayList_isVerbose(list)) printf("%s: start\n", __func__);

	// initialize variable arguments list
	va_list valist;
	va_start(valist, argc);

	// add each argument to the list
	for (size_t i = 0; i < argc; i++)
	{
		ArrayList_add(list, va_arg(valist, char*));
	}

	if (ArrayList_isVerbose(list)) printf("%s: end\n", __func__);
}


void ArrayList_addArray(ArrayList dest, size_t n, char** items)
{
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


ArrayList ArrayList_copy(ArrayList list)
{
	if (list->__verbose__)
	{
		printf("ArrayList_copy(): copying list\n");
	}

	ArrayList copy = ArrayList_create(list->buffer);
	copy->__verbose__ = list->__verbose__;
	for (size_t i = 0; i < list->size; i++)
	{
		ArrayList_add(copy, ArrayList_get(list, i));
	}
	return copy;
}


ArrayList ArrayList_create(size_t size)
{
	// Size cannot be 0
	if (size == 0)
	{
		fprintf(stderr,
			"ArrayList_create(): cannot create ArrayList of size 0\n");
		return NULL;
	}

	// Construct list and allocate memory
	ArrayList list = malloc(sizeof(struct ArrayList_s));
	list->size = 0;
	list->buffer = size;
	list->items = malloc(list->buffer * sizeof(char*));

	return list;
}


void ArrayList_expand(ArrayList list, size_t amount)
{
	if (list->__verbose__)
	{
		printf("ArrayList_expand(): expanding buffer from %lu to %lu\n",
			   list->buffer, list->buffer + amount);
	}

	list->buffer += amount;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
}


void ArrayList_free(ArrayList list)
{
	// Free all items held by the list
	for (size_t i = 0; i < list->size; i++)
	{
		if (list->__verbose__)
		{
			printf("ArrayList_free(): freeing %s\n", list->items[i]);
		}

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
	if (n >= list->size)
	{
		fprintf(stderr, "ArrayList_get(): index %lu out of bounds\n", n);
		return NULL;
	}

	char* item = list->items[n];

	if (list->__verbose__)
	{
		printf("ArrayList_get(): getting list[%lu]: %s\n", n, item);
	}

	return list->items[n];
}


unsigned short ArrayList_isVerbose(ArrayList list)
{
	return list->__verbose__;
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
	if (list->__verbose__)
	{
		printf("ArrayList_range(): Selecting from range [%lu, %lu)\n",
			start, end);
	}

	ArrayList sublist = ArrayList_create(list->size);
	sublist->__verbose__ = list->__verbose__;

	while (start < end && start < list->size)
	{
		ArrayList_add(sublist, ArrayList_get(list, start));
		start++;
	}

	return sublist;
}


void ArrayList_remove(ArrayList list, size_t n)
{
	if (n >= list->size)
	{
		fprintf(stderr, "ArrayList_remove(): index %lu out of bounds\n", n);
		return;
	}

	if (list->__verbose__)
	{
		printf("ArrayList_remove(): removing list[%lu]: %s\n",
			n, list->items[n]);
	}

	free(list->items[n]);

	for (size_t i = n + 1; i < list->size; i++)
	{
		list->items[i-1] = list->items[i];
	}

	list->size--;
}


void ArrayList_reverse(ArrayList list)
{
	// No reversing needed
	if (list->size <= 1) return;

	for (size_t i = 0; i < list->size/2; i++)
	{
		if (list->__verbose__)
		{
			printf("ArrayList_reverse(): reversing %s and %s\n",
				list->items[i], list->items[list->size-1-i]);
		}

		// Swap the two items
		char* temp = list->items[i];
		list->items[i] = list->items[list->size-1-i];
		list->items[list->size-1-i] = temp;
	}
}


void ArrayList_set(ArrayList list, char* item, size_t n)
{
	// index out of bounds
	if (n >= list->size)
	{
		fprintf(stderr, "ArrayList_set(): index %lu out of bounds\n", n);
		return;
	}

	// copy new item
	list->items[n] = realloc(list->items[n], strlen(item) + 1);
	strcpy(list->items[n], item);

	if (list->__verbose__)
	{
		printf("ArrayList_set(): set list[%lu] to %s\n", n, item);
	}
}


void ArrayList_setVerbose(ArrayList list, unsigned short mode)
{
	list->__verbose__ = mode;
}


void ArrayList_trim(ArrayList list)
{
	if (list->__verbose__)
	{
		printf("ArrayList_trim(): Trimming buffer from %lu to %lu\n",
			list->buffer, list->size + 1);
	}

	list->buffer = list->size  + 1;
	list->items = realloc(list->items, list->buffer * sizeof(char*));
}
