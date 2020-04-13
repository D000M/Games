/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dijkstra.cpp
 * Author: default
 * 
 * Created on February 20, 2019, 1:22 PM
 */

#include "Dijkstra.h"

Dijkstra::Dijkstra() {
}

Dijkstra::~Dijkstra() {
//    for(auto& a : m_Vertices) {
//        delete a;
//    }
}

void Dijkstra::createVertex(const std::string& l_val) {
    m_Vertices.push_back(std::unique_ptr<Vertex>(new Vertex(false, l_val)));
}

void Dijkstra::createMatrix(int row, int col, int weight) {
    m_matrix[row][col] = weight;
    m_matrix[col][row] = weight;
}

void Dijkstra::executeLoads() {
    loadVertices();
    setMatrixSize();
    loadMatrix();
    printMatrix();
}
//0A 1B 2C 3D 4E 5F 6G 7H 8I 9J 10K 11L 12M 13N 14O
void Dijkstra::loadMatrix() {
    createMatrix(0, 1, 53);     //A -> B = 53
    createMatrix(0, 2, 12);     //A -> C = 12   
    createMatrix(0, 5, 18);     //A -> E = 18
    createMatrix(0, 8, 25);     //A -> I = 25
    createMatrix(0, 10, 68);    //A -> K = 68
    createMatrix(0, 13, 14);    //A -> N = 14
    createMatrix(1, 2, 5);      //B -> C = 5
    createMatrix(1, 7, 86);     //B -> H = 82
    createMatrix(1, 11, 30);    //B -> L = 30
    createMatrix(2, 3, 19);     //C -> D = 19
    createMatrix(2, 12, 50);    //C -> M = 50
    createMatrix(3, 5, 13);     //D -> F = 13 
    createMatrix(3, 4, 31);     //D -> E = 31
    createMatrix(1, 4, 6);      //B -> E = 6
    createMatrix(4, 6, 16);     //E -> G = 16
    createMatrix(4, 8, 27);     //E -> I = 27
    createMatrix(5, 8, 19);     //F -> I = 19
    createMatrix(6, 8, 99);     //G -> I = 99
    createMatrix(6, 9, 60);     //G -> J = 60
    createMatrix(7, 9, 41);     //H -> J = 41
    createMatrix(8, 10, 2);     //I -> K = 2
    createMatrix(8, 11, 5);     //I -> L = 5
    createMatrix(9, 13, 56);    //J -> N = 56
    createMatrix(9, 14, 78);    //J -> O = 78
    createMatrix(10, 11, 1);    //K -> L = 1
    createMatrix(11, 12, 4);    //L -> M = 4
    createMatrix(11, 14, 62);   //L -> O = 62
    createMatrix(12, 1, 8);     //M -> B = 8
}

void Dijkstra::loadVertices() {
    createVertex("A");
    createVertex("B");
    createVertex("C");
    createVertex("D");
    createVertex("E");
    createVertex("F");
    createVertex("G");
    createVertex("H");
    createVertex("I");
    createVertex("J");
    createVertex("K");
    createVertex("L");
    createVertex("M");
    createVertex("N");
    createVertex("O");
}

void Dijkstra::setMatrixSize() {
    std::size_t matrixSize = m_Vertices.size();
    m_matrix.resize(matrixSize);
    for(int i = 0; i < matrixSize; ++i) {
        m_matrix.at(i).resize(matrixSize);
    }
}

void Dijkstra::printMatrix() {
    for(int i = 0; i < m_matrix.size(); ++i) {
        std::cout << "\t" <<char(i + 65);
    }
    std::cout << std::endl;
    for(int i = 0; i < m_matrix.size(); ++i) {
        std::cout << char(i + 65) << ":";
        for(int j = 0; j < m_matrix.size(); ++j) {
            std::cout << "\t" << m_matrix[i].at(j);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}


