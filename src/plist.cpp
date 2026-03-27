#include "plist.h"
#include <stdexcept>

template <typename T>
class List {
    public:
        List(unsigned capacity = 16) {
            this->capacity = capacity;
            arr = new T[capacity]
        }

        unsigned len() const;
        void append(T val);
        T pop();
        T get(unsigned inx) const;
        void set(unsigned inx, T val);

    private:
        unsigned capacity = 16;
        unsigned size = 0;
        T *arr;

        void resize(unsigned factor = 2);
};

template <typename T>
List<T>::List(unsigned capacity = 16) {
    this->capacity = capacity;
    arr = new T[capacity];
}

template <typename T>
unsigned List<T>::len() const { return size; }

template <typename T>
void List<T>::append(T val) {
    if (size == capacity) resize();
    arr[size] = val;
    ++size;
}

template <typename T>
T List<T>::pop() {
    if (size == 0)
        throw std::runtime_error("err: popping from an empty list..");
    --size;
    return arr[size];
}

template <typename T>
T List<T>::get(unsigned inx) const {
    if (size <= inx)
        throw std::runtime_error("err: index out of range..");
    return arr[inx];
}

template <typename T>
void List<T>::set(unsigned inx, T val) {
    if (size <= inx)
        throw std::runtime_error("err: index out of range..");
    arr[inx] = val;
}

template <typename T>
void List<T>::resize(unsigned factor = 2) {
    capacity *= factor;
    T *new_arr = new T[capacity];
    for (unsigned inx = 0; inx < size; ++inx) new_arr[inx] = arr[inx];
    delete[] arr;
    arr = new_arr;
}
