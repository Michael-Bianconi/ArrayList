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

int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	TEST_CREATE();
	TEST_ADD();
}