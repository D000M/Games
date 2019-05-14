/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define GTEST_LANG_CX11 1
#include <gtest/gtest.h>
#include "Creational/Singleton/SingletonImplementation.h"

//First Argument is the name of the test case, and the second argument is the name of the test, one test case can have multiple tests
TEST(RecordFinderTest, SingletonTotalPopulationTest) {
        SingletonImplementation::SingletonDBRecordFinder rf;
        std::vector<std::string> names{"Tokyo", "Delhi", "Mexico City"};
        int totalPop = rf.totalPopulation(names);
        std::cout << "Total Pop: " << totalPop << std::endl;
        EXPECT_EQ(33200000 + 14300000 + 17400000, totalPop);  
}
TEST(RecordFinderTest, testTwo) {
    int a = 10;
    EXPECT_EQ(10, a);  
}

TEST(ConfigurableRecordFinder, DummyDB) {
    SingletonImplementation::DummyDataBase db;
    SingletonImplementation::ConfigurableRecordFinder rf{db};
    EXPECT_EQ(3, rf.totalPopulation(std::vector<std::string>{"alpha", "beta"}));
    EXPECT_EQ(4, rf.totalPopulation(std::vector<std::string>{"alpha", "gamma"}));
    EXPECT_EQ(1, rf.totalPopulation(std::vector<std::string>{"alpha"}));
}