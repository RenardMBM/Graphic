#ifndef GRAPHIC_COORDINATESYSTEM_H
#define GRAPHIC_COORDINATESYSTEM_H
#include "./Matrix.h"
#include "./Vector.h"
#include "./Pointer.h"
#include "./VectorSpace.h"

template <typename T>
class CoordinateSystem{
private:
    using floatType = long double;

public:
    Pointer<T> initial_point;
    VectorSpace<T> space;
    CoordinateSystem(Pointer<T> initial, VectorSpace<T> basis): initial_point(initial), space(basis){};

    template<typename T_other>
    bool operator==(const CoordinateSystem<T_other> &other){
        return (initial_point == other.initial_point) && (space, other.space);
    }
    bool operator==(const CoordinateSystem<T> &other){
        return (initial_point == other.initial_point) && (space, other.space);
    }
};
#endif //GRAPHIC_COORDINATESYSTEM_H
