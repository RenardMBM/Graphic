#ifndef GRAPHIC_POINT_H
#define GRAPHIC_POINT_H

#include "./Vector.h"

namespace LowLevel {
    template<typename T>
    class Point : private Vector<T> {
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
        size_t _size() const {
            return this->n;
        }
    public:
        // region constructs
        using Vector<T>::Vector;

        explicit Point(const Vector<T> &other) {
            this->is_float = check_float<T>();
            this->n = other.size();
            this->m = 1;
            this->matrix = std::vector<std::vector<T>>(this->n, std::vector<T>(1));
            for (size_t i = 0; i < this->n; ++i){
                this->matrix[i][0] = other[i];
            }
        }
        // endregion

        // region methods
        size_t size() const {
            return this->_size();
        }

        template<typename T_other>
        bool equalPrecision(const Point<T_other> &other, int precision = -1) const {
            floatType p;
            if (precision < 0) p = EPS;
            else {
                if (precision > 20) throw std::exception();
                p = 1/std::pow(10, (size_t)precision);
            }
            if (this->size() != other.size()) return false;
            for (size_t i = 0; i < this->size(); ++i) {
                if (std::max(this->operator[](i), static_cast<T>(other[i])) -
                    std::min(this->operator[](i), static_cast<T>(other[i])) > p)
                    return false;
            }
            return true;
        }
        // endregion

        // region operators
        template<typename T_other>
        bool operator==(const Point<T_other> &other) const {
            if (is_float) return equalPrecision(other);
            if (size() != other.size()) return false;
            for (size_t i = 0; i < size(); ++i) {
                if (this->operator[](i) != other.operator[](i)) return false;
            }
            return true;
        }

        Point<T>& operator+=(const Vector<T> &other) {
            if (this->size() < other.size()) {
                throw VectorSizeError::lessThen("Point", this->size(),
                                                "Vector", other.size());
            }
            for (size_t i = 0; i < std::min(this->size(), other.size()); ++i) {
                this->operator[](i) += other[i];
            }
            return *this;
        }

        Point<T>& operator-=(const Vector<T> &other) {
            return *this += (-other);
        }

        Point<T> operator+(const Vector<T> &other) const {
            Point<T> tmp = *this;
            tmp += other;
            return tmp;
        }

        Point<T> operator-(const Vector<T> &other) const {
            return *this + (-other);
        }

        using Vector<T>::operator[];
        // endregion
    };


    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Point<T> &pt) {
        if (check_float<T>()) out << std::setprecision(PRECISION);
        for (size_t i = 0; i < pt.size(); ++i) {
            out << pt[i];
            if (i + 1 != pt.size()) out << ' ';
        }
        return out;
    }
}
#endif //GRAPHIC_POINT_H
