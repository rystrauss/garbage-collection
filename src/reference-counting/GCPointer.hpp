#ifndef GCPOINTER_HPP
#define GCPOINTER_HPP

#include <cstdint>
#include <vector>


template<typename T>
class GCPointer {

private:
    T *data;
    uint32_t *references;

public:

    explicit GCPointer(T *pointer = nullptr);

    GCPointer(const GCPointer &gcPointer);

    ~GCPointer();

    GCPointer<T> &operator=(const GCPointer<T> &gcPointer);

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

    T *pointer();

};

template<typename T>
GCPointer<T>::GCPointer(T *pointer) : data{pointer}, references{new uint32_t(1)} {}

template<typename T>
GCPointer<T>::GCPointer(const GCPointer<T> &gcPointer) : data{gcPointer.data}, references{gcPointer.references} {
    references++;
}

template<typename T>
GCPointer<T>::~GCPointer() {
    if (--references == 0) {
        delete references;
        delete data;
    }
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator=(const GCPointer<T> &gcPointer) {
    ~this();
    data = gcPointer.data;
    references = gcPointer.references;
    return *this;
}

template<typename T>
GCPointer<T> GCPointer<T>::operator+(int i) const {
    return new GCPointer<T>(data + i);
}

template<typename T>
GCPointer<T> GCPointer<T>::operator-(int i) const {
    return new GCPointer<T>(data - i);
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator+=(int i) {
    data += i;
    ~this();
    references = new uint32_t{1};
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator-=(int i) {
    data -= i;
    ~this();
    references = new uint32_t{1};
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator++() {
    data++;
    ~this();
    references = new uint32_t{1};
    return *this;
}

template<typename T>
const GCPointer<T> GCPointer<T>::operator++(int) {
    GCPointer<T> unmodified{*this}; // TODO: Figure out how copy constructor needs to behave here
    data++;
    return unmodified;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator--() {
    data--;
    ~this();
    references = new uint32_t{1};
    return *this;
}

template<typename T>
const GCPointer<T> GCPointer<T>::operator--(int) {
    GCPointer<T> unmodified{*this};
    data--;
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

#endif //GCPOINTER_HPP
