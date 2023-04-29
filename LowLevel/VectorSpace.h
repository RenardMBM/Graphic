#ifndef GRAPHIC_VECTORSPACE_H
#define GRAPHIC_VECTORSPACE_H
#include "Vector.h"
#include "Point.h"

template <typename T>
class Point;

template<typename T>
class VectorSpace{
private:
    using floatType = long double;
    std::vector<Vector<T>> basis;
    Matrix<floatType> gram;
    std::pair<size_t, size_t> _dim;
    public:
    explicit VectorSpace(const std::vector<Vector<T>> &basis): basis(basis.begin(),basis.end()),
                                                      gram(Matrix<T>::gram(basis)),
                                                      _dim({(basis.size() ? basis[0].size() : 0),
                                                            basis.size()}){
        for (const Vector<T> &b: basis){
            if (b.size() != _dim.first){
                throw MatrixSizeError::not_rectangular("Basis",
                                                       _dim,
                                                       {b.size(), 1},
                                                       "NotRectangularBasis");
            }
        }
    };

    template<class T_other>
    bool operator==(const VectorSpace<T_other> &other){
        if (_dim != other._dim) return false;
        return (other.basis == this->basis);
    }
    bool operator==(const VectorSpace<T> &other){
        if (_dim != other._dim) return false;
        return (other.basis == this->basis);
    }

    floatType scalar_product(const Vector<T> &first, const Vector<T> &second){
        floatType tmp = (first * gram) % second;
        return tmp;
    };

    Vector<T> vector_product(const Vector<T> &first, const Vector<T> &second){
        if (_dim.first != 3 || _dim.second != 3 || first.size() != 3 || second.size() != 3){
            throw MatrixSizeError::not_matches({
                                                       {"Basis", {_dim,                {"3", "3"}}},
                                                       {"Vector", {{first.size(),  1}, {"3", 1}}},
                                                       {"Vector", {{second.size(), 1}, {"3", 1}}}
            }, "VectorProductOnly3D");
        }

        Vector<T> tmp1 = basis[1] ^ basis[2], tmp2 = basis[2] ^ basis[0], tmp3 = basis[0] ^ basis[1];
        return  tmp1 * (first[1] * second[2] - first[2] * second[1]) +
                tmp2 * (first[2] * second[0] - first[0] * second[2]) +
                tmp3 * (first[0] * second[1] - first[1] * second[0]);
    }

    Vector<T> as_vector(const Point<T> &pt){
        if (pt.sz() != _dim.second){
            throw MatrixSizeError::not_match("Point", {pt.sz(), 1},
                                             "VectorSpace(basis)", _dim,
                                             {"N", "1"}, {"M", "N"},
                                             "notMatchDimPointerAndVP");
            throw std::invalid_argument("VectorSpace and Point dimensions don't match");
        }
        Vector<T> tmp(_dim.first);
        tmp *= 0;
        for (size_t i = 0; i < _dim.second; ++i){
            tmp += basis[i] * pt.operator[](i);
        }
        return tmp;
    };

};
#endif //GRAPHIC_VECTORSPACE_H
