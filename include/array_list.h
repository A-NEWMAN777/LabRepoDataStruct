#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <stdexcept>  // For std::out_of_range exception
#include <string>
#include "person.h"   // Assuming you have this header for the Person class

namespace ssuds {
    /// <summary>
    /// A dynamic array class that supports automatic resizing and various
    /// methods for manipulating the data.
    /// </summary>
    /// <typeparam name="T">Type of elements stored in the array</typeparam>
    template <typename T>
    class ArrayList {
    private:
        T* mData;  // Pointer to the array data
        unsigned int mSize;  // Current size of the array (number of elements)
        unsigned int mCapacity;  // Current capacity of the array

    public:
        /// <summary>
        /// Constructs an ArrayList with an initial capacity
        /// </summary>
        /// <param name="initialCapacity">Initial Capacity of the array (default is 10).</param>
        ArrayList(unsigned int initialCapacity = 10)
            : mSize(0), mCapacity(initialCapacity) {
            mData = new T[mCapacity];
        }

        /// <summary>
        /// Destroys the ArrayList, releasing the allocated memory.
        /// </summary>
        ~ArrayList() {
            delete[] mData;
        }
        /// <summary>
        /// Copy constructor for creating a new ArrayList as a copy of another.
        /// </summary>
        /// <param name="other">The ArrayList to copy</param>
        ArrayList(const ArrayList<T>& other)
            : mSize(other.mSize), mCapacity(other.mCapacity) {
            mData = new T[mCapacity];
            for (unsigned int i = 0; i < mSize; i++) {
                mData[i] = other.mData[i];
            }
        }

        /// <summary>
        /// Assignment operator for copying data from one ArrayList to another
        /// </summary>
        /// <param name="other">The ArrayList to copy</param>
        /// <returns>A reference to the current ArrayList.</returns>
        ArrayList<T>& operator=(const ArrayList<T>& other) {
            if (this != &other) {
                delete[] mData;
                mSize = other.mSize;
                mCapacity = other.mCapacity;
                mData = new T[mCapacity];
                for (unsigned int i = 0; i < mSize; i++) {
                    mData[i] = other.mData[i];
                }
            }
            return *this;
        }

        /// <summary>
        /// Gets the current # of elements in the ArrayList.
        /// </summary>
        /// <returns>The current size of the ArrayList.</returns>
        unsigned int size() const {
            return mSize;
        }
        
        /// <summary>
        ///Gets the current capacity of the ArrayList
        /// </summary>
        /// <returns>The current capacity of the ArrayList</returns>
        unsigned int capacity() const {
            return mCapacity;
        }

        /// <summary>
        /// Reserves space for a larger capacity if needed
        /// </summary>
        /// <param name="newCapacity">the new capacity for the ArrayList</param>
        void reserve(unsigned int newCapacity) {
            if (newCapacity > mCapacity) {
                resize(newCapacity);
            }
        }

        /// <summary>
        /// Resizes the ArrayList to the specified new capacity
        /// </summary>
        /// <param name="newCapacity">The new capacity for the ArrayList.</param>
        void resize(unsigned int newCapacity) {
            if (newCapacity == 0) {
                throw std::invalid_argument("New capacity must be greater than zero.");
            }

            T* newData = new T[newCapacity];
            for (unsigned int i = 0; i < mSize; i++) {
                newData[i] = mData[i];
            }
            delete[] mData;
            mData = newData;
            mCapacity = newCapacity;
        }

        /// <summary>
        /// Appends an item to the end of the ArrayList.
        /// </summary>
        /// <param name="item"the item to append></param>
        void append(const T& item) {
            if (mSize == mCapacity) {
                resize(mCapacity * 2);
            }
            mData[mSize++] = item;
        }
        /// <summary>
        /// Prepends an item to the beginning of the ArrayList.
        /// </summary>
        /// <param name="item">the item to prepend</param>
        void prepend(const T& item) {
            if (mSize == mCapacity) {
                resize(mCapacity * 2);
            }
            for (unsigned int i = mSize; i > 0; --i) {
                mData[i] = mData[i - 1];
            }
            mData[0] = item;
            mSize++;
        }

        /// <summary>
        /// Inserts an item at a specified index in the ArrayList.
        /// </summary>
        /// <param name="item">the item to insert</param>
        /// <param name="index">the index at which to insert the item.</param>
        void insert(const T& item, unsigned int index) {
            if (index > mSize) {
                throw std::out_of_range("Index out of range");
            }
            if (mSize == mCapacity) {
                resize(mCapacity * 2);
            }
            for (unsigned int i = mSize; i > index; --i) {
                mData[i] = mData[i - 1];
            }
            mData[index] = item;
            mSize++;
        }

        /// <summary>
        /// Gets the item at a specific index
        /// </summary>
        /// <param name="index">the index if the item to retrieve</param>
        /// <returns>the item at the specified index.</returns>
        T& at(unsigned int index) {
            if (index >= mSize) {
                throw std::out_of_range("Index out of range");
            }
            return mData[index];
        }
        /// <summary>
        /// Get the item at a specified index (const version)
        /// </summary>
        /// <param name="index">the index of the item to retrieve</param>
        /// <returns>the item at the specified index</returns>
        const T& at(unsigned int index) const {
            if (index >= mSize) {
                throw std::out_of_range("Index out of range");
            }
            return mData[index];
        }

        /// <summary>
        /// Removes the item at the specified index
        /// </summary>
        /// <param name="index">the index of the item to remove</param>
        /// <returns>the removed item</returns>
        T remove(unsigned int index) {
            if (index >= mSize) {
                throw std::out_of_range("Index out of range");
            }
            T removedItem = mData[index];
            for (unsigned int i = index; i < mSize - 1; i++) {
                mData[i] = mData[i + 1];
            }
            mSize--;
            if (mSize <= mCapacity / 4) {
                resize(mCapacity / 2);
            }
            return removedItem;
        }
        /// <summary>
        /// Removes all instances of a specific value from the ArrayList
        /// </summary>
        /// <param name="value">the value to remove</param>
        /// <returns>the number of items removed</returns>
        unsigned int remove_all(const T& value) {
            unsigned int count = 0;
            for (unsigned int i = 0; i < mSize;) {
                if (mData[i] == value) {
                    remove(i);
                    count++;
                }
                else {
                    ++i;
                }
            }
            return count;
        }

        /// <summary>
        /// finds the index of the first occurence of a value
        /// </summary>
        /// <param name="value">The value to search for</param>
        /// <param name="startIndex">The index from which to start searching (default is 0)</param>
        /// <returns>The index of the first occurence of the value, or -1 if not found.</returns>
        int find(const T& value, unsigned int startIndex = 0) const {
            for (unsigned int i = startIndex; i < mSize; i++) {
                if (mData[i] == value) {
                    return i;
                }
            }
            return -1;  // Not found
        }

        /// <summary>
        /// Outputs the ArrayList to a stream
        /// </summary>
        /// <param name="os">the outout stream</param>
        void output(std::ostream& os) const {
            os << "[";
            for (unsigned int i = 0; i < mSize; i++) {
                os << mData[i];
                if (i < mSize - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }

        /// <summary>
        /// Non-member output operator for ArrayList
        /// </summary>
        /// <param name="os">the output stream</param>
        /// <param name="list">the ArrayList to output</param>
        /// <returns>the output stream</returns>

        friend std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
            list.output(os);
            return os;
        }
    };

} // namespace ssuds

#endif
