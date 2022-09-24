#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "Hand.h"

namespace poker_hands {

    enum SpecialHand
    {
        highCard,
        onePair,
        twoPair,
        threeOfKind,
        straight,
        flush,
        fullHouse,
        fourOfKind,
        straightFlush,
        royalFlush,
        last
    };

    class SpecialHandChecker
    {
    public:
        // const SpecialHand hand_type;
        virtual SpecialHand handType() = 0;
        virtual std::vector<Rank> check(Hand& hand) = 0;

        // Counts each rank in the hand
        std::unordered_map<Rank, int> count_ranks(Hand& hand);
    };

    class HighCardChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::highCard; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class PairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::onePair; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class TwoPairChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::twoPair; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class ThreeOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::threeOfKind; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class StraightChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::straight; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class FlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::flush; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class FullHouseChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::fullHouse; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class FourOfKindChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::fourOfKind; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class StraightFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::straightFlush; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    class RoyalFlushChecker : public SpecialHandChecker {
    public:
        virtual SpecialHand handType() { return SpecialHand::royalFlush; }
        virtual std::vector<Rank> check(Hand& hand);
    };

    static std::vector<std::shared_ptr<SpecialHandChecker>> handCheckers = {
        std::shared_ptr<HighCardChecker>(new HighCardChecker),
        std::shared_ptr<PairChecker>(new PairChecker),
        std::shared_ptr<TwoPairChecker>(new TwoPairChecker),
        std::shared_ptr<ThreeOfKindChecker>(new ThreeOfKindChecker),
        std::shared_ptr<StraightChecker>(new StraightChecker),
        std::shared_ptr<FlushChecker>(new FlushChecker),
        std::shared_ptr<FullHouseChecker>(new FullHouseChecker),
        std::shared_ptr<FourOfKindChecker>(new FourOfKindChecker),
        std::shared_ptr<StraightFlushChecker>(new StraightFlushChecker),
        std::shared_ptr<RoyalFlushChecker>(new RoyalFlushChecker),
    };

}
