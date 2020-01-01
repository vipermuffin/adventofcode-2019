//
//  Advent of Code 2019 Tests: Day 22
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/22/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day22.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay22{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay22;

TEST(Y2019_SolveDay22, FinalSolutionPartA) {
    EXPECT_EQ("2480", solvea());
}

TEST(Y2019_SolveDay22, FinalSolutionPartAa) {
    EXPECT_EQ("2480", solvea1());
}
TEST(Y2019_SolveDay22, FinalSolutionPartB) {
    
    
    EXPECT_EQ("---", solveb());
}

TEST(Y2019_Day22Example,Test1) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0,sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(9, sd.cardAtPos(9));
    EXPECT_EQ(8, sd.cardPosition(8));
    EXPECT_EQ(6, sd.cardPosition(6));
}

TEST(Y2019_Day22Example,DealNewDeck) {
    SpaceDeck sd{10};
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(i,sd.cardAtPos(i));
    }
    EXPECT_TRUE(sd.isReset());
    sd.dealN(0);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(9-i,sd.cardAtPos(i));
    }
    EXPECT_FALSE(sd.isReset());
}

TEST(Y2019_Day22Example,TestDealInc3) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    sd.dealN(3);
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(7, sd.cardAtPos(1));
    EXPECT_EQ(4, sd.cardAtPos(2));
    EXPECT_EQ(1, sd.cardAtPos(3));
    EXPECT_EQ(8, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(2, sd.cardAtPos(6));
    EXPECT_EQ(9, sd.cardAtPos(7));
    EXPECT_EQ(6, sd.cardAtPos(8));
    EXPECT_EQ(3, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,TestCutNis3) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    sd.cut(3);
    EXPECT_EQ(3, sd.cardAtPos(0));
    EXPECT_EQ(4, sd.cardAtPos(1));
    EXPECT_EQ(5, sd.cardAtPos(2));
    EXPECT_EQ(6, sd.cardAtPos(3));
    EXPECT_EQ(7, sd.cardAtPos(4));
    EXPECT_EQ(8, sd.cardAtPos(5));
    EXPECT_EQ(9, sd.cardAtPos(6));
    EXPECT_EQ(0, sd.cardAtPos(7));
    EXPECT_EQ(1, sd.cardAtPos(8));
    EXPECT_EQ(2, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,CutNisN4) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    sd.cut(-4);
    EXPECT_EQ(6, sd.cardAtPos(0));
    EXPECT_EQ(7, sd.cardAtPos(1));
    EXPECT_EQ(8, sd.cardAtPos(2));
    EXPECT_EQ(9, sd.cardAtPos(3));
    EXPECT_EQ(0, sd.cardAtPos(4));
    EXPECT_EQ(1, sd.cardAtPos(5));
    EXPECT_EQ(2, sd.cardAtPos(6));
    EXPECT_EQ(3, sd.cardAtPos(7));
    EXPECT_EQ(4, sd.cardAtPos(8));
    EXPECT_EQ(5, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,TestMoves1) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    vector<string> moves {
       "deal with increment 7",
       "deal into new stack",
       "deal into new stack"
    };
    for_each(moves.begin(),moves.end(),[&sd](const string& s){sd.shuffleMove(s);});

    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(3, sd.cardAtPos(1));
    EXPECT_EQ(6, sd.cardAtPos(2));
    EXPECT_EQ(9, sd.cardAtPos(3));
    EXPECT_EQ(2, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(8, sd.cardAtPos(6));
    EXPECT_EQ(1, sd.cardAtPos(7));
    EXPECT_EQ(4, sd.cardAtPos(8));
    EXPECT_EQ(7, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,TestMoves2) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    vector<string> moves {
        "cut 6",
        "deal with increment 7",
        "deal into new stack"
    };
    for_each(moves.begin(),moves.end(),[&sd](const string& s){sd.shuffleMove(s);});
    
    EXPECT_EQ(3, sd.cardAtPos(0));
    EXPECT_EQ(0, sd.cardAtPos(1));
    EXPECT_EQ(7, sd.cardAtPos(2));
    EXPECT_EQ(4, sd.cardAtPos(3));
    EXPECT_EQ(1, sd.cardAtPos(4));
    EXPECT_EQ(8, sd.cardAtPos(5));
    EXPECT_EQ(5, sd.cardAtPos(6));
    EXPECT_EQ(2, sd.cardAtPos(7));
    EXPECT_EQ(9, sd.cardAtPos(8));
    EXPECT_EQ(6, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,TestMoves3) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    vector<string> moves {
        "deal with increment 7",
        "deal with increment 9",
        "cut -2"
    };
    for_each(moves.begin(),moves.end(),[&sd](const string& s){sd.shuffleMove(s);});
    
    EXPECT_EQ(6, sd.cardAtPos(0));
    EXPECT_EQ(3, sd.cardAtPos(1));
    EXPECT_EQ(0, sd.cardAtPos(2));
    EXPECT_EQ(7, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(1, sd.cardAtPos(5));
    EXPECT_EQ(8, sd.cardAtPos(6));
    EXPECT_EQ(5, sd.cardAtPos(7));
    EXPECT_EQ(2, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
}

TEST(Y2019_Day22Example,TestMoves4) {
    SpaceDeck sd{10};
    
    EXPECT_EQ(0, sd.cardAtPos(0));
    EXPECT_EQ(1, sd.cardAtPos(1));
    EXPECT_EQ(2, sd.cardAtPos(2));
    EXPECT_EQ(3, sd.cardAtPos(3));
    EXPECT_EQ(4, sd.cardAtPos(4));
    EXPECT_EQ(5, sd.cardAtPos(5));
    EXPECT_EQ(6, sd.cardAtPos(6));
    EXPECT_EQ(7, sd.cardAtPos(7));
    EXPECT_EQ(8, sd.cardAtPos(8));
    EXPECT_EQ(9, sd.cardAtPos(9));
    
    vector<string> moves {
        "deal into new stack",
        "cut -2",
        "deal with increment 7",
        "cut 8",
        "cut -4",
        "deal with increment 7",
        "cut 3",
        "deal with increment 9",
        "deal with increment 3",
        "cut -1"
    };
    for_each(moves.begin(),moves.end(),[&sd](const string& s){sd.shuffleMove(s);});
    
    EXPECT_EQ(9, sd.cardAtPos(0));
    EXPECT_EQ(2, sd.cardAtPos(1));
    EXPECT_EQ(5, sd.cardAtPos(2));
    EXPECT_EQ(8, sd.cardAtPos(3));
    EXPECT_EQ(1, sd.cardAtPos(4));
    EXPECT_EQ(4, sd.cardAtPos(5));
    EXPECT_EQ(7, sd.cardAtPos(6));
    EXPECT_EQ(0, sd.cardAtPos(7));
    EXPECT_EQ(3, sd.cardAtPos(8));
    EXPECT_EQ(6, sd.cardAtPos(9));
}
