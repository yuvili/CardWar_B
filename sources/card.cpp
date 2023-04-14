#include "card.hpp"
#include <string>

namespace ariel{
Card::Card(int suit_type, int val)
    : suit(suit_type), value(val)
{}

int Card::compare(Card card2){
    if(value == 1){
        if(card2.value > 2){
            return 1;
        }
        else if(card2.value == 2){
            return -1;
        }
        return 0;
    }
    else if(card2.value ==1){
        if(value > 2){
            return -1;
        }
        else if(value == 2){
            return 1;
        }
    }
    
    if(value > card2.value){
        return 1;
    }
    else if(value < card2.value){
        return -1;
    }
    return 0;
}

std::string Card::toString(){
    std::string suit_str;
    std::string value_str;
    
    switch(suit){
        case 0:
            suit_str = "Clubs";
            break;

        case 1:
            suit_str = "Hearts";
            break;

        case 2:
            suit_str = "Diamonds";
            break;

        case 3:
            suit_str = "Spades";
            break;
    }

    if(value < 11 && value != 1){
        value_str = std::to_string(value);
    }
    else{
        switch (value)
        {
        case 1:
            value_str = "Ace";
            break;
        
        case 11:
            value_str = "Jack";
            break;

        case 12:
            value_str = "Queen";
            break;

        case 13:
            value_str = "King";
            break;
        }
    }
    return value_str + " of " + suit_str;
}
}