class LinkedList:
    """
    Simple implementation of a Linked List using iterative methods
    """
    class Node:
        """A single Node in the linked list"""
        
        def __init__(self, data):
            self.__next  = None
            self.__data = data
        
        # Getters and Setters for properties are useful if the API ever needs to change
        # It's reasonable practice to put them in
        @property
        def data(self):
            return self.__data
        
        @data.setter
        def data(self, new_data):
            self.__data = new_data
    
        @property
        def next(self):
            return self.__next
        
        @next.setter
        def next(self, new_node):
            self.__next = new_node
            
        def __str__(self):
            return f'{self.__data}'


    def __init__(self):
        """Initialise with an empty head"""
        self.__head : self.Node | None = None
        self.__size : int = 0

    def __init__(self, size : int, value = None):
        """
        Initialise a list with a predefined size

        Optionally, initialise with a value
        """
        self.__head = None
        self.__size : int = 0

        if (size == 0): return self

        self.__head = self.Node(value)
        current_node = self.__head
        i : int = 1
        while (i < size):
            current_node.next(self.Node(value))
            current_node = current_node.next()

    def __init__(self, values : list):
        """Create a linked list from a built-in list"""
        self.__head = None
        self.__size = 0
        if (len(values) == 0): return self
        self.__head = self.Node(values[0])
        current_node = self.__head
        for value in values[1:]:
            current_node.next = self.Node(value)
            current_node = current_node.next
        self.__size = len(values)

    def __iter__(self):
        """Iterator for generator expressions (e.g. List comprehension)"""
        current_node : self.Node | None = self.__head
        while (current_node is not None):
            yield current_node.data
            current_node = current_node.next
    
    def __str__(self):
        """String representation of the object"""
        return f"{[i.data for i in self]}"
    
    def __len__(self):
        """Number of elements in the list"""
        return self.__size
    
    @property
    def head(self) -> Node | None:
        """The first node"""
        return self.__head

    def __traverse_to_index(self, index : int) -> Node | None:
        """Helper method to traverse to a given index, returning the node"""
        if index > self.__size:
            raise(IndexError)
        curr_node : self.Node = self.__head
        i : int = 0
        while (i < index):
            curr_node = curr_node.next
            i += 1
        return curr_node
        
    def __getitem__(self, index : int):
        """Allow the use of the [] indexing operator"""
        return self.__traverse_to_index(index).data
    
    def append(self, value):
        """Append a value to the last item in the array"""
        last_node = self.__traverse_to_index(self.__size - 1)
        last_node.next(value)
        self.__size += 1

    def pop(self):
        """Remove the last Node in the list and return its value"""
        penultimate_node : self.Node = self.__traverse_to_index(self.__size - 2)
        last_node : self.Node = penultimate_node.next
        penultimate_node.next = None
        self.__size -= 1
        return last_node.data
    
    def insert_at(self, index : int, value):
        """Insert a single value at a given index"""
        target_node : self.Node = self.__traverse_to_index(index)
        temp_node : self.Node = target_node.next
        target_node.next = self.Node(value)
        target_node.next.next = temp_node
        self.__size += 1
    
    def delete_from(self, index : int):
        """Delete a given index"""
        target_node : self.Node = self.__traverse_to_index(index - 1)
        target_node.next = target_node.next.next
        self.__size -= 1


ll = LinkedList([i for i in range(100)])
