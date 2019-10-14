#ifndef HUMANITYGENERATIONSIMULATION_DATA_H
#define HUMANITYGENERATIONSIMULATION_DATA_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "enums.h"
#include <random>

using namespace std;

class Board;
class Data {
private:
    struct Name {
        Gender gender;
        string name;
    };
    struct Roles {
    private:
        struct States {
            float max_value;
            float min_value;
            float on_meet;
            float on_generation;
        };
    public:
        States friends_states; // TODO: submit values for this role in the initialize.
        // TODO: use those values in relevant places.
    } roles;
    vector<Name> names;
    Board *board;
    float game_period_increasing;
    size_t max_years_ages_distance_for_marriage;
    size_t legal_age_for_marriage;
    size_t get_max_years_distance_for_marriage();
    size_t get_legal_age_for_marriage();

public:
    Data(Board *board);
    string get_name(Gender gender);
    float get_period_increasing();
    Gender generate_random_gender(float boy_percents = 50);
    vector<Gender> generate_random_gender(float boy_percents, size_t count);
    Board* get_board();
    bool test_marriage_legality(float age1, float age2);
};


#endif //HUMANITYGENERATIONSIMULATION_DATA_H