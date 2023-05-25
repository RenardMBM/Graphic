#ifndef GRAPHIC_MATRIX_H
#define GRAPHIC_MATRIX_H

#include <vector>
#include <set>
#include "../Exceptions/MatrixError.h"

template <typename T>
class Vector;

template <typename T>
class Matrix{
protected:
    size_t n, m; // height, width
    using floatType = long double;
    floatType EPS = 1e-5;
private:
    Matrix<T> submatrix_except(size_t row, size_t col) const{
        Matrix<T> tmp(n - 1, m - 1);
        size_t d_row = 0, d_col = 0;
        for (size_t i = 0; i < n; ++i){
            if (i == row) {d_row = 1; continue;}
            for (size_t j = 0; j < m; ++j){
                if (j == col) {d_col = 1; continue;}
                tmp.matrix[i - d_row][j - d_col] = matrix[i][j];
            }
            d_col = 0;
        }
        return tmp;
    }

    bool is_identity(floatType precision = -1){
        if (precision < 0) precision = EPS;
        if (this->size().first != this->size().second) return false;
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < n; ++j){
                if (i == j){
                    if (std::max(matrix[i][j],1) - std::min(matrix[i][j],1) > precision)
                        return false;
                }
                else{
                    if (std::abs(matrix[i][j]) > precision)
                        return false;
                }
            }
        }
        return true;
    }
public:
    using sizeType = std::pair<size_t, size_t>;

    std::vector<std::vector<T>> matrix;

    // region constructs
    explicit Matrix(size_t n): n(n), m(n), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))){};
    explicit Matrix(size_t n, size_t m): n(n), m(m), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))){};
    Matrix(size_t n, size_t m, T value): n(n), m(m), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, value))){};
    Matrix(const Matrix<T> &other): n(other.n), m(other.m), matrix(std::vector<std::vector<T>>(other.matrix)){};
    template<typename T_other>
    explicit Matrix(const Matrix<T_other> &other): n(other.n), m(other.m), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m))){
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                matrix[i][j] = static_cast<T>(other[i][j]);
            }
        }
    }
    explicit Matrix(const std::vector<std::vector<T>> &other){
        n = other.size();
        m = 0;
        if (n) {
            m = other[0].size();
        }
        if (!m) n = 0;
        for (auto &r: other){
            if (r.size()!= m)
                throw MatrixSizeError::not_rectangular(
                        "vector<vector>",
                        {n, m},
                        {1, r.size()},
                        "InitFromNoRectangular");
        }
        matrix = other;
    }

    Matrix() {}
    // endregion

    // region methods
    sizeType size() const {return std::make_pair(n, m);}

    void transpose(){
        std::vector<std::vector<T>> tmp(m, std::vector<T>(n));
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                tmp[j][i] = matrix[i][j];
            }
        }

        std::swap(m, n);
        std::swap(matrix, tmp);
    }

    Matrix<T> transposed() const {
        Matrix<T> tmp(*this);
        tmp.transpose();
        return tmp;
    }

    T det() const {
        if (n != m) throw MatrixSizeError::not_square("Matrix", size());

        if (n == 0) return 0;
        if (n == 1) return matrix[0][0];

        short int sign = 1;
        T tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp += sign * matrix[0][i] * submatrix_except(0, i).det();
            sign *= -1;
        }
        return tmp;
    }

    Matrix<floatType> inverse() const {
        T d = det();
        if (d == 0) throw MatrixClassificationError::singular("NoInverse");

        Matrix<floatType> res = Matrix().identity<floatType>(n);
        std::vector<std::vector<floatType>> mat(n, std::vector<floatType>(n));
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < n; ++ j){
                mat[i][j] = matrix[i][j];
            }
        }
        for (size_t i = n - 1; i > 0; i--) {
            if (mat[i - 1][0] < mat[i][0]) {
                std::swap(mat[i], mat[i - 1]);
            }
        }
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (j != i) {
                    floatType temp = mat[j][i] / mat[i][i];
                    for (size_t k = 0; k < n; k++) {
                        mat[j][k] -= mat[i][k] * temp;
                        res.matrix[j][k] -= res.matrix[i][k] * temp;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            floatType temp = mat[i][i];
            for (int j = 0; j < n; j++) {
                mat[i][j] = mat[i][j] / temp;
                res.matrix[i][j] = res.matrix[i][j] / temp;
            }
        }
        return res;
    }

    floatType norm(){
        floatType tmp = 0;
        for (size_t i = 0; i < size().first; ++i){
            for (size_t j = 0; j < size().second; ++j){
                tmp += static_cast<T>(operator[](i)[j]) * static_cast<T>(operator[](i)[j]);
            }
        }
        return sqrt(tmp);
    }

    template<typename T_other>
    bool equalPrecision(const Matrix<T_other>& other, floatType precision=-1){
        if (precision < 0) precision = EPS;
        if (this->size() != other.size()) return false;
        for (size_t i =0; i < this->size().first; ++i){
            for (size_t j = 0; j < this->size().second; ++j){
                if (std::max(this->matrix[i][j], static_cast<T>(other.matrix[i][j])) -
                             std::min(this->matrix[i][j], static_cast<T>(other.matrix[i][j])) > precision)
                    return false;
            }
        }
        return true;
    }
    // endregion

    // region operators
    template<typename T_other>
    Matrix<T> &operator*=(const T_other &other){
        for (size_t i = 0; i < this->size().first; ++i){
            for (size_t j = 0; j < this->size().second; ++j){
                this->matrix[i][j] *= static_cast<T>(other);
            }
        }
        return *this;
    }

    template<typename T_other>
    Matrix<T> &operator*=(const Matrix<T_other>& other){
        if (this->size().second != other.size().first){
            throw MatrixSizeError::product(
                    "Matrix",
                    this->size(),
                    "Matrix",
                    other.size());
        }
        Matrix<T> tmp(this->size().first, other.size().second);

        for (size_t i = 0; i < tmp.size().first; ++i){
            for (size_t j = 0; j < tmp.size().second; ++j){
                for (size_t k = 0; k < this->size().second; ++k){
                    tmp.matrix[i][j] += this->matrix[i][k] * static_cast<T>(other.matrix[k][j]);
                }
            }
        }
        *this = tmp;
        return *this;
    }

    template<typename T_other>
    Matrix<T> &operator/=(const T_other &other){
        if (other == 0){
            throw ArithmeticException::divByZero("Matrix");
        }
        for (size_t i = 0; i < this->size().first; ++i){
            for (size_t j = 0; j < this->size().second; ++j){
                this->matrix[i][j] /= static_cast<T>(other);
            }
        }
        return *this;
    }

    template<typename T_other>
    Matrix<T> &operator/=(const Matrix<T_other>& other){
        if (this->size().second != other.size().first){
            throw MatrixSizeError::product(
                    "Matrix",
                    this->size(),
                    "Matrix",
                    other.size());
        }
        Matrix<T> tmp = *this * other.inverse();
        *this = tmp;
        return *this;
    }

    Matrix<T> operator-() const{
        Matrix<T> tmp = *this;
        tmp *= -1;
        return tmp;
    }

    template<typename T_other>
    Matrix<T> &operator+=(const Matrix<T_other>& other){
        if (this->size() != other.size()){
            throw MatrixSizeError::not_match("Matrix",
                                             this->size(),
                                             "Matrix",
                                             other.size());
        }
        for (size_t x = 0; x < n; ++x){
            for (size_t y = 0; y < m; ++y){
                matrix[x][y] += static_cast<T>(other.matrix[x][y]);
            }
        }
        return *this;
    }
    template<typename T_other>
    Matrix<T> &operator-=(const Matrix<T_other>& other){
        return *this+=(-other);
    }

    std::vector<T>& operator[](size_t i){
        if (i >= size().first)
            throw MatrixIndexError::index_out("Matrix", size(), {i, "?"});
        return matrix[i];
    }
    std::vector<T> operator[](size_t i) const {
        if (i >= size().first)
            throw MatrixIndexError::index_out("Matrix", size(), {i, "?"});

        return matrix[i];
    }
    // endregion

    // region static methods
    template<typename T_new>
    static Matrix<T_new> identity(size_t n){
        Matrix<T_new> tmp(n, n);
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < n; ++j){
                tmp.matrix[i][j] = (i == j);
            }
        }
        return tmp;
    }

    template<typename T_vec>
    static Matrix<T_vec> gram(const std::vector<Vector<T_vec>>& vecs){
        Matrix<T_vec> tmp(vecs.size());

        for (size_t i = 0; i < vecs.size(); ++i){
            for (size_t j = 0; j < vecs.size(); ++j){
                tmp[i][j] = static_cast<Vector<T_vec>>(vecs[i]) % static_cast<Vector<T_vec>>(vecs[j]);
            }
        }
        return tmp;
    }
    // endregion
};

template<typename T1, typename T2>
Matrix<T1> operator* (const Matrix<T1>& first, const T2& second){
    Matrix<T1> tmp = first;
    tmp *= second;
    return tmp;
}


template<typename T1, typename T2>
Matrix<T1> operator* (const Matrix<T1>& first, const Matrix<T2>& second){
    Matrix<T1> tmp = first;
    tmp *= second;
    return tmp;
}

template<typename T1, typename T2>
Matrix<T1> operator/ (const Matrix<T1>& first, const T2& second){
    Matrix<T1> tmp = first;
    tmp /= second;
    return tmp;
}

template<typename T1, typename T2>
Matrix<T1> operator/ (const Matrix<T1>& first, const Matrix<T2>& second){
    Matrix<T1> tmp = first;
    tmp /= second;
    return tmp;
}


template<typename T1, typename T2>
Matrix<T1> operator+ (const Matrix<T1>& first, const Matrix<T2>& second){
    Matrix<T1> tmp = first;
    tmp += second;
    return tmp;
}

template<typename T1, typename T2>
Matrix<T1> operator- (const Matrix<T1>& first, const Matrix<T2>& second){
    Matrix<T1> tmp = first;
    tmp -= second;
    return tmp;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat) {
    for (size_t i = 0; i < mat.size().first; ++i) {
        for (size_t j = 0; j < mat.size().second; ++j) {
            out << mat.matrix[i][j] << ' ';
        }
        if (i + 1 != mat.size().first) out << '\n';
    }
    return out;
}
template<typename T>
std::istream &operator>>(std::istream &in,  Matrix<T> &mat) {
    for (size_t i = 0; i < mat.size().first; ++i) {
        for (size_t j = 0; j < mat.size().second; ++j) {
            in >> mat.matrix[i][j];
        }
    }
    return in;
}

template<typename T1, typename T2>
bool operator==(const Matrix<T1> &first, const Matrix<T2> &second){
    if (first.size() != second.size()) return false;
    for (size_t i = 0; i < first.size().first; ++i){
        for (size_t j = 0; j < first.size().second; ++j){
            if (first.matrix[i][j] != static_cast<T1>(second.matrix[i][j])) return false;
        }
    }
    return true;
}

template<typename T1, typename T2>
bool operator!=(const Matrix<T1> &first, const Matrix<T2> &second){
    return ! (first == second);
}

#endif //GRAPHIC_MATRIX_H
