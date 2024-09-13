# Quicksort

Quicksort is a much faster sorting algorithm than the Selection Sort algorithm detailed elsewhere.
It's an example of a *divide and conquer* approach to problem-solving.

The aim of this section are to introduce divide-and-conquer strategies through the example of quicksort.

 > N.B. This section relies on recursion, which I have not covered in this set.

## Divide and Conquer

Divide and Conquer algorithms are recursive algorithms.
As with all recursive algorithms, there must be a base case.
The approach is then to divide or decrease the size of a problem until it reaches its base case, then build up the whole solution from there.

"Grokking Algorithms" illustrates this via an example: How can a plot of land with unequal length and width be divided evenly into the largest possible square plots?

![A field](./resources/field_undivided.svg "A 1680 * 640 field")

The divide and conquer strategy can be applied to this problem, in the two steps described:

 1. Find the base case
 2. Divide or reduce the size of the problem until it becomes the base case

### 1. The base case

 The easiest base case for a given field is if the length of one side was a multiple of the other side's length.

 ![A small, proportional field](./resources/small-split-field.svg)

 For example, if one side is 50m and the other 25m, then the largest box required would be 25m * 25m.

### 2. The Recursive Case

 In a divide and conquer strategy, each step must reduce the original problem.
 The fastest way to do this for the field is to start with the largest square possible: one that has the same length as the smallest side.
 In this example, that would be 400m:

  ![Using the largest possible square](./resources/large-field-split.svg)

 The field space is now divided into 3 sections: two squares of 640m x 640m, and a 400m x 640m rectangle.
 The recursive step comes into play in the latter of these sections: apply the same algorithm to split the remaining segment.
 From Euclid's algorithm, the largest box that works for this segment will also be the largest box that works for the entire field.

 So, applying the same algorithm to the remaining segment:

 1. 400m x 640m can be split into a single 400m x 400m box, and a remaining 240m x 400m box
 2. A 240m x 400m box can be split into a single 240m x 240m box, and a remaining 160m x 240m segment.
 3. The 160m x 240m box can be split into a 160m x 160m box, and a 160m x 80m box.

160 can be divided exactly by 80m, and so this is the base case. 
Thus, the original field can be divided into squares of 80m x 80m.

### Python Algorithm

Here is the algorithm, summarised in Python:

```python
def divide_plot(height: int, width: int) -> int:
    larger : int = max([height, width])
    smaller : int = min([height, width])
    remainder : int = larger % smaller
    
    if remainder == 0: return smaller
    else: return divide_plot(remainder, smaller)
```

 > ### N.B Why Recursion?
 > This algorithm can be performed iteratively as well as recursively.
 > However, in functional programming languages such as Haskell, there are no loops.
 > Instead, recursion *must* be used to write functions such as this.
 >
 > Functional languages are much easier to understand with a pre-existing understanding of recursive strategies.


## Quicksort

As the name implies, Quicksort is a sorting algorithm.
Created by Tony Hoare in 1959, it has become the de-facto sorting algorithm. 
For example, the C standard library contains the `qsort` function, and Python's TimSort is based off of quicksort.

To begin, consider the simplest array that could be passed to a sorting algorithm.
This would be either an empty array, or an array containing only a single element: these do not need to be sorted at all.
As there's nothing to sort, single-value and empty arrays are the base case:

```python
def quicksort(array : List) -> List:
    if (len(array) < 2): return array
```

An array with two elements is also easy to sort: just compare the two elements, and swap them accordingly.

```python
def quicksort(array : List) -> List:
    if (len(array) < 2): return array

    if (len(array) == 2):
        if (array[0] > array[1]):
            array[0], array[1] = array[1], array[0]
    
    return array
```

Once arrays begin to contain more than 2 elements, the arrays should be broken down into smaller arrays until the algorithm arrives at the base case.
Quicksort breaks the elements down by picking an element from the array (known as the *pivot*), and creating two arrays: one containing smaller elements, the other containing larger elements.

For example, take an array containing 3 elements: $[52, 7, 2]$.
Choose a pivot, e.g. the first element, and place the elements smaller than the pivot in one array, and elements larger than the pivot into another: 

$[7, 2], 52, [\_]$

This step is called *partitioning*.
If the sub-arrays were sorted, then they could be combined with the pivot to produce a sorted array:

$[2, 7] + [52] + [\_] = [2, 7, 52]$

The base case of quicksort already accounts for empty arrays, and arrays with two elements.
So, calling quicksort on the remaining sub-arrays, then combining the result, will lead to a sorted array.

This works with any chosen pivot. E.g., choosing 7 as the pivot:

$[2], [7], [52]$

Both sub-arrays only have one element, and the algorithm has base cases for those.

So, to sort 3 elements

 1. Pick a pivot
 2. Split the array into two sub-arrays:
    - one containing elements less than the pivot
    - one containing elements greater than the pivot
 3. Call quicksort recursively on the two sub-arrays.

Suppose an array contains more than 3 elements, e.g. $[4, 7, 2, 10]$

Picking 10 as the pivot creates two sub-arrays: 

$[4, 7, 2], 10, [\_]$ 

The left-hand array has 3 elements, which can be sorted by calling Quicksort on this sub-array.
If an array of 4 elements can be sorted, than an array of 5 elements can also be sorted.
For an array of 5 elements, it's possible to pick a pivot that leaves a sub-array with 4, 3, 2, or 1 elements.
Each of these can be sorted by calling Quicksort recursively.

This works with any element as the pivot.
If an array with 5 elements can be sorted, then an array of 6 elements can be sorted.
Using the same logic, this can be expanded to arrays of any size.

With all this in mind, here is a simple version of Quicksort:

```python
def quicksort(array: List) -> List:
    if (len(array) < 2): return array

    pivot = array[0]
    # Compare all elements except the first
    less = [i for i in array[1:] if i <= pivot]
    greater = [i for i in array[1:] if i > pivot]

    return quicksort(less) + [pivot] + quicksort(greater)
```

 > N.B. This is not the version use in the Python implementation, for reasons that will soon become clear.

## The Speed of Quicksort

Quicksort is fairly unique in that its speed depends on which pivot is chosen.
For example, always taken the first element as the pivot may lead to the algorithm taking $O(n^2)$ time.
In different terms, it's as slow as sellection sort.

Another algorithm, *Merge Sort*, always runs in $O(nlog(n))$: much faster than quicksort.
However, in the **average** case, quicksort takes $O(nlog(n))$ time.
So, why not use merge sort if it's always going to take $O(nlog(n))$ time?

 > ### Important
 > When writing big O notation, constants are removed in favour of showing growth terms.
 > As an example, an algorithm that takes $O(n)$ time might really take $cn$ seconds, where $c$ is a constant amount of time.
 >
 > Constants are usually omitted for algorithms with two different big O times, as they don't matter much.
 > Big O shows how the speed or memory usage of an algorithm is affected by the size of its input.
 >
 > But in cases where the Big O expressions are the same, these constants do make a difference

Quicksort and merge sort are both $O(nlog(n))$, but quicksort has smaller constants.
In practice, quicksort hits the average case much more often that the worst case.

### Average Case vs Worst case

The speed of quicksort depends heavily on the chosen pivot.
For example: if the chosen pivot is always the first element and the array is already sorted, quicksort does not check if the input array is already sorted.
The array and sub-arrays are never split into to halves, and one of the sub-arrays is always empty.
This creates an incredibly long call stack, massively increasing the time taken to sort the array.

If, instead, a middle element is picked, then fewer recursive calls are needed and the call stack is much shorter.
This is the best-case scenario, where the stack size is $O(log(n))$. In the worst case, the call stack size is $O(n)$.

For each level of the stack, all $n$ remaining elements must be touched in order to split them about the pivot (even though they all end up in the same sub-array).
Even splitting the array differently, each call in the stack still touches $n$ elements.

In the best-case scenario, the height of the call stack is $O(log(n))$, making the overall time $O(nlog(n))$
In the worst-case scenario, the height of the call stack is $O(n)$, making the overall time $O(n^2)$.

With quicksort, the average case is also the best-case scenario.
By choosing a random pivot for each level in the stack, quicksort can hit this average case more often.
With this in mind, here's an example implementation of quicksort using random pivot points:

```python
from random import randint

def quicksort(array: List) -> List:
    if (len(array) < 2): return array

    pivot = array[randint(0, len(array) - 1)]

    # Compare all elements except the first
    less = [i for i in array[1:] if i <= pivot]
    greater = [i for i in array[1:] if i > pivot]

    return quicksort(less) + [pivot] + quicksort(greater)
```

## Notes

The quicksort algorithm described thus far is taken practically verbatim from Grokking Algorithms.
However, this implementation involves a lot of copying and moving around of data, including the creation of new lists at each step of the call.
It also requires iteration through the input list *twice*: one for each of the arrays created above and below the pivot.

Faster implementations will use in-place sorting, where no new lists/arrays are required.
This requires a new partitioning scheme, as creating new arrays requires that the sorting must take place within ranges of the original array.
The solution is to represent slices using two indices, low and high, to represent the beginning and end of the slice, respectively.

```python
def in_place_quicksort(arr : list, low : int, high : int) -> None:
    return None
```

Since sorting and partitioning must be performed in-place, elements must be moved around within the original array.
The algorithm will also need to work out the final position for the pivot element.
To do this, the algorithm can find the position first element in the sequence (from low to high) that is higher than the pivot.
For now, this process is easier if the pivot element is at beginning or end of the array

```python
def in_place_quicksort(arr : list, low : int, high : int) -> None:
    pivot_idx : int = high
    pivot = arr[pivot_idx]

    left : int = low

    while (arr[left] < pivot): left += 1
    
    return None
```

This approach isn't going to work, as the loop only continues until it finds the first high element;
there may be low elements beyond this point.
These should be swapped with the high element found by increment a pointer from the left.
This can be achieved with a second pointer starting from the high position and moving downwards until it finds an element lower than the pivot.
The elements at those indices can then be swapped.

```python
def in_place_quicksort(arr : list, low : int, high : int) -> None:
    pivot_idx : int = high
    pivot = arr[pivot_idx]

    left  : int = low
    right : int = high - 1

    while (arr[left] < pivot): left += 1
    while (arr[right] >= pivot) right -= 1

    arr[left], arr[right] = arr[right], arr[left]

    return None
```

But this only swaps the first elements matching the condition, and the right-hand pointer should always be greater than the left-hand pointer.
When these two pointers cross must be where the pivot element should go: all elements to the right of the crossing point will be high, and all points to the left will be low.
So, the left and right pointers can be incremented/decremented continuously until the two pointers meet:

```python
def in_place_quicksort(arr : list, low : int, high : int) -> None:
    pivot_idx : int = high
    pivot = arr[pivot_idx]

    left  : int = low
    right : int = high - 1

    while (left != right):
        while (arr[left] <= arr[partition_idx] and left < right):
            left += 1
        while (arr[right] > arr[partition_idx] and right > left):
            right -= 1

        arr[left], arr[right] = arr[right], arr[left]
    return None
```
note that, in this case the inner loops must also check that they don't exceed the other pointer.

The final step is to swap the pivot idx with the element found at the right pointer, and call the function recursively on the two resulting sides.
When low and high point to the same value, then the array size is 1 (or 0) and the base case has been reached.

```python
def in_place_quicksort(arr : list, low : int, high : int) -> None:
    if (low == high): return None

    pivot_idx : int = high
    pivot = arr[pivot_idx]

    left  : int = low
    right : int = high - 1

    while (left != right):
        while (arr[left] <= arr[partition_idx] and left < right):
            left += 1
        while (arr[right] > arr[partition_idx] and right > left):
            right -= 1

        arr[left], arr[right] = arr[right], arr[left]

    arr[pivot_idx], arr[right] = arr[right], arr[pivot_idx]

    in_place_quicksort(arr, low, left - 1)
    in_place_quicksort(arr, left + 1, high)
    return None
```

Earlier, it was said that quicksort performs best when the pivot index is randomly selected.
The easiest way to achieve this, while not introducing further complexity, is to move the randomly selected pivot to the end of the current slice.
Ask me how I know this is the simplest way (hours of my life, wasted).

```python
from random import randint

def in_place_quicksort(arr : list, low : int, high : int) -> None:
    if (low >= high):
        return None

    pivot_idx : int = randint(low, high)
    arr[pivot_idx], arr[high] = arr[high], arr[pivot_idx]
    pivot = arr[high]

    left  : int = low
    right : int = high

    while (left != right):
        while (arr[left] <= pivot and left < right):
            left += 1

        while (arr[right] >= pivot and right > left):
            right -= 1

        arr[left], arr[right] = arr[right], arr[left]

    arr[high], arr[left] = arr[left], arr[high]
    
    in_place_quicksort(arr, low, left - 1)
    in_place_quicksort(arr, left + 1, high)
    return None
```

### Other in-place methods

This is only one of many in-place partitioning schemes: there are many, many others.
What's used here is by-no-means perfect, and creating a unique method can be a worthwhile exercise.