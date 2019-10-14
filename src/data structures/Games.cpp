#include "Games.h"
#include "Human.h"

using namespace std;

float Games::guess_my_number(Human *player1, Human *player2) {
    cout << "Player: " << player1->get_name() << " & " << player2->get_name() << " Game: guess_my_number" << endl;
    float shared_score = 0;
    size_t iterations_number = 10;
    size_t first_player_number, second_player_numbeer;
    for (size_t iteration = 0; iteration < iterations_number; iteration++) {
        if (iteration < iterations_number / 2) {
            first_player_number = player1->think_of_number();
            second_player_numbeer = player2->think_of_number();
            cout << "Game: " << player1->get_name() << ": Number=> " << first_player_number << " | " <<
                                player2->get_name() << ": Number=> " << second_player_numbeer << endl;
        } else {
            first_player_number = player2->think_of_number();
            second_player_numbeer = player1->think_of_number();
            cout << "Game: " << player2->get_name() << ": Number=> " << first_player_number << " | " <<
                                player1->get_name() << ": Number=> " << second_player_numbeer << endl;
        }
        shared_score += 10 - std::abs((int)(first_player_number - second_player_numbeer));
        cout << "Current score: " << shared_score / (iteration + 1) << endl;
    }
    shared_score /= iterations_number;
    cout << "Total score: " << shared_score << endl;
    return shared_score;
}