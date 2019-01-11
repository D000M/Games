/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGraphs.h
 * Author: default
 *
 * Created on January 11, 2019, 10:43 AM
 */

#ifndef TESTGRAPHS_H
#define TESTGRAPHS_H

#include "library/CppGraphs.h"



namespace TEST {
    
    void testDFSCpp() {
        GRAPHS::BFS(1, 6);
    }
    
    void testBFSShortestPath() {
        GRAPHS::findShortestPath(1, 6);
    }
    
    void testDFS() {
        constexpr int startElem = 5; 
        GRAPHS::DFS(startElem - 1);
    }
    
    void testForCycleDFS() {
        for(int i = 0; i < GRAPHS::SIZE; i++) {
            if(!GRAPHS::isVisited[i]) {
                GRAPHS::DFScheckForCycle(i, -1);
            }
            if(GRAPHS::isCycle) {
                break;
            }
        }
        if(GRAPHS::isCycle == false) {
            std::cout << "The Graphs is actualy a Tree. Doesnt have any cycles!\n";
        }
    }
    
    void printAllPathsInGraph() {
        int a = 10;
        int b = 15;
        std::cout << "Simple paths between " << a << " and " << b << std::endl;
        GRAPHS::allDFS(a - 1, b - 1);
    }
    
}


#endif /* TESTGRAPHS_H */

