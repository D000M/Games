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

/*
 * 01
 * Изхарчени пари за Date 01 06 2019 април: -268лева.
 * Получени пари за Date 01 06 2019 април: 0лева.
 * Total Income: 0 - 268 = -268
 * 
 * 
 * 02
    Average Outcome Per Day: -154
    Average Income Per Day: 0

 * 03
 *  Average Outcome Per Day: -263.64
    Average Income Per Day: 0

 * 04
 *  Average Outcome Per Day: -204.255
    Average Income Per Day: 0
 
 * 05
 *  Average Outcome Per Day: -169.056
    Average Income Per Day: 0

 * 06
 * Average Outcome Per Day: -143.147
   Average Income Per Day: 0

 * 07
 *  Average Outcome Per Day: -129.839
    Average Income Per Day: 0

 * 08
 *  Average Outcome Per Day: -120.484
    Average Income Per Day: 0

 * 09
 *  Average Outcome Per Day: -118.986
    Average Income Per Day: 0


 * 10
 *  Average Outcome Per Day: -122.197
    Average Income Per Day: 0

 * 11
 *  Average Outcome Per Day: -121.443
    Average Income Per Day: 9.09091
 * 
 * 12
 *  Average Outcome Per Day: -113.156
    Average Income Per Day: 8.33333

 * 13
 *  Average Outcome Per Day: -106.298
    Average Income Per Day: 7.69231

 * 14
 *  Average Outcome Per Day: -107.301
    Average Income Per Day: 7.14286

 * 15
 *  Average Outcome Per Day: -107.342
    Average Income Per Day: 6.66667
 * 
 * 16
 *  Average Outcome Per Day: -104.193
    Average Income Per Day: 6.25
 * 
 * 17
 *  Average Outcome Per Day: -120.17
    Average Income Per Day: 5.88235

 */


void addTransaction(Program& p) {

}

void simpleTest() {
    Program p{""};

//    p.setDay("Date 18 06 2019");
//    p.setRecord("Обяд", -4.4);
//    p.setRecord("Солети", -0.4);
//    p.setRecord("Заем Серго", -300);
//    p.setRecord("Фантастико", -6);
//    p.setRecord("Квартира", -5);
//    p.setRecord("Вечеря", -60);
//    p.writeToFile("results/062019.txt");
    
    p.readFromFile("results/062019.txt");
    p.printAllItems();
    p.printAveragePerDay("results/062019.txt");
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

//    towerOfHanoi(3, "A", "B", "C");
    
    return 0;
}

