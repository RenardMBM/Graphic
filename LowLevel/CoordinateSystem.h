#ifndef GRAPHIC_COORDINATESYSTEM_H
#define GRAPHIC_COORDINATESYSTEM_H
#include "./Matrix.h"
#include "./Vector.h"
#include "./Point.h"
#include "./VectorSpace.h"

namespace LowLevel {
    typedef long double floatType;

    template<typename T>
    class CoordinateSystem {
    public:
        Point<T> initial_point;
        VectorSpace<T> space;

        CoordinateSystem(): initial_point(Point<T>(3)), space(VectorSpace<T>({
            Vector<T>({1, 0, 0}).transposed(),
            Vector<T>({0, 1, 0}).transposed(),
            Vector<T>({0, 0, 1}).transposed()
        })) {};
        CoordinateSystem(const Point<T>& initial, const VectorSpace<T>& basis) : initial_point(initial), space(basis) {};

        template<typename T_other>
        bool operator==(const CoordinateSystem<T_other> &other) const{
            return (initial_point == other.initial_point) && (space == other.space);
        }
    };
}
#endif //GRAPHIC_COORDINATESYSTEM_H
