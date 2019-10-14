#include <memory>
#include "Human.h"


Human::Human(const string &name, Gender gender, Parents parents, Point position, float generation_birth, Data *game_data) : name(name), gender(gender), generation_birth(generation_birth) {
    this->parents.father = parents.father;
    this->parents.mother = parents.mother;
    this->game_data = game_data;
    this->place_on_board = position;
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10);
    favorites.number = dist6(rng);
}

/// Events

void Human::meet(Human &human) {
    bool is_friend = search_human_in_friends(human) != friends.size();
    bool is_mine_partner = &human == partner;
    bool is_one_of_my_kids = search_human_in_kids(human) != kids.size();

    if (is_one_of_my_kids) {
        this->meet_my_kid(human);
    } else if (is_mine_partner) {
        this->meet_partner(human);
    } else if (is_friend) {
        this->meet_friend(human);
    } else {
        this->consider_relationship_start(human);
    }
}

/// Friendship

// Base conditions for basic relationship
bool Human::friendship_conditions(Human &potential_friend) {
    // TODO: consider set an individual roles to accept/denied requests
    // TODO: check in blacklist.
    // TODO: check in favorite celebrations list.
    return true;
}

// Stage 1: Consider relationship's start with the potential friend
bool Human::consider_relationship_start(Human &potential_friend) {
    bool response = false;
    if (this->friendship_conditions(potential_friend)) {
        response = this->invite_to_game(potential_friend);
    }
    return response;
}

// Stage 2: Found match with base conditions - invite potential friend to game (after response - if positive: offer friendship)
bool Human::invite_to_game(Human &potential_friend) {
    bool response = potential_friend.consider_game_proposal(*this);
    if (response) {
        response = this->offer_friendship(potential_friend);
    }
    return response;
}

// Stage 3 (friend's method): Consider relationship's start with the potential friend
bool Human::consider_game_proposal(Human &potential_friend) {
    bool answer = this->friendship_conditions(potential_friend);
    if (answer) {
        Games games;
        answer = false;
        cout << "Favorite numbers: " << name << ": " << favorites.number << " | " << potential_friend.name << ": " << potential_friend.favorites.number << endl;
        float social_score = games.guess_my_number(&potential_friend, this);
        if (social_score > 7) {
            answer = true;
        }
    }
    return answer;
}

// Stage 4: Offer friendship to the potential friend (after response - if positive: add to friends list)
bool Human::offer_friendship(Human &potential_friend) {
    bool response = potential_friend.consider_friendship_proposal(*this);
    if (response) {
        friends.emplace_back(&potential_friend, 0);
    }
    return response;
}

// Stage 5 (friend's method): Consider friendship - if positive: Add potential friend to friends list and return true.
bool Human::consider_friendship_proposal(Human &potential_friend) {
    // Accept friendship offer
    // todo: Add event (FRIENDSHIP_STARTED)
    friends.emplace_back(&potential_friend, 0);
    cout << "******************* Friendship started: " << this->name << " & " << potential_friend.name <<  "***************" << endl;
    return true;
}

/// Marriage

bool Human::marriage_conditions(Human &potential_partner) {
    // Find potential partner in friends list
    size_t index_in_friends = search_human_in_friends(potential_partner);

    bool response = partner == nullptr &&
                    index_in_friends < friends.size() &&
                    friends[index_in_friends].friend_connection_value > 95 &&
                    this->attraction_to_gender == potential_partner.gender &&
                    game_data->test_marriage_legality(age, potential_partner.age);

    return response;
}

bool Human::consider_propose_marriage(Human &potential_partner) {
    bool conditions = marriage_conditions(potential_partner);
    bool response = false;
    if (conditions) {
        response = this->propose_marriage(potential_partner);
    }
    return response;
}

bool Human::propose_marriage(Human &potential_partner) {
    bool response = potential_partner.consider_marriage_proposition(*this);
    if (response) {
        // todo: Add event (MARRIAGE)
        partner = &potential_partner;
        size_t index_in_friends = search_human_in_friends(potential_partner);
        friends.erase(friends.begin() + index_in_friends);
        make_love();
    }
    return response;
}

bool Human::consider_marriage_proposition(Human &potential_partner) {
    bool answer = this->marriage_conditions(potential_partner);

    if (answer) {
        // Accept marriage proposition
        // todo: Add event (MARRIAGE)

        // Find potential partner in friends list
        size_t index_in_friends = search_human_in_friends(potential_partner);
        friends.erase(friends.begin() + index_in_friends);
        partner = &potential_partner;
    }
    return answer;
}

/// Meetings

void Human::meet_friend(Human &my_friend) {
    size_t index_in_friends = search_human_in_friends(my_friend);
    friends[index_in_friends].friend_connection_value += 10;
    if (partner == nullptr) {
        consider_propose_marriage(my_friend);
    }
}

void Human::meet_partner(Human &my_partner) {

}

void Human::meet_my_kid(Human &my_kid) {

}

/// Functionality

size_t Human::search_human_in_friends(Human &human) {
    size_t index_in_friends = friends.size();
    for (size_t i = 0; i < friends.size(); i++) {
        if (friends[i].friend_ptr == &human) {
            index_in_friends = i;
            break;
        }
    }
    return index_in_friends;
}

size_t Human::search_human_in_kids(Human &human) {
    size_t index_in_kids = kids.size();
    for (size_t i = 0; i < kids.size(); i++) {
        if (kids[i] == &human) {
            index_in_kids = i;
            break;
        }
    }
    return index_in_kids;
}

size_t Human::think_of_number() { // TODO: Get the human to guess his number (if familiar, try to find his favorite number)
    size_t preferred_number = favorites.number;
    size_t max_number = 10;
    std::vector<float> numbers_statistic(max_number + 1, 10);
    float percent_idx;

    if (preferred_number + 2 > max_number) {
        preferred_number = (preferred_number + 2) % max_number;
    }

    for (size_t i = preferred_number - 2; i <= preferred_number + 2; i++) {
        if (i == preferred_number - 2 || i == preferred_number + 2) {
            percent_idx = 30;
        } else if (i == preferred_number) {
            percent_idx = 150;
        } else {
            percent_idx = 45;
        }
        numbers_statistic[i] = percent_idx;
    }
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::discrete_distribution<std::mt19937::result_type> dist6(numbers_statistic.begin(), numbers_statistic.end());
    return dist6(rng);
}

void Human::make_love() {
    int genders_sum = gender + partner->gender;
    if (genders_sum == 3) {
        // Child born
        Human *father, *mother;
        if (gender == MALE) {
            father = this;
            mother = partner;
        } else {
            father = partner;
            mother = this;
        }
        Point child_point{};
        if (game_data->get_board()->new_child_place(*mother, &child_point)) {
            Gender child_gender = generate_new_child_gender();
            string child_name = game_data->get_name(child_gender);
            /// Pay attention! get_last_generation_update is in use - make sure that the age getting update before this part!!
            shared_ptr<Human> child = make_shared<Human>(child_name, child_gender, Parents{mother, father}, child_point, get_last_generation_update(), game_data);
            game_data->get_board()->child_born(child);
            // todo: New Event (KID_BORN)
        }
    }
}

Gender Human::generate_new_child_gender() {
    Human *male;
    float boy_percents = 50;
    size_t parents_generation_to_decide = 3;
    if (gender == MALE) {
        male = this;
    } else {
        male = partner;
    }
    if (male->wish_to_be_gender != MALE)
        boy_percents -= 10;
    Human *prev_generation = male;
    for (size_t i = 0; i <= parents_generation_to_decide; i++) {
        if (prev_generation) {
            if (prev_generation->wish_to_be_gender != MALE)
                boy_percents -= 5;
        } else {
            break;
        }
        prev_generation = prev_generation->parents.father;
    }

    return game_data->generate_random_gender(boy_percents);
}

/// Access methods

bool Human::operator>(const Human &human) {
    return age > human.age;
}

bool Human::operator<(const Human &human) {
    return age < human.age;
}

Role Human::get_role() const {
    return role;
}

float Human::get_age() const {
    return age;
}

Gender Human::get_gender() const {
    return gender;
}

bool Human::alive() const {
    return is_alive;
}

void Human::add_period_to_age(float period) {
    age += period;
}

string Human::get_name() const {
    return name;
}

Point Human::get_point() const {
    return place_on_board;
}

float Human::get_last_generation_update() {
    return (generation_birth + age) / game_data->get_period_increasing();
}