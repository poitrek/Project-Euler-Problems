#include "pch.h"

using namespace poker_hands;
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(CardTest, CardComparison1) {
	Card c1(Rank::five, Suit::diamonds);
	Card c2(Rank::four, Suit::clubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(CardTest, CardComparisonEqual) {
	Card c1(Rank::five, Suit::diamonds);
	Card c2(c1);
	EXPECT_TRUE(c1 == c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_TRUE(c1 <= c2);
	EXPECT_FALSE(c1 != c2);
	EXPECT_FALSE(c1 > c2);
	EXPECT_FALSE(c1 < c2);
}

TEST(CardTest, CardComparisonEqualRanks) {
	Card c1(Rank::jack, Suit::hearts);
	Card c2(Rank::jack, Suit::clubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(RankVectorTest, RankVectorComparison1) {
	std::vector<Rank> vr1 = {
		Rank::four, Rank::eight,
		Rank::queen, Rank::nine
	};
	std::vector<Rank> vr2 = {
		Rank::four, Rank::eight,
		Rank::queen, Rank::seven
	};
	EXPECT_TRUE(vr1 > vr2);
	EXPECT_FALSE(vr1 == vr2);
	std::vector<Rank> vr3(vr1);
	EXPECT_TRUE(vr3 == vr1);
	EXPECT_FALSE(vr3 > vr1);
}

TEST(RankVectorTest, RankVectorComparison2) {
	std::vector<Rank> vr1{
		Rank::four, Rank::eight,
		Rank::queen, Rank::nine
	};
	std::vector<Rank> vr2{
		Rank::four, Rank::eight,
		Rank::queen
	};
	EXPECT_THROW(vr1 == vr2, PokerException);
	EXPECT_THROW(vr1 > vr2, PokerException);
}

TEST(HandTest, HandSort1) {
	Hand h(Card(Rank::jack, Suit::clubs), Card(Rank::six, Suit::hearts),
		Card(Rank::three, Suit::hearts), Card(Rank::king, Suit::diamonds),
		Card(Rank::ten, Suit::spades));
	EXPECT_TRUE(h.cards.front() == Card(Rank::king, Suit::diamonds));
	EXPECT_TRUE(h.cards.back() == Card(Rank::three, Suit::hearts));
	// Compilation error: "const left-hand operand"
	//EXPECT_EQ(h.cards.back(), Card(Rank::three, Suit::hearts));
}

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
		Hand(Card(king, spades), Card(jack, clubs),
			Card(nine, clubs), Card(five, diamonds),
			Card(two, hearts)));
}

TEST(HandCheckerTest, HighCardChecker1) {
	Hand h("9C 5D KS 2H JC");
	EXPECT_TRUE(HighCardChecker().check(h) ==
		std::vector<Rank>({ king, jack, nine, five, two }));
}

TEST(HandCheckerTest, PairChecker1) {
	Hand h("6D 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().check(h),
		std::vector<Rank>({ six, jack, four, two }));
}

TEST(HandCheckerTest, PairChecker2) {
	Hand h("QD 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().check(h),
		std::vector<Rank>());
}

TEST(HandCheckerTest, TwoPairChecker1) {
	Hand h("KC 3S TH KS 3D");
	EXPECT_EQ(TwoPairChecker().check(h),
		std::vector<Rank>({ king, three, ten }));
}

TEST(HandCheckerTest, TwoPairChecker2) {
	Hand h1("KC 3S TH QS 3D");
	Hand h2("KC KD KS TH 3D");
	EXPECT_EQ(TwoPairChecker().check(h1), std::vector<Rank>());
	EXPECT_EQ(TwoPairChecker().check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, ThreeofKindChecker1) {
	Hand h("2S QC QD TC QH");
	EXPECT_EQ(ThreeOfKindChecker().check(h),
		std::vector<Rank>({ queen, ten, two }));
}

TEST(HandCheckerTest, ThreeofKindChecker2) {
	Hand h1("AS 6C QD 2C TH");
	Hand h2("2S QC QD 2C QH");
	Hand h3("2S 3C QD 2C QH");
	Hand h4("QS QC QD 2C QH");
	EXPECT_EQ(ThreeOfKindChecker().check(h1), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h2), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h3), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().check(h4), std::vector<Rank>());
}

TEST(HandCheckerTest, StraightChecker1) {
	Hand h1("7D 8C 9C TS JD");
	Hand h2("7D 8C 9C TS QD");
	EXPECT_EQ(StraightChecker().check(h1),
		std::vector<Rank> { jack });
	EXPECT_EQ(StraightChecker().check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, FlushChecker1) {
	Hand h1("7D 9D 3D AD 4D");
	Hand h2("7C 9D 3D AD 4D");
	EXPECT_EQ(FlushChecker().check(h1),
		std::vector<Rank> ({ ace, nine, seven, four, three }));
	EXPECT_EQ(FlushChecker().check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, FullHouseChecker1) {
	Hand h1("6C 6D 6S JS JC");
	Hand h2("6C 6D 6S 6H JS");
	Hand h3("6C 6D JS JC AD");
	Hand h4("6C 6D 6S 9D 8H");
	EXPECT_EQ(FullHouseChecker().check(h1),
		std::vector<Rank>({ six, jack }));
	EXPECT_EQ(FullHouseChecker().check(h2), std::vector<Rank>());
	EXPECT_EQ(FullHouseChecker().check(h3), std::vector<Rank>());
	EXPECT_EQ(FullHouseChecker().check(h4), std::vector<Rank>());
}

TEST(HandCheckerTest, FourOfKindChecker1) {
	Hand h1("6C 6D 6S 6H JS");
	Hand h2("6C 6D 6S JS JC");
	Hand h3("6C 6D 6S 9D 8H");
	EXPECT_EQ(FourOfKindChecker().check(h1),
		std::vector<Rank>({ six, jack }));
	EXPECT_EQ(FourOfKindChecker().check(h2), std::vector<Rank>());
	EXPECT_EQ(FourOfKindChecker().check(h3), std::vector<Rank>());
}


TEST(HandCheckerTest, StraightFlushChecker1) {
	Hand h1("7C 8C 9C TC JC");
	Hand h2("7C 8C 9D TC JC");
	Hand h3("7C 8C TC JC QC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(StraightFlushChecker().check(h1),
		std::vector<Rank>({ jack }));
	EXPECT_EQ(StraightFlushChecker().check(h2), std::vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().check(h3), std::vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().check(h4), std::vector<Rank>());
}


TEST(HandCheckerTest, RoyalFlushChecker1) {
	Hand h1("TC JC QC KC AC");
	Hand h2("7C 8C 9C TC JC");
	Hand h3("TC JD QC KC AC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(RoyalFlushChecker().check(h1),
		std::vector<Rank>({ ace }));
	EXPECT_EQ(RoyalFlushChecker().check(h2), std::vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().check(h3), std::vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().check(h4), std::vector<Rank>());
}

TEST(HandTest, HighestSpecialHand1) {
	std::vector<Hand> hands = {
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
	std::vector <std::pair<SpecialHand, std::vector<Rank>>> highest_special_hands = {
		{ SpecialHand::highCard, {ace, queen, ten, eight, five}},
		{ SpecialHand::onePair, {eight, four, three, two}},
		{ SpecialHand::twoPair, {queen, four, eight}},
		{ SpecialHand::threeOfKind, {queen, ten, two}},
		{ SpecialHand::straight, {eight}},
		{ SpecialHand::flush, {king, queen, eight, four, two}},
		{ SpecialHand::fullHouse, {five, jack}},
		{ SpecialHand::fourOfKind, {ten, seven}},
		{ SpecialHand::straightFlush, {eight}},
		{ SpecialHand::royalFlush, {ace}}
	};
	for (int i = 0; i < hands.size(); i++) {
		EXPECT_EQ(hands[i].highestSpecialHand(), highest_special_hands[i]);
	}
}

TEST(HandTest, HandComparison1) {
	// onePair vs highCard
	EXPECT_TRUE(Hand("4D 6C 9H 9C 3D") > Hand("AC QD 2D 4H 5H"));
	// threeOfKind vs onePair
	EXPECT_TRUE(Hand("2D 2C 7H 2D JD") > Hand("4D 6C 9H 9C 3D"));
	// flush vs threeOfKind
	EXPECT_TRUE(Hand("3C JC KC 9C 7C") > Hand("2D 2C 7H 2D JD"));
}

TEST(HandTest, HandComparison2) {
	// onePair
	EXPECT_TRUE(Hand("AC QD 2D 4H 5H") > Hand("AC TD 2D 4H 5H"));
	// twoPair
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

// With current model this should not compile

//TEST(ComparableTest, CardHandComparison) {
//	Card c(Rank::five, Suit::clubs);
//	Hand h("JS 9C 7S KH 4C");
//	EXPECT_THROW(c > h, PokerException);
//	EXPECT_THROW(c <= h, PokerException);
//	EXPECT_THROW(h == c, PokerException);
//	EXPECT_THROW(h != c, PokerException);
//}
