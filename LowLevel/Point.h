#ifndef GRAPHIC_POINT_H
#define GRAPHIC_POINT_H

#include "./Vector.h"

template <typename T>
class Point: Vector<T>{
public:
    using floatType = typename Vector<T>::floatType;
    using Vector<T>::Vector;

    Point<T>(const Vector<T> &other){
        this->matrix = other.matrix;
        this->n = other.size();
        this->m = 1;
    }

    template<typename T_other>
    bool operator==(const Point<T_other> &other){
        if (size() != other.sz()) return false;
        for (size_t i = 0; i < size(); ++i){
            if (this->operator[](i) != other.operator[](i)) return false;
        }
        return true;
    }

    Point<T>& operator+=(const Vector<T> &other){
        if (this->size() < other.size()){
            throw VectorSizeError::lessThen( "Point", {this->size(), 1},
                                             "Vector", {other.size(), 1});
        }
        for (size_t i = 0; i < std::min(this->size(), other.size()); ++i){
            this->operator[](i) += other[i];
        }
        return *this;
    }
    Point<T>& operator-=(const Vector<T> &other){
        return *this+=(-other);
    }

    Point<T> operator+(const Vector<T> &other){
        Point<T> tmp = *this;
        tmp += other;
        return tmp;
    }
    Point<T> operator-(const Vector<T> &other){
        return *this + (-other);
    }

    [[nodiscard]] size_t size() const{
        return this->_size();
    }
    using Vector<T>::operator[];
};


#endif //GRAPHIC_POINT_H
