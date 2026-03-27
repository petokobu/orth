#include "pvector.h"
#include <iostream>

void setup(Vector *v, double *vals, unsigned size) {
    for (unsigned i = 0; i < size; ++i)
        v->set(i, vals[i]);
}

void print(Vector v) {
    unsigned dim = v.get_dim();
    std::cout << "Vector values: (";
    for (int i = 0; i < dim - 1; ++i)
        std::cout << v.get(i) << ", ";
    std::cout << v.get(dim - 1);
    std::cout << ")\n";
}

void print(List<Vector> vectors) {
    unsigned len = vectors.len();
    for (unsigned i = 0; i < len; ++i)
        print(vectors.get(i));
}

Vector init(unsigned dim) {
    Vector v(dim);
    double val;
    std::cout << "Vector definition..\n";
    for (unsigned i = 0; i < dim; ++i) {
        std::cout << "Enter a value: ";
        std::cin >> val;
        v.set(i, val);
    }
    return v;
}

int main() {
    List<Vector> vectors;
    unsigned dim;
    unsigned count;

    std::cout << "Enter dimension: ";
    std::cin >> dim;

    std::cout << "Enter vector count: ";
    std::cin >> count;

    for (unsigned i = 0; i < count; ++i) vectors.append(init(dim));

    unsigned action;
    std::cout << "[0]Orthogonalize/[1]Orthonormalize: ";
    std::cin >> action;

    if (action > 1) {
        std::cout << "invalid argument..\n";
        return 0;
    }

    List<Vector> orth = (action == 0)
                        ? orthogonalize(vectors) : orthonormalize(vectors);
    print(orth);

    return 0;
}