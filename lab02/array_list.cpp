#include "array_list.h"

namespace ssuds {

    // Constructor with an optional reserve amount
    template <typename T>
    ArrayList<T>::ArrayList(unsigned int reserve_size)
        : mSize(0), mCapacity(reserve_size) {
        if (mCapacity > 0)
            mArray = new T[mCapacity];
        else
            mArray = nullptr;
    }

    // Destructor to clean up memory
    template <typename T>
    ArrayList<T>::~ArrayList() {
        delete[] mArray;
    }

    // Get size of the array
    template <typename T>
    unsigned int ArrayList<T>::size() const {
        return mSize;
    }

    // Get capacity of the array
    template <typename T>
    unsigned int ArrayList<T>::capacity() const {
        return mCapacity;
    }

    // Reserve space for at least the requested amount
    template <typename T>
    void ArrayList<T>::reserve(unsigned int new_capacity) {
        if (new_capacity > mCapacity) {
            T* newArray = new T[new_capacity];
            for (unsigned int i = 0; i < mSize; i++)
                newArray[i] = mArray[i];
            delete[] mArray;
            mArray = newArray;
            mCapacity = new_capacity;
        }
    }

    // Append method to add at the end
    template <typename T>
    void ArrayList<T>::append(const T& item) {
        if (mSize == mCapacity) {
            grow();
        }
        mArray[mSize++] = item;
    }

    // Prepend method to add at the beginning
    template <typename T>
    void ArrayList<T>::prepend(const T& item) {
        if (mSize == mCapacity) {
            grow();
        }
        for (unsigned int i = mSize; i > 0; i--) {
            mArray[i] = mArray[i - 1];
        }
        mArray[0] = item;
        mSize++;
    }

    // Insert method to insert at a specific index
    template <typename T>
    bool ArrayList<T>::insert(const T& item, unsigned int index) {
        if (index > mSize) {
            std::cout << "Error: Index out of range.\n";
            return false;
        }
        if (mSize == mCapacity) {
            grow();
        }
        for (unsigned int i = mSize; i > index; i--) {
            mArray[i] = mArray[i - 1];
        }
        mArray[index] = item;
        mSize++;
        return true;
    }

    // Method to access an element at a specific index
    template <typename T>
    T& ArrayList<T>::at(unsigned int index) {
        if (index >= mSize) {
            std::cout << "Error: Index out of range.\n";
            return mArray[0]; // Return the first element as a fallback (or handle this more appropriately)
        }
        return mArray[index];
    }

    // Const method to access an element at a specific index
    template <typename T>
    const T& ArrayList<T>::at(unsigned int index) const {
        if (index >= mSize) {
            std::cout << "Error: Index out of range.\n";
            return mArray[0]; // Return the first element as a fallback (or handle this more appropriately)
        }
        return mArray[index];
    }

    // Method to print the ArrayList
    template <typename T>
    void ArrayList<T>::print(std::ostream& os) const {
        os << "[";
        for (unsigned int i = 0; i < mSize; i++) {
            os << mArray[i];
            if (i != mSize - 1) os << ", ";
        }
        os << "]";
    }

    // Method to remove an element at a specific index
    template <typename T>
    T ArrayList<T>::remove(unsigned int index) {
        if (index >= mSize) {
            std::cout << "Error: Index out of range.\n";
            return T(); // Return default value of T
        }

        T removed_value = mArray[index];
        for (unsigned int i = index; i < mSize - 1; i++) {
            mArray[i] = mArray[i + 1];
        }
        mSize--;

        // Shrink capacity if needed
        if (mSize <= mCapacity / 4) {
            shrink();
        }

        return removed_value;
    }

    // Remove all occurrences of a specific value
    template <typename T>
    unsigned int ArrayList<T>::remove_all(const T& value) {
        unsigned int count = 0;
        for (unsigned int i = 0; i < mSize; i++) {
            if (mArray[i] == value) {
                remove(i);
                count++;
                i--; // Adjust the index since the array shrinks
            }
        }
        return count;
    }

    // Find a value in the array and return its index, or -1 if not found
    template <typename T>
    int ArrayList<T>::find(const T& value, unsigned int start_index) const {
        if (start_index >= mSize) {
            std::cout << "Error: Start index out of range.\n";
            return -1; // Return -1 to indicate failure
        }

        for (unsigned int i = start_index; i < mSize; i++) {
            if (mArray[i] == value) {
                return i;
            }
        }

        return -1; // Value not found
    }

    // Double the size of the array when it is full
    template <typename T>
    void ArrayList<T>::grow() {
        unsigned int new_capacity = mCapacity == 0 ? 1 : mCapacity * 2;
        reserve(new_capacity);
    }

    // Shrink the capacity when the size is much smaller than the capacity
    template <typename T>
    void ArrayList<T>::shrink() {
        unsigned int new_capacity = mCapacity / 2;
        reserve(new_capacity);
    }

} // namespace ssuds

// Explicit template instantiation for commonly used types
template class ssuds::ArrayList<int>;
template class ssuds::ArrayList<float>;
template class ssuds::ArrayList<double>;

