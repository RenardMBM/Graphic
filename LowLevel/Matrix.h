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
private:
    Matrix<T> submatrix_except(size_t row, size_t col){
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
public:
    using sizeType = std::pair<size_t, size_t>;

    std::vector<std::vector<T>> matrix;

//    static_assert(checkType<T>(), "This type can't be used for a matrix.");
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


    [[nodiscard]] sizeType size() const {return std::make_pair(n, m);}

    template<typename T_other>
    bool operator==(const Matrix<T_other> &other){
        if (size() != other.size()) return false;
        for (size_t i =0; i < size().first; ++i){
            for (size_t j = 0; j < size().second; ++j){
                if (this->matrix[i][j] != other.matrix[i][j]) return false;
            }
        }
        return true;
    }

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
                    other.size().first);
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
                this->matrix[i][j] /= other;
            }
        }
        return *this;
    }

    template<typename T_other>
    Matrix<T> &operator/=(const Matrix<T_other>& other){
        return this *= this->inverse();
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
                matrix[x][y] += other.matrix[x][y];
            }
        }
        return *this;
    }
    template<typename T_other>
    Matrix<T> &operator-=(const Matrix<T_other>& other){
        return *this+=(-other);
    }

    void transpose(){
        std::vector<std::vector<T>> tmp(m, std::vector<T>(n));
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                tmp[j][i] = matrix[i][j];
            }
        }

        std::swap(matrix, tmp);
    }

    Matrix<T> transposed() const {
        Matrix<T> tmp(this);
        tmp.transpose();
        return tmp;
    }

    /*
    Matrix<T> get_minor(const std::vector<size_t> &rows, const std::vector<size_t> &columns) const{
        std::set<size_t> tmp_rows(rows.begin(), rows.end()), tmp_columns(columns.begin(), columns.end());
        size_t cnt_rows = tmp_rows.size(), cnt_columns = tmp_columns.size();

        for (size_t ind: tmp_rows){ if ( ind >= n) --cnt_rows;}
        for (size_t ind: tmp_columns){ if ( ind >= m) --cnt_columns;}

        Matrix<T> tmp(n - cnt_rows, m - cnt_columns);

        auto l = tmp_rows.begin();
        size_t i = 0, j = 0;
        for (size_t i_line = 0; i_line < n; ++i_line){
            if (*l == i_line) {++l; continue;}

            auto c = tmp_columns.begin();
            for (size_t i_col = 0; i_col < m; ++i_col){
                if (*c == i_col) {++c; continue;}
                tmp.matrix[i][j] = matrix[i_line][i_col];
                ++j;
            }
            ++i;
        }

        return tmp;
    }
    */

    floatType det() const {
        if (n != m) throw MatrixSizeError::not_square("Matrix", size());

        if (n == 0) return 0;
        if (n == 1) return matrix[0][0];

        short int sign = 1;
        floatType tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp += sign * matrix[0][i] * submatrix_except(0, i).det();
            sign *= -1;
        }
        return tmp;
    }

    Matrix<T> inverse(){ //TODO: inverse matrix
        T d = det();
        if (d == 0) throw MatrixClassificationError::singular("NoInverse");

        Matrix<T> tmp(n, n);
        for (size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < m; ++j){
                tmp[i][j] = ((i% 2 == j % 2) ? 1 : -1) * submatrix_except(i, j) / d;
            }
        }

        return tmp.transposed();
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

    floatType norm(){
        floatType tmp = 0;
        for (size_t i = 0; i < size().first; ++i){
            for (size_t j = 0; j < size().second; ++j){
                tmp += static_cast<T>(operator[](i)[j]) * static_cast<T>(operator[](i)[j]);
            }
        }
        return sqrt(tmp);
    }

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
    static Matrix<floatType> gram(const std::vector<Vector<T_vec>>& vecs){
        Matrix<floatType> tmp(vecs.size());

        for (size_t i = 0; i < vecs.size(); ++i){
            for (size_t j = 0; j < vecs.size(); ++j){
                tmp[i][j] = vecs[i] % vecs[j];
            }
        }
        return tmp;
    }
};

template<typename T1, typename T2>
Matrix<T1> operator* (const Matrix<T1>& first, const T2& second){
    Matrix<T1> tmp = first;
    tmp *= second;
    return tmp;
}

template<typename T1, typename T2>
Matrix<T2> operator* (const T1& first, const Matrix<T2>& second){
    Matrix<T1> tmp = second;
    tmp *= first;
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

#endif //GRAPHIC_MATRIX_H
