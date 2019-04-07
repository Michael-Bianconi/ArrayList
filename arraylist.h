/**
 * @author Michael Bianconi
 * @since 04-02-2019
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>

// STRUCT DEFINITION ==========================================================

/**
 * ArrayList_s is a dynamically-resizing array of strings.
 */
struct ArrayList_s
{
	/** The current max elements that can be in memory. */
	size_t buffer;

	/** The current number of elements in the ArrayList. */
	size_t size;

	/** The data held by this ArrayList. */
	char** items;
};

typedef struct ArrayList_s* ArrayList;

// FUNCTION DECLARATION =======================================================


/**
 * Adds a new Element to the given ArrayList. If the new
 * element would otherwise exceed the buffer, then
 * ArrayList_expand() is called.
 *
 * @param list ArrayList to add to.
 * @param item Item to copy into the List.
 */
void ArrayList_add(ArrayList list, char* item);


/**
 * Adds all given arguments to the list.
 *
 * @param list List to add to.
 * @param argc Number of given arguments.
 * @param ... Items to add (must be char*).
 */
void ArrayList_addAll(ArrayList list, int argc, ...);


/**
 * Adds all elements in the array to the list.
 *
 * @param dest List to add to.
 * @param n Number of items in the array.
 * @param items Array to add from.
 */
void ArrayList_addArray(ArrayList dest, size_t n, char** items);


/**
 * Adds all elements from source list into destination list.
 *
 * @param dest List to add to.
 * @param src List to add from.
 */
void ArrayList_addList(ArrayList dest, ArrayList src);


/**
 * Removes all items from the list.
 *
 * @param list List to alter.
 */
void ArrayList_clear(ArrayList list);


/**
 * Checks if the given string exists in the list.
 *
 * @param list List to check.
 * @param item Item to search for.
 * @return Returns 1 if present, 0 otherwise.
 */
unsigned short ArrayList_contains(ArrayList list, char* item);


/**
 * Construct a new ArrayList with the same data as
 * the given ArrayList.
 *
 * @param list List to copy.
 * @return Returns a new ArrayList.
 */
ArrayList ArrayList_copy(ArrayList list);


/**
 * Construct a new ArrayList with the default given size.
 * 
 * @param size Allocate enough space to hold this many items.
 *             ArrayList will never resize under this amount.
 *             May not be 0.
 * @return Returns the constructed ArrayList.
 */
ArrayList ArrayList_create(size_t size);


/**
 * Takes the first N items in the array and adds them to
 * a newly created list.
 *
 * @param n Number of items to add (must be <= array size).
 * @param array Array to add from.
 * @return Returns newly created list.
 */
ArrayList ArrayList_createFromArray(size_t n, char** array);


/**
 * Checks if each item is the same across lists. Does not
 * check buffer size.
 *
 * @param a First list.
 * @param b Second list.
 * @return returns 1 if equal, 0 otherwise.
 */
unsigned short ArrayList_equals(ArrayList a, ArrayList b);


/**
 * Increases the size of the ArrayList's buffer. Called automatically
 * when adding an item that exceeds the allocated memory.
 *
 * @param list List to expand.
 * @param amount Amount to expand by.
 */
void ArrayList_expand(ArrayList list, size_t amount);


/**
 * Frees all memory allocated by this ArrayList.
 *
 * @param list ArrayList to free.
 */
void ArrayList_free(ArrayList list);


/**
 * Retrieves a pointer to the n'th item from the ArrayList.
 *
 * @param list ArrayList to retrieve from.
 * @param n Index to retrieve at.
 * @return Returns the n'th item, or null if out of bounds.
 * @see ArrayList_getCopy()
 */
char* ArrayList_get(ArrayList list, size_t n);


/**
 * Inserts the item into the array and shifts
 * all further items up by 1.
 *
 * @param list List to alter.
 * @param item Item to add.
 * @param size_t idx Position to insert.
 */
void ArrayList_insert(ArrayList list, char* item, size_t idx);


/**
 * Print the contents of the ArrayList.
 *
 * @param list ArrayList to print.
 */
void ArrayList_print(ArrayList list);


/**
 * Creates a new ArrayList with all the items in list that
 * are within the given range. If the original list is
 * verbose, the sublist will be too.
 *
 * If start is greater than end, no items will be copied.
 * If end is greater than the size of the list, all item
 * after start will be copied.
 *
 * @param list List to select from.
 * @param start The beginning of the range, inclusive.
 * @param end The end of the range, exclusive.
 * @return Returns a new ArrayList.
 */
ArrayList ArrayList_range(ArrayList list, size_t start, size_t end);


/**
 * Removes an element from the ArrayList. Shifts all others down
 * to fill the gap. Does not resize the array.
 *
 * @param list ArrayList to alter.
 * @param n Remove the n'th item in the list.
 */
void ArrayList_remove(ArrayList list, size_t n);


/**
 * Remove all items from the list that match the given item.
 *
 * @param list List to alter.
 * @param match Item to match.
 */
void ArrayList_removeAllMatches(ArrayList list, char* match);


/**
 * Reverse all items in the list.
 *
 * @param list List to reverse.
 */
void ArrayList_reverse(ArrayList list);


/**
 * Set the given item to the given value.
 *
 * @param list List to alter.
 * @param item Item to set.
 * @param n N'th index.
 */
void ArrayList_set(ArrayList list, char* item, size_t n);


/**
 * Shuffles the ArrayList using a Fisher-Yates shuffle.
 *
 * @param list List to shuffle.
 */
void ArrayList_shuffle(ArrayList list);


/**
 * Sorts the list lexigraphically, in-place,
 * using quick sort, in ascending order.
 *
 * @param list List to sort.
 */
void ArrayList_sort(ArrayList list);


/**
 * Swaps the two given elements with each other.
 *
 * @param list List to alter.
 * @param i First index.
 * @param j Second index.
 */
void ArrayList_swap(ArrayList list, size_t i, size_t j);


/**
 * Trims unneeded memory space from the ArrayList's buffer.
 * Use if the size of the list decreased dramatically.
 * Reduces buffer to current list size + 1.
 *
 * @param list ArrayList to trim.
 */
void ArrayList_trim(ArrayList list);


#endif