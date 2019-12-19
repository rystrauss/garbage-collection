#ifndef GCPOINTER_HPP
#define GCPOINTER_HPP

#include "reference_counting.h"


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
    inline void increment_references() const {
        if (data != nullptr) {
            if (references.find(data) == references.end())
                references[data] = 0;

            references[data]++;
        }
    }

    /**
     * Decrements the number of references to the data contained in this smart pointer.
     *
     * If necessary, i.e. if the data has zero references after being decremented, this method
     * will also free the now unused data.
     *
     * If the data is nullptr, nothing will happen.
     */
    inline void decrement_references() {
        if (data != nullptr && --references[data] == 0) {
            references.erase(data);
            delete data;
        }
    }

public:

    // Constructor
    explicit GCPointer(T *pointer = nullptr) : data{pointer} {
        increment_references();
    }

    // Copy Constructor
    GCPointer(const GCPointer &gcPointer) : data{gcPointer.data} {
        increment_references();
    }

    // Move Constructor
    GCPointer(GCPointer &&gcPointer) noexcept {
        decrement_references();
        data = gcPointer.data;
        gcPointer.data = nullptr;
    }

    // Destructor
    ~GCPointer() {
        decrement_references();
    }

    // Copy Assignment
    GCPointer<T> &operator=(const GCPointer<T> &gcPointer) {
        if (this == &gcPointer)
            return *this;

        decrement_references();
        data = gcPointer.data;
        increment_references();
        return *this;
    }

    GCPointer<T> &operator=(T *t) {
        decrement_references();
        data = t;
        increment_references();
        return *this;
    }

    // Move Assignment
    GCPointer<T> &operator=(GCPointer<T> &&gcPointer) noexcept {
        decrement_references();
        data = gcPointer.data;
        gcPointer.data = nullptr;
        return *this;
    }

    GCPointer<T> operator+(int i) const {
        return new GCPointer<T>{data + i};
    }

    GCPointer<T> operator-(int i) const {
        return new GCPointer<T>{data - i};
    }

    GCPointer<T> &operator+=(int i) {
        decrement_references();
        data += i;
        increment_references();
        return *this;
    }

    GCPointer<T> &operator-=(int i) {
        decrement_references();
        data -= i;
        increment_references();
        return *this;
    }

    GCPointer<T> &operator++() {
        decrement_references();
        data++;
        increment_references();
        return *this;
    }

    const GCPointer<T> operator++(int) {
        GCPointer<T> unmodified{*this};
        data++;
        increment_references();
        return unmodified;
    }

    GCPointer<T> &operator--() {
        decrement_references();
        data--;
        increment_references();
        return *this;
    }

    const GCPointer<T> operator--(int) {
        GCPointer<T> unmodified{*this};
        data--;
        increment_references();
        return unmodified;
    }

    T *operator->() const {
        return data;
    }

    T &operator*() const {
        return *data;
    }

    /**
     * Retrieves the pointer contained in this smart pointer.
     *
     * @return the pointer that this GCPointer wraps around
     */
    T *pointer() {
        return data;
    }

};

#endif //GCPOINTER_HPP
