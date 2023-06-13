#include "Identifier.h"

namespace Engine {
    Identifier::Identifier() = default;

    std::string Identifier::get_value() const{
        return value;
    }

    bool Identifier::operator==(const Identifier& other) const{
        return value == other.get_value();
    }

    bool Identifier::operator!=(const Identifier& other) const{
        return !(this->operator==(other));
    }

    std::string Identifier::_generate_() {
        return std::string();
    }

    long long HexIdentifier::last = 0;
    std::set<std::string> HexIdentifier::identifiers = std::set<std::string>();

    long long HexIdentifier::rnd(long long from, long long to){ // [from, to]
        return from + rand() % (to - from + 1);
    }

    std::string HexIdentifier::cast_to_hex(const long long &num) {
        std::string alphabet = "0123456789ABCDEF";
        long long tmp = abs(num);
        std::string res;
        while (tmp){
            res = alphabet[tmp % 16] + res;
            tmp /= 16;
        }
        if (num < 0) res = "-" + res;
        return res;
    }

    std::string HexIdentifier::_generate_() {
        std::srand(seed);
        last += rnd(1, 30);
        return cast_to_hex(last);
    }

    HexIdentifier::HexIdentifier(){
//        identifiers();
        if (identifiers.empty()) {
            last = 0;
            value = cast_to_hex(last);
            identifiers.insert(value);
        }
        else {
            value = _generate_();
            identifiers.insert(value);
        }
    }


//    std::string HexIndetifier::get_value();


} // Engine