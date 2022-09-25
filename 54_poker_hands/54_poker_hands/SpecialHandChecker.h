#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "Hand.h"

namespace poker_hands {

    enum SpecialHand
    {
        kHighCard,
        kOnePair,
        kTwoPair,
        kThreeOfKind,
        kStraight,
        kFlush,
        kFullHouse,
        kFourOfKind,
        kStraightFlush,
        kRoyalFlush,
        kSpecialHandLast
    };

    class SpecialHandChecker
    {
    public:
        virtual SpecialHand HandType() = 0;
        virtual std::vector<Rank> Check(Hand& hand) = 0;

        // Counts each rank_ in the hand
        std::unordered_map<Rank, int> CountRanks(Hand& hand);
    };

    class HighCardChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kHighCard; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class PairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kOnePair; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class TwoPairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kTwoPair; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class ThreeOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kThreeOfKind; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class StraightChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kStraight; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class FlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kFlush; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class FullHouseChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kFullHouse; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class FourOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kFourOfKind; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class StraightFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kStraightFlush; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

    class RoyalFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() { return SpecialHand::kRoyalFlush; }
        virtual std::vector<Rank> Check(Hand& hand);
    };

}
