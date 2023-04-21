//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_VECTORERROR_H
#define GRAPHIC_VECTORERROR_H

#include "MatrixError.h"

class VectorError: MatrixError{
    using MatrixError::MatrixError;
};

class VectorSizeError: MatrixSizeError{
public:
    using MatrixSizeError::MatrixSizeError;

    static VectorSizeError lessThen(
            msgType vec1_name,
            sizeType vec1_sz,
            msgType vec2_name,
            sizeType vec2_sz
            ){
        return VectorSizeError("Size of " + vec1_name +
                                " = " + msgMatSz(vec1_sz) +
                                "less then size of "+ vec2_name +
                                " = " + msgMatSz(vec2_sz));
    }

    static VectorSizeError not_match(const std::string &first_vec_name,
              const sizeType &first_vec_sz,
              const std::string &second_vec_name,
              const sizeType &second_vec_sz){
        return VectorSizeError(_not_valid(
                first_vec_name,
                first_vec_sz,
                second_vec_name,
                second_vec_sz,
                {"N", "1"},
                {"N", "1"},
                "MatchError" ));
    }
};

#endif //GRAPHIC_VECTORERROR_H
