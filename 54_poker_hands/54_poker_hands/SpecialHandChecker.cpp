#include "SpecialHandChecker.h"

namespace poker_hands {

    std::unordered_map<Rank, int> SpecialHandChecker::CountRanks(Hand& hand) {
        std::unordered_map<Rank, int> rank_count;
        for (Card& c : hand.cards_) {
            if (rank_count.find(c.rank_) == rank_count.end()) {
                rank_count.insert({ c.rank_, 1 });
            }
            else {
                rank_count[c.rank_]++;
            }
        }
        return rank_count;
    }

    std::vector<Rank> HighCardChecker::Check(Hand& hand) {
        std::vector<Rank> vr;
        for (Card& c : hand.cards_)
            vr.push_back(c.rank_);
        return vr;
    }

    std::vector<Rank> PairChecker::Check(Hand& hand) {
        Rank pair_rank;
        int pair_pos;
        bool found_pair = false;
        for (int i = 0; i < Hand::kNumberOfCardsInHand - 1; i++) {
            if (hand.cards_[i].rank_ == hand.cards_[i + 1].rank_) {
                pair_rank = hand.cards_[i].rank_;
                pair_pos = i;
                found_pair = true;
            }
        }
        if (!found_pair) {
            return std::vector<Rank>();
        }
        else {
            // Add the rank_ of the pair
            std::vector<Rank> vr{ pair_rank };
            // Add the rest of the ranks, from the highest
            for (int i = 0; i < Hand::kNumberOfCardsInHand; i++)
                if (i != pair_pos && i != pair_pos + 1)
                    vr.push_back(hand.cards_[i].rank_);
            return vr;
        }
    }

    std::vector<Rank> TwoPairChecker::Check(Hand& hand) {
        std::vector<Rank> vr;
        for (int i = 0; i < Hand::kNumberOfCardsInHand - 1; i++) {
            if (hand.cards_[i].rank_ == hand.cards_[i + 1].rank_) {
                vr.push_back(hand.cards_[i].rank_);
            }
        }
        // If two distinct pairs where found
        if (vr.size() == 2 && vr[0] != vr[1]) {
            // triple_ranks contains sorted ranks of the two pairs,
            // add the remaining (kicker) ranks
            for (Card& c : hand.cards_)
                if (c.rank_ != vr[0] && c.rank_ != vr[1])
                    vr.push_back(c.rank_);
            return vr;
        }
        else {
            return std::vector<Rank>();
        }
    }

    std::vector<Rank> ThreeOfKindChecker::Check(Hand& hand) {
        std::vector<Rank> triple_ranks;
        for (int i = 0; i < Hand::kNumberOfCardsInHand - 2; i++) {
            if (hand.cards_[i].rank_ == hand.cards_[i + 1].rank_ &&
                hand.cards_[i + 1].rank_ == hand.cards_[i + 2].rank_) {
                triple_ranks.push_back(hand.cards_[i].rank_);
            }
        }
        // If exactly one triple was found
        if (triple_ranks.size() == 1) {
            for (Card& c : hand.cards_) {
                if (c.rank_ != triple_ranks[0]) {
                    triple_ranks.push_back(c.rank_);
                }
            }
            if (triple_ranks.size() == 3 && triple_ranks[1] != triple_ranks[2])
                return triple_ranks;
            else
                return std::vector<Rank>();
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> StraightChecker::Check(Hand& hand) {
        for (int i = 0; i < Hand::kNumberOfCardsInHand - 1; i++)
            if (hand.cards_[i].rank_ != hand.cards_[i + 1].rank_ + 1)
                return std::vector<Rank>();
        // return the highest rank_
        return { hand.cards_[0].rank_ };
    }

    std::vector<Rank> FlushChecker::Check(Hand& hand) {
        for (int i = 0; i < Hand::kNumberOfCardsInHand - 1; i++)
            if (hand.cards_[i].suit_ != hand.cards_[i + 1].suit_)
                return std::vector<Rank>();
        std::vector<Rank> vr;
        for (Card& c : hand.cards_)
            vr.push_back(c.rank_);
        return vr;
    }

    std::vector<Rank> FullHouseChecker::Check(Hand& hand) {
        std::unordered_map<Rank, int> rank_count = CountRanks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank triple_rank, pair_rank;
            for (auto rc : rank_count) {
                if (rc.second == 2)
                    pair_rank = rc.first;
                else if (rc.second == 3)
                    triple_rank = rc.first;
                else
                    // A rank_ has different count - not fullhouse
                    return std::vector<Rank>();
            }
            return { triple_rank, pair_rank };
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> FourOfKindChecker::Check(Hand& hand) {
        std::unordered_map<Rank, int> rank_count = CountRanks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank quadruple_rank, single_rank;
            for (auto rc : rank_count) {
                if (rc.second == 1)
                    single_rank = rc.first;
                else if (rc.second == 4)
                    quadruple_rank = rc.first;
                else
                    // A rank_ has different count - not four of kind
                    return std::vector<Rank>();
            }
            return { quadruple_rank, single_rank };
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> StraightFlushChecker::Check(Hand& hand) {
        if (FlushChecker().Check(hand) != std::vector<Rank>()) {
            return StraightChecker().Check(hand);
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> RoyalFlushChecker::Check(Hand& hand) {
        std::vector<Rank> straight_vr = StraightFlushChecker().Check(hand);
        if (straight_vr == std::vector<Rank>({ kAce })) {
            return straight_vr;
        }
        else
            return std::vector<Rank>();
    }

}
