#include "54_poker_hands.hpp"

//bool compareHands(Hand &hand1, Hand &hand2) {
//    // prototype
//}


int main()
{
    Hand h1(Card(RankType::Jack, SuitType::Clubs), Card(RankType::Six, SuitType::Hearts),
        Card(RankType::Three, SuitType::Hearts), Card(RankType::King, SuitType::Diamonds),
        Card(RankType::Ten, SuitType::Spades));
    //h1.sort("descending");
    return 0;
}