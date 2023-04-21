#ifndef GRAPHIC_VECTOR_H
#define GRAPHIC_VECTOR_H
#include "./Matrix.h"
#include "../Exceptions/VectorError.h"


template <typename T>
class Vector: protected Matrix<T>{
public:
    using floatType = typename Matrix<T>::floatType;
//    using Matrix<T>::Matrix;
    explicit Vector(const size_t &n): Matrix<T>(n, 1) {};
//    Vector(const size_t &n, T val): Matrix<T>(n, 1, val) {};
    explicit Vector(const std::vector<std::vector<T>> &vec): Matrix<T>(vec){};
    explicit Vector(const std::vector<T> &vec): Matrix<T>(vec.size(), 1){
        for (size_t i = 0; i < vec.size(); ++i){this->matrix[i][0] = vec[i];}
    };

    [[nodiscard]] size_t dim() const {
        return this->n;
    }

    T& operator[](size_t i){
        if (i >= this->dim())
            throw MatrixIndexError::index_out("Vector", {dim(), 1}, {i, "0"});
        return this->matrix[i][0];
    }
    T operator[](size_t i) const{
        if (i >= this->dim())
            throw MatrixIndexError::index_out("Matrix", {dim(), 1}, {i, "0"});
        return this->matrix[i][0];
    }


    floatType length(){
        floatType tmp = 0;

        for (size_t i = 0; i < dim(); ++i){
            tmp += this->operator[](i) * this->operator[](i);
        }
        return sqrt(tmp);
    }

    template<typename T_other>
    bool operator==(const Vector<T_other> &other){
        if (this->dim() != other.dim()) return false;
        for (size_t i = 0; i < dim(); ++i){
            if (this->operator[](i) != other[i]) return false;
        }
        return true;
    }
    bool operator==(const Vector<T> &other){
        if (this->dim() != other.dim()) return false;
        for (size_t i = 0; i < dim(); ++i){
            if (this->operator[](i) != other[i]) return false;
        }
        return true;
    }

    template<typename T_other>
    Vector<T> &operator*=(const T_other &other){
        for (size_t i = 0; i < this->dim(); ++i){
            this->operator[](i) *= other;
        }
        return *this;
    }
    template<typename T_other>
    Vector<T> &operator/=(const T_other &other){
        if (other == 0){
            throw ArithmeticException::divByZero("Vector");
        }
        for (size_t i = 0; i < this->dim(); ++i){
            this->operator[](i) /= other;
        }
        return *this;
    }

    Vector<T> operator-() const{
        Vector<T> tmp = *this;
        tmp *= -1;
        return tmp;
    }
    Vector<T> &operator+=(const Vector& other){
        if (this->dim() > other.dim()){
            throw VectorSizeError::lessThen("Vector", {this->dim(), 1},
                                            "Vector", {other.dim(), 1});
        }

        for (size_t i = 0; i < std::min(this->dim(), other.dim()); ++i){
            this->operator[](i) += other[i];
        }
        return *this;
    }
    Vector<T> &operator-=(const Vector& other){
        return *this+=(-other);
    }

    floatType operator%(const Vector& other){ // scalar product
        if (this->dim() != other.dim()){
            throw VectorSizeError::not_match("Vector", {this->dim(), 1},
                                             "Vector", {other.dim(), 1});
        }
        floatType tmp = 0;
        for (size_t i = 0; i < this->dim(); ++i){
            tmp += this->operator[](i) * other[i];
        }
        return tmp;
    }
    Vector<T> operator^(const Vector<T>& other){ // vector product
        if (this->dim() != 3 || other.dim() != 3){
            throw VectorSizeError::not_match("Vector", this->dim(),
                                             "Vector", other.dim(),
                                             {"3", "1"}, {"3", "1"}, "SizeError");
        }
        Vector<T> tmp(3);

        tmp[0] = this->operator[](1) * other[2] - this->operator[](2) * other[1];
        tmp[1] = this->operator[](2) * other[0] - this->operator[](0) * other[2];
        tmp[2] = this->operator[](0) * other[1] - this->operator[](1) * other[0];
        return tmp;
    }

    Vector<floatType> normalize(){
        Vector<floatType> tmp(this->dim());
        floatType sz = this->length();
        for (size_t i = 0; sz != 0 && i < this->dim(); ++i){
            tmp[i] = this->operator[](i) / sz;
        }
        return tmp;
    }
};


template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &vec) {
    for (size_t i = 0; i < vec.dim(); ++i) {
        out << vec[i];
        if (i + 1 != vec.dim()) out << '\n';
    }
    return out;
}


template<typename T1, typename T2>
Vector<T2> operator*(const T1& first, const Vector<T2>& second){
    Vector<T1> tmp = second;
    tmp *= first;
    return tmp;
}

template<typename T1, typename T2>
Vector<T1> operator*(const Vector<T1>& first, const T2& second){
    Vector<T1> tmp = first;
    tmp *= second;
    return tmp;
}

template<typename T1, typename T2>
Vector<T2> operator/(const T1& first, const Vector<T2>& second){
    Vector<T1> tmp = second;
    tmp /= first;
    return tmp;
}

template<typename T1, typename T2>
Vector<T1> operator/(const Vector<T1>& first, const T2& second){
    Vector<T1> tmp = first;
    tmp /= second;
    return tmp;
}

template<typename T1, typename T2>
Vector<T1> operator*(const Vector<T1>& vec, const Matrix<T2>& mat){
    if (vec.dim() != mat.dim().first){
        throw MatrixSizeError::product("Vector", {1, vec.dim()},
                                       "Matrix", mat.dim());
    }
    Vector<T1> tmp(mat.dim().second);

    for (size_t i = 0; i < mat.dim().second; ++i) {
        tmp[i] = 0;
        for (size_t j = 0; j < vec.dim(); ++j) {
            tmp[i] += vec[j] * mat[j][i];
        }
    }

    return tmp;
}

template<typename T1, typename T2>
Vector<T1> operator*(const Matrix<T2>& mat, const Vector<T1>& vec){
    if (vec.dim() != mat.dim().second){
        MatrixSizeError::product("Matrix", mat.dim(),
                                 "Vector", {vec.dim(), 1});
    }
    Vector<T1> tmp(mat.dim().first);
    for (size_t i = 0; i < mat.dim().first; ++i) {
        tmp[i] = 0;
        for (size_t j = 0; j < vec.dim(); ++j) {
            tmp[i] += vec[j] * mat[i][j];
        }
    }
    return tmp;
}



template<typename T>
T BilinearForm(Matrix<T> mat, Vector<T> vec1, Vector<T> vec2){
    if (mat.dim() != std::make_pair(vec1.dim(), vec2.dim()) || vec1.dim() != vec2.dim()){
        throw MatrixSizeError::not_matches({
                                                 {"Vector", {{1, vec1.dim()}, {"1", "N"}}},
                                                 {"Matrix", {mat.dim(), {"1", "N"}}},
                                                 {"Vector", {{vec2.dim(), 1}, {"N", "1"}}}
        }, "BilinearFormSizeError");
    }
    T tmp = 0;
    for (size_t i = 0; i < vec1.dim(); ++i){
        for (size_t j = 0; j < vec1.dim(); ++j){
            tmp += mat[i][j] * vec1[i] * vec2[j];
        }
    }
    return tmp;
}


#endif //GRAPHIC_VECTOR_H
