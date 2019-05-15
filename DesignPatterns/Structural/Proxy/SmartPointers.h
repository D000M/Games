/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SmartPointers.h
 * Author: default
 *
 * Created on May 14, 2019, 3:59 PM
 */

#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <memory>


namespace SmartPointers {
    //Smart pointers are proxy to the normal pointers
    struct BankAccount{
        virtual ~BankAccount() = default;
        virtual void deposit(int amount) = 0;
        virtual void withdraw(int amount) = 0;
    };
    
    struct CurrentAccount : BankAccount {
        explicit CurrentAccount(const int balance) 
            : balance{balance} {}
        void deposit(int amount) override {
            balance += amount;
        }
        void withdraw(int amount) override {
            if(balance >= amount) {
                balance -= amount;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const CurrentAccount& obj) {
            // Write obj to stream
            
            return os << "balance: " << obj.balance;
        }

    private:
        int balance;
    };
    
    void testSmartPtrs() {
        BankAccount *a = new CurrentAccount(123);
        a->deposit(321);
        
        
        auto b = std::make_shared<CurrentAccount>(123);
        BankAccount* actual = b.get();  //Enhancement
        actual->deposit(345);
        b->withdraw(100);

        std::cout << a << std::endl << b << std::endl;
        delete a;
    }
}

#endif /* SMARTPOINTERS_H */

