/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CppGraphs.h
 * Author: default
 *
 * Created on January 11, 2019, 10:18 AM
 */

#ifndef CPPGRAPHS_H
#define CPPGRAPHS_H

#include <algorithm>
#include <iostream>


namespace GRAPHS {

constexpr int SIZE = 15;    
    
const int graphTable[SIZE][SIZE] = {
  // 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //2
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //5
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, //6
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, //7
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //8
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, //9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //10
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0}, //11
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, //12
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, //13
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, //14
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}  //15
    
    //Graph without cycle!
  // 1  2  3  4  5  6  7  
//    {0, 1, 0, 1, 1, 0, 0}, //1
//    {1, 0, 1, 0, 0, 1, 0}, //2
//    {0, 1, 0, 0, 0, 0, 0}, //3
//    {1, 0, 0, 0, 0, 0, 1}, //4
//    {1, 0, 0, 0, 0, 0, 0}, //5
//    {0, 1, 0, 0, 0, 0, 0}, //6
//    {0, 0, 0, 1, 0, 0, 0} //7


};

int path[SIZE];

/**
 * BFS - Breadth First Search - 
 * @param startElement starting element of the graph,
 * @param endOfPath - if we reach the end element stop searching.
 */
void BFS(int startElement, int endOfPath = -1) {
    bool visited[SIZE];
    std::fill_n(visited, SIZE, false);
    
    int queue[SIZE];
    std::fill_n(queue, SIZE, 0);
    
    queue[0] = startElement - 1;
    visited[startElement - 1] = true;
    int currVert = 0;
    int endVert = 1;
    int level = 1;
    int queueEnd = 1;
    int quitElem = endOfPath;
    int j;
    while(currVert < queueEnd) {
        std::cout << "Level " << level++ << ": ";
        
        for(int i = currVert; i < endVert; i++) {
            std::cout << queue[i] + 1 << " ";
            currVert++;
            
            //Stop cycle if searching element is found
            if(queue[i] + 1 == quitElem) {
                path[j] = queue[i];
                return;
            }
            
            for(j = 0; j < SIZE; j++) {
                if(graphTable[queue[i]][j] == 1 && visited[j] == false) {
                    queue[queueEnd++] = j;
                    visited[j] = true;
                    path[j] = queue[i];
                }
            }
        }
        std::cout << std::endl;
        endVert = queueEnd;
    }
    
}

int printPath(int pos) {
    int count = 1;
    if(path[pos] > -1) {
        count += printPath(path[pos]);
    }
    std::cout << pos + 1 << " ";
    return count;
}

void findShortestPath(int start, int end) {
    for(int i = 0; i < SIZE; i++) {
        path[i] = -1;
    }
    BFS(start, end);
    
    if(path[end - 1] > -1) {
        std::cout << "The Path is Found: \n";
        std::cout << "\nPath Length: " << printPath(end - 1) << std::endl;
    }
    else {
        std::cout << "There is no path between " << start << " and " << end<< std::endl; 
    }
}
////////////////////////////

bool isVisited[SIZE] = {false};
/**
 * Depth First Search through all elements in a graph
 * @param elem current vertix
 */
void DFS(int elem) {
    isVisited[elem] = true;
    std::cout << elem + 1 << " ";
    
    for(int i = 0; i < SIZE; i++) {
        if(graphTable[elem][i] && !isVisited[i]) {
            DFS(i);
        }
    }
}
///////////////////////////////

/**
 * Depth First Search for checking if there is cycle in the graph
 * @param currElem - current element, we are at this element right now
 * @param nextElem - next element, the elemen which we will check if is different from -1, if is than this graph has cycle
 */
bool isCycle = false;
void DFScheckForCycle(int currElem, int nextElem) {
    isVisited[currElem] = true;
    
    for(int i = 0; i < SIZE; i++) {
        if(isCycle) {   //Cycle is found exit the loop
            return;
        }
        if(graphTable[currElem][i]) {
            if(isVisited[i] && i != nextElem) {
                std::cout << "The Graph has Cycle!\n";
                isCycle = true;
                return;
            }
            else if(i != nextElem){
                DFScheckForCycle(i, currElem);
            }
        }
    }
}
////////////End check for Cycles


int pathLength = 0;

void printCurrPath() {
    for(int i = 0; i <= pathLength; i++) {
        std::cout << path[i] + 1 << " ";
    }
    std::cout << std::endl;
}
/**
 * Fild all paths in Graph from start to end
 * Recursive
 * @param currElem - start pos in Graph
 * @param nextElem - end pos in Graph
 */
void allDFS(int currElem, int nextElem) {
    
    //Bottom of the recursion, one path is found print the path.
    if(currElem == nextElem) {
        path[pathLength] = nextElem;
        printCurrPath();
        return;
    }
    
    isVisited[currElem] = true;
    path[pathLength++] = currElem;
    
    //Recursion for all neighbors of currElem.
    for(int i = 0; i < SIZE; i++) {
        if(graphTable[currElem][i] && isVisited[i] == false) {
            allDFS(i, nextElem);
        }
    }
    //Return from recursion: demark of curr Elem.
    isVisited[currElem] = false;
    pathLength--;
}
//////////////////////////////////////////////////////////////

//!?!?!?!
void allBFSpaths(int startElem, int endOfPath = -1) {
    bool visited[SIZE];
    std::fill_n(visited, SIZE, false);
    
    int queue[SIZE];
    std::fill_n(queue, SIZE, 0);
    
    queue[0] = startElem - 1;
    visited[startElem - 1] = true;
    
    int currVert = 0;
    int endVert = 1;
    int level = 1;
    int queueEnd = 1;
    int quitElem = endOfPath;
}

};

#endif /* CPPGRAPHS_H */

