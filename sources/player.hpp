#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel{
class Player{
    private:
        std::string p_name;
        std::vector<Card> cards;
        std::vector<Card> cardsWon;
        int wonMatches = 0;
        bool inGame = false;
    
    public:
        Player(std::string name);
        int stacksize();
        int cardesTaken();
        void addCard(Card new_card);
        void addWonCard(Card won_card);
        int getWonMatches();
        bool getInGame();
        void printRates(int turns, int draws);
        Card getCard();
        void setWonMatches(int matches);
        void setInGame(bool status);
        std::string getName();
        
        Player() = default;
};
}
#endif