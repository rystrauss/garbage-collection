#include <iostream>
#include <reference_counting.h>

using std::cout;
using std::endl;

template<class T>
class DataHolder {
private:
    T data;

public:
    // Constructor
    explicit DataHolder(T initialValue) {
        data = initialValue;
    }

    // Destructor
    ~DataHolder() = default;

    void set(T data) {
        this->data = data;
    }

    T get() {
        return data;
    }
};

int main() {
    GCPointer<DataHolder<int>> d{new DataHolder<int>(4)};
    cout << d.pointer() << endl;
    ++d;
    cout << d.pointer() << endl;

    return 0;
}