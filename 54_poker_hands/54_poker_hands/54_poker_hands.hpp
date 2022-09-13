#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <regex>
#include <unordered_map>

using namespace std;

class PokerEntityException : public exception {
public:
    string msg;
    PokerEntityException(string msg) : msg(msg) {
    }
    virtual const char* what() const noexcept {
        return msg.c_str();
    }
};

const string entity_comparison_error_msg = "Invalid entity type for comparison";
const string vector_rank_comparison_error_msg = "Incompatible rank vectors. Should be the same size";

enum SpecialHand
{
    HighCard,
    Pair,
    TwoPair,
    ThreeOfKind,
    Straight,
    Flush,
    FullHouse,
    FourOfKind,
    StraightFlush,
    RoyalFlush,
    _Last
};

enum Suit
{
    _Suit_None,
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

enum Rank
{
    _Rank_None,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Entity
{
public:
    virtual bool operator>(Entity& e) = 0;
    virtual bool operator==(Entity& e) = 0;
    virtual bool operator>=(Entity& e)
    {
        return (*this) > e || (*this) == e;
    }
    virtual bool operator<(Entity& e)
    {
        return !(*this >= e);
    }
    virtual bool operator<=(Entity& e)
    {
        return !(*this > e);
    }
    virtual bool operator!=(Entity& e)
    {
        return !(*this == e);
    }
};

class Card : public Entity
{
public:
    inline static const unordered_map<char, Rank> rank_codes = {
        {'2', Rank::Two},
        {'3', Rank::Three},
        {'4', Rank::Four},
        {'5', Rank::Five},
        {'6', Rank::Six},
        {'7', Rank::Seven},
        {'8', Rank::Eight},
        {'9', Rank::Nine},
        {'T', Rank::Ten},
        {'J', Rank::Jack},
        {'Q', Rank::Queen},
        {'K', Rank::King},
        {'A', Rank::Ace}
    };
    inline static const unordered_map<char, Suit> suit_codes = {
        {'C', Suit::Clubs},
        {'D', Suit::Diamonds},
        {'H', Suit::Hearts},
        {'S', Suit::Spades}
    };
    Rank rank;
    Suit suit;
    Card() {
        rank = Rank::_Rank_None;
        suit = Suit::_Suit_None;
    }
    Card(const string& card_code) {
        rank = Card::rank_codes.at(card_code[0]);
        suit = Card::suit_codes.at(card_code[1]);
    }
    Card(Rank rank, Suit suit)
        : rank(rank), suit(suit) {}
    virtual bool operator>(Entity& e) {
        if (Card* c = dynamic_cast<Card*>(&e)) {
            return this->rank > c->rank || (this->rank == c->rank && this->suit > c->suit);
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
        // throw EntityTypeException("")
    }
    virtual bool operator==(Entity& e) {
        if (Card* c = dynamic_cast<Card*>(&e)) {
            return this->rank == c->rank && this->suit == c->suit;
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
    }
    // virtual bool operator>(Card &c)
    // {
    //     return this->rank > c.rank || (this->rank == c.rank && this->suit > c.suit);
    // }
    // virtual bool operator==(Card &c)
    // {
    //     return this->rank == c.rank && this->suit == c.suit;
    // }
};

//const unordered_map<char, Rank> Card::rank_codes = {
//    {'2', Rank::Two},
//    {'3', Rank::Three},
//    {'4', Rank::Four},
//    {'5', Rank::Five},
//    {'6', Rank::Six},
//    {'7', Rank::Seven},
//    {'8', Rank::Eight},
//    {'9', Rank::Nine},
//    {'T', Rank::Ten},
//    {'J', Rank::Jack},
//    {'Q', Rank::Queen},
//    {'K', Rank::King},
//    {'A', Rank::Ace}
//};

//const unordered_map<char, Suit> Card::suit_codes = {
//    {'C', Suit::Clubs},
//    {'D', Suit::Diamonds},
//    {'H', Suit::Hearts},
//    {'S', Suit::Spades}
//};


class Hand {
public:
    inline static const int I = 0;
    inline static const string card_code_pattern_string = "[23456789TJQKAtjqka][CDHScdhs]";
    inline static const regex card_code_pattern = regex(Hand::card_code_pattern_string);
    inline static const regex hand_code_pattern = regex("\\s*(?:(" + card_code_pattern_string + ")\\s+){4}(" + card_code_pattern_string + ")\\s*");
    //static 
    vector<Card> cards;
    Hand(Card c1, Card c2, Card c3, Card c4, Card c5) {
        cards = { c1, c2, c3, c4, c5 };
        sort("descending");
    }
    Hand(vector<Card>& cards) : cards(cards) {
        if (cards.size() != 5)
            throw PokerEntityException("Incorrect number of cards in a hand");
        sort("descending");
    }

    Hand(string code) {
        smatch hcp_match;
        if (regex_match(code, hcp_match, Hand::hand_code_pattern)) {
            cout << "yes" << endl;
            smatch ccp_match;
            auto match_begin =
                sregex_iterator(code.begin(), code.end(), Hand::card_code_pattern);
            auto match_end = sregex_iterator();
            cout << "card codes:" << endl;
            for (sregex_iterator i = match_begin; i != match_end; ++i) {
                cout << "->" << (*i).str();
                cards.push_back(Card((*i).str()));
            }
            cout << endl;
        }
        else {
            throw PokerEntityException("Invalid hand code");
        }
        sort("descending");
    }

    Hand(char* code) : Hand(string(code)) {}

    /* Sorts cards in the hand. Use "ascending" or "descending" mode.*/
    void sort(string mode="descending") {
        if (mode == "descending") {
            std::sort(cards.begin(), cards.end(), [](Card& c1, Card& c2) -> bool {
                return c1 > c2;
                });
        }
        else {
            // "ascending"
            std::sort(cards.begin(), cards.end(), [](Card& c1, Card& c2) -> bool {
                return c1 < c2;
                });
        }
    }
    bool operator>(Hand& hand);
    bool operator==(Hand& hand);
    //string to_string() {

    //}
};


//const regex Hand::card_code_pattern = regex(Hand::card_code_pattern_string);
//const regex Hand::hand_code_pattern = regex("\\s*(?:(" + card_code_pattern_string + ")\\s+){4}(" + card_code_pattern_string + ")\\s*");


class SpecialHandChecker
{
public:
    // const SpecialHand hand_type;
    virtual SpecialHand handType() = 0;
    virtual vector<Rank> check(Hand& hand) = 0;

    // Counts each rank in the hand
    unordered_map<Rank, int> count_ranks(Hand& hand) {
        unordered_map<Rank, int> rank_count;
        for (Card& c : hand.cards) {
            if (rank_count.find(c.rank) == rank_count.end()) {
                rank_count.insert({ c.rank, 1 });
            }
            else {
                rank_count[c.rank]++;
            }
        }
        return rank_count;
    }
};

class HighCardChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::HighCard; }
    virtual vector<Rank> check(Hand& hand) {
        vector<Rank> vr;
        for (Card& c : hand.cards)
            vr.push_back(c.rank);
        return vr;
    }
};

class PairChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::Pair; }
    virtual vector<Rank> check(Hand& hand) {
        Rank pair_rank;
        int pair_pos;
        bool found_pair = false;
        for (int i = 0; i < 4; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank) {
                pair_rank = hand.cards[i].rank;
                pair_pos = i;
                found_pair = true;
            }
        }
        if (!found_pair) {
            return vector<Rank>();
        }
        else {
            // Add the rank of the pair
            vector<Rank> vr{ pair_rank };
            // Add the rest of the ranks, from the highest
            for (int i = 0; i < 5; i++)
                if (i != pair_pos && i != pair_pos + 1)
                    vr.push_back(hand.cards[i].rank);
            return vr;
        }
    }
};

class TwoPairChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::TwoPair; }
    virtual vector<Rank> check(Hand& hand) {
        vector<Rank> vr;
        for (int i = 0; i < 4; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank) {
                vr.push_back(hand.cards[i].rank);
            }
        }
        // If two distinct pairs where found
        if (vr.size() == 2 && vr[0] != vr[1]) {
            // triple_ranks contains sorted ranks of the two pairs,
            // add the remaining (kicker) ranks
            for (Card& c : hand.cards)
                if (c.rank != vr[0] && c.rank != vr[1])
                    vr.push_back(c.rank);
            return vr;
        }
        else {
            return vector<Rank>();
        }
    }
};

class ThreeOfKindChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::ThreeOfKind; }
    virtual vector<Rank> check(Hand& hand) {
        vector<Rank> triple_ranks;
        for (int i = 0; i < 3; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank &&
                hand.cards[i + 1].rank == hand.cards[i + 2].rank) {
                triple_ranks.push_back(hand.cards[i].rank);
            }
        }
        // If exactly one triple was found
        if (triple_ranks.size() == 1) {
            for (Card& c : hand.cards) {
                if (c.rank != triple_ranks[0]) {
                    triple_ranks.push_back(c.rank);
                }
            }
            if (triple_ranks.size() == 3 && triple_ranks[1] != triple_ranks[2])
                return triple_ranks;
            else
                return vector<Rank>();
        }
        else
            return vector<Rank>();
    }
};

class StraightChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::Straight; }
    virtual vector<Rank> check(Hand& hand) {
        for (int i = 0; i < 4; i++)
            if (hand.cards[i].rank != hand.cards[i + 1].rank + 1)
                return vector<Rank>();
        // return the highest rank
        return { hand.cards[0].rank };
    }
};

class FlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::Flush; }
    virtual vector<Rank> check(Hand& hand) {
        for (int i = 0; i < 4; i++)
            if (hand.cards[i].suit != hand.cards[i+1].suit)
                return vector<Rank>();
        vector<Rank> vr;
        for (Card& c : hand.cards)
            vr.push_back(c.rank);
        return vr;
    }
};

class FullHouseChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::FullHouse; }
    virtual vector<Rank> check(Hand& hand) {
        unordered_map<Rank, int> rank_count = count_ranks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank triple_rank, pair_rank;
            for (auto rc : rank_count) {
                if (rc.second == 2)
                    pair_rank = rc.first;
                else if (rc.second == 3)
                    triple_rank = rc.first;
                else
                    // A rank has different count - not fullhouse
                    return vector<Rank>();
            }
            return { triple_rank, pair_rank };
        }
        else
            return vector<Rank>();
    }
};

class FourOfKindChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::FourOfKind; }
    virtual vector<Rank> check(Hand& hand) {
        unordered_map<Rank, int> rank_count = count_ranks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank quadruple_rank, single_rank;
            for (auto rc : rank_count) {
                if (rc.second == 1)
                    single_rank = rc.first;
                else if (rc.second == 4)
                    quadruple_rank = rc.first;
                else
                    // A rank has different count - not fullhouse
                    return vector<Rank>();
            }
            return { quadruple_rank, single_rank };
        }
        else
            return vector<Rank>();
    }
};

class StraightFlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::StraightFlush; }
    virtual vector<Rank> check(Hand& hand) {
        if (FlushChecker().check(hand) != vector<Rank>()) {
            return StraightChecker().check(hand);
        }
        else
            return vector<Rank>();
    }
};

class RoyalFlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::RoyalFlush; }
    virtual vector<Rank> check(Hand& hand) {
        vector<Rank> straight_vr = StraightFlushChecker().check(hand);
        if (straight_vr == vector<Rank>({ Ace })) {
            return straight_vr;
        }
        else
            return vector<Rank>();
    }
};

inline vector<shared_ptr<SpecialHandChecker>> handCheckers = {
    shared_ptr<HighCardChecker>(new HighCardChecker),
    shared_ptr<PairChecker>(new PairChecker),
    shared_ptr<TwoPairChecker>(new TwoPairChecker),
    shared_ptr<ThreeOfKindChecker>(new ThreeOfKindChecker),
    shared_ptr<StraightChecker>(new StraightChecker),
    shared_ptr<FlushChecker>(new FlushChecker),
    shared_ptr<FullHouseChecker>(new FullHouseChecker),
    shared_ptr<FourOfKindChecker>(new FourOfKindChecker),
    shared_ptr<StraightFlushChecker>(new StraightFlushChecker),
    shared_ptr<RoyalFlushChecker>(new RoyalFlushChecker),
};

/* Finds the highest SpecialHand for a hand. Returns pair<special_hand_type, vector_of_ranks> where
vector_of_ranks will be used for a comparison with a hand of the same special type.*/
inline pair<SpecialHand, vector<Rank>> highestSpecialHand(Hand& hand) {
    SpecialHand highest_sh;
    vector<Rank> highest_check_result;
    for (shared_ptr<SpecialHandChecker> handChecker : handCheckers) {
        vector<Rank> check_result = handChecker->check(hand);
        if (check_result != vector<Rank>()) {
            highest_check_result = check_result;
            highest_sh = handChecker->handType();
        }
    }
    return pair<SpecialHand, vector<Rank>>(highest_sh, highest_check_result);
}

/* Compares two vectors of ranks. Used when two hands are of the same special type.*/
inline bool operator>(vector<Rank>& vr1, vector<Rank>& vr2) {
    if (vr1.size() != vr2.size()) {
        throw PokerEntityException(vector_rank_comparison_error_msg);
    }
    int i = 0;
    while (i < vr1.size() && vr1[i] == vr2[i])
        i++;
    if (i == vr1.size())
        return false;
    else
        return vr1[i] > vr2[i];
}

/* Compares two vectors of ranks (equality).*/
inline bool operator==(vector<Rank>& vr1, vector<Rank>& vr2) {
    if (vr1.size() != vr2.size()) {
        throw PokerEntityException(vector_rank_comparison_error_msg);
    }
    for (int i = 0; i < vr1.size(); i++)
        if (vr1[i] != vr2[i])
            return false;
    return true;
}

/* Compares two hands according to Poker rules */
inline bool Hand::operator>(Hand& hand) {
    auto p1 = highestSpecialHand(*this);
    auto p2 = highestSpecialHand(hand);
    if (p1.first != p1.first)
        return p1.first > p2.first;
    else {
        return p2.second > p2.second;
    }
}

/* Compares two hands according to Poker rules (equality) */
inline bool Hand::operator==(Hand& hand)
{
    auto p1 = highestSpecialHand(*this);
    auto p2 = highestSpecialHand(hand);
    return p1.first == p2.first && p1.second == p2.second;
}
