# Binary Search

Binary search is a relatively simple algorithm that can drastically reduce the time taken to find an item in a sorted list.

## The Problem

Imagine that a program must look up names in a database, or words in a dictionary.
In both instances, the data is sorted in some way (e.g. alphabetically).
The program could choose a naive approach, in which the algorithm checks each value until it finds the correct value.

However, in most cases, it would be faster to start at the middle, and have the program from there.

This is an example of a *Search Problem*, and can be solved using Binary Search for the special case where the list is sorted.

## Naive Search

Say that there's a list containing 10 numbers, 0-9, and an algorithm is required to find if a particular element the list.
A naive implementation might simply check each element in the list to see whether or not it matches the target value:

```python
values : List = list(range(10))

def naive_search(values : list, target : int):
    """Naive search for a given element"""
    for item in values:
        if (item == target): return True
    
    return False
```

This implementation is fine, but consider the number of steps taken for each element.
In this case, there is only one step: checking to see if the values are equal.

> N.B. This is a simplified case where only integers are checked, which can be done in a single step.
> For more complex data structures, equality checking may take more than 1 step.
> Generally, however, the number of steps needed for an equality comparison will be either constant or increase linearly with the structure

So, if the target value was 5, the algorithm would take 6 steps to return the solution (True).

Now consider the worst-case scenario for performance: that the target is not in the list of values.
The algorithm could only return False after checking every single element in the list.
For a large list containing one billion items, it could take 1 billion steps.

The time taken for the algorithm to complete will, in the worst case, increase linearly with the number of elements.
This makes it an O(n) algorithm.

> See the note about big O notation in the main README file // TODO: Add a note in the README for Big O


## Binary Search

A much better approach to the problem is to first compare the target value to the element in the **middle** of the list.
If the value is greater than the target, then so too will all elements after this one be greater.
This effectively eliminates the need to check the second half of the list.
The process works similarly if the middle value is less than the target.

This process can then be repeated for the remaining half of the elements.
Each time, roughly half of the remaining elements in the list are eliminated from the list.

For example: A list contains all numbers from 0-100, and the target value 80.
First, the target is compared against the middle value (50).
80 > 50, so the next *pass* of the algorithm only checks the top half of the values.

The element in the middle of the remaining values is 75. 
80 is greater than 75, so the next pass only checks values above 75.
This process repeats, comparing against 88, then then 81, then 78, and finally 80 (in this case).

For the implementation:

```python

def binary_search(sorted_list : list, target : int) -> int:

    low : int = 0
    high : int = len(sorted_list) - 1

    while low <= high:
        mid = low + high / 2
        guess = sorted_list[mid]
        if guess == target:
            return mid
        elif guess <= target:
            high = mid - 1
        elif guess >= target:
            low = mid + 1
    
    return None
```

`binary_search` takes a sorted list an a target.
If the target is in the list, then its position is returned.
If it cannot, then it returns -1.

`low` and `high` keep track of the section of the list under search.
This starts defining the entire array, and adjusts the values based on the comparison between the guess and the current target.

When this algorithm runs the list, it splits the list in two and performs several equality checks.
The number of checks performed is constant for each step, but the algorithm eliminates half the values from the search with each iteration.

In the worst case, the algorithm must take $log_{2}(n + 3)$ steps.
So the time complexity of the function must grow as $O(log_{2}(n))$.