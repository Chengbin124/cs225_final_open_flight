#include <ostream>
namespace Color {
    enum Code {
        RED      = 31,
        GREEN    = 32,
        BLUE     = 34,
        DEFAULT  = 39,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}