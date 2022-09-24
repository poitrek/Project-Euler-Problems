#include "SpecialHandChecker.h"

namespace poker_hands {

    std::unordered_map<Rank, int> SpecialHandChecker::count_ranks(Hand& hand) {
        std::unordered_map<Rank, int> rank_count;
        for (Card& c : hand.cards) {
            if (rank_count.find(c.rank) == rank_count.end()) {
                rank_count.insert({ c.rank, 1 });
            }
            else {
                rank_count[c.rank]++;
            }
        }
        return rank_count;
    }

    std::vector<Rank> HighCardChecker::check(Hand& hand) {
        std::vector<Rank> vr;
        for (Card& c : hand.cards)
            vr.push_back(c.rank);
        return vr;
    }

    std::vector<Rank> PairChecker::check(Hand& hand) {
        Rank pair_rank;
        int pair_pos;
        bool found_pair = false;
        for (int i = 0; i < 4; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank) {
                pair_rank = hand.cards[i].rank;
                pair_pos = i;
                found_pair = true;
            }
        }
        if (!found_pair) {
            return std::vector<Rank>();
        }
        else {
            // Add the rank of the pair
            std::vector<Rank> vr{ pair_rank };
            // Add the rest of the ranks, from the highest
            for (int i = 0; i < 5; i++)
                if (i != pair_pos && i != pair_pos + 1)
                    vr.push_back(hand.cards[i].rank);
            return vr;
        }
    }

    std::vector<Rank> TwoPairChecker::check(Hand& hand) {
        std::vector<Rank> vr;
        for (int i = 0; i < 4; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank) {
                vr.push_back(hand.cards[i].rank);
            }
        }
        // If two distinct pairs where found
        if (vr.size() == 2 && vr[0] != vr[1]) {
            // triple_ranks contains sorted ranks of the two pairs,
            // add the remaining (kicker) ranks
            for (Card& c : hand.cards)
                if (c.rank != vr[0] && c.rank != vr[1])
                    vr.push_back(c.rank);
            return vr;
        }
        else {
            return std::vector<Rank>();
        }
    }

    std::vector<Rank> ThreeOfKindChecker::check(Hand& hand) {
        std::vector<Rank> triple_ranks;
        for (int i = 0; i < 3; i++) {
            if (hand.cards[i].rank == hand.cards[i + 1].rank &&
                hand.cards[i + 1].rank == hand.cards[i + 2].rank) {
                triple_ranks.push_back(hand.cards[i].rank);
            }
        }
        // If exactly one triple was found
        if (triple_ranks.size() == 1) {
            for (Card& c : hand.cards) {
                if (c.rank != triple_ranks[0]) {
                    triple_ranks.push_back(c.rank);
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

    std::vector<Rank> StraightChecker::check(Hand& hand) {
        for (int i = 0; i < 4; i++)
            if (hand.cards[i].rank != hand.cards[i + 1].rank + 1)
                return std::vector<Rank>();
        // return the highest rank
        return { hand.cards[0].rank };
    }

    std::vector<Rank> FlushChecker::check(Hand& hand) {
        for (int i = 0; i < 4; i++)
            if (hand.cards[i].suit != hand.cards[i + 1].suit)
                return std::vector<Rank>();
        std::vector<Rank> vr;
        for (Card& c : hand.cards)
            vr.push_back(c.rank);
        return vr;
    }

    std::vector<Rank> FullHouseChecker::check(Hand& hand) {
        std::unordered_map<Rank, int> rank_count = count_ranks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank triple_rank, pair_rank;
            for (auto rc : rank_count) {
                if (rc.second == 2)
                    pair_rank = rc.first;
                else if (rc.second == 3)
                    triple_rank = rc.first;
                else
                    // A rank has different count - not fullhouse
                    return std::vector<Rank>();
            }
            return { triple_rank, pair_rank };
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> FourOfKindChecker::check(Hand& hand) {
        std::unordered_map<Rank, int> rank_count = count_ranks(hand);
        // If two distinct ranks were found
        if (rank_count.size() == 2) {
            Rank quadruple_rank, single_rank;
            for (auto rc : rank_count) {
                if (rc.second == 1)
                    single_rank = rc.first;
                else if (rc.second == 4)
                    quadruple_rank = rc.first;
                else
                    // A rank has different count - not four of kind
                    return std::vector<Rank>();
            }
            return { quadruple_rank, single_rank };
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> StraightFlushChecker::check(Hand& hand) {
        if (FlushChecker().check(hand) != std::vector<Rank>()) {
            return StraightChecker().check(hand);
        }
        else
            return std::vector<Rank>();
    }

    std::vector<Rank> RoyalFlushChecker::check(Hand& hand) {
        std::vector<Rank> straight_vr = StraightFlushChecker().check(hand);
        if (straight_vr == std::vector<Rank>({ ace })) {
            return straight_vr;
        }
        else
            return std::vector<Rank>();
    }

}
