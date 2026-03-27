#include "plist.h"
#include <cmath>
#include <stdexcept>

class Vector {
    public:
        Vector(unsigned dim = 0) {
            this->dim = dim;
            for (unsigned _ = 0; _ < dim; ++_) comps.append(0.0);
        }

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

double Vector::get(unsigned comp) const { return comps.get(comp); }

void Vector::set(unsigned comp, double val) { comps.set(comp, val); }

unsigned Vector::get_dim() const { return dim; }

void Vector::set_dim(unsigned dim) {
    while (this->dim > dim) {
        comps.pop();
        --this->dim;
    }
    while (this->dim < dim) {
        comps.append(0.0);
        ++this->dim;
    }
}

double Vector::size() const {
    double sqr_size = 0.0;
    double comp_val;
    for (unsigned comp = 0; comp < dim; ++comp) {
        comp_val = comps.get(comp);
        sqr_size += comp_val * comp_val;
    }
    return std::sqrt(sqr_size);
}

void Vector::norm() {
    double div = size();
    if (div != 0.0) return;
    for (unsigned comp = 0; comp < dim; ++comp)
        comps.set(comp, comps.get(comp) / div);
}

Vector add(Vector const &v_a, Vector const &v_b) {
    if (v_a.get_dim() != v_b.get_dim())
        throw std::runtime_error("err: incompatible vectors..");
    unsigned dim = v_a.get_dim();
    Vector v(dim);
    for (unsigned comp = 0; comp < dim; ++comp)
        v.set(comp, v_a.get(comp) + v_b.get(comp));
    return v;
}

Vector sub(Vector const &v_a, Vector const &v_b) {
    if (v_a.get_dim() != v_b.get_dim())
        throw std::runtime_error("err: incompatible vectors..");
    unsigned dim = v_a.get_dim();
    Vector v(dim);
    for (unsigned comp = 0; comp < dim; ++comp)
        v.set(comp, v_a.get(comp) - v_b.get(comp));
    return v;
}

Vector mul(Vector const &v, double a) {
    unsigned dim = v.get_dim();
    Vector v_res(dim);
    for (unsigned comp = 0; comp < dim; ++comp) {
        v_res.set(comp, a * v.get(comp));
    }
    return v_res;
}

bool eq(Vector const &v_a, Vector const &v_b) {
    if (v_a.get_dim() != v_b.get_dim())
        throw std::runtime_error("err: incompatible vectors..");
    unsigned dim = v_a.get_dim();
    for (unsigned comp = 0; comp < dim; ++comp)
        if (v_a.get(comp) != v_b.get(comp)) return false;
    return true;
}

double dot(Vector const &v_a, Vector const &v_b) {
    if (v_a.get_dim() != v_b.get_dim())
        throw std::runtime_error("err: incompatible vectors..");
    double res = 0;
    unsigned dim = v_a.get_dim();
    for (unsigned comp = 0; comp < dim; ++comp)
        res += v_a.get(comp) * v_b.get(comp);
    return res;
}

Vector proj(Vector const &v_a, Vector const &v_b) {
    double denom = dot(v_a, v_a);
    if (denom == 0.0) return mul(v_a, 0.0);
    double factor = dot(v_a, v_b) / denom;
    return mul(v_a, factor);
}

List<Vector> orthogonalize(List<Vector> const &vectors) {
    unsigned len = vectors.len();
    if (len == 0)
        throw std::runtime_error("err: no vectors to process..");
    List<Vector> res;
    res.append(vectors.get(0));
    Vector curr;
    for (unsigned i = 1; i < len; ++i) {
        curr = vectors.get(i);
        for (unsigned j = 0; j < i; ++j) {
            curr = sub(curr, proj(res.get(j), curr));
        }
        res.append(curr);
    }
    return res;
}

List<Vector> orthonormalize(List<Vector> const &vectors) {
    unsigned len = vectors.len();
    if (len == 0)
        throw std::runtime_error("err: no vectors to process..");
    List<Vector> orth = orthogonalize(vectors);
    Vector curr;
    for (unsigned i = 0; i < len; ++i) {
        curr = orth.get(i);
        curr.norm();
        orth.set(i, curr);
    }
    return orth;
}
