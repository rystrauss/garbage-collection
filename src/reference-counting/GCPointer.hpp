#ifndef GCPOINTER_HPP
#define GCPOINTER_HPP

#include <cstdint>


template<typename T>
class GCPointer {

private:
    T *data;
    uint32_t references;

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
GCPointer<T>::GCPointer(T *pointer) : data{pointer}, references{1} {}

template<typename T>
GCPointer<T>::GCPointer(const GCPointer<T> &gcPointer) : data{new T(gcPointer.data)}, references{1} {}

template<typename T>
GCPointer<T>::~GCPointer() {
    delete data;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator=(const GCPointer<T> &gcPointer) {
    delete data;
    data = gcPointer.data;
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
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator-=(int i) {
    data -= i;
    return *this;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator++() {
    data++;
    return *this;
}

template<typename T>
const GCPointer<T> GCPointer<T>::operator++(int) {
    GCPointer<T> unmodified{*this};
    data++;
    return unmodified;
}

template<typename T>
GCPointer<T> &GCPointer<T>::operator--() {
    data--;
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
