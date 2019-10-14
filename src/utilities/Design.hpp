#ifndef CIRCLESQUEREGAMEPROTOTYPE_DESIGN_H
#define CIRCLESQUEREGAMEPROTOTYPE_DESIGN_H

#include <iostream>

namespace Design {
    enum Color {
        BLACK = -2,
        WHITE = -1,
        BLUE = 1,
        RED = 2,
        GREEN = 3,
        YELLOW = 4,
        MAGENTA = 5,
        CYAN = 6
    };

    std::string make_colored(const std::string &text, Color color, bool bold);
}




#endif //CIRCLESQUEREGAMEPROTOTYPE_DESIGN_H
