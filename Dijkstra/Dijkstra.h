/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dijkstra.h
 * Author: default
 *
 * Created on February 20, 2019, 1:22 PM
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>


class Dijkstra {
    /**
     * Class to represent a single vertex.
     */
    class Vertex {
    public:
        Vertex(bool l_visited, std::string l_value) 
            : m_bIsVisited{l_visited},
              m_sValue{l_value} {
                std::cout << "Vertex CREATED!\n";
        } //end of Vertex constructor.
        ~Vertex() {
            std::cout << "Vertex with value: [" << m_sValue << "] DESTROYED!\n";
        }
    private:
        bool m_bIsVisited;
        std::string m_sValue;
        void setVisited(bool l_visited) {
            m_bIsVisited = l_visited;
        }
        bool getIsVisited() const {
            return m_bIsVisited;
        } 
    }; //end of nested class Vertex
    
public:
    Dijkstra();
    ~Dijkstra();
    
    //Methods
    void createVertex(const std::string& l_val);
    void createMatrix(int row, int col, int weight);
    
    void executeLoads();
private:
    std::vector<std::unique_ptr<Vertex>> m_Vertices;
    std::vector<std::vector<int> > m_matrix;
    
    void loadVertices();
    void loadMatrix();
    void printMatrix();
    void setMatrixSize();
};

#endif /* DIJKSTRA_H */

