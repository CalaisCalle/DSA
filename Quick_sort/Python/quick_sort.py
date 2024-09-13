from random import randint

def quicksort(array: list) -> list:
    if (len(array) < 2): return array

    pivot = array[randint(0, len(array) - 1)]

    # Compare all elements except the first
    less = [i for i in array[1:] if i <= pivot]
    greater = [i for i in array[1:] if i > pivot]

    return quicksort(less) + [pivot] + quicksort(greater)


def in_place_quicksort(arr : list, low : int, high : int) -> None:
    if (low >= high): # base-case, nothing to be done
        return None

    # Select a random index as the pivot, and move it to the end
    pivot_idx : int = randint(low, high)
    arr[pivot_idx], arr[high] = arr[high], arr[pivot_idx]
    pivot = arr[high]

    left  : int = low
    right : int = high

    # Two "Pointer" approach
    # If the left pointer encounters an element greater than the pivot
    # and the right pointer simultaneously encounters an lesser than the pivot
    # Swap the two
    # Otherwise, keep increment the pointers
    while (left != right):
        while (arr[left] <= pivot and left < right):
            left += 1

        while (arr[right] >= pivot and right > left):
            right -= 1

        arr[left], arr[right] = arr[right], arr[left]

    # Swap the pivot element to its proper location
    arr[high], arr[left] = arr[left], arr[high]
    
    # Recursively call the algorithm on the partitions
    in_place_quicksort(arr, low, left - 1)
    in_place_quicksort(arr, left + 1, high)
    return None