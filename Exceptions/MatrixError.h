//
// Created by renard_liss on 20.04.2023.
//

#ifndef GRAPHIC_MATRIXERROR_H
#define GRAPHIC_MATRIXERROR_H

#include "./LowLevelException.h"
#    define _NOEXCEPT noexcept

class MatrixError: public LowLevelException{
public:
    using sizeType = std::pair<size_t, size_t>;
    using sizeTitleType = std::pair<msgType, msgType>;
    using halfSizeType = std::pair<size_t, msgType>;
    using rhalfSizeType = std::pair<msgType, size_t>;

    using LowLevelException::LowLevelException;

    static msgType msgMatSz(const sizeType &mat_sz){
        return std::to_string(mat_sz.first) + "x" +
               std::to_string(mat_sz.second);
    }
    static msgType msgMatSz(const sizeTitleType &mat_sz){
        return mat_sz.first + "x" + mat_sz.second;
    }
    static msgType msgMatSz(const halfSizeType &mat_sz){
        return std::to_string(mat_sz.first) + "x" + mat_sz.second;
    }
    static msgType msgMatSz(const rhalfSizeType &mat_sz){
        return mat_sz.first + "x" + std::to_string(mat_sz.second);
    }
};

class MatrixChangeError: public MatrixError{
public:
    using MatrixError::MatrixError;

    static MatrixChangeError set_item(const std::string& name, const std::string& type_name){
    //        char* tmp = "sdafsad";
    //TODO: wtf
        msgType msg = "Wrong item value: "+name+"'s item must be int | float, not " + type_name;
        return MatrixChangeError(msg);
    }
};

class MatrixSizeError: public MatrixError{
protected:
    static msgType _not_match_size(const std::string& obj_name, const sizeType &expected_sz,
                                   const sizeType &found_sz){
        msgType tmp = obj_name +
                     " size expected: " + msgMatSz(expected_sz) +
                     ", but found: " + msgMatSz(found_sz);
        return tmp;
    }
    static msgType _not_match_size(const std::string &obj_name, const sizeTitleType &expected_sz,
                                   const sizeType &found_sz){
        msgType tmp = obj_name +
                      " size expected: " + msgMatSz(expected_sz) +
                      ", but found: " + msgMatSz(found_sz);
        return tmp;
    }
    static msgType _not_valid(const std::string &first_mat_name,
                                      const sizeType &first_mat_sz,
                                      const std::string &second_mat_name,
                                      const sizeType &second_mat_sz,
                                      const sizeTitleType &first_mat_sz_title={"N", "M"},
                                      const sizeTitleType &second_mat_sz_title={"N", "M"},
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
    static msgType _not_valid(const std::string &first_mat_name,
                                      const sizeType &first_mat_sz,
                                      const sizeTitleType &first_mat_sz_title={"N", "M"},
                                      const msgType& title="ValidError"){
        return title +": "+
                               _not_match_size(first_mat_name,
                                               first_mat_sz_title,
                                               first_mat_sz);
    }

    static msgType _not_valid(const std::vector<
                                            std::pair<
                                                    std::string,
                                                    std::pair<sizeType, sizeTitleType>
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
//        msgType msg;
//        for (auto& obj_data: data){
//            msg += _not_match_size(obj_data.first,
//                                   obj_data.second[0],
//                                   obj_data.second[1]) + "\n";
//        }
//        return MatrixSizeError(msg);
//    }

public:
    using MatrixError::MatrixError;
    static MatrixSizeError not_square(const std::string &mat_name,
                                      const sizeType &mat_sz){
        return MatrixSizeError(_not_valid(
                mat_name,
                mat_sz,
                {"N", "N"},
                "NotSquare"));
    }
    static MatrixSizeError not_rectangular(const std::string &mat_name,
                                           const sizeType &expected_mat_sz,
                                           const sizeType &elem_sz,
                                           const msgType &title="NotRectangular"){
        return MatrixSizeError(title + ": " + mat_name +
                               " size expected: " + msgMatSz(expected_mat_sz) +
                               " but found elem with size: " + msgMatSz(elem_sz)
        );
    };
    static MatrixSizeError not_matches(const std::vector<
            std::pair<
                    std::string,
                    std::pair<sizeType, sizeTitleType>
            >> &data,
                                     const msgType& title="MatchError"){
        return MatrixSizeError(_not_valid(data, title));
    }
    static MatrixSizeError not_match(const std::string &first_mat_name,
                                     const sizeType &first_mat_sz,
                                     const std::string &second_mat_name,
                                     const sizeType &second_mat_sz,
                                     const sizeTitleType &first_mat_sz_title={"N", "M"},
                                     const sizeTitleType &second_mat_sz_title={"N", "M"},
                                     const msgType &title="MatchError"){
        return MatrixSizeError(_not_valid(
                first_mat_name, first_mat_sz, second_mat_name, second_mat_sz,
                first_mat_sz_title,
                second_mat_sz_title,
                title));
    }

    static MatrixSizeError product(const std::string &first_mat_name,
                                   const sizeType &first_mat_sz,
                                   const std::string &second_mat_name,
                                   const sizeType &second_mat_sz){
        return MatrixSizeError(_not_valid(
                first_mat_name, first_mat_sz, second_mat_name, second_mat_sz,
                {"N", "M"},
                {"M", "L"},
                "ProductError"));
    }


//    static MatrixSizeError out_range(const std::string &first_mat_name,
//                                     const sizeType &first_mat_sz,
//                                     const std::string &second_mat_name,
//                                     const sizeType &second_mat_sz,
//                                     const msgType &title="OutOfRangeError: "){
//
//    };
};

class MatrixIndexError: public MatrixError {
//protected:

public:
    using MatrixError::MatrixError;
    static MatrixIndexError index_out(const std::string &mat_name,
                                     const sizeType &mat_sz,
                                     const sizeType &indexes){
        return MatrixIndexError("IndexOut: Size of " + mat_name +
                                " is " + msgMatSz(mat_sz) +
                                ", but try to get " + msgMatSz(indexes));
    }
    static MatrixIndexError index_out(const std::string &mat_name,
                                      const sizeType &mat_sz,
                                      const halfSizeType &indexes){
        return MatrixIndexError("IndexOut: Size of " + mat_name +
                                " is " + msgMatSz(mat_sz) +
                                ", but try to get " + msgMatSz(indexes));
    }
    static MatrixIndexError index_out(const std::string &mat_name,
                                      const sizeType &mat_sz,
                                      const rhalfSizeType &indexes){
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
