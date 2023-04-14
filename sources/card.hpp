#ifndef CARD_HPP
#define CARD_HPP
#include <string>

namespace ariel{
class Card{
    private:
        int suit;
        int value;
    public:
        Card(int suit_type, int val);
        int compare(Card card2);
        std::string toString();
};
}
#endif