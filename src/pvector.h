#ifndef PVECTOR_H
#define PVECTOR_H

#include "plist.h"

class Vector {
    public:
        Vector(unsigned dim = 0);

        double get(unsigned comp) const;
        void set(unsigned comp, double val);
        unsigned get_dim() const;
        void set_dim(unsigned dim);
        double size() const;
        void norm();

    private:
        unsigned dim;
        List<double> comps;

    friend Vector add(Vector const &v_a, Vector const &v_b);
    friend Vector sub(Vector const &v_a, Vector const &v_b);
    friend Vector mul(Vector const &v, double a);
    friend bool eq(Vector const &v_a, Vector const &v_b);
    friend double dot(Vector const &v_a, Vector const &v_b);
};

Vector add(Vector const &v_a, Vector const &v_b);
Vector sub(Vector const &v_a, Vector const &v_b);
Vector mul(Vector const &v, double a);
bool eq(Vector const &v_a, Vector const &v_b);
double dot(Vector const &v_a, Vector const &v_b);
Vector proj(Vector const &v_a, Vector const &v_b);
List<Vector> orthogonalize(List<Vector> const &vectors);
List<Vector> orthonormalize(List<Vector> const &vectors);

#endif