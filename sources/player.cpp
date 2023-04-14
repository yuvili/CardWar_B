#include "player.hpp"
#include <string>
#include <iostream>
using namespace std;

namespace ariel{
Player::Player(std::string name)
    : p_name(name), cards(), cardsWon(), wonMatches(), inGame()
{
    wonMatches = 0;
    inGame = false;
};

int Player::stacksize(){
    return cards.size();
}

int Player::cardesTaken(){
    return cardsWon.size();
}

void Player::addCard(Card new_card){
    cards.push_back(new_card);
}

void Player::addWonCard(Card won_card){
    cardsWon.push_back(won_card);
}

int Player::getWonMatches(){
    return wonMatches;
}
bool Player::getInGame(){
    return inGame;
}

Card Player::getCard(){
    Card c = cards.back();
    cards.pop_back();
    return c;
}

std::string Player::getName(){
    return p_name;
}

void Player::setWonMatches(int matches){
    wonMatches = matches;
}
void Player::setInGame(bool status){
    inGame = status;
}

void Player::printRates(int turns, int draws){
    double winRate = ((double)wonMatches/(double)turns)*100.0;
    cout << "Player: " << p_name << endl;
    cout << "   Win rate: " << winRate << "%" << endl;
    cout << "   Cards won: " << cardsWon.size() << endl;
}
}