/**
 * @author Michael Bianconi
 * @since 04-02-2019
 *
 * Test harness for ArrayList structure.
 */
#include "arraylist.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static const int BAD_ARRAYSIZE = 0;
static const int START_ARRAYSIZE = 7;
static const unsigned int NUM_ITEMS = 10;
static char* ADD_ITEMS[] = {"0","1","2","3","4","5","6","7","8","9"};
static char* SET_ITEMS[] = {"9","1","2","3","4","5","6","7","8","0"};
static char* REVERSED_ITEMS[] = {"9","8","7","6","5","4","3","2","1","0"};



int main(int argc, char** argv)
{
	(void) argc;
	(void) argv;

	ArrayList list = ArrayList_create(5);
	ArrayList_addAll(list, 2, "hello", "world");
}