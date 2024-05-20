#include <array>
#include <cstdint>
#include <optional>
#include <vector>


/*
* NOTE
* ====
*
* These functions use templates to achieve the same functionality across many basic types
* There's no need to do this in Python, given that everything there is weekly typed.
* I'm aware that there are ways of doing this with iterators - I'm simply being lazy
* 
* I'm also using std::optional to allow the passing of a fail state, indicated by
* an empty optional.
*/

template <typename T>
std::optional<std::size_t> binary_search(const T* values, std::size_t size, T target)
{
    std::size_t low { 0 };
    std::size_t high { size - 1 };

    while (low <= high) {
        std::size_t mid { (low + high) / 2 };
        auto guess = values[mid];
        
        if (guess == target) return mid;
        else if (guess > target) high = mid - 1;
        else low = mid + 1;
    }

    return { }; // Returns an optional with no value
}


template <typename T>
std::optional<std::size_t> binary_search(const std::vector<T>& values, T target)
{
    return binary_search(values.data(), values.size(), target);
}


template <typename T, std::size_t SIZE>
std::optional<std::size_t> binary_search(const std::array<T, SIZE>& values, T target)
{
    return binary_search(values.data(), values.size(), target);
}