//
//  Advent of Code 2019 Tests: Day 12
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/12/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day12.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay12{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay12;

TEST(Y2019_SolveDay12, FinalSolutionPartA) {
    EXPECT_EQ("7722", solvea());
}

TEST(Y2019_SolveDay12, FinalSolutionPartB) {
//    EXPECT_EQ("---", solveb());
}

TEST(Y2019_Day12Example,Test1) {
    /*
     <x=-1, y=0, z=2>
     <x=2, y=-10, z=-7>
     <x=4, y=-8, z=8>
     <x=3, y=5, z=-1>
     */
    vector<Moon> moons;
    moons.emplace_back(-1,0,2);
    moons.emplace_back(2,-10,-7);
    moons.emplace_back(4,-8,8);
    moons.emplace_back(3,5,-1);
    
    EXPECT_EQ(0,moons[0].kineticEnergy());
    EXPECT_EQ(0,moons[1].kineticEnergy());
    EXPECT_EQ(0,moons[2].kineticEnergy());
    EXPECT_EQ(0,moons[3].kineticEnergy());
    EXPECT_EQ(3,moons[0].potentialEnergy());
    EXPECT_EQ(19,moons[1].potentialEnergy());
    EXPECT_EQ(20,moons[2].potentialEnergy());
    EXPECT_EQ(9,moons[3].potentialEnergy());
}

TEST(Y2019_Day12Example,Test2) {
        /*
     <x=-1, y=0, z=2>
     <x=2, y=-10, z=-7>
     <x=4, y=-8, z=8>
     <x=3, y=5, z=-1>
     */
    vector<Moon> moons;
    moons.emplace_back(-1,0,2);
    moons.emplace_back(2,-10,-7);
    moons.emplace_back(4,-8,8);
    moons.emplace_back(3,5,-1);
    
    for(int i = 0; i < moons.size(); i++) {
        for(int j = 0; j < moons.size(); j++) {
            if(i != j) {
                moons[i] += moons[j];
            }
        }
    }
    
    EXPECT_EQ(5,moons[0].kineticEnergy());
    EXPECT_EQ(7,moons[1].kineticEnergy());
    EXPECT_EQ(7,moons[2].kineticEnergy());
    EXPECT_EQ(5,moons[3].kineticEnergy());
    EXPECT_EQ(3,moons[0].potentialEnergy());
    EXPECT_EQ(19,moons[1].potentialEnergy());
    EXPECT_EQ(20,moons[2].potentialEnergy());
    EXPECT_EQ(9,moons[3].potentialEnergy());
}

TEST(Y2019_Day12Example,Test3) {
        /*
     <x=-1, y=0, z=2>
     <x=2, y=-10, z=-7>
     <x=4, y=-8, z=8>
     <x=3, y=5, z=-1>
     */
    vector<Moon> moons;
    moons.emplace_back(-1,0,2);
    moons.emplace_back(2,-10,-7);
    moons.emplace_back(4,-8,8);
    moons.emplace_back(3,5,-1);
    
    for(int i = 0; i < moons.size(); i++) {
        for(int j = 0; j < moons.size(); j++) {
            if(i != j) {
                moons[i] += moons[j];
            }
        }
    }
    for_each(moons.begin(),moons.end(),[](Moon& m){m.step();});
    
    EXPECT_EQ(5,moons[0].kineticEnergy());
    EXPECT_EQ(7,moons[1].kineticEnergy());
    EXPECT_EQ(7,moons[2].kineticEnergy());
    EXPECT_EQ(5,moons[3].kineticEnergy());
    EXPECT_EQ(4,moons[0].potentialEnergy());
    EXPECT_EQ(14,moons[1].potentialEnergy());
    EXPECT_EQ(13,moons[2].potentialEnergy());
    EXPECT_EQ(4,moons[3].potentialEnergy());
}

#if 1
TEST(Y2019_Day12Example,Test4) {
        /*
     <x=-8, y=-10, z=0>
     <x=5, y=5, z=10>
     <x=2, y=-7, z=3>
     <x=9, y=-8, z=-3>
     */
    Moon m[] = {{-8,-10,0},{5,5,10},{2,-7,3},{9,-8,-3}};
    vector<Moon> moons;
    moons.emplace_back(-8,-10,0);
    moons.emplace_back(5,5,10);
    moons.emplace_back(2,-7,3);
    moons.emplace_back(9,-8,-3);
    long lastTime[4] = {0};
    for(long j = 0; j < 4686774924; j++)
    {
        for(int i = 0; i < moons.size(); i++) {
            for(int j = 0; j < moons.size(); j++) {
                if(i != j) {
                    moons[i] += moons[j];
                }
            }
        }
        for_each(moons.begin(),moons.end(),[](Moon& m){m.step();});
        for(int i = 0; i < moons.size(); i++) {
            if(moons[i] == m[i]) {
                cout << i << " " << j-lastTime[i] << " " << lastTime[i] << " " << j << endl;
                lastTime[i] = j;
            }
        }
    }
    
    EXPECT_EQ(0,moons[0].kineticEnergy());
    EXPECT_EQ(0,moons[1].kineticEnergy());
    EXPECT_EQ(0,moons[2].kineticEnergy());
    EXPECT_EQ(0,moons[3].kineticEnergy());
//    EXPECT_EQ(4,moons[0].potentialEnergy());
//    EXPECT_EQ(14,moons[1].potentialEnergy());
//    EXPECT_EQ(13,moons[2].potentialEnergy());
//    EXPECT_EQ(4,moons[3].potentialEnergy());
}
#endif
