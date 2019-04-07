/**
 * @author Michael Bianconi
 * @since 04-02-2019
 *
 * Test harness for ArrayList structure.
 */
#include "arraylist.h"
#include "verbose.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static char* ADD_ITEMS[] = {"0","1","2","3","4","5","6","7","8","9"};

static void TEST_ADD()
{
	VERBOSE_FUNC_START;

	const size_t BUFFER = 75;
	const size_t NUM_ITEMS = 145;
	ArrayList list = ArrayList_create(BUFFER);

	for (size_t n = 0; n < NUM_ITEMS; n++)
	{
		int pos = n % 10;
		ArrayList_add(list, ADD_ITEMS[pos]);

		assert(!strcmp(list->items[n],ADD_ITEMS[pos]));
		assert(list->size == n+1);
		if (n < BUFFER) assert(list->buffer == BUFFER);
		if (n >= BUFFER) assert(list->buffer == BUFFER*2);
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_ADDALL()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(5);
	ArrayList_addAll(list, 2, "hello", "world");
	ArrayList_add(list, "my");
	ArrayList_addAll(list, 3, "name", "is", "gcc");

	assert(!strcmp(list->items[0],"hello"));
	assert(!strcmp(list->items[1],"world"));
	assert(!strcmp(list->items[2],"my"));
	assert(!strcmp(list->items[3],"name"));
	assert(!strcmp(list->items[4],"is"));
	assert(!strcmp(list->items[5],"gcc"));

	assert(list->size == 6);
	assert(list->buffer == 10);

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_ADDARRAY()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(4);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	ArrayList_addArray(list, 10, ADD_ITEMS);

	assert(list->size == 20);

	for (size_t n = 0; n < list->size; n++)
	{
		assert(!strcmp(list->items[n], ADD_ITEMS[n%10]));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}

static void TEST_ADDLIST()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(4);
	ArrayList copy = ArrayList_create(4);
	ArrayList_addArray(copy, 10, ADD_ITEMS);

	ArrayList_addList(list, copy);
	ArrayList_addList(list, copy);

	assert(list->size == 20);

	for (size_t n = 0; n < list->size; n++)
	{
		assert(!strcmp(list->items[n], ADD_ITEMS[n%10]));
	}

	ArrayList_free(list);
	ArrayList_free(copy);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_COPY()
{
	VERBOSE_FUNC_START;

	ArrayList src = ArrayList_create(10);
	ArrayList_addArray(src, 10, ADD_ITEMS);

	ArrayList dest = ArrayList_copy(src);
	assert(dest->size == src->size);

	for (size_t i = 0; i < dest->size; i++)
	{
		assert(!strcmp(dest->items[i],src->items[i]));
	}

	ArrayList_free(src);
	ArrayList_free(dest);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


/**
 * Create a good array and a bad array.
 */
static void TEST_CREATE()
{
	VERBOSE_FUNC_START;

	const size_t GOOD_SIZE = 5;
	const size_t BAD_SIZE = 0;

	ArrayList good = ArrayList_create(GOOD_SIZE);
	assert(good != NULL);
	assert(good->size == 0);
	assert(good->buffer == GOOD_SIZE);
	ArrayList_free(good);

	ArrayList bad = ArrayList_create(BAD_SIZE);
	assert(bad == NULL);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_EQUALS()
{
	VERBOSE_FUNC_START;

	ArrayList list1 = ArrayList_create(10);
	ArrayList_addArray(list1, 10, ADD_ITEMS);
	ArrayList list2 = ArrayList_copy(list1);
	assert(ArrayList_equals(list1, list2));
	ArrayList_reverse(list2);
	assert(!ArrayList_equals(list1, list2));

	ArrayList_free(list1);
	ArrayList_free(list2);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_EXPAND()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(5);

	assert(list->buffer == 5);

	ArrayList_expand(list, 2);

	assert(list->buffer == 7);

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_GET()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(5);
	ArrayList_addArray(list, 10, ADD_ITEMS);

	assert(list->size == 10);

	for (size_t n = 0; n < list->size; n++)
	{
		assert(!strcmp(ADD_ITEMS[n], ArrayList_get(list, n)));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_INSERT()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);
	assert(list->buffer == 10);

	ArrayList_insert(list, "new", 5);
	assert(list->size == 11);
	assert(list->buffer == 20);
	assert(!strcmp(list->items[5], "new"));

	for (size_t n = 0; n < list->size; n++)
	{
		if (n != 5)
		{
			assert(!strcmp(list->items[n],
				n < 5 ? ADD_ITEMS[n] : ADD_ITEMS[n-1]));
		}
	}

	ArrayList_insert(list, "bad", 13);
	assert(list->size == 11);
	assert(list->buffer == 20);

	ArrayList_insert(list, "end", 11);
	assert(list->size == 12);
	assert(list->buffer == 20);

	assert(!strcmp(list->items[11],"end"));

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_RANGE()
{
	VERBOSE_FUNC_START;

	ArrayList src = ArrayList_create(10);
	ArrayList_addArray(src, 10, ADD_ITEMS);
	assert(src->size == 10);

	ArrayList dest = ArrayList_range(src, 2, 8);
	assert(dest->size == 6);
	for (size_t n = 0; n < dest->size; n++)
	{
		assert(!strcmp(src->items[n+2], dest->items[n]));
	}
	ArrayList_free(dest);

	dest = ArrayList_range(src, 5, 2);
	assert(dest->size == 0);
	ArrayList_free(dest);

	dest = ArrayList_range(src, 5, 100);
	assert(dest->size == 5);
	for (size_t n = 0; n < dest->size; n++)
	{
		assert(!strcmp(src->items[n+5], dest->items[n]));
	}
	ArrayList_free(dest);

	ArrayList_free(src);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_REMOVE()
{
	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);

	assert(list->size == 10);

	for (size_t n = 0; n < list->size-1; n++)
	{
		ArrayList_remove(list, 0);
		assert(list->size == 10 - n - 1);
		assert(!strcmp(list->items[0],ADD_ITEMS[n+1]));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_REVERSE()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);
	ArrayList_reverse(list);

	for (size_t n = 0; n < list->size; n++)
	{
		assert(!strcmp(list->items[n], ADD_ITEMS[list->size-n-1]));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_SORT()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(5);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);

	ArrayList_shuffle(list);
	ArrayList_sort(list);

	for (size_t n = 0; n < list->size; n++)
	{
		assert(!strcmp(list->items[n], ADD_ITEMS[n]));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_SET()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);

	for (size_t n = 0; n < list->size; n++)
	{
		ArrayList_set(list, "0", n);
		assert(!strcmp(list->items[n], "0"));
	}

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_SHUFFLE()
{

	// IMPOSSIBLE TO FULLY TEST THIS FUNCTION
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);
	ArrayList_shuffle(list);
	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_SWAP()
{
	VERBOSE_FUNC_START;

	ArrayList list = ArrayList_create(10);
	ArrayList_addArray(list, 10, ADD_ITEMS);
	assert(list->size == 10);

	ArrayList_swap(list, 0, 100); // bad swap
	ArrayList_swap(list, 100, 0); // bad swap
	ArrayList_swap(list, 100, 100); // bad swap

	ArrayList_swap(list, 0, 9);
	assert(!strcmp(list->items[0], ADD_ITEMS[9]));
	assert(!strcmp(list->items[9], ADD_ITEMS[0]));

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}


static void TEST_TRIM()
{
	VERBOSE_FUNC_START;

	const size_t buffer = 7;
	ArrayList list = ArrayList_create(buffer);
	ArrayList_addArray(list, 10, ADD_ITEMS);

	assert(list->size == 10);
	assert(list->buffer == buffer*2);
	ArrayList_trim(list);
	assert(list->buffer == 11);

	ArrayList_free(list);

	VERBOSE_TESTS_SUCCESS;
	VERBOSE_FUNC_END;
}

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	TEST_ADD();
	TEST_ADDALL();
	TEST_ADDARRAY();
	TEST_ADDLIST();
	TEST_COPY();
	TEST_CREATE();
	TEST_EQUALS();
	TEST_EXPAND();
	TEST_GET();
	TEST_INSERT();
	TEST_RANGE();
	TEST_REMOVE();
	TEST_REVERSE();
	TEST_SORT();
	TEST_SET();
	TEST_SHUFFLE();
	TEST_SWAP();
	TEST_TRIM();
}