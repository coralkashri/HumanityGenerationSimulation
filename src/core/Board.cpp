#include "Board.h"
#include <fstream>
#include <filesystem>

#define CLEAR_SCREEN true

using namespace boost::numeric::ublas;
using namespace std;

Board::Board(size_t board_size) : board_size(board_size < 20 ? 20 : board_size), board(this->board_size, this->board_size), game_data(this) {
    running = false;
}

void Board::print_board(const board_type &board) {
    string shape;
    Design::Color color;
    size_t humans_count = 0;
    for (size_t i = 0; i < board.size1(); i++) {
        for (size_t j = 0; j < board.size2(); j++) {
            if (board(i, j)) {
                humans_count++;
                switch (board(i, j)->get_role()) {
                    case POLICEMAN:
                        shape = 'P';
                        break;

                    case DOCTOR:
                        shape = 'D';
                        break;

                    case BAD:
                        shape = 'B';
                        break;

                    case NOTHING_SPECIAL:
                    default:
                        shape = board(i, j)->get_age() < 16 ? 'y' : 'Y';
                        break;
                }
                color = (Design::Color)board(i, j)->get_gender();
            } else {
                shape = '-';
                color = Design::Color::WHITE;
            }
            cout << Design::make_colored(shape, color, false) << " ";
        }
        cout << endl;
    }
    cout << "Humans counter: " << humans_count << endl;
}

void Board::check_meet(board_type &board, Point human_point) {
    shared_ptr<Human> me = board(human_point.x, human_point.y);
    //size_t start_x_searching = ((int)human_point.x - (int)1 < 0) ? 0 : human_point.x - 1;
    //size_t start_y_searching = ((int)human_point.y - (int)1 < 0) ? 0 : human_point.y - 1;
    for (int i = (int)human_point.x - (int)1; i <= (int)(human_point.x + 1) && i < (int)board.size1(); i++) {
        if (i < 0) continue;
        for (int j = (int)human_point.y - (int)1; j <= (int)(human_point.y + 1) && j < (int)board.size2(); j++) {
            if (j < 0) continue;
            //if (board(i, j)) cout << "Human " << (board(i, j).get() == me.get() ? "(ME) " : "") << "detected: " << board(i, j)->get_name() << endl;
            if (board(i, j) && board(i, j).get() != me.get()) {
                // todo: Add event (MEETS)
                cout << "Meet occurred: " << me->get_name() << " & " << board(i, j)->get_name() << endl;
                me->meet(*board(i, j));
                //cout << "Me: (" << human_point.x << ", " << human_point.y << ") | Meeting: (" << i << ", " << j << ")" << endl;
            }
        }
    }
}

/**
 * Check Attraction
 * ----------------
 * @Description Looking for humans in the area that mach the attraction gender of a specific human, and returns
 *  the direction that the human have to choose to get closer.
 */
Direction check_attraction(board_type &board, Point human_point) {
    shared_ptr<Human> me = board(human_point.x, human_point.y);
    size_t attraction_range = 2;

}

void Board::next_generation(board_type &board, size_t &current_generation) {
    current_generation++;
    for (size_t i = 0; i < board.size1(); i++) {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dists(0, 2);
        for (size_t j = 0; j < board.size2(); j++) {
            if (!board(i, j) || board(i, j)->generation == current_generation) continue;
            Point current_element_point = {i, j};
            bool is_updated;
            Point square_point = {};

            // Add period to human's age
            board(i, j)->generation = current_generation;
            board(i, j)->add_period_to_age(game_data.get_period_increasing());

            // Move
            size_t random_x_change = dists(rng) - 1;
            size_t random_y_change = dists(rng) - 1;
            if (i + random_x_change >= 0 && i + random_x_change < board.size1() &&
                    j + random_y_change >= 0 && j + random_y_change < board.size2() &&
                    !board(i + random_x_change, j + random_y_change)) {
                board(i + random_x_change, j + random_y_change) = std::move(board(i, j));
                //board(i, j) = nullptr;
                current_element_point = {i + random_x_change, j + random_y_change};
            }

            // Check meet
            check_meet(board, current_element_point);
        }
    }
}

void Board::ClearScreen() {
#if CLEAR_SCREEN
    std::system("tput reset");
#endif
}

void Board::start() {
    running = true;
    const size_t initial_civilians_count = 10;
    size_t players_count = 2;
    size_t generation = 0;
    std::vector<Gender> genders = game_data.generate_random_gender(50, initial_civilians_count);
    for (size_t i = 0; i < initial_civilians_count; i++) {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dists(0, board_size - 1);
        string name = game_data.get_name(genders[i]);
        Point p = {dists(rng), dists(rng)};
        board(p.x, p.y) = make_shared<Human>(Human(name, genders[i], Parents{nullptr, nullptr}, p, generation, &game_data));
    }

    while (running) {
        cout << "Generation: " << generation << endl;
        next_generation(board, generation);
        print_board(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cout << endl << endl << endl<< endl << endl;
        write_protect.wait_for_write_access();
        // todo Write data to file
        write_protect.close_write_access();
        ClearScreen();
    }
}

void Board::stop() {
    running = false;
}

bool Board::new_child_place(Human &mother, Point *child_point) {
    bool is_place_founded = false;
    Point mother_point = mother.get_point();
    size_t start_x_searching = ((int)mother_point.x - (int)1 < 0) ? 0 : mother_point.x - 1;
    size_t start_y_searching = ((int)mother_point.y - (int)1 < 0) ? 0 : mother_point.y - 1;
    for (size_t i = start_x_searching; i < mother_point.x + 1; i++) {
        for (size_t j = start_y_searching; j < mother_point.y + 1; j++) {
            if (!board(i, j)) {
                child_point->x = i;
                child_point->y = j;
                is_place_founded = true;
            }
        }
    }

    return is_place_founded;
}

void Board::child_born(shared_ptr<Human> child) {
    board(child->get_point().x, child->get_point().y) = child;
}
