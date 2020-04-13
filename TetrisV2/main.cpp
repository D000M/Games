/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on June 7, 2019, 1:12 PM
 */

#include <cstdlib>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Examples/UDVector2.h"
#include "Game.h"
#include "MastersAlgs/SparseMatrix.h"
#include "MastersAlgs/Polynomial.h"
#include "MastersAlgs/LinkedList/C/CLinkedList.h"
#include "MastersAlgs/LinkedList/CPlusPlus/TestLL.h"
#include "MastersAlgs/LinkedList/C/CCircularLinkedList.h"
#include "MastersAlgs/LinkedList/C/CDoubleLinkedList.h"
#include "MastersAlgs/LinkedList/C/CCircularDoubleLinkedList.h"
#include "MastersAlgs/Stack/CStackArr.h"
#include "MastersAlgs/Stack/CStackLL.h"
#include "MastersAlgs/Stack/CPP/TestStack.h"
#include "MastersAlgs/queues/C/CQueue.h"
#include "MastersAlgs/queues/CPP/TestMyQueue.h"
#include "MastersAlgs/trees/C/CBinaryTree.h"
#include "MastersAlgs/trees/CPP/CppTreeTest.h"

using namespace std;

/*
 * 
 */
void testChapter1() {
    
    sf::RenderWindow window{sf::VideoMode{640, 480}, "First Window"};
    
    UDVector2i myIntVec{150, 20};
    
    std::cout << myIntVec.x << " " << myIntVec.y << std::endl;
    
    UDVector2f myFloatVec{12.5f, 10.3f};
    std::cout << myFloatVec.x << " " << myFloatVec.y << std::endl;

    window.setPosition(sf::Vector2i{250, 200});
    
    sf::RectangleShape myRect{sf::Vector2f{128.0f, 128.0f}};
    myRect.setFillColor(sf::Color::Red);
    myRect.setPosition(320, 240);
    myRect.setOrigin(myRect.getSize().x / 2, myRect.getSize().y / 2);   //Set center coord to the middle of the rectangle.
    
    
    sf::Texture texture;
    if(!texture.loadFromFile("resources/smallMario.png")) {
        std::cout << "Error loading File! " << std::endl; 
    }
    
    sf::Sprite marioSprite{texture};
    //or using sprite.setTexture(sf::Texture&); method
    marioSprite.setScale(sf::Vector2f{3.0f, 3.0f});
    sf::Vector2u spriteSize = texture.getSize();
    marioSprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
    sf::Vector2f increment{0.04f, 0.04f};
    
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close(); //When close button is clicked on the window exit.
            }
        }
        
        window.clear(sf::Color{192,192,192});
        //Draw Here
        if((marioSprite.getPosition().x + (spriteSize.x * 3 / 2) > window.getSize().x && increment.x > 0) ||
            (marioSprite.getPosition().x - (spriteSize.x * 3 / 2) < 0 && increment.x < 0)) {
            //reverse X axis direction
            increment.x = -increment.x;
        }
        
        if((marioSprite.getPosition().y + (spriteSize.y * 3 / 2) > window.getSize().y && increment.y > 0) ||
            (marioSprite.getPosition().y - (spriteSize.y * 3 / 2) < 0 && increment.y < 0)) {
            //reverse Y axis direction
            increment.y = -increment.y;
        }
        
        marioSprite.setPosition(marioSprite.getPosition() + increment);
        
        window.draw(marioSprite);
        window.draw(myRect);
        
        window.display();
    }
}

int recursiveBinarySearch(int left, int right, int arr[], int key) {
    
    int middle = (left + right) / 2;
    
    if(left > right) {
        return -1;      //Element not found.
    }
    else if(arr[middle] == key) {
        return middle;
    }
    else if(arr[middle] > key) {
        return recursiveBinarySearch(left, middle - 1, arr, key);
    }
    else if(arr[middle] < key) {
        return recursiveBinarySearch(middle + 1, right, arr, key);
    }
}

void calculateZaem() {
    double pepoZaem = 200 + 300 + 100 + 100;
    double cvetiZaem = 162 + 160 + 162 + 160 + 166 + 70 + 85 + 80 + 176 + 184 + 196;
    double sergoZaem = 180 + 300 + 70 + 85 + 700 + 80;
    double stelaZaem = 400 + 70 + 47;
    double psihoZaem = 80;
    
    std::cout << "Pepo: " << pepoZaem << "\nCveti: " << cvetiZaem << "\nSergo: " << sergoZaem << "\nStela: " << stelaZaem <<
        "\nPsiho: " << psihoZaem << "\nTotal: " << (pepoZaem + cvetiZaem + sergoZaem + stelaZaem + psihoZaem) << std::endl;
}

long long int recFib(int n) {
    if(n <= 1) {
        return 1;
    }
    return recFib(n - 1) + recFib(n - 2);
}

int main(int argc, char** argv) {

//    Game game;
//    
//    while(!game.getWindow()->isDone()) {
//        game.handleInput();
//        game.update();
//        game.render();
//        game.restartClock();
//    }
//    testCppTree();

//    testCppTree();
    
//    bool left = true;
//    bool right = true;
//    if(left ^ right) {
//        std::cout << "True!\n";
//    }
//    else {
//        std::cout << "False!\n";
//    }

    testBST();
    
    return 0;
}

