#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include <cstring>

namespace ssuds
{
    /// <summary>
    /// A dynamic array implementation for storing alements of type T.
    /// </summary>
    /// <typeparam name="T">The type of elements stored in the array.</typeparam>
    template <class T>
    class ArrayList
    {
    protected:
        static const int msMinCapacity = 5;///The minimum initial capacity of the list.
        unsigned int mCapacity;///the current capacity of the list.
        unsigned int mSize;///the current number of items in the list.
        unsigned char* mData;///a pointer to the raw memory where elements are stored.

    public:
        ArrayList() : mSize(0), mCapacity(msMinCapacity), mData(nullptr) {
            mData = new unsigned char[mCapacity * sizeof(T)];
        }

        ~ArrayList()
        {
            delete[] mData;
        }
        /// <summary>
        /// Appends an element to the end of the list
        /// </summary>
        /// <param name="val">the element to append to the list</param>
        void append(const T& val)
        {
            grow();
            memcpy(&mData[mSize * sizeof(T)], &val, sizeof(T));
            mSize++;
        }
        /// <summary>
        /// Accesses the element at the given index
        /// </summary>
        /// <param name="index"></param>
        /// <returns>A reference to the element at the specifed index</returns>
        T& at(const unsigned int index) const
        {
            if (index >= mSize)
                throw std::out_of_range("Invalid index");
            return *(reinterpret_cast<T*>(&mData[index * sizeof(T)]));
        }
        /// <summary>
        /// Gets the current capacity of the list.
        /// </summary>
        /// <returns></returns>
        unsigned int capacity() const { return mCapacity; }  // Capacity function
        /// <summary>
        /// clears the list by deleting the underlying ddata and resetting size and capacity.
        /// </summary>
        void clear()
        {
            delete[] mData;
            mData = nullptr;
            mSize = 0;
            mCapacity = 0;
        }
        /// <summary>
        /// Inserts and element at the specified index; if the list is full, 
        /// the capacity is increased.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="index"></param>
        void insert(const T& val, unsigned int index)
        {
            if (index > mSize)  // Prevent invalid insert positions
                throw std::out_of_range("Invalid index");
            grow();
            memcpy(&mData[(index + 1) * sizeof(T)], &mData[index * sizeof(T)], (mSize - index) * sizeof(T));
            memcpy(&mData[index * sizeof(T)], &val, sizeof(T));
            mSize++;
        }
        /// <summary>
        /// Finds the first occurence of the specified element.
        /// starts from the specified index.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="start_index"></param>
        /// <returns></returns>
        int find(const T& val, unsigned int start_index = 0)
        {
            if (start_index >= mSize)
                return -1;  // If starting index is out of bounds, return -1

            for (unsigned int i = start_index; i < mSize; ++i)
            {
                T& item = at(i);
                if (item == val)  // If the item at index i matches 'val'
                    return i;
            }
            return -1;  // Return -1 if 'val' is not found
        }

        /// <summary>
        /// Reserves a minimum capacity for the list
        /// </summary>
        /// <param name="desired_capacity"></param>
        void reserve(unsigned int desired_capacity)
        {
            if (desired_capacity > mCapacity)
            {
                unsigned char* temp_array = new unsigned char[desired_capacity * sizeof(T)];
                memset(temp_array, 0, sizeof(T) * desired_capacity);
                memcpy(temp_array, mData, mSize * sizeof(T));
                delete[] mData;
                mData = temp_array;
                mCapacity = desired_capacity;
            }
        }
        /// <summary>
        /// the current # of elements in the list
        /// </summary>
        /// <returns></returns>
        unsigned int size() const { return mSize; }
        /// <summary>
        /// an iterator class for traversing the elements in the ArrayList
        /// </summary>
        class ArrayListIterator
        {
        private:
            ArrayList<T>* mArrayList;///Pointer to the ArrayList being iterated.
            unsigned int mIndex;///The current index in the iteration.

        public:
            ArrayListIterator(ArrayList<T>* arrayList, unsigned int index)
                : mArrayList(arrayList), mIndex(index) {
            }

            T& operator*() const
            {
                return *(reinterpret_cast<T*>(&mArrayList->mData[mIndex * sizeof(T)]));
            }

            T* operator->() const
            {
                return &(operator*());
            }

            ArrayListIterator& operator++()
            {
                mIndex++;
                return *this;
            }

            ArrayListIterator operator++(int)
            {
                ArrayListIterator temp = *this;
                ++(*this);
                return temp;
            }

            ArrayListIterator& operator--()
            {
                mIndex--;
                return *this;
            }

            ArrayListIterator operator--(int)
            {
                ArrayListIterator temp = *this;
                --(*this);
                return temp;
            }

            ArrayListIterator operator+(int n) const
            {
                ArrayListIterator temp = *this;
                temp.mIndex += n;
                return temp;
            }

            bool operator==(const ArrayListIterator& other) const
            {
                return mArrayList == other.mArrayList && mIndex == other.mIndex;
            }

            bool operator!=(const ArrayListIterator& other) const
            {
                return !(*this == other);
            }
        };
        /// <summary>
        /// returns an iterator pointing to the first element of the list
        /// </summary>
        /// <returns></returns>
        ArrayListIterator begin()
        {
            return ArrayListIterator(this, 0);
        }
        /// <summary>
        /// returns an  iterator pointing to the element after the last element
        /// </summary>
        /// <returns></returns>
        ArrayListIterator end()
        {
            return ArrayListIterator(this, mSize);
        }
        /// <summary>
        /// removes all occurences of the specifed element
        /// </summary>
        /// <param name="val"></param>
        /// <returns></returns>
        unsigned int remove_all(const T& val)
        {
            unsigned int count = 0;
            unsigned int i = 0;

            // Traverse the list to find occurrences of 'val'
            while (i < mSize)
            {
                if (at(i) == val)
                {
                    // Shift elements left to remove the current element
                    for (unsigned int j = i; j < mSize - 1; ++j)
                    {
                        memcpy(&mData[j * sizeof(T)], &mData[(j + 1) * sizeof(T)], sizeof(T));
                    }
                    mSize--;
                    count++;
                }
                else
                {
                    ++i;
                }
            }

            // Optionally, shrink the capacity if needed
            if (mSize < mCapacity / 4)
            {
                shrink();
            }

            return count;  // Return the number of removed elements
        }

        /// <summary>
        /// Shrinks the capacity of the list to fit its size
        /// </summary>

        void shrink()
        {
            // If the size is much smaller than the capacity, reduce the capacity
            if (mCapacity > msMinCapacity && mSize < mCapacity / 4)
            {
                unsigned char* new_array = new unsigned char[mSize * sizeof(T)];
                memcpy(new_array, mData, mSize * sizeof(T));
                delete[] mData;
                mData = new_array;
                mCapacity = mSize;
            }
        }

    protected:
        /// <summary>
        /// Grows the capacity of the list if its full; the capacity is doubled if its full.
        /// </summary>
        void grow()
        {
            if (mSize == mCapacity)
            {
                unsigned char* new_array = nullptr;
                if (mCapacity == 0)
                {
                    new_array = new unsigned char[msMinCapacity * sizeof(T)];
                    memset(new_array, 0, msMinCapacity * sizeof(T));
                }
                else
                {
                    new_array = new unsigned char[(mCapacity * 2) * sizeof(T)];
                    memset(new_array, 0, (mCapacity * 2) * sizeof(T));
                }

                if (mData != nullptr)
                {
                    memcpy(new_array, mData, sizeof(T) * mSize);
                    delete[] mData;
                }

                mData = new_array;
                mCapacity = (mCapacity == 0) ? msMinCapacity : mCapacity * 2;
            }
        }
        

    };
}
