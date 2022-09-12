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

enum SuitType
{
    _Suit_None,
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

enum RankType
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
    virtual bool operator>(Entity* e) = 0;
    virtual bool operator==(Entity* e) = 0;
    virtual bool operator>=(Entity* e)
    {
        return (*this) > e || (*this) == e;
    }
    virtual bool operator<(Entity* e)
    {
        return !(*this >= e);
    }
    virtual bool operator<=(Entity* e)
    {
        return !(*this > e);
    }
    virtual bool operator!=(Entity* e)
    {
        return !(*this == e);
    }
};

class Card : public Entity
{
public:
    inline static const unordered_map<char, RankType> rank_codes = {
        {'2', RankType::Two},
        {'3', RankType::Three},
        {'4', RankType::Four},
        {'5', RankType::Five},
        {'6', RankType::Six},
        {'7', RankType::Seven},
        {'8', RankType::Eight},
        {'9', RankType::Nine},
        {'T', RankType::Ten},
        {'J', RankType::Jack},
        {'Q', RankType::Queen},
        {'K', RankType::King},
        {'A', RankType::Ace}
    };
    inline static const unordered_map<char, SuitType> suit_codes = {
        {'C', SuitType::Clubs},
        {'D', SuitType::Diamonds},
        {'H', SuitType::Hearts},
        {'S', SuitType::Spades}
    };
    RankType rank;
    SuitType suit;
    Card() {
        rank = RankType::_Rank_None;
        suit = SuitType::_Suit_None;
    }
    Card(const string& card_code) {
        rank = Card::rank_codes.at(card_code[0]);
        suit = Card::suit_codes.at(card_code[1]);
    }
    Card(RankType rank, SuitType suit)
        : rank(rank), suit(suit) {}
    virtual bool operator>(Entity* e) {
        if (Card* c = dynamic_cast<Card*>(e)) {
            return this->rank > c->rank || (this->rank == c->rank && this->suit > c->suit);
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
        // throw EntityTypeException("")
    }
    virtual bool operator==(Entity* e) {
        if (Card* c = dynamic_cast<Card*>(e)) {
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

//const unordered_map<char, RankType> Card::rank_codes = {
//    {'2', RankType::Two},
//    {'3', RankType::Three},
//    {'4', RankType::Four},
//    {'5', RankType::Five},
//    {'6', RankType::Six},
//    {'7', RankType::Seven},
//    {'8', RankType::Eight},
//    {'9', RankType::Nine},
//    {'T', RankType::Ten},
//    {'J', RankType::Jack},
//    {'Q', RankType::Queen},
//    {'K', RankType::King},
//    {'A', RankType::Ace}
//};

//const unordered_map<char, SuitType> Card::suit_codes = {
//    {'C', SuitType::Clubs},
//    {'D', SuitType::Diamonds},
//    {'H', SuitType::Hearts},
//    {'S', SuitType::Spades}
//};

class Suit : public Entity {
public:
    SuitType suit_type;
    Suit(SuitType suit_type) : suit_type(suit_type) {}
    virtual bool operator>(Entity* e) {
        if (Suit* s = dynamic_cast<Suit*>(e)) {
            return this->suit_type > s->suit_type;
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
    }
    virtual bool operator==(Entity* e) {
        if (Suit* s = dynamic_cast<Suit*>(e)) {
            return this->suit_type == s->suit_type;
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
    }
};

class Rank : public Entity {
public:
    RankType rank_type;
    Rank(RankType rank_type) : rank_type(rank_type) {}
    virtual bool operator>(Entity* e) {
        if (Rank* r = dynamic_cast<Rank*>(e)) {
            return this->rank_type > r->rank_type;
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
    }
    virtual bool operator==(Entity* e) {
        if (Rank* r = dynamic_cast<Rank*>(e)) {
            return this->rank_type == r->rank_type;
        }
        else {
            throw PokerEntityException(entity_comparison_error_msg);
        }
    }
};

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
                return c1 > &c2;
                });
        }
        else {
            // "ascending"
            std::sort(cards.begin(), cards.end(), [](Card& c1, Card& c2) -> bool {
                return c1 < &c2;
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
        RankType pair_rank = RankType::_Rank_None;
        int pair_pos;
        for (int i = 0; i < 4; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank) {
                pair_rank = hand.cards[i].rank;
                pair_pos = i;
            }
        }
        if (pair_rank == RankType::_Rank_None) {
            return vector<Rank>();
        }
        else {
            // Add the rank of the pair
            vector<Rank> vr{ Rank(pair_rank) };
            // Add the rest of the ranks, from the highest
            for (int i = 0; i < 5; i++)
                if (i != pair_pos && i != pair_pos + 1)
                    vr.push_back(Rank(hand.cards[i].rank));
            return vr;
        }
    }
};

class TwoPairChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::TwoPair; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class ThreeOfKindChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::ThreeOfKind; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class StraightChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::Straight; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class FlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::Flush; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class FullHouseChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::FullHouse; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class FourOfKindChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::FourOfKind; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class StraightFlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::StraightFlush; }
    virtual vector<Rank> check(Hand& hand) {
        return vector<Rank>();
    }
};

class RoyalFlushChecker : public SpecialHandChecker {
public:
    virtual SpecialHand handType() { return SpecialHand::RoyalFlush; }
    virtual vector<Rank> check(Hand& hand) {
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
        if (!check_result.empty()) {
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
    while (i < vr1.size() && vr1[i] == &vr2[i])
        i++;
    if (i == vr1.size())
        return false;
    else
        return vr1[i] > &vr2[i];
}

/* Compares two vectors of ranks (equality).*/
inline bool operator==(vector<Rank>& vr1, vector<Rank>& vr2) {
    if (vr1.size() != vr2.size()) {
        throw PokerEntityException(vector_rank_comparison_error_msg);
    }
    for (int i = 0; i < vr1.size(); i++)
        if (vr1[i] != &vr2[i])
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
