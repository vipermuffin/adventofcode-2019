//
//  Advent of Code 2019 Tests: Day 14
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/14/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day14.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay14{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay14;

TEST(Y2019_SolveDay14, FinalSolutionPartA) {
    EXPECT_EQ("502491", solvea());
}

TEST(Y2019_SolveDay14, FinalSolutionPartB) {
    EXPECT_EQ("2944565", solveb());
}

TEST(Y2019_Day14Example,Test1) {
    ChemicalDictionary x;
    string def{"10 ORE => 10 A"};
    parseChemicalFormula(def, x);
    ASSERT_EQ(1,x.size());
    ASSERT_EQ(2,x["A"].size());
    EXPECT_EQ(10,x["A"][0].second);
    EXPECT_EQ("ORE",x["A"][0].first);
    EXPECT_EQ(10,x["A"][1].second);
    EXPECT_EQ("A",x["A"][1].first);
}

TEST(Y2019_Day14Example,Test2) {
    ChemicalDictionary x;
    string def{"7 A, 1 B => 1 C"};
    parseChemicalFormula(def, x);
    ASSERT_EQ(1,x.size());
    ASSERT_EQ(3,x["C"].size());
    EXPECT_EQ(7,x["C"][0].second);
    EXPECT_EQ("A",x["C"][0].first);
    EXPECT_EQ(1,x["C"][1].second);
    EXPECT_EQ("B",x["C"][1].first);
    EXPECT_EQ(1,x["C"][2].second);
    EXPECT_EQ("C",x["C"][2].first);
}

TEST(Y2019_Day14Example,Test3) {
    vector<string> input{
        "10 ORE => 10 A",
        "1 ORE => 1 B",
        "7 A, 1 B => 1 C",
        "7 A, 1 C => 1 D",
        "7 A, 1 D => 1 E",
        "7 A, 1 E => 1 FUEL"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    
    ASSERT_EQ(6,x.size());
    ASSERT_EQ(3,x["C"].size());
    ASSERT_EQ(2,x["B"].size());
}

TEST(Y2019_Day14Example,Test4) {
    vector<string> input{
        "10 ORE => 10 A",
        "1 ORE => 1 B",
        "7 A, 1 B => 1 C",
        "7 A, 1 C => 1 D",
        "7 A, 1 D => 1 E",
        "7 A, 1 E => 1 FUEL"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    auto actual = findIngredients("ORE", "FUEL", x);
    EXPECT_EQ(31,actual);
}

TEST(Y2019_Day14Example,Test5) {
    vector<string> input{
        "9 ORE => 2 A",
        "8 ORE => 3 B",
        "7 ORE => 5 C",
        "3 A, 4 B => 1 AB",
        "5 B, 7 C => 1 BC",
        "4 C, 1 A => 1 CA",
        "2 AB, 3 BC, 4 CA => 1 FUEL"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    auto actual = findIngredients("ORE", "FUEL", x);
    EXPECT_EQ(165,actual);
}

TEST(Y2019_Day14Example,Test6) {
    vector<string> input{
        "157 ORE => 5 NZVS",
        "165 ORE => 6 DCFZ",
        "44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL",
        "12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ",
        "179 ORE => 7 PSHF",
        "177 ORE => 5 HKGWZ",
        "7 DCFZ, 7 PSHF => 2 XJWVT",
        "165 ORE => 2 GPVTF",
        "3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    auto actual = findIngredients("ORE", "FUEL", x);
    EXPECT_EQ(13312,actual);
}

TEST(Y2019_Day14Example,Test6b) {
    vector<string> input{
        "157 ORE => 5 NZVS",
        "165 ORE => 6 DCFZ",
        "44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL",
        "12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ",
        "179 ORE => 7 PSHF",
        "177 ORE => 5 HKGWZ",
        "7 DCFZ, 7 PSHF => 2 XJWVT",
        "165 ORE => 2 GPVTF",
        "3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    string base = "ORE";
    string start = "FUEL";
    auto actual = findIngredients(base, start, x,10);
    int64_t num = 1000000000000;
    int64_t low = 10*num/(actual);
    while(actual < num) {
        low+=100;
        actual = findIngredients(base, start, x, low);
    }
    low-=100;
    actual = 0;
    while(actual < num) {
        low++;
        actual = findIngredients(base, start, x, low);
    }

    EXPECT_EQ(82892753,--low);
}

TEST(Y2019_Day14Example,Test7) {
    vector<string> input{
        "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG",
        "17 NVRVD, 3 JNWZP => 8 VPVL",
        "53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL",
        "22 VJHF, 37 MNCFX => 5 FWMGM",
        "139 ORE => 4 NVRVD",
        "144 ORE => 7 JNWZP",
        "5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC",
        "5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV",
        "145 ORE => 6 MNCFX",
        "1 NVRVD => 8 CXFTF",
        "1 VJHF, 6 MNCFX => 4 RFSQX",
        "176 ORE => 6 VJHF"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    auto actual = findIngredients("ORE", "FUEL", x);
    EXPECT_EQ(180697,actual);
}

TEST(Y2019_Day14Example,Test7b) {
    vector<string> input{
        "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG",
        "17 NVRVD, 3 JNWZP => 8 VPVL",
        "53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL",
        "22 VJHF, 37 MNCFX => 5 FWMGM",
        "139 ORE => 4 NVRVD",
        "144 ORE => 7 JNWZP",
        "5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC",
        "5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV",
        "145 ORE => 6 MNCFX",
        "1 NVRVD => 8 CXFTF",
        "1 VJHF, 6 MNCFX => 4 RFSQX",
        "176 ORE => 6 VJHF"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    string base = "ORE";
    string start = "FUEL";
    auto actual = findIngredients(base, start, x,10);
    int64_t num = 1000000000000;
    int64_t low = 10*num/(actual);
    while(actual < num) {
        low+=100;
        actual = findIngredients(base, start, x, low);
    }
    low-=100;
    actual = 0;
    while(actual < num) {
        low++;
        actual = findIngredients(base, start, x, low);
    }
    EXPECT_EQ(5586022,--low);
}

TEST(Y2019_Day14Example,Test8) {
    vector<string> input{
        "171 ORE => 8 CNZTR",
        "7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL",
        "114 ORE => 4 BHXH",
        "14 VRPVC => 6 BMBT",
        "6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL",
        "6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT",
        "15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW",
        "13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW",
        "5 BMBT => 4 WPTQ",
        "189 ORE => 9 KTJDG",
        "1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP",
        "12 VRPVC, 27 CNZTR => 2 XDBXC",
        "15 KTJDG, 12 BHXH => 5 XCVML",
        "3 BHXH, 2 VRPVC => 7 MZWV",
        "121 ORE => 7 VRPVC",
        "7 XCVML => 6 RJRHP",
        "5 BHXH, 4 VRPVC => 5 LTCX"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    auto actual = findIngredients("ORE", "FUEL", x);
    EXPECT_EQ(2210736,actual);
}

TEST(Y2019_Day14Example,Test8b) {
    vector<string> input{
        "171 ORE => 8 CNZTR",
        "7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL",
        "114 ORE => 4 BHXH",
        "14 VRPVC => 6 BMBT",
        "6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL",
        "6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT",
        "15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW",
        "13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW",
        "5 BMBT => 4 WPTQ",
        "189 ORE => 9 KTJDG",
        "1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP",
        "12 VRPVC, 27 CNZTR => 2 XDBXC",
        "15 KTJDG, 12 BHXH => 5 XCVML",
        "3 BHXH, 2 VRPVC => 7 MZWV",
        "121 ORE => 7 VRPVC",
        "7 XCVML => 6 RJRHP",
        "5 BHXH, 4 VRPVC => 5 LTCX"
    };
    ChemicalDictionary x;
    buildMapOfChemicals(input, x);
    string base = "ORE";
    string start = "FUEL";
    auto actual = findIngredients(base, start, x,10);
    int64_t num = 1000000000000;
    int64_t low = 10*num/(actual);
    while(actual < num) {
        low+=100;
        actual = findIngredients(base, start, x, low);
    }
    low-=100;
    actual = 0;
    while(actual < num) {
        low++;
        actual = findIngredients(base, start, x, low);
    }
    EXPECT_EQ(460664,--low);
}
