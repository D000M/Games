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

#include "Program.h"

using namespace std;

/**
 * 01
 *  Average Outcome Per Day: -506.44
    Average Income Per Day: 0

 * 02
 *  Average Outcome Per Day: -282.36
    Average Income Per Day: 0

 * 03
 *  Average Outcome Per Day: -195.097
    Average Income Per Day: 0
 * 
 * 04
 *  Average Outcome Per Day: -152.485
    Average Income Per Day: 130

 * 05
 *  Average Outcome Per Day: -136.002
    Average Income Per Day: 104

 * 06
 *  Average Outcome Per Day: -117.9
    Average Income Per Day: 86.6667

 * 07
 *  Average Outcome Per Day: -104.606
    Average Income Per Day: 74.2857

 * 08
 *  Average Outcome Per Day: -95.5812
    Average Income Per Day: 108.75
 * 
 * 09
 *  Average Outcome Per Day: -90.1389
    Average Income Per Day: 96.6667

 * 10
 *  Average Outcome Per Day: -82.965
    Average Income Per Day: 87
 * 
 * 11
 *  Average Outcome Per Day: -81.1409
    Average Income Per Day: 79.0909

 * 12
 *  Average Outcome Per Day: -77.1883
    Average Income Per Day: 72.5
 * 
 * 13
 *  Average Outcome Per Day: -77.8969
    Average Income Per Day: 66.9231
 */

void addTransaction(Program& p) {

}

void simpleTest() {
    Program p{""};

    p.setDay("Date 14 10 2019");
    p.setRecord("Закуска", -0.5);
    p.setRecord("Месо", -13.05);
    p.setRecord("Зеленчуци", -5.1);
    p.setRecord("Фантастико", -16.41);
//    p.setRecord("Бира", -11.1);
    p.setRecord("Квартира", -5);
//    p.setIncome("Приход Серго", 50);
//    p.setIncome("Приход Цвети", 300);
    p.writeToFile("results/102019.txt");
    
    p.readFromFile("results/102019.txt");
    p.printAllItems();
    p.printAveragePerDay("results/102019.txt");
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


int main(int argc, char** argv) {

    simpleTest();

    
    return 0;
}

