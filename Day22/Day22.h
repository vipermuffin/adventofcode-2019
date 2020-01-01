//
//  Advent of Code 2019 Solutions: Day 22
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/22/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay22 {
//Function Definitions
    std::string solvea1();
    class SpaceDeck {
    public:
        SpaceDeck() = delete;
        SpaceDeck(const int64_t numCards);
        ~SpaceDeck() = default;
        void shuffleMove(const std::string& description);
        void reset();
        void dealN(const int64_t n);
        void cut(const int64_t x);
        int64_t cardAtPos(const int64_t pos);
        size_t cardPosition(const int64_t cardId);
        bool isReset() const;
        
    private:
        std::vector<int64_t> cards;
        std::vector<int64_t> tempStorage;
    };
}
