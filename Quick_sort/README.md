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
