/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 *     
 * 
 * Created on March 19, 2019, 11:21 AM
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

#include "Program.h"

using namespace std;

/**
 * 01
 *  Average Outcome Per Day: -3
    Average Income Per Day: 0

 * 02
 *  Average Outcome Per Day: -55.89
    Average Income Per Day: 0
 * 
 * 03
 *  Average Outcome Per Day: -159.51
    Average Income Per Day: 0

 * 04
 *  Average Outcome Per Day: -157.772
    Average Income Per Day: 0

 * 05
 *  Average Outcome Per Day: -155.694
    Average Income Per Day: 0
 * 
 * 06
 *  Average Outcome Per Day: -132.445
    Average Income Per Day: 0

 * 07
 *  Average Outcome Per Day: -124.411
    Average Income Per Day: 0

 * 08
 *  Average Outcome Per Day: -114.757
    Average Income Per Day: 0
 * 
 * 09
 *  Average Outcome Per Day: -115.551
    Average Income Per Day: 27.7778
 * 
 * 10
 *  Average Outcome Per Day: -154.802
    Average Income Per Day: 25

 * 11
 *  Average Outcome Per Day: -147.051
    Average Income Per Day: 22.7273

 * 12
 *  Average Outcome Per Day: -134.797
    Average Income Per Day: 20.8333
 * 
 * 13
 *  Average Outcome Per Day: -172.494
    Average Income Per Day: 19.2308

 * 14
 *  Average Outcome Per Day: -165.909
    Average Income Per Day: 17.8571

 * 15
 *  Average Outcome Per Day: -157.108
    Average Income Per Day: 16.6667

 * 16
 *  Average Outcome Per Day: -148.001
    Average Income Per Day: 15.625
 */

void addTransaction(Program& p) {

}

void simpleTest() {
    Program p{""};

    p.setDay("Date 17 01 2020");
//    p.setRecord("Фантастико", -28.7);
//    p.setRecord("Зеленчуци", -4.8);
//    p.setRecord("Футбол", -6);
//    p.setRecord("Револют Инвест", -527.86);
    p.setRecord("Фъстъци", -4.5);
    p.setRecord("Обяд", -6.9);
//    p.setRecord("Вечеря", -27);
//    p.setRecord("Вода", -1.1);
//    p.setIncome("Приход Пепо", 250);
    p.writeToFile("results/012020.txt");
    
    p.readFromFile("results/012020.txt");
    p.printAllItems();
    p.printAveragePerDay("results/012020.txt");
    p.printDailyExpenses();
    std::cout << "Total Income: " << p.getTotalIncome() << " - " << (p.getTotalOutcome() * -1)<< " = " << p.getTotalDifference() << std::endl;
    std::cout << "Exit program!\n";
}

void towerOfHanoi(int disks, const std::string& left, const std::string& middle, const std::string& right) {
    if(disks > 0) {
        towerOfHanoi(disks - 1, left, right, middle);
        std::cout << "from disk: " << left << " to disk: " << right << std::endl;
        towerOfHanoi(disks - 1, middle, left, right);
    }
}

void calculateYearIncome(double& currMoney) {
    double salary = 3900;
    double result = currMoney + (salary * 12);
    std::cout << "Total Money After 13 months: " << result;
}

void calculateZaem() {
    double pepoZaem = 500;
    double cvetiZaem = 693;
    double sergoZaem = 1715;
    double psihoZaem = 80;
    
    std::cout << "Pepo: " << pepoZaem << "\nCveti: " << cvetiZaem << "\nSergo: " << sergoZaem  <<
        "\nPsiho: " << psihoZaem << "\nTotal: " << (pepoZaem + cvetiZaem + sergoZaem + psihoZaem) << std::endl;
    double bank = 10587.13;
    double revolut = 945.28 + 28;
    double inMe = 105;
    double total = pepoZaem + cvetiZaem + sergoZaem + psihoZaem;
    double gold1g = (90 * 46);
    double gold20g = (2 * 1735);
    double zaemDo18 = 8300;
    std::cout << "In Me: " << inMe << std::endl;
    std::cout << "Bank: " << bank << std::endl;
    std::cout << "Revolut: " << revolut << std::endl;
    std::cout << "zaemDo18: " << zaemDo18 << std::endl;
    std::cout << "Gold 1g: " << gold1g << std::endl;
    std::cout << "Gold 20g: " << gold20g << std::endl;
    double actives = bank + revolut + inMe + total + gold1g + gold20g + zaemDo18;
    std::cout << "Total Money: " << actives << std::endl;
    /**
        19.12.2019
        Pepo: 690
        Cveti: 693
        Sergo: 1715
        Psiho: 80
        Total: 3178
        Gold 1g: 3956
        Gold 20g: 3304
        Total Money: 24138.7

     */
//    calculateYearIncome(actives);
}

void calculatePercentIncrease(float total, float increase) {
    float percent = ((increase - total) / total) * 100.0f;
    if(total == 0) {
        percent = 100;
    }
    std::string temp = "Win: ";
    if(percent < 0) {
        temp = "Lose: ";
    }
    std::cout << "Percent " << temp << percent << "%" << std::endl;
}
void calculateMoney(float buy, float sell, float& totalBuy, float& totalWin) {
    float totalPay = 0;
    float totalSell = 0;
    for(int i = 0; i < 5; i++) {
        totalPay += buy;
        totalSell += sell;
    }
    totalBuy += totalPay;
    totalWin += totalSell;
    std::cout << "Buyed for: " << totalPay << ", Can Sell For: " << totalSell << " Win: " << (totalSell - totalPay) 
        << "\n###################" << std::endl;
    
}
void calclulate20g(float buy, float sell, float& totalBuy, float& totalWin) {
    totalBuy += buy;
    totalWin += sell;
    std::cout << "Buyed for: " << buy << ", Can Sell For: " << sell << " Win: " << (sell - buy) 
        << "\n###################" << std::endl;
} 
/**
 * Total Spend: 5075, Total Can Win: 5915
20g Gold PAMP: Percent Win: 17.7539%
Buyed for: 1487, Can Sell For: 1751 Win: 264
###################
20g Gold Valcambi: Percent Win: 17.2806%
Buyed for: 1493, Can Sell For: 1751 Win: 258
###################
Total Spend: 8055, Total Can Win: 9417

============================ FINAL SCORE ===========================
Money Won: 1362, Percent Win: 16.9088%

 */
void caluclateYear(const std::string& year) {
    //This rally High
//    constexpr int SELL1G = 91;
//    constexpr int SELL20G = 1760;
    
    constexpr int SELL1G = 92;
    constexpr int SELL20G = 1772;

    float spend = 0;
    float canWin = 0;
    std::cout << "November: ";
    calculatePercentIncrease(76, SELL1G);
    calculateMoney(76, SELL1G, spend, canWin);
    std::cout << "December: ";
    calculatePercentIncrease(77, SELL1G);
    calculateMoney(77, SELL1G, spend, canWin);
    std::cout << "January: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "February: ";
    calculatePercentIncrease(81, SELL1G);
    calculateMoney(81, SELL1G, spend, canWin);
    std::cout << "March: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "April: ";
    calculatePercentIncrease(81, SELL1G);
    calculateMoney(81, SELL1G, spend, canWin);
    std::cout << "May: ";
    calculatePercentIncrease(80, SELL1G);
    calculateMoney(80, SELL1G, spend, canWin);
    std::cout << "Juny: ";
    calculatePercentIncrease(83, SELL1G);
    calculateMoney(83, SELL1G, spend, canWin);
    std::cout << "July: ";
    calculatePercentIncrease(88, SELL1G);
    calculateMoney(88, SELL1G, spend, canWin);
    
    std::cout << "August: ";
    calculatePercentIncrease(92, SELL1G);
    calculateMoney(92, SELL1G, spend, canWin);
    std::cout << "September: ";
    calculatePercentIncrease(98, SELL1G);
    calculateMoney(98, SELL1G, spend, canWin);
    std::cout << "October: ";
    calculatePercentIncrease(96, SELL1G);
    calculateMoney(96, SELL1G, spend, canWin);
    std::cout << "Bonus: ";
    calculatePercentIncrease(0, SELL1G);
    calculateMoney(0, SELL1G, spend, canWin);
    std::cout << "Total Spend: " << spend << ", Total Can Win: " << canWin << std::endl;
    
    std::cout << "20g Gold PAMP: ";
    calculatePercentIncrease(1487, SELL20G);
    calclulate20g(1487, SELL20G, spend, canWin);
    std::cout << "20g Gold Valcambi: ";
    calculatePercentIncrease(1493, SELL20G);
    calclulate20g(1493, SELL20G, spend, canWin);
    std::cout << "Total Spend: " << spend << ", Total Can Win: " << canWin << std::endl;
    std::cout << std::endl;
    std::cout << "============ FINAL SCORE " << year << " =================\n";
    std::cout << "Money Won: " << (canWin - spend) << ", ";
    calculatePercentIncrease(spend, canWin);
    
}

int main(int argc, char** argv) {

//    simpleTest();

    calculateZaem();
    
//    caluclateYear("2019");

    return 0;
}

