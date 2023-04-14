#include "game.hpp"
#include "player.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>

namespace ariel {
Game::Game(Player &plyr1, Player &plyr2)
    : player1(plyr1), player2(plyr2), pile(), cards_pack(), logs(), turns(0), draws(0), totalDraws(0), gameOver(false)
{
     // Check if either player is already in a game
    if (plyr1.getInGame() || plyr2.getInGame()) {
        throw std::runtime_error("Error: One or both players are already in a game.");
    }
    plyr1.setInGame(true);
    plyr2.setInGame(true);
    // Initialize the cards pack
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            Card card(i,j);
            cards_pack.emplace_back(card);
        }
    }
    
    // Shuffle cards
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards_pack.begin(), cards_pack.end(), g);

    // Deviding cards pack evenly among the players
    int i = 0;
    for(Card card: cards_pack){
        if(i % 2 == 0){
            player1.addCard(card);
        }
        else{
            player2.addCard(card);
        }
        i++;
    }

}

void Game::wonCards(Player& player){
    for(Card card: pile){
        player.addWonCard(card);
    }
}

void Game::drawHandle(){
    if(player1.stacksize() == 0 || player2.stacksize() == 0){
        gameOver = true;
        player1.setInGame(false);
        player2.setInGame(false);
        return;
    }
    
    Card c1 = player1.getCard();
    Card c2 = player2.getCard();
    pile.push_back(c1);
    pile.push_back(c2);

    int result = c1.compare(c2);
    if(result == 1){
        // player1 wins
        wonCards(player1);
        pile.clear();
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". " + player1.getName() + " wins.");
        player1.setWonMatches(player1.getWonMatches() + 1);
    }
    else if(result == -1){
        // player2 wins
        wonCards(player2);
        pile.clear();
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". " + player2.getName() + " wins.");
        player2.setWonMatches(player2.getWonMatches() + 1);
    }
    else{
        // draw
        totalDraws++;
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". Draw.");

        if(player1.stacksize() < 2 || player2.stacksize() < 2){
            int i = 0;
            for(Card card: pile){
                if(i % 2 == 0){
                    player1.addWonCard(card);
                }
                else{
                    player2.addWonCard(card);
                }
                i++;
            }
            pile.clear();
            gameOver = true;
        }
        else{
            Card c11 = player1.getCard();
            Card c21 = player2.getCard();
            pile.push_back(c11);
            pile.push_back(c21);
            drawHandle();
        }
    }
}

void Game::playTurn(){
    if(gameOver){
        throw std::runtime_error("Error: Can't play turn, Game is over.");
        return;
    }
    if(&player1 == &player2){
        throw std::runtime_error("Error: Can't play with the same player.");
        return;
    }

    if(player1.stacksize() == 0 || player2.stacksize() == 0){
        gameOver = true;
        player1.setInGame(false);
        player2.setInGame(false);
        return;
    }
    
    Card c1 = player1.getCard();
    Card c2 = player2.getCard();
    pile.push_back(c1);
    pile.push_back(c2);
    
    turns++;
    int result = c1.compare(c2);
    if(result == 1){
        // player1 wins
        wonCards(player1);
        pile.clear();
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". " + player1.getName() + " wins.");
        player1.setWonMatches(player1.getWonMatches() + 1);
    }
    else if(result == -1){
        // player2 wins
        wonCards(player2);
        pile.clear();
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". " + player2.getName() + " wins.");
        player2.setWonMatches(player2.getWonMatches() + 1);
    }
    else{
        // draw
        draws++; totalDraws++;
        logs.push_back(player1.getName() + " played " + c1.toString() + ", " + player2.getName() + " played " + c2.toString() + ". Draw.");

        if(player1.stacksize() < 2 || player2.stacksize() < 2){
            int i = 0;
            for(Card card: pile){
                if(i % 2 == 0){
                    player1.addWonCard(card);
                }
                else{
                    player2.addWonCard(card);
                }
                i++;
            }
            pile.clear();
            gameOver = true;
        }
        else{
            Card c11 = player1.getCard();
            Card c21 = player2.getCard();
            pile.push_back(c11);
            pile.push_back(c21);
           
            drawHandle();
        }
    }
}

void Game::printLastTurn(){
    std::string lastTurn = logs.back();
    cout << lastTurn << endl;
}

void Game::playAll(){
    if(gameOver){
        cout << "Can't play turn, Game is over." << endl;
        return;
    }
    
    while(!gameOver){
        playTurn();
    }
    player1.setInGame(false);
    player2.setInGame(false);
}

void Game::printWiner(){
    if(!gameOver){
        cout << "Game is not over yet." << endl;
        return;
    }
    std::string winner_name = winner();
    if(winner_name == "tie"){
        cout << "There's a tie!" << endl;
    }
    else{
        cout << "The winner is " + winner_name << endl;
    }
}

void Game::printLog(){
    for(std::string turn: logs){
        cout << turn << endl;
    }
}

void Game::printStats(){
    double drawRates = ((double)draws/(double)turns)*100;
    cout << "---------------- Game statistics ----------------" << endl;
    player1.printRates(turns, draws);
    player2.printRates(turns, draws);
    cout << "Draw rate: " << drawRates << "%" << endl;
    cout << "Number of draws: " << totalDraws << endl;
    cout << "Total turns: " << turns << endl;
}

std::string Game::winner(){
    if(player1.cardesTaken() > player2.cardesTaken()){
        return player1.getName();
    }
    else if(player1.cardesTaken() == player2.cardesTaken()){
        return "tie";
    }
    return player2.getName();
}
}