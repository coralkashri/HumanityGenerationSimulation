#ifndef CIRCLESQUEREGAMEPROTOTYPE_STRUCTS_H
#define CIRCLESQUEREGAMEPROTOTYPE_STRUCTS_H

#include <iostream>
#include "enums.h"
#include <vector>

struct Point {
    std::size_t x, y;
};

class Human;
struct Parents {
    Human *mother;
    Human *father;
};

struct Friend {
    Friend(Human *friend_ptr, float friend_connection_value) : friend_ptr(friend_ptr), friend_connection_value(friend_connection_value) {

    }
    float friend_connection_value;
    Human *friend_ptr;
};



struct Favorite {
    unsigned int number;
    Animals animal;
};
#endif //CIRCLESQUEREGAMEPROTOTYPE_STRUCTS_H