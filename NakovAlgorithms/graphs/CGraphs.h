/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CGraphs.h
 * Author: default
 *
 * Created on January 9, 2019, 3:25 PM
 */

#ifndef CGRAPHS_H
#define CGRAPHS_H

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

namespace CGRAPHS {

//Maksimalen broi vurhove na grafa
#define MAXN 200          
//Broi na vurhovete v grafa
const int n = 15;    
//Obhojdane v shirina s nachalo vryh 5
const unsigned int v = 5;   
    
//Nai kratuk put
const unsigned int begin = 10;   //Nachalo na putq
const unsigned int exit = 15;    //Krai na putq

//matrica na susedstvo na grafa
int A[MAXN][MAXN] = {
//    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
//    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
//    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
//    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
//    { 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 }
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
}; //end of matrix A

int pred[MAXN];
char used[MAXN];
char vertices[MAXN];

//Funkcia na obhojdane v shirina ot daden vruh
//Breadth First Search
void BFS(unsigned i) {
    unsigned k, j, p, queue[MAXN], currentVert, levelVertex, queueEnd;
    
    for(k = 0; k < n; k++) {
        queue[k] = 0;
        used[k] = 0;
    }
    queue[0] = i;
    used[i] = 1;
    currentVert = 0;
    levelVertex = 1;
    queueEnd = 1;
    int level = 1;
    while(currentVert < queueEnd) { //Dokato opashkata ne e prazna
        printf("Level %u: ", level);
        level++;
        for(p = currentVert; p < levelVertex; p++) {
            //p - vzemame poredniq element ot opashkata
            printf("%u ", queue[p] + 1);
            currentVert++;
            vertices[queue[p]] = 1;
            
            //Ako sme namerili krainia put nqma smisyl da produljavame obhojdaneto. 
//            if(queue[p] + 1 == exit) {
//                pred[j] = queue[p];
//                levelVertex = queueEnd;
//                break;
//            }
            ////////////////
            
            
            //Za vseki neobhoden naslednik j na queue[p]
            for(j = 0; j < n; j++) {
                if(A[queue[p]][j] && !used[j]) {
                    queue[queueEnd++] = j;
                    used[j] = 1;
                    pred[j] = queue[p];
                }
            }
        }
        printf("\n");
        levelVertex = queueEnd;
    }
}   //End of BFS(unsinged i);


//Otpechatva vurhovete ot minimalnia put i vrushta duljinata mu
unsigned printPath(unsigned j) {
    unsigned count = 1;
    if(pred[j] > -1) {
        count += printPath(pred[j]);
    }
    printf("%u ", j + 1); //Otpechatva prednia vryh ot namereniq put
    return count;
}

void solve(unsigned start, unsigned end ) {
    unsigned k;
    for(k = 0; k < n; k++) {
        used[k] = 0;
        pred[k] = -1;
    }
    BFS(start);
    if(pred[end] > -1) {
        printf("Namereniqt put e: \n");
        printf("\nDuljinata na putq e %u: \n", printPath(end));
    }
    else {
        printf("Ne Sushtestvuva put mejdu dvata vurha!\n");
    }
}

void testShortestPath() {
    solve(begin - 1, exit - 1);
}

void testCBFSGraph() {
    printf("Obhojdane v shirina ot vryh %u: \n", v);
    BFS(v - 1);
    for(int i = 0; i < n; i++) {
        if(!vertices[i]) {
            printf("Obhojdane v shirina ot vryh %u: \n", i + 1);
            BFS(i);
            break;
        }
    }
}

//Obhojdane v dulbochina Recursivno
//Deapth First Search
void DFS(unsigned i) {
    unsigned k;
    used[i] = 1;
    printf("%u ", i + 1);
    for(k = 0; k < n; k++) {
        if(A[i][k] && !used[k]) {
            DFS(k);
        }
    }
} //End of DFS(unsigned i);

//Proverka za ciklichnost na graf
char cycle;

void checkCycleDFS(unsigned i, int parent) {
    unsigned k;
    used[i] = 1;
    
    for(k = 0; k < n; k++) {
        if(cycle) {
            return;
        }
        if(A[i][k]) {
            if(used[k] && k != parent) {
                printf("Grafyt e ciklichen! \n");
                cycle = 1;
                return;
            }
            else {
                if(k != parent) {
                    checkCycleDFS(k, i);
                }
            }
        }
    }
}

void testCycleDFS() {
    unsigned k, i;
    for(k = 0; k < n; k++) {
        used[k] = 0;
    }
    cycle = 0;
    for(i = 0; i < n; i++) {
        if(!used[i]) {
            checkCycleDFS(i, -1);
        }
        if(cycle) {
            break;
        }
    }
    if(cycle == 0) {
        printf("Grafyt e Dyrvo (Ne sydyrja cikli)! \n");
    }
}
/////////////////////////////////////////////////////


//////////Namirane na vsichki vyzmojni putishta v Graf
unsigned path[MAXN], length;
void printPath2(void) {
    unsigned k;
    for(k = 0; k <= length; k++) {
        printf("%u ",path[k] + 1);
    }
    printf("\n");
}


//Namira vsichki vuzmojni putishta mejdu vurhovete (i, j)
void allDFS(unsigned i, unsigned j) {
    unsigned k;
    
    //Duno na rekursiata.
    if(i == j) {
        path[length] = j;
        printPath2();
        return;
    }
    
    //Markirane na poseteniq vruh
    used[i] = 1;
    path[length++] = i;
    
    //Recursia za vsichki susedi na i;
    for(k = 0; k < n; k++) {
        if(A[i][k] && !used[k]) {
            allDFS(k, j);
        }
    }
    //Vryshtane razmarkirane na poseteniq vryh
    used[i] = 0;
    length--;
}

void testAllDFS() {
    unsigned k;
    for(k = 0; k < n; k++) {
        used[k] = 0;
    }
    length = 0;
    printf("Prosti putishta mejdu %u i %u: \n", begin, exit);
    allDFS(begin - 1, exit - 1);
}
///////////////////////////////////////////////////


void testCDFSGraph() {
    unsigned k;
    for(k = 0; k < n; k++) {
        used[k] = 0;
    }
    printf("Obhojdane v dulbochina ot vryh %u: \n", v);
    DFS(v - 1);
    printf("\n");
}
///////////////////////////////////////////////////


} //end of namespace CGRAPH



#ifdef __cplusplus
}
#endif

#endif /* CGRAPHS_H */

