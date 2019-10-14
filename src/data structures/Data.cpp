#include "Data.h"

Data::Data(Board *board) {
    this->board = board;
    game_period_increasing = 0.1;
    max_years_ages_distance_for_marriage = 5;
    legal_age_for_marriage = 18;
    names.push_back({MALE, "Mark"});
    names.push_back({MALE, "Dilan"});
    names.push_back({MALE, "Anton"});
    names.push_back({MALE, "Mulder"});
    names.push_back({MALE, "Lorend"});
    names.push_back({FEMALE, "Scully"});
    names.push_back({FEMALE, "Dolly"});
    names.push_back({FEMALE, "Olivia"});
    names.push_back({FEMALE, "Amelia"});
    names.push_back({FEMALE, "Grace"});
    names.push_back({FEMALE, "Chloe"});
}

string Data::get_name(Gender gender) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dists(0, names.size());
    size_t random_name = dists(rng);
    while (names[random_name].gender != gender) {
        random_name = dists(rng);
    }
    return names[random_name].name;
}

float Data::get_period_increasing() {
    return game_period_increasing;
}

Gender Data::generate_random_gender(float boy_percents) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::discrete_distribution<std::mt19937::result_type> dist6({boy_percents, 100 - boy_percents});
    return (Gender)(dist6(rng) + 1);
}

vector<Gender> Data::generate_random_gender(float boy_percents, size_t count) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::discrete_distribution<std::mt19937::result_type> dist6({boy_percents, 100 - boy_percents});
    vector<Gender> result;
    for (size_t i = 0; i < count; i++) {
        result.push_back((Gender)(dist6(rng) + 1));
    }
    return result;
}

Board *Data::get_board() {
    return board;
}

size_t Data::get_max_years_distance_for_marriage() {
    return max_years_ages_distance_for_marriage;
}

size_t Data::get_legal_age_for_marriage() {
    return legal_age_for_marriage;
}

bool Data::test_marriage_legality(float age1, float age2) {
    float min_age, max_age;
    min_age = age1 > age2 ? age2 : age1;
    max_age = age1 + age2 - min_age;

    return min_age >= legal_age_for_marriage &&
           max_age - max_years_ages_distance_for_marriage < max_age - min_age;
}
