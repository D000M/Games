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
#include <ios>
#include "Program.h"

using namespace std;

/*
 * 01
 *  Average Outcome Per Day: -75
    Average Income Per Day: 0

 * 02
 *  Average Outcome Per Day: -66.45
    Average Income Per Day: 0

 * 03
 *  Average Outcome Per Day: -44.3
    Average Income Per Day: 0
 * 
 * 04
 *  Average Outcome Per Day: -46.8625
    Average Income Per Day: 0

 * 05
 *  Average Outcome Per Day: -40.412
    Average Income Per Day: 0

 * 06
 *  Average Outcome Per Day: -42.3983
    Average Income Per Day: 0
 * 
 * 07
 *  Average Outcome Per Day: -38.4229
    Average Income Per Day: 0

 * 08
 *  Average Outcome Per Day: -40.745
    Average Income Per Day: 0

 * 09
 *  Average Outcome Per Day: -42.3289
    Average Income Per Day: 0

 * 10
 *  Average Outcome Per Day: -40.593
    Average Income Per Day: 0

 * 11
 *  Average Outcome Per Day: -39.5782
    Average Income Per Day: 0

 * 12
 *  Average Outcome Per Day: -42.6817
    Average Income Per Day: 1.66667
 * 
 * 13
 *  Average Outcome Per Day: -44.8138
    Average Income Per Day: 1.53846

 * 14
 *  Average Outcome Per Day: -119.628
    Average Income Per Day: 1.42857

 * 15
 *  Average Outcome Per Day: -116.517
    Average Income Per Day: 1.33333
 * 
 * 16
 *  Average Outcome Per Day: -111.109
    Average Income Per Day: 1.25
 * 
 * 17
 *  Average Outcome Per Day: -108.323
    Average Income Per Day: 1.17647
 * 
 * 18
 *  Average Outcome Per Day: -158.754
    Average Income Per Day: 1.11111

 * 19
 *  Average Outcome Per Day: -204.342
    Average Income Per Day: 472.855
 * 
 * 20
 *  Average Outcome Per Day: -146.677
    Average Income Per Day: 541.912

 * 21
 *  Average Outcome Per Day: -567.471
    Average Income Per Day: 609.44
 * 
 * 22
 *  Average Outcome Per Day: -543.495
    Average Income Per Day: 581.738

 * 
 * 23
 *  Average Outcome Per Day: -524.13
    Average Income Per Day: 556.445
 * 
 * 24
 *  Average Outcome Per Day: -503.616
    Average Income Per Day: 533.885
 * 
 * 25
 *  Average Outcome Per Day: -485.726
    Average Income Per Day: 513.33
 * 
 * 26
 *  Average Outcome Per Day: -468.487
    Average Income Per Day: 493.586

 * 27
 *  Average Outcome Per Day: -572.062
    Average Income Per Day: 596.231

 */

void addTransaction(Program& p) {

}

void simpleTest() {
    Program p{""};

    p.setDay("Date 27 05 2020");
//    p.setRecord("Фантастико", -19.53);
//    p.setRecord("Банка", -2);
//    p.setRecord("Квартира", -5);
//    p.setRecord("Зленчуци", -11.3);
//    p.setRecord("Благотворителност", -3);
//    p.setRecord("Вечеря", -15);
//    p.setRecord("Такси", -10);  
//    p.setRecord("Интерактив Инвест", -1955.30 + (-6981));
//    p.setRecord("Бира", -19.34);
    p.setRecord("Интерактив Инвест", -3265);
    p.setIncome("Револют Инвест", 3265);
    p.writeToFile("results/052020.txt");
    
    p.readFromFile("results/052020.txt");
    p.printAllItems();
    p.printAveragePerDay("results/052020.txt");
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
    double salary = 3824;
    double result = currMoney + (salary * 10);
    std::cout << "Total Money After 10 months: " << result;
}
void calculateCurrMoney(const std::string&, const std::string&);

void calculateZaem() {
    
    double cvetiZaem = 80;
    double sergoZaem = 2065;
    double psihoZaem = 80 + 50;
    double pepoZaem = 1000;
    double usdPrice = 1.77948;
    double euroPrice = 1.95583;
    
    double cvetiSharesCurrPrice = 1300.54;
    double cvetiLeftUSD = 32.29;    //usd by 26.05.2020 
    double cvetiStartAmount = 2363; //leva
    double cvetiCurrentAmount = (cvetiSharesCurrPrice + cvetiLeftUSD) * usdPrice;
    
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed;
    ss << std::right << std::setw(20) << "Cveti: " << std::right << std::setw(18) << cvetiZaem << std::endl
       << std::right << std::setw(20) << "Sergo: " << std::right << std::setw(18) << sergoZaem << std::endl 
       << std::right << std::setw(20) << "Psiho: " << std::right << std::setw(18) << psihoZaem << std::endl
       << std::right << std::setw(20) << "Pepo: " << std::right << std::setw(18) << pepoZaem << std::endl
       << std::right << std::setw(20) << "Total: " << std::right << std::setw(18) << (cvetiZaem + sergoZaem + psihoZaem + pepoZaem) << std::endl;
    
    double bank = 13593.48;
    double revolut = 146.82 + 2300.48;
    double IBActivesUSD = 7214.99 * usdPrice;
//    double IBActivesEURO = 1000 * euroPrice;
    double inMe = 55;
    double totalLoan = cvetiZaem + sergoZaem + psihoZaem + pepoZaem;
//    double gold1g = (102 * 14);
    double gold20g = (2 * 1948);
    double zaemDo18 = 8300;
    
    ss << std::right << std::setw(20) << "In Me: " << std::right << std::setw(18)  << inMe << std::endl;
    ss << std::right << std::setw(20) << "Bank: " << std::right << std::setw(18)  << bank << std::endl;
    ss << std::right << std::setw(20) << "Revolut: " << std::right << std::setw(18) << revolut << std::endl;
    ss << std::right << std::setw(20) << "IBActivesUSD: " << std::right << std::setw(18) << IBActivesUSD << std::endl;
//    ss << std::right << std::setw(20) << "IBActivesEURO: " << std::right << std::setw(18) << IBActivesEURO << std::endl;
    ss << std::right << std::setw(20) << "zaemDo18: " << std::right << std::setw(18)<< zaemDo18 << std::endl;
    ss << std::right << std::setw(20) << "Cveti Amount: " << std::right << std::setw(18)<< -cvetiCurrentAmount << std::endl;
//    ss << std::right << std::setw(20) << "Gold 1g: " << std::right << std::setw(18) << gold1g << std::endl;
    ss << std::right << std::setw(20) << "Gold 20g: " << std::right << std::setw(18) << gold20g << std::endl;
    double actives = bank + revolut + inMe + totalLoan + gold20g + IBActivesUSD /*+ IBActivesEURO*/ - cvetiCurrentAmount;
    ss << std::right << std::setw(20) << "Total Money: "<< std::right << std::setw(18) << actives << std::endl;
    std::cout << ss.str() << std::endl;
//    calculateYearIncome(actives);

    calculateCurrMoney("\n************ 28/05/2020 08:50 ************\n", ss.str());
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
void calculateMoney(float buy, float sell, float& totalBuy, float& totalWin, int cycle) {
    float totalPay = 0;
    float totalSell = 0;
    for(int i = 0; i < cycle; i++) {
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
    constexpr int SELL1G102 = 102;
    constexpr int SELL1G103 = 103;
    constexpr int SELL20G = 2000;

    float spend = 0;
    float canWin = 0;
    std::cout << "November: ";
    calculatePercentIncrease(76, SELL1G102);
    calculateMoney(76, SELL1G102, spend, canWin, 5);
    std::cout << "December: ";
    calculatePercentIncrease(77, SELL1G102);
    calculateMoney(77, SELL1G102, spend, canWin, 5);
    std::cout << "Cveti RD: ";
    calculatePercentIncrease(77, SELL1G);
    calculateMoney(77, SELL1G, spend, canWin, 3);
    std::cout << "January: ";
    calculatePercentIncrease(80, SELL1G102);
    calculateMoney(80, SELL1G102, spend, canWin, 5);
    std::cout << "February: ";
    calculatePercentIncrease(81, SELL1G102);
    calculateMoney(81, SELL1G102, spend, canWin, 5);
    std::cout << "March: ";
    calculatePercentIncrease(80, SELL1G102);
    calculateMoney(80, SELL1G102, spend, canWin, 5);
    std::cout << "April: ";
    calculatePercentIncrease(81, SELL1G103);
    calculateMoney(81, SELL1G103, spend, canWin, 5);
    std::cout << "May: ";
    calculatePercentIncrease(80, SELL1G103);
    calculateMoney(80, SELL1G103, spend, canWin, 5);
    std::cout << "Juny: ";
    calculatePercentIncrease(83, SELL1G103);
    calculateMoney(83, SELL1G103, spend, canWin, 5);
    std::cout << "July: ";
    calculatePercentIncrease(88, SELL1G103);
    calculateMoney(88, SELL1G103, spend, canWin, 5);
    
    std::cout << "August: ";
    calculatePercentIncrease(92, SELL1G103);
    calculateMoney(92, SELL1G103, spend, canWin, 5);
    std::cout << "September: ";
    calculatePercentIncrease(98, SELL1G);
    calculateMoney(98, SELL1G, spend, canWin, 5);
    std::cout << "October: ";
    calculatePercentIncrease(96, SELL1G);
    calculateMoney(96, SELL1G, spend, canWin, 5);
    std::cout << "Bonus: ";
    calculatePercentIncrease(0, SELL1G);
    calculateMoney(0, SELL1G, spend, canWin, 5);
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
    if(start == 0) {
        percent = 0;
    }
    std::string temp = "Win: ";
    if(percent < 0) {
        temp = "Lose: ";
    }
    std::stringstream ss;
    ss << "Percent " << std::setw(8) << temp << std::fixed << std::setprecision(2) << std::setw(7) << percent << "%" 
            << " Start" << std::setw(10) << start << "$" << " End" << std::setw(10) << end << "$" <<
            " Dollars " << std::setw(8) << temp << std::setw(10) << end - start << "$";
    std::string result = ss.str();
    std::cout << result << std::endl;
    
    return result;
}
std::string totalWinInvesting(float start, float end) {
    float percent = ((end - start) / start) * 100.0f;
    if(start == 0) {
        percent = 0;
    }
    std::string temp = "Win: ";
    if(percent < 0) {
        temp = "Lose: ";
    }
    std::stringstream ss;
    ss <<  std::setw(10) << temp << std::fixed << std::setprecision(2) << std::setw(10) << percent << "%";
    return ss.str();
}
void calculateDayPercent(const std::string& date, float start, float end, const float invested, const float avaible) {
    const double avaibleMoney = avaible;
    const double totalInvested = invested;
    std::string day = date;
    std::ofstream file;
    file.open("invest/052020.txt", std::ios::out | std::ios::app);
    file << std::fixed << std::setprecision(2) << day << calculatePercentIncreaseInvest(start, end);
    file << std::setw(10) << " Cash:" << std::setw(10) << avaibleMoney << "$" << std::setw(10) << " Total:" << std::setw(10) << (end + avaibleMoney) << "$";
    file << std::setw(15) << " Invested:" << std::setw(10) << totalInvested 
         << std::setw(12) << "Total Win:" << std::setw(10) << (end + avaibleMoney) - totalInvested
         << std::setw(12) << "Percent" << totalWinInvesting(totalInvested, (end + avaibleMoney)) << std::endl;
    file.close();
}

void calculateCurrMoney(const std::string& date, const std::string& activity) {
    std::ofstream file;
    file.open("money/april.txt", std::ios::out | std::ios::app);
    file << date << std::endl << activity << "\n==============================================================\n";
    file.close();
}
void calculateInvesting() {
    //minus is because cveti money.
    const double investedMoney = 3680.0 + 546 + 3841.25;
    const double avaibleMoney = 1972.37 + 0.65;
    calculateDayPercent("27/05/2020: ",6424.54, 6533.26, investedMoney, avaibleMoney);
}
int main(int argc, char** argv) {

//    simpleTest();

//    calculateZaem();
    
//    caluclateYear("2019");
    
//    calculateInvesting();
    
    return 0;
}

