def binary_search(sorted_list : list, target) -> int:
    """
    Perform a binary search for a given target in log(n) time.

    This implementation is based on the one found in Adiya Y. Bhargava's
    "Grokking Algorithms". 
    """
    low : int = 0
    high : int = len(sorted_list) - 1

    while low <= high:
        mid = (low + high) // 2
        guess = sorted_list[mid]
        if guess == target:
            return mid
        elif guess > target:
            high = mid - 1
        else:
            low = mid + 1
    
    return None
