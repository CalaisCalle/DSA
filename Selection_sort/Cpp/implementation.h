#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <vector>
#include <array>

// Note: this implementation ends up deleting the elements in the original vector
// It could probably be done better
//
template <typename T>
std::size_t find_smallest(const T* arr, std::size_t sz)
{
    T           smallest        { arr[0] };
    std::size_t smallest_index  { 0 };

    for (std::size_t i { 0 }; i < sz; ++i)
    {
        if (arr[i] < smallest)
        {
            smallest        = arr[i];
            smallest_index  = i;
        }
    }

    return smallest_index;
}


template <typename T>
void selection_sort(T* data, std::size_t size)
{
    // This implementation is quick, and not very safe
    //
    for (std::size_t i { 0 }; i < size; ++i)
    {
        // Finds the minimum of the remaining elements,
        // then swaps that minimum to the ith position
        // Repeats with smaller elements
        // 
        std::size_t smallest_from_i = find_smallest(data + i, size - i);
        T* temp = *(data + i);
        *(data + i) = *(data + smallest_from_i + i);
        *(data + smallest_from_i + i) = temp;
    }
}


// Specialisations for a couple of common containers
// It's possible to create a template-template that will accept all containers,
// But it's a lot to look at for someone just trying to get DSA knowledge
//
template <typename T>
void selection_sort(std::vector<T>& arr)
{
    // Perform an in-place sort
    //
    selection_sort(arr.data(), arr.size());
}


template <typename T, std::size_t N>
void selection_sort(std::array<T, N> & arr)
{
    selection_sort(arr.data(), arr.size());
}
#endif