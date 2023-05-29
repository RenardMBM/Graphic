#ifndef GRAPHIC_IDENTIFIER_H
#define GRAPHIC_IDENTIFIER_H
#include <set>
#include <string>

namespace Engine {
    class Identifier {
    private:
        static std::set<std::string> identifiers;
        std::string value;
        virtual std::string _generate_();
    public:
        explicit Identifier();

        virtual std::string get_value() const;
    };
} // Engine

#endif //GRAPHIC_IDENTIFIER_H
