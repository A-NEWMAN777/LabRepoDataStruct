#include "array_list.h"

namespace ssuds {

    template <typename T>
    ArrayList<T>::ArrayList(unsigned int initialCapacity)
        : mSize(0), mCapacity(initialCapacity) {
        mData = new T[mCapacity];
    }

    template <typename T>
    ArrayList<T>::~ArrayList() {
        delete[] mData;
    }

    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList<T>& other)
        : mSize(other.mSize), mCapacity(other.mCapacity) {
        mData = new T[mCapacity];
        for (unsigned int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }
    }

    template <typename T>
    ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
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

    template <typename T>
    unsigned int ArrayList<T>::size() const {
        return mSize;
    }

    template <typename T>
    unsigned int ArrayList<T>::capacity() const {
        return mCapacity;
    }

    template <typename T>
    void ArrayList<T>::reserve(unsigned int newCapacity) {
        if (newCapacity > mCapacity) {
            resize(newCapacity);
        }
    }

    template <typename T>
    void ArrayList<T>::resize(unsigned int newCapacity) {
        T* newData = new T[newCapacity];
        for (unsigned int i = 0; i < mSize; i++) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mCapacity = newCapacity;
    }

    template <typename T>
    void ArrayList<T>::append(const T& item) {
        if (mSize == mCapacity) {
            resize(mCapacity * 2);
        }
        mData[mSize++] = item;
    }

    template <typename T>
    void ArrayList<T>::prepend(const T& item) {
        if (mSize == mCapacity) {
            resize(mCapacity * 2);
        }
        for (unsigned int i = mSize; i > 0; --i) {
            mData[i] = mData[i - 1];
        }
        mData[0] = item;
        mSize++;
    }

    template <typename T>
    void ArrayList<T>::insert(const T& item, unsigned int index) {
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

    template <typename T>
    T& ArrayList<T>::at(unsigned int index) {
        if (index >= mSize) {
            throw std::out_of_range("Index out of range");
        }
        return mData[index];
    }

    template <typename T>
    const T& ArrayList<T>::at(unsigned int index) const {
        if (index >= mSize) {
            throw std::out_of_range("Index out of range");
        }
        return mData[index];
    }

    template <typename T>
    T ArrayList<T>::remove(unsigned int index) {
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

    template <typename T>
    unsigned int ArrayList<T>::remove_all(const T& value) {
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

    template <typename T>
    int ArrayList<T>::find(const T& value, unsigned int startIndex) const {
        for (unsigned int i = startIndex; i < mSize; i++) {
            if (mData[i] == value) {
                return i;
            }
        }
        return -1;  // Not found
    }

    template <typename T>
    void ArrayList<T>::output(std::ostream& os) const {
        os << "[";
        for (unsigned int i = 0; i < mSize; i++) {
            os << mData[i];
            if (i < mSize - 1) {
                os << ", ";
            }
        }
        os << "]";
    }

    // Non-member output operator
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
        list.output(os);
        return os;
    }

} // namespace ssuds

