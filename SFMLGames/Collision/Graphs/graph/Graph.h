/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.h
 * Author: DooM
 *
 * Created on February 10, 2019, 1:44 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>


class Graph {
    std::vector<std::vector<int>> G;        //dvumeren masiv
    int size;                               //size na masiva
    std::vector<bool> bVisited;             //array za visited.
public:
    Graph(std::vector<std::vector<int>> graph, const int graphSize);
    void printVec();
    void clear();
    
    void DFS(int fromElem);
    void BFS(int fromElem);
private:
    
};

#endif /* GRAPH_H */

