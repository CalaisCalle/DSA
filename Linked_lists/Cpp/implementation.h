#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <memory>
#include <initializer_list>
#include <iostream>
#include <sstream>

template <typename T>
class LinkedList {
    // This is a simplified version of a Linked List,
    // using iterative methods, and not defining 
    // or using iterators just yet.
    //
public:
    LinkedList<T>() = default;
    LinkedList<T>(std::size_t init_size, const T& val);
    ~LinkedList<T>();

    void    append(const T& item);
    T       pop();
    void    insert_at(std::size_t index, const T& item);
    void    delete_from(std::size_t index);

    std::size_t size()  { return size_val; };

    void print();

    // operator overloads
    //
    T& operator[](std::size_t index);
private:
    class Node {
    public:
        Node() = delete; // Delete the default constructor : Never want a node without a value
        Node(T data) : data_val { data }, next_val { nullptr } { }
        Node(T data, Node* next) : data_val { data }, next_val { next } { }

        // Accessors
        //
        T&      data()              { return data_val; }
        void    data(const T& val)  { data_val = val; }        

        Node*                   next()           { return next_val; }
        void                    next(Node* val)  { next_val = val; }
    private:
        T       data_val    { };
        Node*   next_val    { nullptr };
    };

    // Linked List members 
    //
    Node*           head        { nullptr };
    std::size_t     size_val    { 0 };

    // Linked List functions
    //
    auto traverse_to(std::size_t index);
};


template <typename T>
LinkedList<T>::LinkedList(std::size_t init_size, const T& val) :
head { new Node { val } }
{
    auto current_node = head;
    auto nodes { 1 };
    for (std::size_t i { 1 }; i < init_size; ++i)
    {
        current_node->next(new Node { val });
        current_node = current_node->next();
    }
    size_val = init_size;
}


template <typename T>
T& LinkedList<T>::operator[](std::size_t index)
{
    auto node_at_index = traverse_to(index);
    return node_at_index->data();
}


template <typename T>
LinkedList<T>::~LinkedList()
{
    auto current_node = head;
    if (current_node == nullptr) return; // nothing to do

    while (current_node != nullptr)
    {
        auto next_node = current_node->next();
        delete current_node;
        current_node = next_node;
    }
}


template <typename T>
void    LinkedList<T>::append(const T& item)
{
    auto last_node = traverse_to(size_val - 1);
    last_node->next(new Node { item });
    size_val++;
}


template <typename T>
T      LinkedList<T>::pop()
{
    // C++ STL doesn't usually delete the item being popped
    // Here it's done to keep it in line with the Python version
    //
    auto penultimate_node = traverse_to(size_val - 2);
    auto last_node = penultimate_node->next();
    auto val = last_node->data();
    delete last_node;
    penultimate_node->next(nullptr);
    size_val--;
    return val;
}


template <typename T>
void    LinkedList<T>::insert_at(std::size_t index, const T& item)
{
    // Traverse to the given index
    // Get the old neighbour
    // Create the new neighbour and give it the old neighbour's address
    // reassign the "next" value of the node at the index
    //
    auto insert_on = traverse_to(index);
    auto post_node = insert_on->next();

    insert_on->next(new Node { item, post_node} );
    size_val++;
}


template <typename T>
void    LinkedList<T>::delete_from(std::size_t index)
{
    // Delete the node at the specified index
    // Grab the pointer to the node to delete
    // And that of the next node
    // Give the latter to the node prior to the deleted
    //

    if (index >= size_val) throw std::out_of_range("Out of range!");

    // Special case: Deleting the zero index
    // where there is no prior node
    //
    if (index == 0)
    {
        auto next_node = head->next();
        delete head;
        head = next_node;
    }
    else
    {
        auto previous = traverse_to(index - 1);
        auto current = previous->next();
        auto next = previous->next()->next();
        delete current;
        previous->next(next);
    }
    size_val--;

}



template <typename T>
auto LinkedList<T>::traverse_to(std::size_t index)
{
    // Simple traversal: helper function: Keep going until
    // the index is reached
    if (index >= size_val) {
        throw std::out_of_range("Out of range!");
    }

    auto current_node = head;
    for (std::size_t i { 0 }; i < index; ++i)
    {
        current_node = current_node->next();
    }

    return current_node;
}


template <typename T>
void LinkedList<T>::print()
{
    // This wouldn't normally be a part of a linked list
    // Here it's provided to show the results of operations
    //
    std::stringstream ss { };
    ss << "{ ";
    auto current_node = head;

    while (current_node != nullptr) {
        ss << current_node->data() << ", ";
        current_node = current_node->next();
    }
    ss << "}";

    std::cout << ss.str() << std::endl;
}

#endif