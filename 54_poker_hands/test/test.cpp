#include "pch.h"
//#include "54_poker_hands.hpp"
//extern const std::regex Hand::Hand::hand_code_pattern;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(CardTest, CardComparison1) {
	Card c1(RankType::Five, SuitType::Diamonds);
	Card c2(RankType::Four, SuitType::Clubs);
	EXPECT_TRUE(c1 > &c2);
	EXPECT_TRUE(c1 >= &c2);
	EXPECT_FALSE(c1 < &c2);
	EXPECT_FALSE(c1 <= &c2);
}

TEST(CardTest, CardComparisonEqual) {
	Card c1(RankType::Five, SuitType::Diamonds);
	Card c2(c1);
	EXPECT_TRUE(c1 == &c2);
	EXPECT_TRUE(c1 >= &c2);
	EXPECT_TRUE(c1 <= &c2);
	EXPECT_FALSE(c1 != &c2);
	EXPECT_FALSE(c1 > &c2);
	EXPECT_FALSE(c1 < &c2);
}

TEST(CardTest, CardComparisonEqualRanks) {
	Card c1(RankType::Jack, SuitType::Hearts);
	Card c2(RankType::Jack, SuitType::Clubs);
	EXPECT_TRUE(c1 > &c2);
	EXPECT_TRUE(c1 >= &c2);
	EXPECT_FALSE(c1 < &c2);
	EXPECT_FALSE(c1 <= &c2);
}

TEST(RankVectorTest, RankVectorComparison1) {
	vector<Rank> vr1 = {
		Rank(RankType::Four), Rank(RankType::Eight),
		Rank(RankType::Queen), Rank(RankType::Nine)
	};
	vector<Rank> vr2 = {
		Rank(RankType::Four), Rank(RankType::Eight),
		Rank(RankType::Queen), Rank(RankType::Seven)
	};
	EXPECT_TRUE(vr1 > vr2);
	EXPECT_FALSE(vr1 == vr2);
	vector<Rank> vr3(vr1);
	EXPECT_TRUE(vr3 == vr1);
	EXPECT_FALSE(vr3 > vr1);
}

TEST(RankVectorTest, RankVectorComparison2) {
	vector<Rank> vr1{
		Rank(RankType::Four), Rank(RankType::Eight),
		Rank(RankType::Queen), Rank(RankType::Nine)
	};
	vector<Rank> vr2{
		Rank(RankType::Four), Rank(RankType::Eight),
		Rank(RankType::Queen)
	};
	EXPECT_THROW(vr1 == vr2, PokerEntityException);
	EXPECT_THROW(vr1 > vr2, PokerEntityException);
}

TEST(HandTest, HandSort1) {
	Hand h(Card(RankType::Jack, SuitType::Clubs), Card(RankType::Six, SuitType::Hearts),
		Card(RankType::Three, SuitType::Hearts), Card(RankType::King, SuitType::Diamonds),
		Card(RankType::Ten, SuitType::Spades));
	EXPECT_TRUE(h.cards.front() == &Card(RankType::King, SuitType::Diamonds));
	EXPECT_TRUE(h.cards.back() == &Card(RankType::Three, SuitType::Hearts));
	//EXPECT_EQ(h.cards.front(), &Card(RankType::King, SuitType::Diamonds));
	//EXPECT_EQ(h.cards.back(), &Card(RankType::Three, SuitType::Hearts));
}

//string card_code_pattern_string = "[23456789TJQKAtjqka][CDHScdhs]";
//regex hand_code_pattern = regex("\\s*(?:(" + card_code_pattern_string + ")\\s+){4}(" + card_code_pattern_string + ")\\s*");

TEST(HandTest, HandCodeRegex1) {
	EXPECT_TRUE(regex_match("5H KS 9C 7D 9H", Hand::hand_code_pattern));
	EXPECT_TRUE(regex_match(" 9S 9D 9C AC 3D ", Hand::hand_code_pattern));
	EXPECT_TRUE(regex_match("  6C	 QC 9S KD  JC  ", Hand::hand_code_pattern));
	EXPECT_TRUE(regex_match("aC ts 3c 3d 5c", Hand::hand_code_pattern));
}

TEST(HandTest, HandCodeRegex2) {
	EXPECT_FALSE(regex_match("5H KX 9C 7D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H KS 1C 7D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5HH KS 9C 7D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H KS 9C 7D", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H KS 9C 7D 9H JC", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H KS 9 7D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H KS 9C D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5H-KS 9C 7D 9H", Hand::hand_code_pattern));
	EXPECT_FALSE(regex_match("5HFKS 9C 7D 9H", Hand::hand_code_pattern));
}

TEST(HandTest, HandInitFromCode1) {
	EXPECT_TRUE(Hand("KS JC 9C 5D 2H") ==
		Hand(Card(King, Spades), Card(Jack, Clubs),
			Card(Nine, Clubs), Card(Five, Diamonds),
			Card(Two, Hearts)));
}