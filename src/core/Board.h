#ifndef CIRCLESQUEREGAMEPROTOTYPE_BOARD_H
#define CIRCLESQUEREGAMEPROTOTYPE_BOARD_H

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "../utilities/Design.hpp"
#include "../data structures/Structs.h"
#include "../data structures/Human.h"
#include "../data structures/Data.h"

using namespace boost::numeric::ublas;
using namespace std;
using board_type = matrix<shared_ptr<Human>>;

class Board {
private:
    size_t board_size;
    board_type board;
    Data game_data;
    bool running;
    void print_board(const board_type &board);
    void next_generation(board_type &board, size_t &current_generation);
    void ClearScreen();

public:
    Board(size_t board_size);
    bool new_child_place(Human &mother, Point *child_point);
    void child_born(shared_ptr<Human> child);
    void start(); // todo:: Turn flag on
    void stop(); // todo:: Turn flag off
};


#endif //CIRCLESQUEREGAMEPROTOTYPE_GAME_H
