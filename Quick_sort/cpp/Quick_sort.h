#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <random>
#include <vector>

// This is definitely not the most efficient implementation of quick_sort
// For one, it constantly regenerates the uniform_int_distribution.
//
// For another, there are two loops to loop through each half and
// emplace elements back. Additionally, there's a new array created
// When combining the elements.
//
// The first point could be solved either by turning quick_sort into a functor,
// (though doing this nicely would require C++ 23)
// or by having a second function that can take a uniform_int_distribution as
// input.
//
//
template <typename T>
std::vector<T> quick_sort(const std::vector<T>& arr) {
  if (arr.size() < 2)
    return arr;

  std::uniform_int_distribution<> dstrb(0, arr.size() - 1);
  std::size_t pivot_idx{};

  T pivot{arr[pivot_idx]};

  std::vector<T> less{};
  std::vector<T> greater{};

  // Elements below the pivot
  //
  for (std::size_t i{0}; i < pivot_idx; ++i) {
    if (arr[i] <= pivot)
      less.emplace_back(arr[i]);
    else
      greater.emplace_back(arr[i]);
  }

  // Elements above the pivot
  //
  for (std::size_t i{pivot_idx + 1}; i < arr.size(); ++i) {
    if (arr[i] <= pivot)
      less.emplace_back(arr[i]);
    else
      greater.emplace_back(arr[i]);
  }

  // Sort the lesser and larger arrays
  //
  auto less_sorted = quick_sort(less);
  auto greater_sorted = quick_sort(greater);

  // Recombine the two arrays
  //
  std::vector<T> out{};
  out.insert(out.end(), less_sorted.begin(), less_sorted.end());
  out.emplace_back(pivot);
  out.insert(out.end(), greater_sorted.begin(), greater_sorted.end());

  return out;
}

// This is an alternative version of quicksort, which instead swaps the elements
// in place Since it re-uses the same memory, it has more efficient memory usage
// than the above.
//
// It also avoids having to combine the elements at the end of function
//

// Partition function to partition the array
// And return the location of the pivot
// Haven't bothered randomising here
//
template <typename T>
std::size_t partition(std::vector<T>& arr, std::size_t low, std::size_t high) {
  const T& pivot = arr[high];

  std::size_t greatest_idx{low - 1};

  std::size_t left{low};
  std::size_t right{high};

  while (left != right) {
    while (arr[left] <= pivot && left < right)
      ++left;
    while (arr[right] >= pivot && left > right)
      ++right;

    std::swap(arr[left], arr[right]);
  }

  std::swap(arr[left], arr[high]);
  return left;
}

template <typename T>
void in_place_quicksort(std::vector<T>& arr,
                        std::size_t low,
                        std::size_t high) {
  if (low >= high)
    return;

  std::size_t pivot_idx{partition<T>(arr, low, high)};
  std::cout << pivot_idx << std::endl;

  // The conditional check prevents the int from attempting to go below zero,
  // and creating a potential overflow
  in_place_quicksort(arr, low, pivot_idx > 0 ? pivot_idx - 1 : 0);
  in_place_quicksort(arr, pivot_idx + 1, high);
}
#endif