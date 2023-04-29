#ifndef GRAPHIC_VECTOR_H
#define GRAPHIC_VECTOR_H
#include "./Matrix.h"
#include "../Exceptions/VectorError.h"


template <typename T>
class Vector: protected Matrix<T>{
private:
    template<typename T_other>
    T _productRowColumn(const Vector<T_other> &other){
        T tmp = 0;
        for (size_t i = 0; i < this->size(); ++i){
            tmp += this->operator[](i) * static_cast<T>(other.operator[](i));
        }
        return tmp;
    }

    template<typename T_other>
    Matrix<T> _productColumnRow(const Vector<T_other> &other){
        Matrix<T> tmp(this->size(), other.size());
        for (size_t i = 0; i < this->size(); ++i){
            for (size_t j = 0; j < this->size(); ++j){
                tmp[i][j] = this->operator[](i) * static_cast<T>(other.operator[](i));
            }
        }
    }
protected:
    size_t _size() const{
        return this->n;
    }
public:
    bool isTransposed;
    using floatType = typename Matrix<T>::floatType;

    explicit Vector(const size_t &n): Matrix<T>(n, 1), isTransposed(false) {};
    explicit Vector(const size_t &n, const T &value): Matrix<T>(n, 1, value), isTransposed(false) {};
    explicit Vector(const std::vector<std::vector<T>> &vec): Matrix<T>(vec), isTransposed(false) {};
    explicit Vector(const std::vector<T> &vec): Matrix<T>(vec.size(), 1), isTransposed(true) {
        for (size_t i = 0; i < vec.size(); ++i){this->matrix[i][0] = vec[i];}
    };

    [[nodiscard]] size_t size() const {
        return this->n;
    }

    T& operator[](size_t i){
        if (i >= this->size())
            throw MatrixIndexError::index_out("Vector", {size(), 1}, {i, "0"});
        return this->matrix[i][0];
    }
    T operator[](size_t i) const{
        if (i >= this->size())
            throw MatrixIndexError::index_out("Matrix", {size(), 1}, {i, "0"});
        return this->matrix[i][0];
    }

    floatType length(){
        return sqrt(this->operator%(*this));
    }

    template<typename T_other>
    bool operator==(const Vector<T_other> &other){
        if (this->size() != other.size()) return false;
        for (size_t i = 0; i < size(); ++i){
            if (this->operator[](i) != other[i]) return false;
        }
        return true;
    }
    bool operator==(const Vector<T> &other){
        if (this->size() != other.size()) return false;
        for (size_t i = 0; i < size(); ++i){
            if (this->operator[](i) != other[i]) return false;
        }
        return true;
    }

    template<typename T_other>
    Vector<T> &operator*=(const T_other &other){
        for (size_t i = 0; i < this->size(); ++i){
            this->operator[](i) *= other;
        }
        return *this;
    }
    template<typename T_other>
    Vector<T> &operator/=(const T_other &other){
        if (other == 0){
            throw ArithmeticException::divByZero("Vector");
        }
        for (size_t i = 0; i < this->size(); ++i){
            this->operator[](i) /= other;
        }
        return *this;
    }


    template<typename T_other>
    Vector<T_other> operator*(const T_other& second){
        Vector<T_other> tmp = *this;
        tmp *= second;
        return tmp;
    }


    template<typename T_other>
    Matrix<T> operator*(const Vector<T_other> &second){
        if (this->isTransposed || !second.isTransposed) throw MatrixError("column * row");
        _productColumnRow();
    }

    template<typename T_other>
    T operator*(const Vector<T_other> &second){
        if (!this->isTransposed || second.isTransposed) throw MatrixError("");
        _productRowColumn();
    }

    Vector<T> operator-() const{
        Vector<T> tmp = *this;
        tmp *= -1;
        return tmp;
    }

    Vector<T> &operator+=(const Vector& other){
        if (this->size() > other.size()){
            throw VectorSizeError::lessThen("Vector", this->size(),
                                            "Vector", other.size());
        }

        for (size_t i = 0; i < std::min(this->size(), other.size()); ++i){
            this->operator[](i) += other[i];
        }
        return *this;
    }
    Vector<T> &operator-=(const Vector& other){
        return *this+=(-other);
    }

    floatType operator%(const Vector& other){ // scalar product
        if (this->size() != other.size()){
            throw VectorSizeError::not_match(
                    "Vector",
                    this->size(),
                    "Vector",
                    other.size(),
                    this->isTransposed,
                    other.isTransposed,
                    "N", "N",
                    "ScalarProductSizeError");
        }
        floatType tmp = 0;
        for (size_t i = 0; i < this->size(); ++i){
            tmp += this->operator[](i) * other[i];
        }
        return tmp;
    }
    Vector<T> operator^(const Vector<T>& other){ // vector product
        if (this->size() != 3 || other.size() != 3){
            throw VectorSizeError::not_match("Vector", this->size(),
                                             "Vector", other.size(),
                                             false,false,
                                             "3",
                                             "3",
                                             "VectorProductSizeError");
        }
        Vector<T> tmp(3);

        tmp[0] = this->operator[](1) * other[2] - this->operator[](2) * other[1];
        tmp[1] = this->operator[](2) * other[0] - this->operator[](0) * other[2];
        tmp[2] = this->operator[](0) * other[1] - this->operator[](1) * other[0];
        return tmp;
    }

    Vector<floatType> normalize(){
        Vector<floatType> tmp(this->size());
        floatType sz = this->length();
        for (size_t i = 0; sz != 0 && i < this->size(); ++i){
            tmp[i] = this->operator[](i) / sz;
        }
        return tmp;
    }
};


template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 != vec.size()) out << '\n';
    }
    return out;
}


//template<typename T1, typename T2>
//Vector<T2> operator*(const T1& first, const Vector<T2>& second){
//    Vector<T1> tmp = second;
//    tmp *= first;
//    return tmp;
//}


template<typename T1, typename T2>
Vector<T2> operator/(const T1& first, const Vector<T2>& second){
    Vector<T1> tmp(second.size(), first);
    for (size_t i = 0; i < second.size(); ++i){
        tmp[i] /= second[i];
    }
    return tmp;
}



template<typename T1, typename T2>
Vector<T1> operator*(const Vector<T1>& vec, const Matrix<T2>& mat){
    if ((!vec.isTransposed && vec.size() != mat.size().first) ||
        (vec.isTransposed && vec.size() != (mat.size().second || mat.size().first != 1))){
        throw MatrixSizeError::product("Vector", {1, vec.size()},
                                       "Matrix", mat.size());
    }
    Vector<T1> tmp(mat.size().second);
    tmp.isTransposed = vec.isTransposed;
    for (size_t i = 0; i < mat.size().second; ++i) {
        tmp[i] = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            tmp[i] += vec[j] * mat[j][i];
        }
    }

    return tmp;
}

template<typename T1, typename T2>
Vector<T1> operator*(const Matrix<T2>& mat, const Vector<T1>& vec){
    if ((!vec.isTransposed && vec.size() != mat.size().second) ||
    (vec.isTransposed && (vec.size() != mat.size().first || mat.size().second != 1))){
        if (vec.isTransposed)
            throw  MatrixSizeError::product("Matrix", mat.size(),
                                            "Vector", {1, vec.size()});
        throw  MatrixSizeError::product("Matrix", mat.size(),
                                        "Vector", {vec.size(), 1});
    }
    Vector<T1> tmp(mat.size().first);
    tmp.isTransposed = false;

    for (size_t i = 0; i < mat.size().first; ++i) {
        tmp[i] = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            tmp[i] += vec[j] * mat[i][j];
        }
    }
    return tmp;
}

template<typename T>
T BilinearForm(Matrix<T> mat, Vector<T> vec1, Vector<T> vec2){
    if (mat.size() != std::make_pair(vec1.size(), vec2.size()) || vec1.size() != vec2.size()){
        throw MatrixSizeError::not_matches({
                                                 {"Vector", {{1, vec1.size()}, {"1", "N"}}},
                                                 {"Matrix", {mat.size(),       {"1", "N"}}},
                                                 {"Vector", {{vec2.size(), 1}, {"N", "1"}}}
        }, "BilinearFormSizeError");
    }
    T tmp = 0;
    for (size_t i = 0; i < vec1.size(); ++i){
        for (size_t j = 0; j < vec1.size(); ++j){
            tmp += mat[i][j] * vec1[i] * vec2[j];
        }
    }
    return tmp;
}
#endif //GRAPHIC_VECTOR_H
