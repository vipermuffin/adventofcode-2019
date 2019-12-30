//
//  Advent of Code 2019 Solutions: Day 12
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/12/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include "LinearTraveler.h"
#include <string>
#include <vector>

namespace AocDay12 {
//Function Definitions
    class Moon {
    public:
        Moon();
        Moon(int,int,int);
        ~Moon() = default;
        Moon& operator+=(const Moon& rhs);
        bool operator==(const Moon& rhs) const;
        void step();
        int potentialEnergy() const;
        int kineticEnergy() const;
        std::string position() const;
        bool xEquals(const Moon& rhs) const;
        bool yEquals(const Moon& rhs) const;
        bool zEquals(const Moon& rhs) const;
        
    private:
        AocUtils::LinearTraveler<int> x;
        AocUtils::LinearTraveler<int> y;
        AocUtils::LinearTraveler<int> z;
    };
    
    int64_t simulateOneMoonDimension(const std::vector<AocUtils::LinearTraveler<int>>& moons);
    int64_t simulateMoons(const std::vector<Moon>& moons);
}
