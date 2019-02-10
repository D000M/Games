/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: DooM
 *
 * Created on February 10, 2019, 11:47 AM
 */

#include <cstdlib>
#include <iostream>

#include "graph/Graph.h"
using namespace std;

/*
 * 
 */

constexpr int size = 8;

bool bVisited[size];

void DFS(int graph[][size], int vertice) {
    bVisited[vertice] = true;
    std::cout << vertice + 1 << " ";
    for(int col = 0; col < size; ++col) {
        if(graph[vertice][col] == 1 && bVisited[col] == false) {
            DFS(graph, col);
        }
    }
}

int elements[size];

void BFS(int graph[][size], int vertice) {
    
    for(int i = 0; i < size; ++i) {
        bVisited[i] = false;
        elements[i] = 0;
    }
    
    elements[0] = vertice;
    bVisited[vertice] = true;
    
    int currVert = 0;
    int levelVert = 1;
    int queueEnd = 1;
    int level = 1;
    
    while(currVert < queueEnd) {
        std::cout << "Level " << level << ": ";
        level++;
        for(int i = currVert; i < levelVert; ++i) { //1 2  < 3   3 4 < 5
            
            std::cout << elements[i] + 1 << " ";
            currVert++; 
            for(int j = 0; j < size; ++j) {
                if(graph[elements[i]][j] == 1 && bVisited[j] == false) {
                    elements[queueEnd] = j;
                    queueEnd++; //5 //7 //8
                    bVisited[j] = true;
                } //end if
            } //end inner for
            
        } //end outer for
        std::cout << "\n";
        levelVert = queueEnd;   //3 //5 //8
    }
}
int main(int argc, char** argv) {
 
    int graph[size][size] = {
       // 1  2  3  4  5  6  7  8
        { 0, 1, 0, 0, 0, 0, 0, 0 }, // 1
        { 1, 0, 1, 0, 1, 0, 0, 0 }, // 2
        { 0, 1, 0, 1, 0, 1, 0, 0 }, // 3
        { 0, 0, 1, 0, 1, 0, 1, 0 }, // 4
        { 0, 1, 0, 1, 0, 0, 0, 0 }, // 5 
        { 0, 0, 1, 0, 0, 0, 0, 1 }, // 6
        { 0, 0, 0, 1, 0, 0, 0, 0 }, // 7
        { 0, 0, 0, 0, 0, 1, 0, 0 }, // 8
    };
     
    for(int i = 0; i < size; ++i) {
        bVisited[i] = false;
    }
    int fromVertice = 6;
//    std::cout << "Depth First Search From Vertice: " << fromVertice << ": ";
//    DFS(graph, fromVertice - 1);
//    std::cout << std::endl;
//    BFS(graph, fromVertice - 1); 
//    
//    for(int i = 0; i < size; i++) {
//        std::cout << elements[i] + 1 << " ";
//    }
    
    std::vector<std::vector<int>> vecGraph = {
       // 1  2  3  4  5  6  7  8
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
    };
    std::cout << std::endl;
    Graph g(vecGraph, 15);
//    g.printVec();
    g.DFS(10 - 1);
    g.BFS(10 - 1);
    return 0;
}

