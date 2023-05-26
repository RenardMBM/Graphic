#ifndef GRAPHIC_POINT_H
#define GRAPHIC_POINT_H

#include "./Vector.h"

template <typename T>
class Point: private Vector<T>{
public:
    using floatType = typename Vector<T>::floatType;

    // region constructs
    using Vector<T>::Vector;

    Point<T>(const Vector<T> &other){
        this->matrix = other.matrix;
        this->n = other.size();
        this->m = 1;
    }
    // endregion

    // region methods
    size_t size() const{
        return this->_size();
    }
    // endregion

    // region operators
    template<typename T_other>
    bool operator==(const Point<T_other> &other) const{
        if (size() != other.size()) return false;
        for (size_t i = 0; i < size(); ++i){
            if (this->operator[](i) != other.operator[](i)) return false;
        }
        return true;
    }

    Point<T>& operator+=(const Vector<T> &other){
        if (this->size() < other.size()){
            throw VectorSizeError::lessThen( "Point", this->size(),
                                             "Vector", other.size());
        }
        for (size_t i = 0; i < std::min(this->size(), other.size()); ++i){
            this->operator[](i) += other[i];
        }
        return *this;
    }
    Point<T>& operator-=(const Vector<T> &other){
        return *this+=(-other);
    }

    Point<T> operator+(const Vector<T> &other) const{
        Point<T> tmp = *this;
        tmp += other;
        return tmp;
    }
    Point<T> operator-(const Vector<T> &other) const{
        return *this + (-other);
    }

    using Vector<T>::operator[];
    // endregion
};


template<typename T>
std::ostream &operator<<(std::ostream &out, const Point<T> &pt) {
    for (size_t i = 0; i < pt.size(); ++i) {
        out << pt[i];
        if (i + 1 != pt.size()) out << ' ';
    }
    return out;
}
#endif //GRAPHIC_POINT_H
