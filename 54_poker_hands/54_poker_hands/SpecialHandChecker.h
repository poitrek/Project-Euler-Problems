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
        virtual std::vector<Rank> Check(const Hand& hand) = 0;

        // Counts each rank_ in the hand
        std::unordered_map<Rank, int> CountRanks(const Hand& hand);
    };

    class HighCardChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kHighCard; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class PairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kOnePair; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class TwoPairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kTwoPair; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class ThreeOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kThreeOfKind; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class StraightChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kStraight; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class FlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kFlush; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class FullHouseChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kFullHouse; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class FourOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kFourOfKind; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class StraightFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kStraightFlush; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

    class RoyalFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand HandType() override { return SpecialHand::kRoyalFlush; }
        virtual std::vector<Rank> Check(const Hand& hand) override;
    };

}
