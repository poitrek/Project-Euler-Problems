#pragma once
#include <regex>
#include <string>
#include <vector>

#include "Card.h"
#include "Comparable.h"

namespace poker_hands {

    enum SpecialHand;

    class Hand : public Comparable<Hand> {
        static const std::string kCardCodePatternString;
        static const std::regex kCardCodePattern;
        std::vector<Card> cards_;
    public:
        static const std::regex kHandCodePattern;
        static const int kNumberOfCardsInHand;
        enum SortType {
            kAscending, kDescending
        };
        Hand(Card c1, Card c2, Card c3, Card c4, Card c5);
        Hand(std::vector<Card>& cards);
        Hand(std::string code);
        Hand(char* code) : Hand(std::string(code)) {}

        std::vector<Card> GetCards() const {
            return cards_;
        }
        /* Sorts cards in the hand. Use "ascending" or "descending" mode.*/
        void Sort(SortType mode);

        /* Finds the highest SpecialHand for a hand. Returns pair<special_hand_type, vector_of_ranks> where
        vector_of_ranks will be used for a comparison with a hand of the same special type.*/
        std::pair<SpecialHand, std::vector<Rank>> HighestSpecialHand() const;

        /* Compares two hands according to Poker rules */
        bool operator>(const Hand& hand) override;

        /* Compares two hands according to Poker rules (equality) */
        bool operator==(const Hand& hand) override;

    };

}
