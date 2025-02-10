#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>

namespace ssuds {

    template <typename T>
    class ArrayList {
    private:
        T* mArray;             // Array to hold the elements
        unsigned int mSize;    // Current size (number of elements)
        unsigned int mCapacity; // Current capacity of the array

    public:
        // Constructor with an optional reserve amount
        explicit ArrayList(unsigned int reserve_size = 0);

        // Destructor to clean up memory
        ~ArrayList();

        // Get size of the array
        unsigned int size() const;

        // Get capacity of the array
        unsigned int capacity() const;

        // Reserve space for at least the requested amount
        void reserve(unsigned int new_capacity);

        // Append method to add at the end
        void append(const T& item);

        // Prepend method to add at the beginning
        void prepend(const T& item);

        // Insert method to insert at a specific index
        bool insert(const T& item, unsigned int index);

        // Method to access an element at a specific index
        T& at(unsigned int index);

        // Const method to access an element at a specific index
        const T& at(unsigned int index) const;

        // Method to print the ArrayList
        void print(std::ostream& os) const;

        // Method to remove an element at a specific index
        T remove(unsigned int index);

        // Remove all occurrences of a specific value
        unsigned int remove_all(const T& value);

        // Find a value in the array and return its index, or -1 if not found
        int find(const T& value, unsigned int start_index = 0) const;

    private:
        // Double the size of the array when it is full
        void grow();

        // Shrink the capacity when the size is much smaller than the capacity
        void shrink();
    };

} // namespace ssuds

#endif // ARRAY_LIST_H
