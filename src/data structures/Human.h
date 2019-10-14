#ifndef HUMANITYGENERATIONSIMULATION_HUMAN_H
#define HUMANITYGENERATIONSIMULATION_HUMAN_H

#include <iostream>
#include <vector>
#include <random>
#include "../core/Board.h"
#include "enums.h"
#include "Structs.h"
#include "Data.h"
#include "Games.h"

class Board;
class Human {
private:
    std::string name;
    Gender gender;
    Gender attraction_to_gender;
    Gender wish_to_be_gender;
    float happiness;
    /* happiness
     * ---------
     * Every meeting with friend: Increase happiness by 2.
     * Every generation with wishing to be a different gender: Decrease by 0.5.
     * Every generation with wishing to be the same gender: Increase by 0.5.
     * Every meeting with partner: Increase by 5.
     * Every sexual experiment with partner: Increase by 6.
     * Very first meeting with partner: Increase by 15.
     * Every new friend: Increase by 4.
     * Every canceling of relationship with friend: Decrease by 5.
     * Every death of friend: Decrease by abs(@friends_relationship_power / 5)
     * Every death of kid: Decrease by 50.
     * Every death of partner: Decrease by 50.
     * Every new kid: Increase by 10.
     */
    Favorite favorites;
    Role role;
    Role wish_to_be_role;
    float age;
    float generation_birth;
    Work work;
    std::vector<Human *> kids;
    Human *partner;
    std::vector<Friend> friends;
    /* Friend::friend_connection_value
     * -------------------------------
     * Every generation: Decrease by 0.1.
     * Every meeting with the friend: Increase by 10.
     * Max value: 100.
     * Min value: -5.
     * On max_value reaches - propose marriage.
     * After lower then min value: Cancel relationship.
     * After canceling relationship: Define thought, decrease happiness.
    */
    Parents parents;
    std::string thoughts;
    float health;
    std::size_t months_from_birth;
    bool is_alive;
    Data *game_data;
    Point place_on_board;

    bool operator>(const Human &human);

    bool operator<(const Human &human);

    void make_love();

    Gender generate_new_child_gender();

    bool friendship_conditions(Human &potential_friend);

    bool marriage_conditions(Human &potential_partner);

    /**
     * First step consideration - Before offering friendship
     *
     * @preconditions: none.
     *
     * @availiable_developments:
     *      - @method offer_friendship
     */
    bool consider_relationship_start(Human &potential_friend);

    bool invite_to_game(Human &potential_friend);

    /**
     * First step consideration - Before proposing marriage
     *
     * @preconditions: none.
     *
     * @availiable_developments:
     *      - @method propose_marriage
     */
    bool consider_propose_marriage(Human &potential_partner);

    /**
     * Second step - offer friendship
     * @preconditions:
     *      - @method consider_offer_friendship
     *
     * @developments:
     *      - @method potential_friend->consider_friendship_offer
     *
     * @availiable_developments:
     *      - friendship begin
     */
    bool offer_friendship(Human &potential_friend);

    /**
     * Second step - propose marriage
     * @preconditions:
     *      - @method consider_propose_marriage
     *
     * @developments:
     *      - @method potential_friend->consider_marriage_proposition
     *
     * @availiable_developments:
     *      - marriage to the potential partner
     */
    bool propose_marriage(Human &potential_partner);

    /**
     * Third step - Consider friendship offer that sent to you
     * @preconditions:
     *      - @method offer_friendship
     *
     * @availiable_developments:
     *      - friendship begin
     */
    bool consider_friendship_proposal(Human &potential_friend);

    bool consider_game_proposal(Human &potential_friend);

    /**
     * Third step - Consider marriage proposition that sent to you
     * @preconditions:
     *      - @method propose_marriage
     *
     * @availiable_developments:
     *      - marriage to the potential partner
     */
    bool consider_marriage_proposition(Human &potential_partner);

    void meet_friend(Human &my_friend);

    void meet_partner(Human &my_partner);

    void meet_my_kid(Human &my_kid);

    /**
     * Search Human In Friends List
     * ----------------------------
     * @Description Returns the index of the human in my friends list if exist.
     *              If not exists - returns friends list size
     */
    size_t search_human_in_friends(Human &human);

    /**
     * Search Human In Kids List
     * ----------------------------
     * @Description Returns the index of the human in kids vector if he/she is one of my kids.
     *              If not - returns kids list size
     */
    size_t search_human_in_kids(Human &human);

public:

    Human(const string &name, Gender gender, Parents parents, Point position, float generation_birth, Data *game_data);

    size_t generation;
    void meet(Human &human);

    Role get_role() const;

    float get_age() const;

    Gender get_gender() const;

    Point get_point() const;

    string get_name() const;

    bool alive() const;

    void add_period_to_age(float period);

    float get_last_generation_update();

    size_t think_of_number();

    //Animal think_of_animal();
};


#endif //HUMANITYGENERATIONSIMULATION_HUMAN_H