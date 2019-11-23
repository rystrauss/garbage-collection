#ifndef GCPOINTER_HPP
#define GCPOINTER_HPP

#include <vector>
#include <unordered_map>
#include "reference_counting.h"


std::unordered_map<void *, int> references;

/**
 * This class implements a smart pointer, which allows for automatic memory reclamation.
 *
 * This class can be wrapped around any standard pointer and keeps track of the number of
 * references to that pointer. If the number of references every reaches zero, the memory
 * is automatically deallocated.
 *
 * @tparam T the type of the data pointed to by this smart pointer
 * @author Ryan Strauss
 */
template<typename T>
class GCPointer {

private:
    T *data;

    /**
     * Increments the number of references to the data contained in this smart pointer.
     *
     * If the data is nullptr, nothing will happen.
     */
    inline void increment_references() const;

    /**
     * Decrements the number of references to the data contained in this smart pointer.
     *
     * If necessary, i.e. if the data has zero references after being decremented, this method
     * will also free the now unused data.
     *
     * If the data is nullptr, nothing will happen.
     */
    inline void decrement_references();

public:

    // Constructor
    explicit GCPointer(T *pointer = nullptr);

    // Copy Constructor
    GCPointer(const GCPointer &gcPointer);

    // Move Constructor
    GCPointer(GCPointer &&gcPointer) noexcept;

    // Destructor
    ~GCPointer();

    // Copy Assignment
    GCPointer<T> &operator=(const GCPointer<T> &gcPointer);

    GCPointer<T> &operator=(T *t);

    // Move Assignment
    GCPointer<T> &operator=(GCPointer<T> &&gcPointer) noexcept;

    GCPointer<T> operator+(int i) const;

    GCPointer<T> operator-(int i) const;

    GCPointer<T> &operator+=(int i);

    GCPointer<T> &operator-=(int i);

    GCPointer<T> &operator++();

    const GCPointer<T> operator++(int);

    GCPointer<T> &operator--();

    const GCPointer<T> operator--(int);

    T *operator->() const;

    T &operator*() const;

    /**
     * Retrieves the pointer contained in this smart pointer.
     *
     * @return the pointer that this GCPointer wraps around
     */
    T *pointer();

};

template<typename T>
GCPointer<T>::GCPointer(T *pointer) : data{pointer} {
    increment_references();
}

template<typename T>
GCPointer<T>::GCPointer(const GCPointer<T> &gcPointer) : data{gcPointer.data} {
    increment_references();
}

template<typename T>
GCPointer<T>::GCPointer(GCPointer &&gcPointer) noexcept {
    decrement_references();
    data = gcPointer.data;
    gcPointer.data = nullptr;
}

template<typename T>
GCPointer<T>::~GCPointer() {
    decrement_references();
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator=(const GCPointer<T> &gcPointer) {
    decrement_references();
    data = gcPointer.data;
    increment_references();
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator=(T *t) {
    decrement_references();
    data = t;
    increment_references();
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator=(GCPointer<T> &&gcPointer) noexcept {
    decrement_references();
    data = gcPointer.data;
    gcPointer.data = nullptr;
    return *this;
}

template<typename T>
GCPointer<T> GCPointer<T>::operator+(int i) const {
    return new GCPointer<T>{data + i};
}

template<typename T>
GCPointer<T> GCPointer<T>::operator-(int i) const {
    return new GCPointer<T>{data - i};
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator+=(int i) {
    decrement_references();
    data += i;
    increment_references();
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator-=(int i) {
    decrement_references();
    data -= i;
    increment_references();
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator++() {
    decrement_references();
    data++;
    increment_references();
    return *this;
}

template<typename T>
const GCPointer<T> GCPointer<T>::operator++(int) {
    GCPointer<T> unmodified{*this};
    data++;
    increment_references();
    return unmodified;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator--() {
    decrement_references();
    data--;
    increment_references();
    return *this;
}

template<typename T>
const GCPointer<T> GCPointer<T>::operator--(int) {
    GCPointer<T> unmodified{*this};
    data--;
    increment_references();
    return unmodified;
}

template<typename T>
T *GCPointer<T>::operator->() const {
    return data;
}

template<typename T>
T &GCPointer<T>::operator*() const {
    return *data;
}

template<typename T>
T *GCPointer<T>::pointer() {
    return data;
}

template<typename T>
inline void GCPointer<T>::increment_references() const {
    if (data != nullptr) {
        if (references.find(data) == references.end())
            references[data] = 0;

        references[data]++;
    }
}

template<typename T>
inline void GCPointer<T>::decrement_references() {
    if (data != nullptr && --references[data] == 0) {
        references.erase(data);
        delete data;
    }
}


#endif //GCPOINTER_HPP
