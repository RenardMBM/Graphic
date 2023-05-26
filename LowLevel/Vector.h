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

    using mulVecByVecTypes = std::variant<Matrix<T>, T>;
protected:
    size_t _size() const{
        return this->n;
    }
public:
    bool isTransposed;  // default(false) column
    using floatType = typename Matrix<T>::floatType;

    floatType EPS = 10e-5;

    //region constructs
    explicit Vector(): Matrix<T>(0, 0), isTransposed(false) {};
    explicit Vector(const size_t &n): Matrix<T>(n, 1), isTransposed(false) {};
    explicit Vector(const size_t &n, const T &value): Matrix<T>(n, 1, value), isTransposed(false) {};
    explicit Vector(const std::vector<T> &vec): Matrix<T>(vec.size(), 1), isTransposed(true) {
        for (size_t i = 0; i < vec.size(); ++i){this->matrix[i][0] = vec[i];}
    };
    explicit Vector(const std::vector<std::vector<T>> &vec): Matrix<T>(vec), isTransposed(false) {};
    template<typename T_other>
    explicit Vector(const Vector<T_other> &other){
        this->isTransposed = other.isTransposed;
        this->n = other.size(); this->m = 1;
        this->matrix = std::vector<std::vector<T>>(this->n, std::vector<T>(this->m));
        for (size_t i = 0 ; i < this->n; ++i){
            this->matrix[i][0] = static_cast<T>(other[i]);
        }
    };
    // endregion

    // region methods
    size_t size() const {
        return _size();
    }

    floatType length(){
        return sqrt(this->operator%(*this));
    }

    Vector<floatType> normalize(){
        Vector<floatType> tmp(*this);
        floatType ln = this->length();
        for (size_t i = 0; ln != 0 && i < this->size(); ++i){
            tmp[i] /= ln;
        }
        return tmp;
    }

    template<typename T_other>
    bool equalPrecision(const Vector<T_other>& other, floatType precision=-1){
        if (precision < 0) precision = EPS;
        if (this->size() != other.size()) return false;
        for (size_t i =0; i < this->size(); ++i){
            if (std::max(this->operator[](i), static_cast<T>(other[i])) -
                std::min(this->operator[](i), static_cast<T>(other[i])) > precision)
                return false;
        }
        return true;
    }

    void transpose(){
        isTransposed = !isTransposed;
    }

    Vector<T> transposed(){
        Vector<T> tmp = *this;
        tmp.transpose();
        return tmp;
    }
    // endregion

    // region operators
    T& operator[](size_t i){
        if (i >= this->size())
            throw MatrixIndexError::index_out("Vector", {size(), 1}, {i, "0"});
        return this->matrix[i][0];
    }
    T operator[](size_t i) const{
        if (i >= this->size())
            throw MatrixIndexError::index_out("Vector", {size(), 1}, {i, "0"});
        return this->matrix[i][0];
    }


    // region product
    template<typename T_other> // product with scalar
    Vector<T> operator*(const T_other& other){
        Vector<T> tmp = *this;
        for (size_t i = 0; i < tmp.size(); ++i)
            tmp[i] *= static_cast<T>(other);
        return tmp;
    }

    template<typename T_other>
    mulVecByVecTypes operator* (const Vector<T_other> &other){
        if (this->isTransposed && !other.isTransposed && this->size() == other.size()){ // multiplication row by column
            T tmp = 0;
            for (size_t i = 0; i < this->size(); ++i){
                tmp += this->operator[](i) * static_cast<T>(other.operator[](i));
            }
            return mulVecByVecTypes(tmp);
        }

        if (!this->isTransposed && other.isTransposed){ // multiplication column by row
            Matrix<T> tmp(this->size(), other.size());
            for (size_t i = 0; i < this->size(); ++i){
                for (size_t j = 0; j < other.size(); ++j){
                    tmp.matrix[i][j] = this->operator[](i) * static_cast<T>(other.operator[](j));
                }
            }
            return mulVecByVecTypes(tmp);
        }

        throw VectorSizeError::product(
                "Vector",
                this->size(),
                "Vector",
                other.size(),
                this->isTransposed,
                other.isTransposed
        );
    }

    template<typename T_other> // product with matrix
    Vector<T> operator*(const Matrix<T_other> &other){
        if (!this->isTransposed || this->size() != other.size().first){
            std::pair<size_t, size_t> tmp_sz = {1, this->size()};
            if (!this->isTransposed) std::swap(tmp_sz.first, tmp_sz.second);
            throw MatrixSizeError::product("Vector",
                                           tmp_sz,
                                           "Matrix",
                                           other.size());
        }
        Vector<T> tmp(other.size().second);
        for (size_t i = 0; i < tmp.size(); ++i){
            tmp[i] = 0;
            for (size_t j = 0; j < this->size(); ++j){
                tmp[i] += this->operator[](j) * static_cast<T>(other[j][i]);
            }
        }
        tmp.isTransposed = true;
        return tmp;
    }

    template<typename T_other>
    Vector<T> &operator*=(const T_other &other){
        Vector<T> tmp(*this);
        tmp = tmp.operator*(other);
        *this = tmp;
        return *this;
    }
    // endregion

    template<typename T_other>
    Vector<T> operator/(const T_other &other){
        Vector<T> tmp = *this;
        tmp /= other;
        return tmp;
    }

    template<typename T_other>
    Vector<T> &operator/=(const T_other &other){
        if (other == 0){
            throw ArithmeticException::divByZero("Vector");
        }
        for (size_t i = 0; i < this->size(); ++i){
            this->operator[](i) /= static_cast<T>(other);
        }
        return *this;
    }

    Vector<T> operator-() const{
        Vector<T> tmp = *this;
        tmp *= -1;
        return tmp;
    }

    template<typename T_other>
    Vector<T> &operator+=(const Vector<T_other>& other){
        for (size_t i = 0; i < std::min(this->size(), other.size()); ++i){
            if (i < other.size())
                this->operator[](i) += static_cast<T>(other[i]);
        }
        return *this;
    }

    template<typename T_other>
    Vector<T> operator+(const Vector<T_other>& other){
        Vector<T> tmp = *this;
        tmp += other;
        return tmp;
    }

    template<typename T_other>
    Vector<T> &operator-=(const Vector<T_other>& other){
        return *this+=(-other);
    }

    template<typename T_other>
    Vector<T> operator-(const Vector<T_other>& other){
        Vector<T> tmp = *this;
        tmp -= other;
        return tmp;
    }

    template<typename T_other>
    bool operator==(const Vector<T_other> &other) const{
        if (this->size() != other.size() || this->isTransposed != other.isTransposed) return false;
        for (size_t i = 0; i < this->size(); ++i){
            if (this->operator[](i) != other[i]) return false;
        }
        return true;
    }

    // region vector_operator
    template<typename T_other>
    T operator%(const Vector<T_other>& other){ // scalar product
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
            tmp += this->operator[](i) * static_cast<T>(other[i]);
        }
        return tmp;
    }
    template<typename T_other>
    Vector<T> operator^(const Vector<T_other>& other){ // vector product
        if (this->size() != 3 || other.size() != 3){
            throw VectorSizeError::not_match("Vector", this->size(),
                                             "Vector", other.size(),
                                             false,false,
                                             "3",
                                             "3",
                                             "VectorProductSizeError");
        }
        Vector<T> tmp(3);

        tmp[0] = this->operator[](1) * static_cast<T>(other[2]) - this->operator[](2) * static_cast<T>(other[1]);
        tmp[1] = this->operator[](2) * static_cast<T>(other[0]) - this->operator[](0) * static_cast<T>(other[2]);
        tmp[2] = this->operator[](0) * static_cast<T>(other[1]) - this->operator[](1) * static_cast<T>(other[0]);
        return tmp;
    }
    // endregion
    // endregion
};

template<typename T1, typename T2>
Vector<T2> operator/(const T1& first, const Vector<T2>& second){
    Vector<T1> tmp(second.size(), first);
    for (size_t i = 0; i < second.size(); ++i){
        tmp[i] /= second[i];
    }
    return tmp;
}


template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 != vec.size()) out << (vec.isTransposed ? ' ' : '\n');
    }
    return out;
}



template<typename T>
T BilinearForm(Matrix<T> mat, Vector<T> vec1, Vector<T> vec2){
    if (mat.size() != std::make_pair(vec1.size(), vec2.size()) || vec1.size() != vec2.size()){
        throw MatrixSizeError::not_matches({
                                                   {"Vector", {{1, vec1.size()}, {"1", "N"}}},
                                                   {"Matrix", {mat.size(),       {"N", "N"}}},
                                                   {"Vector", {{vec2.size(), 1}, {"N", "1"}}}
                                           }, "BilinearFormSizeError");
    }

    Vector<T> tmp_vec;
    if (!vec1.isTransposed)
        tmp_vec = vec1.transposed() * mat;
    else
        tmp_vec = vec1 * mat;


    std::variant<Matrix<T>, T> calc_res;

    if (vec2.isTransposed)
        calc_res = tmp_vec * vec2.transposed();
    else
        calc_res = tmp_vec * vec2;

    return std::get<T>(calc_res);
}
#endif //GRAPHIC_VECTOR_H
