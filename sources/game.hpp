#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <random>
using namespace std;

#include "player.hpp"

namespace ariel{

class Game{
    private:
        Player &player1;
        Player &player2;
        std::vector<Card> pile;
        std::vector<Card> cards_pack;
        std::vector<std::string> logs;
        int turns;
        int draws;
        int totalDraws;
        bool gameOver;
        void drawHandle();
        void wonCards(Player& player);

    public:
        Game(Player &plyr1, Player &plyr2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        std::string winner();
};
}
#endif