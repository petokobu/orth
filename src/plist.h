#ifndef PLIST_H
#define PLIST_H

template <typename T>
class List {
    public:
        List(unsigned capacity = 16);

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

#include "plist.tpp"

#endif