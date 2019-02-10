/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.cpp
 * Author: DooM
 * 
 * Created on February 10, 2019, 1:44 PM
 */

#include "Graph.h"
#include <iostream>

Graph::Graph(std::vector<std::vector<int>> graph, const int graphSize) { 
    G = graph;
    size = graphSize;
    for(int i = 0; i < size; i++) {
        bVisited.push_back(false);
    }
}

void Graph::printVec() {
    for(const auto elem : G) {
        for(const auto e : elem) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::DFS(int fromElem) {
    bVisited.at(fromElem) = true;
    std::cout << fromElem + 1 << " ";
    for(int col = 0; col < bVisited.size(); ++col) {
        if(G.at(fromElem).at(col) == 1 && bVisited.at(col) == false) {
            DFS(col);
        }
    }
}

void Graph::BFS(int fromElem) {
    std::cout << std::endl;
    int elements[bVisited.size()];    
    for(int i = 0; i < size; ++i) {
        bVisited[i] = false;
        elements[i] = 0;
    }
    
    elements[0] = fromElem;
    bVisited[fromElem] = true;
    
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
                if(G[elements[i]][j] == 1 && bVisited[j] == false) {
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

void Graph::clear() {
    for(int i = 0; i < bVisited.size(); ++i) {
        bVisited.at(i) = false;
    }
}
