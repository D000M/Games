/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VirtualProxy.h
 * Author: default
 *
 * Created on May 14, 2019, 4:26 PM
 */

#ifndef VIRTUALPROXY_H
#define VIRTUALPROXY_H

#include <string>
#include <iostream>


namespace VirtualProxy {
    struct Image {
        virtual void draw() = 0;
        virtual ~Image() = default;
    };
    
    struct Bitmap : Image {
        Bitmap(const std::string& filename) {
            std::cout << "Loading a bitmap from: " << filename << std::endl;
        }
        void draw() override{
            std::cout << "Drawing bitmap\n";
        }
        ~Bitmap() {
            std::cout << "Bitmap Destroyed!\n";
        }
    };
    
    struct LazyBitmap : Image { //Proxy wont load bitmap but save the file, until draw method is needed.
        LazyBitmap(const std::string& filename) : filename{filename} {}
        void draw() override {
            if(!bmp) {
                bmp = new Bitmap{filename};
            }
            bmp->draw();
        }
        ~LazyBitmap() {
            if(bmp != nullptr) {
                delete bmp;
                bmp = nullptr;
            }
        }
    private:
        std::string filename;
        Bitmap* bmp{nullptr};       //Wont be necessery to use bmp = new Bitmap in the constructor.
    };
    void triangleTest() {
        
        struct Triangle {
            float sideA;
            float sideB;
        };
        constexpr int SIZE = 10;
        float sideAArr[SIZE] = {5, 6, 12, 4, 1, 4, 10, 8, 15, 3};
        float sideBArr[SIZE] = {16, 26, 4, 8, 9, 3, 5, 18, 20, 9};
        
        Triangle arr[SIZE];
        for(int i = 0; i < SIZE; i++) {
            arr[i].sideA = sideAArr[i];
            arr[i].sideB = sideBArr[i];
        }
        
        int SMaxIndex = 0;
        float SMax = 0;
        
        for(int i = 0; i < SIZE; i++) {
            float S = (arr[i].sideA * arr[i].sideB) / 2;
            if(S > SMax) {
                SMaxIndex = i;
                SMax = S;
            }
        }
        std::cout << "Biggest Triangle is on index: " << SMaxIndex << ", And S = " << SMax << std::endl; 
        
    }
    
    void testVirtualProxy() {
        Bitmap bmp{"pokemon.png"};
        bmp.draw();
        
        LazyBitmap bmp2{"pokemon.png"};  //now we can just call LazyBitmap and the bmp will be call only when draw() method is call
        bmp2.draw();

        //Not A Proxy :)
        triangleTest();
    }
    
    
}

#endif /* VIRTUALPROXY_H */

