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
#include <fstream>
#include <errno.h>
#include "Program.h"

using namespace std;

/* 
 * 01
 *  Average Outcome Per Day: -300
    Average Income Per Day: 0

 * 02
 *  Average Outcome Per Day: -160.86
    Average Income Per Day: 0
 * 
 * 03
 *  Average Outcome Per Day: -120.3
    Average Income Per Day: 0
 * 
 * 04
 *  Average Outcome Per Day: -95.085
    Average Income Per Day: 0

 * 05
 *  Average Outcome Per Day: -76.068
    Average Income Per Day: 0

 * 06
 *  Average Outcome Per Day: -78.9667
    Average Income Per Day: 0

 * 07
 *  Average Outcome Per Day: -151.35
    Average Income Per Day: 0
 * 
 * 08
 *  Average Outcome Per Day: -132.431
    Average Income Per Day: 0

 * 09
 *  Average Outcome Per Day: -117.717
    Average Income Per Day: 0
 * 
 * 10
 *  Average Outcome Per Day: -109.945
    Average Income Per Day: 0

 * 11
 *  Average Outcome Per Day: -109.945
    Average Income Per Day: 0

 * 12
 *  Average Outcome Per Day: -109.945
    Average Income Per Day: 0

 */


void addTransaction(Program& p) {

}

void simpleTest() {
    Program p{""};

    p.setDay("Date 12 04 2020");
//    p.setRecord("Фантастико", -24.31);
//    p.setRecord("Квартира", -43);
//    p.setRecord("Банка", -9.03);
//    p.setRecord("Бира", -38);
//    p.setRecord("Вечеря", -40);
//    p.setRecord("Железария", -10);
//    p.setRecord("Зеленчуци", -25);
//    p.setRecord("Револют Инвест", -542.65);
//    p.setIncome("Заплата", 3824.25);
    p.writeToFile("results/042020.txt");
    
    p.readFromFile("results/042020.txt");
    p.printAllItems();
    p.printAveragePerDay("results/042020.txt");
    p.printDailyExpenses();
    char c = 'a';
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
    double salary = 3824;
    double result = currMoney + (salary * 10);
    std::cout << "Total Money After 10 months: " << result;
}

void calculateZaem() {
    double cvetiZaem = 693;
    double sergoZaem = 2065;
    double psihoZaem = 80 + 50;
    double vesoAirBnb = 78;
    double stelaAirBnb = 78;
    double minaAirBnb = 78;
    double sergoAirBnb = 78;
    double cvetiAirBnb = 78;
    double totalAirbnb = vesoAirBnb + stelaAirBnb + minaAirBnb + sergoAirBnb + cvetiAirBnb;
    
    std::cout << "\nCveti: " << cvetiZaem << "\nSergo: " << sergoZaem  << "\nPsiho: " << psihoZaem << "\nAirBnbPlovdiv:" << totalAirbnb << "\nTotal: " << (cvetiZaem + sergoZaem + psihoZaem + totalAirbnb) << std::endl;
    double bank = 8619.53;
    double revolut = 2942.68 + 273.27 + 4105;
    double inMe = 240;
    double total = cvetiZaem + sergoZaem + psihoZaem + totalAirbnb;
    double gold1g = (103 * 39);
    double gold20g = (2 * 2024);
    double zaemDo18 = 8300;
    std::cout << "In Me: " << inMe << std::endl;
    std::cout << "Bank: " << bank << std::endl;
    std::cout << "Revolut: " << revolut << std::endl;
    std::cout << "zaemDo18: " << zaemDo18 << std::endl;
    std::cout << "Gold 1g: " << gold1g << std::endl;
    std::cout << "Gold 20g: " << gold20g << std::endl;
    double actives = bank + revolut + inMe + total + gold1g + gold20g;
    std::cout << "Total Money: " << actives << std::endl;

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
 * 
 * 20.02.2020
Total Spend: 8040, Total Can Win: 10041

============ FINAL SCORE 2019 =================
Money Won: 2001, Percent Win: 24.8881%

 */
void caluclateYear(const std::string& year) {
    //This rally High
//    constexpr int SELL1G = 97;
//    constexpr int SELL20G = 1868;
    
    constexpr int SELL1G = 102;
    constexpr int SELL20G = 2000;

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
//    
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
std::string calculatePercentIncreaseInvest(float start, float end) {
    float percent = ((end - start) / start) * 100.0f;

    std::string temp = "Win: ";
    if(percent < 0) {
        temp = "Lose: ";
    }
    std::stringstream ss;
    ss << "Percent " << std::setw(8) << temp << std::fixed << std::setprecision(2) << std::setw(7) << percent << "%" 
            << " Start $" << start << " End $" << end << 
            " Dollars " << std::setw(8) << temp << std::setw(10) << end - start << "$";
    std::string result = ss.str();
    std::cout << result << std::endl;
    
    return result;
}
void calculateDayPercent(const std::string& date, float start, float end) {
    std::string day = date;
    std::ofstream file;
    file.open("invest/042020.txt", std::ios::out | std::ios::app);
    file << day << calculatePercentIncreaseInvest(start, end) << std::endl;
    file.close();
}

int main(int argc, char** argv) {

//    simpleTest();

    calculateZaem();
    
//    caluclateYear("2019");

//    calculateDayPercent("13/04/2020: ", 1635.9, 1700);
    return 0;
}

