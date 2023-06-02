//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_MATRIXERROR_H
#define GRAPHIC_MATRIXERROR_H

#include "./LowLevelException.h"
#    define _NOEXCEPT noexcept

class MatrixError: public LowLevelException{
protected:
    typedef typename std::pair<size_t, size_t> size_type;
    typedef typename std::pair<msgType, msgType> size_title_type;
    typedef typename std::pair<size_t, msgType> half_size_type;
    typedef typename std::pair<msgType, size_t> rhalf_size_type;
public:
    using LowLevelException::LowLevelException;

    static msgType msgMatSz(const size_type &mat_sz){
        return std::to_string(mat_sz.first) + "x" +
               std::to_string(mat_sz.second);
    }
    static msgType msgMatSz(const size_title_type &mat_sz){
        return mat_sz.first + "x" + mat_sz.second;
    }
    static msgType msgMatSz(const half_size_type &mat_sz){
        return std::to_string(mat_sz.first) + "x" + mat_sz.second;
    }
    static msgType msgMatSz(const rhalf_size_type &mat_sz){
        return mat_sz.first + "x" + std::to_string(mat_sz.second);
    }
};

class MatrixSizeError: public MatrixError{
protected:
    static msgType _not_match_size(const msgType &obj_name, const size_type &expected_sz,
                                   const size_type &found_sz){
        msgType tmp = obj_name +
                     " size expected: " + msgMatSz(expected_sz) +
                     ", but found: " + msgMatSz(found_sz);
        return tmp;
    }
    static msgType _not_match_size(const msgType &obj_name, const size_title_type &expected_sz,
                                   const size_type &found_sz){
        msgType tmp = obj_name +
                      " size expected: " + msgMatSz(expected_sz) +
                      ", but found: " + msgMatSz(found_sz);
        return tmp;
    }
    static msgType _not_valid(const msgType &first_mat_name,
                                      const size_type &first_mat_sz,
                                      const msgType &second_mat_name,
                                      const size_type &second_mat_sz,
                                      const size_title_type &first_mat_sz_title={"N", "M"},
                                      const size_title_type &second_mat_sz_title={"N", "M"},
                                      const msgType& title="ValidError"){
        return title +": "+
                               _not_match_size(first_mat_name,
                                               first_mat_sz_title,
                                               first_mat_sz)+
                               "\n"+
                               _not_match_size(second_mat_name,
                                               second_mat_sz_title,
                                               second_mat_sz
        );
    }
    static msgType _not_valid(const msgType &first_mat_name,
                                      const size_type &first_mat_sz,
                                      const size_title_type &first_mat_sz_title={"N", "M"},
                                      const msgType& title="ValidError"){
        return title +": "+
                               _not_match_size(first_mat_name,
                                               first_mat_sz_title,
                                               first_mat_sz);
    }

    static msgType _not_valid(const std::vector<
                                            std::pair<
                                                    msgType,
                                                    std::pair<size_type, size_title_type>
                                            >> &data,
                              const msgType& title="ValidError"){
        msgType msg = title + ": ";
        for (auto& obj_data: data){
            msg += _not_match_size(obj_data.first,
                                   obj_data.second.second,
                                   obj_data.second.first) + "\n";
        }
        return msg;
    }

public:
    using MatrixError::MatrixError;
    static MatrixSizeError not_square(const msgType &mat_name,
                                      const size_type &mat_sz){
        return MatrixSizeError(_not_valid(
                mat_name,
                mat_sz,
                {"N", "N"},
                "NotSquare"));
    }
    static MatrixSizeError not_rectangular(const msgType &mat_name,
                                           const size_type &expected_mat_sz,
                                           const size_type &elem_sz,
                                           const msgType &title="NotRectangular"){
        return MatrixSizeError(title + ": " + mat_name +
                               " size expected: " + msgMatSz(expected_mat_sz) +
                               " but found elem with size: " + msgMatSz(elem_sz)
        );
    };
    static MatrixSizeError not_matches(const std::vector<
            std::pair<
                    msgType,
                    std::pair<size_type, size_title_type>
            >> &data,
                                     const msgType& title="MatchError"){
        return MatrixSizeError(_not_valid(data, title));
    }
    static MatrixSizeError not_match(const msgType &first_mat_name,
                                     const size_type &first_mat_sz,
                                     const msgType &second_mat_name,
                                     const size_type &second_mat_sz,
                                     const size_title_type &first_mat_sz_title={"N", "M"},
                                     const size_title_type &second_mat_sz_title={"N", "M"},
                                     const msgType &title="MatchError"){
        return MatrixSizeError(_not_valid(
                first_mat_name, first_mat_sz, second_mat_name, second_mat_sz,
                first_mat_sz_title,
                second_mat_sz_title,
                title));
    }

    static MatrixSizeError product(const msgType &first_mat_name,
                                   const size_type &first_mat_sz,
                                   const msgType &second_mat_name,
                                   const size_type &second_mat_sz){
        return MatrixSizeError(_not_valid(
                first_mat_name, first_mat_sz, second_mat_name, second_mat_sz,
                {"N", "M"},
                {"M", "L"},
                "ProductError"));
    }
};

class MatrixIndexError: public MatrixError {
public:
    using MatrixError::MatrixError;
    static MatrixIndexError index_out(const msgType &mat_name,
                                     const size_type &mat_sz,
                                     const size_type &indexes){
        return MatrixIndexError("IndexOut: Size of " + mat_name +
                                " is " + msgMatSz(mat_sz) +
                                ", but try to get " + msgMatSz(indexes));
    }
    static MatrixIndexError index_out(const msgType &mat_name,
                                      const size_type &mat_sz,
                                      const half_size_type &indexes){
        return MatrixIndexError("IndexOut: Size of " + mat_name +
                                " is " + msgMatSz(mat_sz) +
                                ", but try to get " + msgMatSz(indexes));
    }
    static MatrixIndexError index_out(const msgType &mat_name,
                                      const size_type &mat_sz,
                                      const rhalf_size_type &indexes){
        return MatrixIndexError("IndexOut: Size of " + mat_name +
                                " is " + msgMatSz(mat_sz) +
                                ", but try to get " + msgMatSz(indexes));
    }
};

class MatrixClassificationError: MatrixError{
public:
    using MatrixError::MatrixError;
    static MatrixClassificationError singular(msgType title="SingularMatrix"){
        return MatrixClassificationError(title + ": Matrix has det = 0 and is singular");
    }

};


#endif //GRAPHIC_MATRIXERROR_H
