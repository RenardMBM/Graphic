#ifndef GRAPHIC_IDENTIFIER_H
#define GRAPHIC_IDENTIFIER_H
#include <set>
#include <string>

namespace Engine {
//    static size_t PRECISION = 9;

    class Identifier {
    private:
        static std::set<std::string> identifiers;
        std::string _generate_();

    protected:
        std::string value;

    public:
        Identifier();

        virtual std::string get_value() const;

        bool operator==(const Identifier&) const;
        bool operator!=(const Identifier&) const;
    };

    class HexIdentifier: virtual public Identifier{
    private:
        static std::set<std::string> identifiers;
        const long long seed = 1833;
        static long long last;

        static long long rnd(long long, long long);
        std::string cast_to_hex(const long long &);
        std::string _generate_();
    public:
        HexIdentifier();
//        using Identifier::get_value;
//        using Identifier::operator==;
//        using Identifier::operator!=;
    };
} // Engine

#endif //GRAPHIC_IDENTIFIER_H
