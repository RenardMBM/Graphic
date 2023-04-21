#ifndef GRAPHIC_POINTER_H
#define GRAPHIC_POINTER_H

#include "./Vector.h"

template <typename T>
class Pointer: Vector<T>{
public:
    using floatType = typename Vector<T>::floatType;
    using Vector<T>::Vector;
    Pointer<T>(const Vector<T> &other){
        this->matrix = other.matrix;
        this->n = other.dim();
        this->m = 1;
    }

    template<typename T_other>
    bool operator==(const Pointer<T_other> &other){
        if (dimension() != other.dimension()) return false;
        for (size_t i = 0; i < dimension(); ++i){
            if (this->operator[](i) != other.operator[](i)) return false;
        }
        return true;
    }

    bool operator==(const Pointer<T> &other){
        if (dimension() != other.dimension()) return false;
        for (size_t i = 0; i < dimension(); ++i){
            if (this->operator[](i) != other.operator[](i)) return false;
        }
        return true;
    }
    Pointer<T> operator-()const{
        Pointer<T> tmp = *this;
        for (size_t i = 0; i < tmp.dim(); ++i){
            tmp[i] *= -1;
        }
        return tmp;
    }
    Pointer<T>& operator+=(const Vector<T> &other){
        if (this->dim() < other.dim()){
            throw VectorSizeError::lessThen( "Pointer", {this->dim(), 1},
                                             "Vector", {other.dim(), 1});
        }
        for (size_t i = 0; i < std::min(this->dim(), other.dim()); ++i){
            this->operator[](i) += other[i];
        }
        return *this;
    }
    Pointer<T>& operator-=(const Vector<T> &other){
        return *this+=(-other);
    }

    Pointer<T> operator+(const Vector<T> &other){
        Pointer<T> tmp = *this;
        tmp += other;
        return tmp;
    }
    Pointer<T> operator-(const Vector<T> &other){
        return *this + (-other);
    }

    size_t dimension() const{
        return this->dim();
    }
    using Vector<T>::operator[];
};


#endif //GRAPHIC_POINTER_H
