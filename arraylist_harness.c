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

static const int BAD_ARRAYSIZE = 0;
static const int START_ARRAYSIZE = 7;
static const unsigned int NUM_ITEMS = 10;
static char* ADD_ITEMS[] = {"0","1","2","3","4","5","6","7","8","9"};
static char* SET_ITEMS[] = {"9","1","2","3","4","5","6","7","8","0"};
static char* REVERSED_ITEMS[] = {"9","8","7","6","5","4","3","2","1","0"};


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
	assert(good->buffer = sizeof(void*) * GOOD_SIZE);
	ArrayList_free(good);

	ArrayList bad = ArrayList_create(BAD_SIZE);
	assert(bad == NULL);

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
	TEST_EXPAND();

}