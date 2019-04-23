# ArrayList
A C-implementation of Java's ArrayList

Look in arraylist.h for the full list of functions.

# Example

    ArrayList list = ArrayList_create(5); // Create an arraylist that can hold 5 items before expanding
    ArrayList_add(list, "hello"); // Add "hello" to the list
    ArrayList_addAll(list, 3, ", ", "world", "!"); // Adds the three strings to the list
    printf("%s\n", ArrayList_get(list, 2)); // prints "world"
    ArrayList_free(list);
    
   
