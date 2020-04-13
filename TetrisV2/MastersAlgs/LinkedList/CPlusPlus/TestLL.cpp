/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestLL.h"
#include "LinkedList.h"
#include "ListUtils.h"
#include <iostream>

void testLinkedListCPP() {
    LinkedList list{1000};
    std::cout << list.length() << std::endl;
    list.insertAt(0, 5);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(0, 1);
    std::cout << list.length() << std::endl;
    list.insertAt(0, 10);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(4, 12);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(2, 20);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(2, 22);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(22, 33);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.insertAt(7, 100);
    std::cout << list.lengthR(list.getNode()) << std::endl;
    list.printList();
    std::cout << "Sum Iterative: " << ListUtils::sumOfList(list) << std::endl;
    std::cout << "Sum Recursive: " << ListUtils::sumOfListR(list.getNode()) << std::endl;
    list.printList();
    std::cout << "Min Iterative: " << ListUtils::min(list) << std::endl;
    std::cout << "Min Recursive: " << ListUtils::minR(list.getNode()) << std::endl;
    std::cout << "Max Iterative: " << ListUtils::max(list) << std::endl;
    std::cout << "Max Recursive: " << ListUtils::maxR(list.getNode()) << std::endl;
    
    std::cout << "Find Element 5 Iteraitive: "; 
    if(ListUtils::linearSearch(list, 5)) {
        std::cout << " Element Found\n";
    }
    else {
        std::cout << " Element Not Found\n";
    }
    
    std::cout << "Find Element 6 Iteraitive: "; 
    if(ListUtils::linearSearch(list, 6)) {
        std::cout << " Element Found\n";
    }
    else {
        std::cout << " Element Not Found\n";
    }
    
    std::cout << "Find Element 5 Recursive: ";
    if(ListUtils::linearSearchR(list.getNode(), 5)) {
        std::cout << " Element Found\n";
    }
    else {
        std::cout << " Element Not Found\n";
    }
    
    std::cout << "Find Element 6 Recursive: ";
    if(ListUtils::linearSearchR(list.getNode(), 6)) {
        std::cout << " Element Found\n";
    }
    else {
        std::cout << " Element Not Found\n";
    }
    
    int a = list.deleteAt(1);
    int b = list.deleteAt(2);
    int c = list.deleteAt(3);
    list.printListR();
}