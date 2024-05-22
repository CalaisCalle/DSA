# Linked Lists

In a linked list, each element consists of a node containing the data, and a pointer or reference to the next item in the list.

## Computer Memory Overview

This will mainly serve as a very quick recap of computer memory.

When variables are created in any programming language, the operating system (typically, this can differ) provides space for the variable and a record of its location.
The location, referred to as an *address*, can be used to access the value at that location.

## Storing Multiple Items

Arrays and Linked Lists are two of the most basic methods for storing multiple items in a single variable.

### Arrays

In an array, elements are stored contiguously: that is, values are placed next to one another in memory.
With arrays, the next location in the memory after an array may be a completely different value, or even owned by another process.
So, adding a new element to the array may involve moving the array to a new location that has space.
This may need to happen many times if the array is updated frequently.
As such, adding an element may take a significant amount of time.

However, knowing the position of the first element allows other values to be found trivially.
For example, if an array of size 5 starts at address 0, the 4th element will start at an address of 4 * \<size of an element\>.
This makes arrays *random access* data structures: Any arbitrary element can be fetched in constant time.

### Linked Lists

In a linked list, each element can be anywhere in memory.

Linked lists consist of nodes, where each node contains a value, and the location of the next node in the list.
To access a particular item in the list, a program will move from one node to another in sequence, using each node's saved location to find the next node in the sequence.
For example: if a program requires the 5th element of a list, it must first traverse through the 1st, 2nd, 3rd, and 4th elements in the list.

Linked lists have the advantage of never needing to move items in the list.
Appending an item to the list is a matter of creating a new node, and giving its location to the last node in the sequence.
Often, linked list implementations will store the location of the last node, to avoid traversing through the whole list to append one element.
To remove an item from the end of the list, the last node is deleted and the location stored in the second-to-last node is changed to a non-existent address.
This makes appending to and deleting the last node of a list are both constant-time.

However, linked lists have *sequential access*, as a result of requiring traversal through sequential nodes to access a specific item.
When inserting at a given index, the list must first traverse to that index.
Then, a newly created node is given the address of the node at $index + 1$.
The location of this new node gets given to the node at the index.

When deleting a node in a list at a given index, the node at $index - 1$ is changed to point to the node at $index + 1$.
The node at the index is then deleted.

### Arrays vs Linked Lists

Arrays can have constant-time access, but linear-time insertions and deletions.

Linked lists have linear time access, but "constant-time" insertion and deletion.

> N.B. Insertion and Deletion are considered separate operations to Indexing (i.e. traversing the list).
> Inserting an element to the middle of the list requires traversal.
> The combined indexing and traversal are $O(n)$

It is said that arrays are usually preferred for data that is mostly accessed, with few insertions and deletions.
Linked lists are used where indexing is required less often than indexing.

> N.B. This mainly applies to inserting on/deleting from the first and last indices.
> Many list structures will store the addresses of the first and last elements.
> Additionally, arrays may be faster overall even when insertion/deletion is concerned, on modern hardware.


## A Note

Many computer science courses and textbooks will give the summary of Linked lists vs arrays as above.
However, in practice and on some architectures, linked lists are hardly ever used.
To expand on the note slightly, Bjarne Stroustrup once did a [talk](https://www.youtube.com/watch?v=YQs6IC-vgmo) on exactly this topic.
In the talk, he talks the performance of vectors: a kind of array that handles movement of data automatically.