# Selection Sort

Sorting collections of items is a common requirement in software.
Doing so efficiently is often crucial to a problem.

Selection sort is a relatively simple sorting algorithm, but it's inefficient.

Selection sort finds the item in the list/array with the greatest (or lowest) value, and places it in the first position of a new list.
From there, the algorithm loops over the list: each loop selects the item of greatest (or lowest) value, and adds it to the new list.

Since the algorithm must do this for each item in the collection, it must run at least n times for a collection of n elements.
To ensure that the highest/lowest value item is taken in each iteration, each iteration must loop through all remaining elements.
E.g. To sort a list of 5 elements, the first iteration will 5 checks, the second 4 checks, and so on.

Searching through a collection for the largest element will take $O(n)$ time.
This must be repeated $n$ times, so the repetition is an $O(n)$ operation.
This therefore takes $O(n * n) = O(n^2)$ time.

> N.B. To explain exactly why, it's worth reading about O(n) time.