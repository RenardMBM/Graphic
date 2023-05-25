//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_VECTORERROR_H
#define GRAPHIC_VECTORERROR_H

#include "MatrixError.h"

class VectorError: MatrixError{
public:
    using MatrixError::MatrixError;
protected:
    typedef size_t sizeType;

};

class VectorSizeError: VectorError, MatrixSizeError{
public:
    using MatrixSizeError::MatrixSizeError;

    static VectorSizeError lessThen(
            const msgType& first_vec_name,
            sizeType first_vec_size,
            const msgType& second_vec_name,
            sizeType second_vec_size,
            bool is_first_row=false,
            bool is_second_row=false
            ){
        MatrixError::size_type first_size= {first_vec_size, 1},
                second_size={second_vec_size, 1};
        if (is_first_row) std::swap(first_size.first, first_size.second);
        if (is_second_row) std::swap(second_size.first, second_size.second);

        return VectorSizeError("Size of " + first_vec_name +
                                " = " + msgMatSz(first_size) +
                                "less then size of "+ second_vec_name +
                                " = " + msgMatSz(second_size));
    }

    static VectorSizeError not_match(
            const msgType &first_vec_name,
            const sizeType &first_vec_size,
            const msgType &second_vec_name,
            const sizeType &second_vec_size,
            bool is_first_row=false,
            bool is_second_row=false,
            const msgType &first_vec_size_title="N",
            const msgType &second_vec_size_title="N",
            const msgType &title="MatchError"
            ){
        MatrixError::size_type first_size= {first_vec_size, 1},
        second_size={second_vec_size, 1};
        MatrixError::size_title_type first_size_title = {first_vec_size_title, "1"},
        second_size_title = {second_vec_size_title, "1"};
        if (is_first_row) {
            std::swap(first_size.first, first_size.second);
            std::swap(first_size_title.first, first_size_title.second);
        }
        if (is_second_row) {
            std::swap(second_size.first, second_size.second);
            std::swap(second_size_title.first, second_size_title.second);
        }

        return VectorSizeError(_not_valid(
                first_vec_name,
                first_size,
                second_vec_name,
                second_size,
                first_size_title,
                second_size_title,
                title));
    }
    
    static VectorSizeError product(const msgType &first_vec_name,
                                   const sizeType &first_vec_size,
                                   const msgType &second_vec_name,
                                   const sizeType &second_vec_size,
                                   bool is_first_row=false,
                                   bool is_second_row=false,
                                   const msgType &first_vec_size_title="N",
                                   const msgType &second_vec_size_title="N",
                                   const msgType &title="VectorProductError"){
        return VectorSizeError::not_match(first_vec_name,
                                          first_vec_size,
                                          second_vec_name,
                                          second_vec_size,
                                          is_first_row,
                                          is_second_row,
                                          first_vec_size_title,
                                          second_vec_size_title,
                                          title);
    }
};

#endif //GRAPHIC_VECTORERROR_H
