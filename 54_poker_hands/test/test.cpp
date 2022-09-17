#include "pch.h"
//#include "54_poker_hands.hpp"
//extern const std::regex Hand::Hand::hand_code_pattern;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(CardTest, CardComparison1) {
	Card c1(Rank::Five, Suit::Diamonds);
	Card c2(Rank::Four, Suit::Clubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(CardTest, CardComparisonEqual) {
	Card c1(Rank::Five, Suit::Diamonds);
	Card c2(c1);
	EXPECT_TRUE(c1 == c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_TRUE(c1 <= c2);
	EXPECT_FALSE(c1 != c2);
	EXPECT_FALSE(c1 > c2);
	EXPECT_FALSE(c1 < c2);
}

TEST(CardTest, CardComparisonEqualRanks) {
	Card c1(Rank::Jack, Suit::Hearts);
	Card c2(Rank::Jack, Suit::Clubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(RankVectorTest, RankVectorComparison1) {
	vector<Rank> vr1 = {
		Rank::Four, Rank::Eight,
		Rank::Queen, Rank::Nine
	};
	vector<Rank> vr2 = {
		Rank::Four, Rank::Eight,
		Rank::Queen, Rank::Seven
	};
	EXPECT_TRUE(vr1 > vr2);
	EXPECT_FALSE(vr1 == vr2);
	vector<Rank> vr3(vr1);
	EXPECT_TRUE(vr3 == vr1);
	EXPECT_FALSE(vr3 > vr1);
}

TEST(RankVectorTest, RankVectorComparison2) {
	vector<Rank> vr1{
		Rank::Four, Rank::Eight,
		Rank::Queen, Rank::Nine
	};
	vector<Rank> vr2{
		Rank::Four, Rank::Eight,
		Rank::Queen
	};
	EXPECT_THROW(vr1 == vr2, PokerException);
	EXPECT_THROW(vr1 > vr2, PokerException);
}

TEST(HandTest, HandSort1) {
	Hand h(Card(Rank::Jack, Suit::Clubs), Card(Rank::Six, Suit::Hearts),
		Card(Rank::Three, Suit::Hearts), Card(Rank::King, Suit::Diamonds),
		Card(Rank::Ten, Suit::Spades));
	EXPECT_TRUE(h.cards.front() == Card(Rank::King, Suit::Diamonds));
	EXPECT_TRUE(h.cards.back() == Card(Rank::Three, Suit::Hearts));
	// Compilation error: "const left-hand operand"
	//EXPECT_EQ(h.cards.back(), Card(Rank::Three, Suit::Hearts));
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

TEST(CheckerTest, HighCardChecker1) {
	Hand h("9C 5D KS 2H JC");
	EXPECT_TRUE(HighCardChecker().check(h) ==
		vector<Rank>({ King, Jack, Nine, Five, Two }));
}

TEST(CheckerTest, PairChecker1) {
	Hand h("6D 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().check(h),
		vector<Rank>({ Six, Jack, Four, Two }));
}

TEST(CheckerTest, PairChecker2) {
	Hand h("QD 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().check(h),
		vector<Rank>());
}

TEST(CheckerTest, TwoPairChecker1) {
	Hand h("KC 3S TH KS 3D");
	EXPECT_EQ(TwoPairChecker().check(h),
		vector<Rank>({ King, Three, Ten }));
}

TEST(CheckerTest, TwoPairChecker2) {
	Hand h1("KC 3S TH QS 3D");
	Hand h2("KC KD KS TH 3D");
	EXPECT_EQ(TwoPairChecker().check(h1), vector<Rank>());
	EXPECT_EQ(TwoPairChecker().check(h2), vector<Rank>());
}

TEST(CheckerTest, ThreeofKindChecker1) {
	Hand h("2S QC QD TC QH");
	EXPECT_EQ(ThreeOfKindChecker().check(h),
		vector<Rank>({ Queen, Ten, Two }));
}

TEST(CheckerTest, ThreeofKindChecker2) {
	Hand h1("AS 6C QD 2C TH");
	Hand h2("2S QC QD 2C QH");
	Hand h3("2S 3C QD 2C QH");
	Hand h4("QS QC QD 2C QH");
	EXPECT_EQ(ThreeOfKindChecker().check(h1), vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h2), vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h3), vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h4), vector<Rank>());
}

TEST(CheckerTest, StraightChecker1) {
	Hand h1("7D 8C 9C TS JD");
	Hand h2("7D 8C 9C TS QD");
	EXPECT_EQ(StraightChecker().check(h1),
		vector<Rank> { Jack });
	EXPECT_EQ(StraightChecker().check(h2), vector<Rank>());
}

TEST(CheckerTest, FlushChecker1) {
	Hand h1("7D 9D 3D AD 4D");
	Hand h2("7C 9D 3D AD 4D");
	EXPECT_EQ(FlushChecker().check(h1),
		vector<Rank> ({ Ace, Nine, Seven, Four, Three }));
	EXPECT_EQ(FlushChecker().check(h2), vector<Rank>());
}

TEST(CheckerTest, FullHouseChecker1) {
	Hand h1("6C 6D 6S JS JC");
	Hand h2("6C 6D 6S 6H JS");
	Hand h3("6C 6D JS JC AD");
	Hand h4("6C 6D 6S 9D 8H");
	EXPECT_EQ(FullHouseChecker().check(h1),
		vector<Rank>({ Six, Jack }));
	EXPECT_EQ(FullHouseChecker().check(h2), vector<Rank>());
	EXPECT_EQ(FullHouseChecker().check(h3), vector<Rank>());
	EXPECT_EQ(FullHouseChecker().check(h4), vector<Rank>());
}

TEST(CheckerTest, FourOfKindChecker1) {
	Hand h1("6C 6D 6S 6H JS");
	Hand h2("6C 6D 6S JS JC");
	Hand h3("6C 6D 6S 9D 8H");
	EXPECT_EQ(FourOfKindChecker().check(h1),
		vector<Rank>({ Six, Jack }));
	EXPECT_EQ(FourOfKindChecker().check(h2), vector<Rank>());
	EXPECT_EQ(FourOfKindChecker().check(h3), vector<Rank>());
}


TEST(CheckerTest, StraightFlushChecker1) {
	Hand h1("7C 8C 9C TC JC");
	Hand h2("7C 8C 9D TC JC");
	Hand h3("7C 8C TC JC QC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(StraightFlushChecker().check(h1),
		vector<Rank>({ Jack }));
	EXPECT_EQ(StraightFlushChecker().check(h2), vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().check(h3), vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().check(h4), vector<Rank>());
}


TEST(CheckerTest, RoyalFlushChecker1) {
	Hand h1("TC JC QC KC AC");
	Hand h2("7C 8C 9C TC JC");
	Hand h3("TC JD QC KC AC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(RoyalFlushChecker().check(h1),
		vector<Rank>({ Ace }));
	EXPECT_EQ(RoyalFlushChecker().check(h2), vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().check(h3), vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().check(h4), vector<Rank>());
}

TEST(HandTest, HighestSpecialHand1) {
	vector<Hand> hands = {
		Hand("TS 8H QD AC 5C"),
		Hand("3C 2D 8H 8C 4D"),
		Hand("4S 8H 4C QD QC"),
		Hand("2S QC QD TC QH"),
		Hand("4D 5C 6C 7H 8H"),
		Hand("2C QC KC 8C 4C"),
		Hand("5C JS JD 5D 5H"),
		Hand("TH TC TD 7D TS"),
		Hand("4D 5D 6D 7D 8D"),
		Hand("QS KS AS TS JS")
	};
	vector <pair<SpecialHand, vector<Rank>>> highest_special_hands = {
		{ SpecialHand::HighCard, {Ace, Queen, Ten, Eight, Five}},
		{ SpecialHand::Pair, {Eight, Four, Three, Two}},
		{ SpecialHand::TwoPair, {Queen, Four, Eight}},
		{ SpecialHand::ThreeOfKind, {Queen, Ten, Two}},
		{ SpecialHand::Straight, {Eight}},
		{ SpecialHand::Flush, {King, Queen, Eight, Four, Two}},
		{ SpecialHand::FullHouse, {Five, Jack}},
		{ SpecialHand::FourOfKind, {Ten, Seven}},
		{ SpecialHand::StraightFlush, {Eight}},
		{ SpecialHand::RoyalFlush, {Ace}}
	};
	for (int i = 0; i < hands.size(); i++) {
		EXPECT_EQ(hands[i].highestSpecialHand(), highest_special_hands[i]);
	}
}

TEST(HandTest, HandComparison1) {
	// Pair vs HighCard
	EXPECT_TRUE(Hand("4D 6C 9H 9C 3D") > Hand("AC QD 2D 4H 5H"));
	// ThreeOfKind vs Pair
	EXPECT_TRUE(Hand("2D 2C 7H 2D JD") > Hand("4D 6C 9H 9C 3D"));
	// Flush vs ThreeOfKind
	EXPECT_TRUE(Hand("3C JC KC 9C 7C") > Hand("2D 2C 7H 2D JD"));
}

TEST(HandTest, HandComparison2) {
	// Pair
	EXPECT_TRUE(Hand("AC QD 2D 4H 5H") > Hand("AC TD 2D 4H 5H"));
	// TwoPair
	EXPECT_TRUE(Hand("QC QD 6D 6H 5H") > Hand("QC QD 6D 6H 3H"));
	// Identical
	EXPECT_TRUE(Hand("AC QD 2D 4H 5H") == Hand("AC QD 2D 4H 5H"));
}

TEST(HandTest, HandComparison3) {
	EXPECT_TRUE(Hand("7S 7D 9H 5C 2D") == Hand("7D 7H 9S 5D 2S"));
	EXPECT_TRUE(Hand("7S 7D 9H 9C 9D") == Hand("7D 7H 9S 9D 9S"));
	EXPECT_TRUE(Hand("JS KS 2S 9S 3S") == Hand("JC KC 2C 9C 3C"));
	EXPECT_TRUE(Hand("4D 5S 6C 7D 8H") == Hand("4C 5D 6D 7C 8S"));
}
