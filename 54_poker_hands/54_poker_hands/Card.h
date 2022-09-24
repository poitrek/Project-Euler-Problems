#pragma once
#include <unordered_map>

#include "Comparable.h"

namespace poker_hands {

    enum Suit
    {
        suitNone,
        clubs,
        diamonds,
        hearts,
        spades
    };

    enum Rank
    {
        rankNone,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        ace
    };

    class Card : public Comparable<Card>
    {
    public:
        static const std::unordered_map<char, Rank> rank_codes;
        static const std::unordered_map<char, Suit> suit_codes;
        Rank rank;
        Suit suit;
        Card() {
            rank = Rank::rankNone;
            suit = Suit::suitNone;
        }
        Card(const std::string& card_code) {
            rank = Card::rank_codes.at(card_code[0]);
            suit = Card::suit_codes.at(card_code[1]);
        }
        Card(Rank rank, Suit suit)
            : rank(rank), suit(suit) {}
        bool operator>(Card& card);
        bool operator==(Card& card);
    };

}
