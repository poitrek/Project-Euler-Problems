#include "pch.h"

using namespace poker_hands;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(CardTest, CardComparison1) {
	Card c1(Rank::kFive, Suit::kDiamonds);
	Card c2(Rank::kFour, Suit::kClubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(CardTest, CardComparisonEqual) {
	Card c1(Rank::kFive, Suit::kDiamonds);
	Card c2(c1);
	EXPECT_TRUE(c1 == c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_TRUE(c1 <= c2);
	EXPECT_FALSE(c1 != c2);
	EXPECT_FALSE(c1 > c2);
	EXPECT_FALSE(c1 < c2);
}

TEST(CardTest, CardComparisonEqualRanks) {
	Card c1(Rank::kJack, Suit::kHearts);
	Card c2(Rank::kJack, Suit::kClubs);
	EXPECT_TRUE(c1 > c2);
	EXPECT_TRUE(c1 >= c2);
	EXPECT_FALSE(c1 < c2);
	EXPECT_FALSE(c1 <= c2);
}

TEST(RankVectorTest, RankVectorComparison1) {
	std::vector<Rank> vr1 = {
		Rank::kFour, Rank::kEight,
		Rank::kQueen, Rank::kNine
	};
	std::vector<Rank> vr2 = {
		Rank::kFour, Rank::kEight,
		Rank::kQueen, Rank::kSeven
	};
	EXPECT_TRUE(vr1 > vr2);
	EXPECT_FALSE(vr1 == vr2);
	std::vector<Rank> vr3(vr1);
	EXPECT_TRUE(vr3 == vr1);
	EXPECT_FALSE(vr3 > vr1);
}

TEST(RankVectorTest, RankVectorComparison2) {
	std::vector<Rank> vr1{
		Rank::kFour, Rank::kEight,
		Rank::kQueen, Rank::kNine
	};
	std::vector<Rank> vr2{
		Rank::kFour, Rank::kEight,
		Rank::kQueen
	};
	EXPECT_THROW(vr1 == vr2, VectorComparisonError);
	EXPECT_THROW(vr1 > vr2, VectorComparisonError);
}

TEST(HandTest, HandSort1) {
	Hand h(Card(Rank::kJack, Suit::kClubs), Card(Rank::kSix, Suit::kHearts),
		Card(Rank::kThree, Suit::kHearts), Card(Rank::kKing, Suit::kDiamonds),
		Card(Rank::kTen, Suit::kSpades));
	EXPECT_TRUE(h.GetCards().front() == Card(Rank::kKing, Suit::kDiamonds));
	EXPECT_TRUE(h.GetCards().back() == Card(Rank::kThree, Suit::kHearts));
	// Compilation error: "const left-hand operand"
	//EXPECT_EQ(h.GetCards().back(), Card(Rank::kThree, Suit::kHearts));
}

TEST(HandTest, HandCodeRegex1) {
	EXPECT_TRUE(regex_match("5H KS 9C 7D 9H", Hand::kHandCodePattern));
	EXPECT_TRUE(regex_match(" 9S 9D 9C AC 3D ", Hand::kHandCodePattern));
	EXPECT_TRUE(regex_match("  6C	 QC 9S KD  JC  ", Hand::kHandCodePattern));
	EXPECT_TRUE(regex_match("aC ts 3c 3d 5c", Hand::kHandCodePattern));
}

TEST(HandTest, HandCodeRegex2) {
	EXPECT_FALSE(regex_match("5H KX 9C 7D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H KS 1C 7D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5HH KS 9C 7D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H KS 9C 7D", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H KS 9C 7D 9H JC", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H KS 9 7D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H KS 9C D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5H-KS 9C 7D 9H", Hand::kHandCodePattern));
	EXPECT_FALSE(regex_match("5HFKS 9C 7D 9H", Hand::kHandCodePattern));
}

TEST(HandTest, HandInitFromCode1) {
	EXPECT_TRUE(Hand("KS JC 9C 5D 2H") ==
		Hand(Card(kKing, kSpades), Card(kJack, kClubs),
			Card(kNine, kClubs), Card(kFive, kDiamonds),
			Card(kTwo, kHearts)));
}

TEST(HandCheckerTest, HighCardChecker1) {
	Hand h("9C 5D KS 2H JC");
	EXPECT_TRUE(HighCardChecker().Check(h) ==
		std::vector<Rank>({ kKing, kJack, kNine, kFive, kTwo }));
}

TEST(HandCheckerTest, PairChecker1) {
	Hand h("6D 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().Check(h),
		std::vector<Rank>({ kSix, kJack, kFour, kTwo }));
}

TEST(HandCheckerTest, PairChecker2) {
	Hand h("QD 2H JC 6H 4C");
	EXPECT_EQ(PairChecker().Check(h),
		std::vector<Rank>());
}

TEST(HandCheckerTest, TwoPairChecker1) {
	Hand h("KC 3S TH KS 3D");
	EXPECT_EQ(TwoPairChecker().Check(h),
		std::vector<Rank>({ kKing, kThree, kTen }));
}

TEST(HandCheckerTest, TwoPairChecker2) {
	Hand h1("KC 3S TH QS 3D");
	Hand h2("KC KD KS TH 3D");
	EXPECT_EQ(TwoPairChecker().Check(h1), std::vector<Rank>());
	EXPECT_EQ(TwoPairChecker().Check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, ThreeofKindChecker1) {
	Hand h("2S QC QD TC QH");
	EXPECT_EQ(ThreeOfKindChecker().Check(h),
		std::vector<Rank>({ kQueen, kTen, kTwo }));
}

TEST(HandCheckerTest, ThreeofKindChecker2) {
	Hand h1("AS 6C QD 2C TH");
	Hand h2("2S QC QD 2C QH");
	Hand h3("2S 3C QD 2C QH");
	Hand h4("QS QC QD 2C QH");
	EXPECT_EQ(ThreeOfKindChecker().Check(h1), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().Check(h2), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().Check(h3), std::vector<Rank>());
	EXPECT_EQ(ThreeOfKindChecker().Check(h4), std::vector<Rank>());
}

TEST(HandCheckerTest, StraightChecker1) {
	Hand h1("7D 8C 9C TS JD");
	Hand h2("7D 8C 9C TS QD");
	EXPECT_EQ(StraightChecker().Check(h1),
		std::vector<Rank> { kJack });
	EXPECT_EQ(StraightChecker().Check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, FlushChecker1) {
	Hand h1("7D 9D 3D AD 4D");
	Hand h2("7C 9D 3D AD 4D");
	EXPECT_EQ(FlushChecker().Check(h1),
		std::vector<Rank> ({ kAce, kNine, kSeven, kFour, kThree }));
	EXPECT_EQ(FlushChecker().Check(h2), std::vector<Rank>());
}

TEST(HandCheckerTest, FullHouseChecker1) {
	Hand h1("6C 6D 6S JS JC");
	Hand h2("6C 6D 6S 6H JS");
	Hand h3("6C 6D JS JC AD");
	Hand h4("6C 6D 6S 9D 8H");
	EXPECT_EQ(FullHouseChecker().Check(h1),
		std::vector<Rank>({ kSix, kJack }));
	EXPECT_EQ(FullHouseChecker().Check(h2), std::vector<Rank>());
	EXPECT_EQ(FullHouseChecker().Check(h3), std::vector<Rank>());
	EXPECT_EQ(FullHouseChecker().Check(h4), std::vector<Rank>());
}

TEST(HandCheckerTest, FourOfKindChecker1) {
	Hand h1("6C 6D 6S 6H JS");
	Hand h2("6C 6D 6S JS JC");
	Hand h3("6C 6D 6S 9D 8H");
	EXPECT_EQ(FourOfKindChecker().Check(h1),
		std::vector<Rank>({ kSix, kJack }));
	EXPECT_EQ(FourOfKindChecker().Check(h2), std::vector<Rank>());
	EXPECT_EQ(FourOfKindChecker().Check(h3), std::vector<Rank>());
}


TEST(HandCheckerTest, StraightFlushChecker1) {
	Hand h1("7C 8C 9C TC JC");
	Hand h2("7C 8C 9D TC JC");
	Hand h3("7C 8C TC JC QC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(StraightFlushChecker().Check(h1),
		std::vector<Rank>({ kJack }));
	EXPECT_EQ(StraightFlushChecker().Check(h2), std::vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().Check(h3), std::vector<Rank>());
	EXPECT_EQ(StraightFlushChecker().Check(h4), std::vector<Rank>());
}


TEST(HandCheckerTest, RoyalFlushChecker1) {
	Hand h1("TC JC QC KC AC");
	Hand h2("7C 8C 9C TC JC");
	Hand h3("TC JD QC KC AC");
	Hand h4("6C 5D 6S 9D 8H");
	EXPECT_EQ(RoyalFlushChecker().Check(h1),
		std::vector<Rank>({ kAce }));
	EXPECT_EQ(RoyalFlushChecker().Check(h2), std::vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().Check(h3), std::vector<Rank>());
	EXPECT_EQ(RoyalFlushChecker().Check(h4), std::vector<Rank>());
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
		{ SpecialHand::kHighCard, {kAce, kQueen, kTen, kEight, kFive}},
		{ SpecialHand::kOnePair, {kEight, kFour, kThree, kTwo}},
		{ SpecialHand::kTwoPair, {kQueen, kFour, kEight}},
		{ SpecialHand::kThreeOfKind, {kQueen, kTen, kTwo}},
		{ SpecialHand::kStraight, {kEight}},
		{ SpecialHand::kFlush, {kKing, kQueen, kEight, kFour, kTwo}},
		{ SpecialHand::kFullHouse, {kFive, kJack}},
		{ SpecialHand::kFourOfKind, {kTen, kSeven}},
		{ SpecialHand::kStraightFlush, {kEight}},
		{ SpecialHand::kRoyalFlush, {kAce}}
	};
	for (int i = 0; i < hands.size(); i++) {
		EXPECT_EQ(hands[i].HighestSpecialHand(), highest_special_hands[i]);
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
//	Card c(Rank::kFive, Suit::kClubs);
//	Hand h("JS 9C 7S KH 4C");
//	EXPECT_THROW(c > h, PokerException);
//	EXPECT_THROW(c <= h, PokerException);
//	EXPECT_THROW(h == c, PokerException);
//	EXPECT_THROW(h != c, PokerException);
//}
