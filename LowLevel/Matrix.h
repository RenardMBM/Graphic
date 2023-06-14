#ifndef GRAPHIC_MATRIX_H
#define GRAPHIC_MATRIX_H

#include <iostream>
#include <vector>
#include <set>
#include <type_traits>
#include <iomanip>

#include "../Exceptions/MatrixError.h"

namespace LowLevel {
    typedef long double floatType;
    static size_t PRECISION = 4;
    static floatType EPS = 1;

    static void updEPS(){
        EPS = 1l / (floatType)(PRECISION > 0 ? std::pow(10, PRECISION) : 1);
    }
    
    template<typename T>
    bool check_float(){
        return std::is_same<T, float>::value ||
               std::is_same<T, long double>::value ||
               std::is_same<T, double>::value;
    }
    
    template<typename T>
    T roundF(const T& num){
        if (!check_float<T>()) return num;

        updEPS();
        T n_num = num - (std::fmod(num, EPS));
        if (std::abs(std::fmod(num, EPS)) >= EPS / 2)
            n_num += (num > 0? 1 : -1) * EPS;
        return n_num;
    }

    template<typename T>
    class Vector;

    template<typename T>
    class Matrix {
    protected:
        size_t n, m; // height, width

    private:
        bool is_float;
        T roundF(const T& num) const {
            if (!is_float) return num;

            updEPS();
            T n_num = num - (std::fmod(num, EPS));
            if (std::abs(std::fmod(num, EPS)) >= EPS / 2)
                n_num += (num > 0? 1 : -1) * EPS;
            return n_num;
        }
        Matrix<T> submatrix_except(size_t row, size_t col) const {
            Matrix<T> tmp(n - 1, m - 1);
            size_t d_row = 0, d_col = 0;
            for (size_t i = 0; i < n; ++i) {
                if (i == row) {
                    d_row = 1;
                    continue;
                }
                for (size_t j = 0; j < m; ++j) {
                    if (j == col) {
                        d_col = 1;
                        continue;
                    }
                    tmp.matrix[i - d_row][j - d_col] = matrix[i][j];
                }
                d_col = 0;
            }
            return tmp;
        }

    public:
        typedef std::pair<size_t, size_t> sizeType;

        std::vector<std::vector<T>> matrix;

        // region constructs
        explicit Matrix() : n(0), m(0), matrix(std::vector<std::vector<T>>(0, std::vector<T>(0, 0))) {check_float<T>();}

        explicit Matrix(size_t n) : n(n), m(n), matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))) {is_float = check_float<T>();};

        explicit Matrix(size_t n, size_t m) : n(n), m(m),
                                              matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))) {is_float = check_float<T>();};

        Matrix(size_t n, size_t m, T value) : n(n), m(m),
                                              matrix(std::vector<std::vector<T>>(n, std::vector<T>(m, value))) {is_float = check_float<T>();};

        Matrix(const Matrix<T> &other) : n(other.size().first), m(other.size().second),
                                         matrix(std::vector<std::vector<T>>(other.matrix)) {is_float = check_float<T>();};

        template<typename T_other>
        explicit Matrix(const Matrix<T_other> &other): n(other.size().first), m(other.size().second),
                                                       matrix(std::vector<std::vector<T>>(n, std::vector<T>(m))) {
            is_float = check_float<T>();
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < m; ++j) {
                    matrix[i][j] = static_cast<T>(other[i][j]);
                }
            }
        }

        explicit Matrix(const std::vector<std::vector<T>> &other) {
            is_float = check_float<T>();
            n = other.size();
            m = 0;
            if (n) {
                m = other[0].size();
            }
            if (!m) n = 0;
            for (auto &r: other) {
                if (r.size() != m)
                    throw MatrixSizeError::not_rectangular(
                            "vector<vector>",
                            {n, m},
                            {1, r.size()},
                            "InitFromNoRectangular");
            }
            matrix = other;
        }
        // endregion

        // region methods
        sizeType size() const { return std::make_pair(n, m); }

        void transpose() {
            std::vector<std::vector<T>> tmp(m, std::vector<T>(n));
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < m; ++j) {
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
            updEPS();
            short int sign = 1;
            T tmp = 0;
            for (int i = 0; i < n; i++) {
                if (is_float) tmp = roundF(tmp + roundF(sign * matrix[0][i] * submatrix_except(0, i).det()));
                else tmp += (sign * matrix[0][i] * submatrix_except(0, i).det());
                sign *= -1;
            }
            return tmp;
        }

        Matrix<floatType> inverse() const {
            T d = det();
            if (d == 0) throw MatrixClassificationError::singular("NoInverse");

            Matrix<floatType> res = Matrix().identity<floatType>(n);
            std::vector<std::vector<floatType>> mat(n, std::vector<floatType>(n));
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    mat[i][j] = matrix[i][j];
                }
            }

            for (size_t i = 0; i < n; i++) {
                floatType tmp = mat[i][i];
                for (size_t j = 0; j < n; j++) {
                    if (is_float){
                        if (j >= i) mat[i][j] = roundF(mat[i][j] / tmp);
                        res.matrix[i][j] = roundF(res.matrix[i][j] / tmp);
                    }
                    else{
                        if (j >= i) mat[i][j] /= tmp;
                        res.matrix[i][j] /= tmp;
                    }

                }
                for (size_t j = 0; j < n; j++) {
                    if (j != i) {
                        tmp = static_cast<floatType>(mat[j][i]) / mat[i][i];
                        for (size_t k = 0; k < n; k++) {
                            if (is_float) {
                                if (k >= i)
                                    mat[j][k] = roundF(mat[j][k] - roundF(tmp * mat[i][k]));
                                res.matrix[j][k] = roundF(res.matrix[j][k] - roundF(tmp * res.matrix[i][k]));

                            }
                            else {
                                if (k >= i) mat[j][k] -= tmp * mat[i][k];
                                res.matrix[j][k] -= tmp * res.matrix[i][k];
                            }
                        }
                    }
                }
            }
            return res;
        }

        floatType norm() const {
            floatType tmp = 0;
            for (size_t i = 0; i < size().first; ++i) {
                for (size_t j = 0; j < size().second; ++j) {
                    if (is_float) tmp += roundF(static_cast<T>(operator[](i)[j]) * static_cast<T>(operator[](i)[j]));
                    else tmp += static_cast<T>(operator[](i)[j]) * static_cast<T>(operator[](i)[j]);
                    tmp = roundF(tmp);
                }
            }
            return roundF(sqrt(tmp));
        }

        template<typename T_other>
        bool equalPrecision(const Matrix<T_other> &other, int precision = -1) const {
            floatType p;
            if (precision < 0) p = EPS;
            else {
                if (precision > 20) throw std::exception();
                p = 1/std::pow(10, (size_t)precision);
            }
            if (this->size() != other.size()) return false;
            for (size_t i = 0; i < this->size().first; ++i) {
                for (size_t j = 0; j < this->size().second; ++j) {
                    if (std::max(this->matrix[i][j], static_cast<T>(other.matrix[i][j])) -
                        std::min(this->matrix[i][j], static_cast<T>(other.matrix[i][j])) > p)
                        return false;
                }
            }
            return true;
        }
        // endregion

        // region operators
        template<typename T_other>
        Matrix<T> &operator*=(const T_other &other) {
            for (size_t i = 0; i < this->size().first; ++i) {
                for (size_t j = 0; j < this->size().second; ++j) {
                    if (is_float) this->matrix[i][j] = roundF(this->matrix[i][j] * roundF(static_cast<T>(other)));
                    else this->matrix[i][j] *= static_cast<T>(other);
                }
            }
            return *this;
        }

        template<typename T_other>
        Matrix<T> &operator*=(const Matrix<T_other> &other) {
            if (this->size().second != other.size().first) {
                throw MatrixSizeError::product(
                        "Matrix",
                        this->size(),
                        "Matrix",
                        other.size());
            }
            Matrix<T> tmp(this->size().first, other.size().second);

            for (size_t i = 0; i < tmp.size().first; ++i) {
                for (size_t j = 0; j < tmp.size().second; ++j) {
                    for (size_t k = 0; k < this->size().second; ++k) {
                        if (is_float) tmp.matrix[i][j] = tmp.matrix[i][j] + roundF(this->matrix[i][k] * roundF(static_cast<T>(other.matrix[k][j])));
                        else tmp.matrix[i][j] += this->matrix[i][k] * static_cast<T>(other.matrix[k][j]);
                    }
                }
            }
            *this = tmp;
            return *this;
        }

        template<typename T_other>
        Matrix<T> operator*(const T_other &other) const {
            Matrix<T> tmp = *this;
            tmp *= other;
            return tmp;
        }

        template<typename T_other>
        Vector<T> operator*(const Vector<T_other> &vec) const {
            if (vec.isTransposed || vec.size() != this->size().second) {
                std::pair<size_t, size_t> tmp_sz = {1, vec.size()};
                if (!vec.isTransposed) std::swap(tmp_sz.first, tmp_sz.second);
                throw MatrixSizeError::product("Matrix",
                                               this->size(),
                                               "Vector",
                                               tmp_sz);
            }
            Vector<T> tmp(vec.size());
            for (size_t i = 0; i < tmp.size(); ++i) {
                tmp[i] = 0;
                for (size_t j = 0; j < vec.size(); ++j) {
                    if (is_float) tmp[i] += roundF(this->operator[](i)[j] * static_cast<T>(vec[j]));
                    else tmp[i] += this->operator[](i)[j] * static_cast<T>(vec[j]);
                }
            }
            tmp.isTransposed = false;
            return tmp;
        }

        template<typename T_other>
        Matrix<T> &operator/=(const T_other &other) {
            if (other == 0) {
                throw ArithmeticException::divByZero("Matrix");
            }
            for (size_t i = 0; i < this->size().first; ++i) {
                for (size_t j = 0; j < this->size().second; ++j) {
                    if (is_float) this->matrix[i][j] = roundF(this->matrix[i][j] / roundF(static_cast<T>(other)));
                    else this->matrix[i][j] /= static_cast<T>(other);
                }
            }
            return *this;
        }

        template<typename T_other>
        Matrix<T> &operator/=(const Matrix<T_other> &other) {
            if (this->size().second != other.size().first) {
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

        template<typename T_other>
        Matrix<T> operator/(const T_other &other) const {
            Matrix<T> tmp = *this;
            tmp /= other;
            return tmp;
        }

        Matrix<T> operator-() const {
            Matrix<T> tmp = *this;
            tmp *= -1;
            return tmp;
        }

        template<typename T_other>
        Matrix<T> &operator+=(const Matrix<T_other> &other) {
            if (this->size() != other.size()) {
                throw MatrixSizeError::not_match("Matrix",
                                                 this->size(),
                                                 "Matrix",
                                                 other.size());
            }
            for (size_t x = 0; x < n; ++x) {
                for (size_t y = 0; y < m; ++y) {
                    if (is_float) matrix[x][y] = roundF(matrix[x][y] + roundF(static_cast<T>(other.matrix[x][y])));
                    else matrix[x][y] += static_cast<T>(other.matrix[x][y]);
                }
            }
            return *this;
        }

        template<typename T_other>
        Matrix<T> &operator-=(const Matrix<T_other> &other) {
            return *this += (-other);
        }

        template<typename T_other>
        Matrix<T> operator+(const Matrix<T_other> &other) const {
            Matrix<T> tmp = *this;
            tmp += other;
            return tmp;
        }

        template<typename T_other>
        Matrix<T> operator-(const Matrix<T_other> &other) const {
            Matrix<T> tmp = *this;
            tmp -= other;
            return tmp;
        }

        std::vector<T> &operator[](size_t i) {
            if (i >= size().first)
                throw MatrixIndexError::index_out("Matrix", size(), {i, "?"});
            return matrix[i];
        }

        std::vector<T> operator[](size_t i) const {
            if (i >= size().first)
                throw MatrixIndexError::index_out("Matrix", size(), {i, "?"});

            return matrix[i];
        }


        template<typename T_other>
        bool operator==(const Matrix<T_other> &other) const {
            if (is_float) return equalPrecision(other);
            if (this->size() != other.size()) return false;
            for (size_t i = 0; i < this->size().first; ++i) {
                for (size_t j = 0; j < this->size().second; ++j) {
                    if (this->matrix[i][j] != static_cast<T_other>(other.matrix[i][j])) return false;
                }
            }
            return true;
        }

        template<typename T_other>
        bool operator!=(const Matrix<T_other> &other) const {
            return !(*this == other);
        }
        // endregion

        // region static methods
        template<typename T_new>
        static Matrix<T_new> identity(size_t n) {
            Matrix<T_new> tmp(n, n);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    tmp.matrix[i][j] = (i == j);
                }
            }
            return tmp;
        }

        template<typename T_vec>
        static Matrix<T_vec> gram(const std::vector<Vector<T_vec>> &vecs) {
            Matrix<T_vec> tmp(vecs.size());

            for (size_t i = 0; i < vecs.size(); ++i) {
                for (size_t j = 0; j < vecs.size(); ++j) {
                    tmp[i][j] = static_cast<Vector<T_vec>>(vecs[i]) % static_cast<Vector<T_vec>>(vecs[j]);
                }
            }
            return tmp;
        }

        static Matrix<floatType> tait_bryan_matrix(floatType angelX = 0, floatType angelY = 0, floatType angelZ = 0) {
            Matrix<floatType> rx = Matrix<floatType>({
                                                             {1, 0,           0},
                                                             {0, cos(angelX), -sin(angelX)},
                                                             {0, sin(angelX), cos(angelX)}
                                                     }),
                    ry = Matrix<floatType>({
                                                   {cos(angelY),  0, sin(angelY)},
                                                   {0,            1, 0},
                                                   {-sin(angelY), 0, cos(angelY)}
                                           }),
                    rz = Matrix<floatType>({
                                                   {cos(angelZ), -sin(angelZ), 0},
                                                   {sin(angelZ), cos(angelZ),  0},
                                                   {0,           0,            1}
                                           });

            return rx * ry * rz;
        }

        static Matrix<floatType> rotation_matrix(std::pair<size_t, size_t> inds, floatType angle, size_t n) {
            if (inds.first == inds.second) throw std::invalid_argument("indexes must be different");
            if (inds.first >= n || inds.second >= n) throw std::invalid_argument("indexes must be less dimensions");

            Matrix<floatType> mat = Matrix<floatType>::identity<floatType>(n);
            mat[inds.first][inds.first] = cos(angle);
            mat[inds.first][inds.second] = -sin(angle);
            mat[inds.second][inds.first] = sin(angle);
            mat[inds.second][inds.second] = cos(angle);

            return mat;
        }
        // endregion
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat) {
        for (size_t i = 0; i < mat.size().first; ++i) {
            out << std::setprecision(PRECISION);
            for (size_t j = 0; j < mat.size().second; ++j) {
                out << mat.matrix[i][j] << ' ';
            }
            if (i + 1 != mat.size().first)
                out << std::endl;
        }
        return out;
    }

    template<typename T>
    std::istream &operator>>(std::istream &in, Matrix<T> &mat) {
        for (size_t i = 0; i < mat.size().first; ++i) {
            for (size_t j = 0; j < mat.size().second; ++j) {
                in >> mat.matrix[i][j];
            }
        }
        return in;
    }
}
#endif //GRAPHIC_MATRIX_H
