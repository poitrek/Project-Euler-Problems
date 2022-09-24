#pragma once
#include <regex>
#include <string>
#include <vector>

#include "Card.h"
#include "Comparable.h"

namespace poker_hands {

    enum SpecialHand;

    class Hand : public Comparable<Hand> {
        static const std::string card_code_pattern_string;
        static const std::regex card_code_pattern;
    public:
        static const std::regex hand_code_pattern;
        enum SortType {
            ascending, descending
        };
        std::vector<Card> cards;
        Hand(Card c1, Card c2, Card c3, Card c4, Card c5);
        Hand(std::vector<Card>& cards);
        Hand(std::string code);
        Hand(char* code) : Hand(std::string(code)) {}

        /* Sorts cards in the hand. Use "ascending" or "descending" mode.*/
        void sort(SortType mode);

        /* Finds the highest SpecialHand for a hand. Returns pair<special_hand_type, vector_of_ranks> where
        vector_of_ranks will be used for a comparison with a hand of the same special type.*/
        std::pair<SpecialHand, std::vector<Rank>> highestSpecialHand();

        /* Compares two hands according to Poker rules */
        bool operator>(Hand& hand);

        /* Compares two hands according to Poker rules (equality) */
        bool operator==(Hand& hand);

    };

}
