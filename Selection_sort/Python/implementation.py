def find_smallest(values : list) -> int:
    current_min = values[0]
    smallest_index : int = 0
    for i in range(1, len(values)):
        if (values[i] < current_min): 
            current_min = values[i]
            smallest_index = i
    return smallest_index


def selection_sort(values : list) -> list:
    new_arr = []
    for _ in range(len(values)):
        smallest = find_smallest(values)
        new_arr.append(values.pop(smallest))
    return new_arr


def selection_sort_comp(values : list) -> list:
    # list comprehension version of selection sort
    return [values.pop(find_smallest(values)) for _ in range(len(values))]
