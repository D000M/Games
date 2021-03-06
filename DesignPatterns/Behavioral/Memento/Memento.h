/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memento.h
 * Author: default
 *
 * Created on May 20, 2019, 3:18 PM
 */

#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>
#include <memory>
#include <vector>

namespace Memento {
    
    //Snapshot of bank account to save states
    //Can be inner class too
    class Memento {
        int balance;
    public:
        Memento(int balance)
            : balance(balance) {
        }
        friend class BankAccount; 
        friend class BankAccount2;  //For Undo and Redo Memento
    };
    
    class BankAccount {
    private:
        int balance{0};
    public:
        BankAccount(int balance)
            : balance(balance) {
        }
        Memento deposit(int balance) {
            this->balance += balance;
            return {this->balance};
        }    
        
        void restore(const Memento& m) {
            this->balance = m.balance;
        }
        friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj) {
            // Write obj to stream
            os << "balance: " << obj.balance; 
            return os;
        }

    };

    void testMemento() {
        BankAccount ba{100};
        auto m1 = ba.deposit(50);   //150
        auto m2 = ba.deposit(25);   //175
        
        std::cout << ba << "\n";
        ba.restore(m1);
        std::cout << "Back To m1: " << ba << std::endl;
        ba.restore(m2);
        std::cout << "Back To m2: " << ba << std::endl;
    }
    
    ///Undo and Redo mechanism with Momento, Story every single Momento generated by BankAccount2 into BankAccount2.
    //This way we can restory every single transaction every done in this BankAccount2
    class BankAccount2 {
        int balance;
        std::vector<std::shared_ptr<Memento>> changes;
        int current;
    public:
        BankAccount2(int balance)
            : balance(balance) {
                changes.emplace_back(std::make_shared<Memento>(balance));
                current = 0;
        }
        
        std::shared_ptr<Memento> deposit(int amount) {
            this->balance += amount;
            auto m = std::make_shared<Memento>(this->balance);
            changes.push_back(m);
            ++current;
            return m;
        }

        void restore(const std::shared_ptr<Memento>& m) {
            if(m) { //Check for default initialized shared_ptr, 
                this->balance = m->balance;
                changes.push_back(m);
                current = changes.size() - 1;
            }
        }
        
        std::shared_ptr<Memento> undo() {
            if(current > 0) {
                --current;
                auto m = changes.at(current);
                this->balance = m->balance;
                return m;
            }
            return {};  //Returns default shared_ptr constructor without object thats why we need check if(m) in restore() method
        }
        std::shared_ptr<Memento> redo() {
            if(current + 1 < changes.size()) {
                ++current;
                auto m = changes.at(current);
                this->balance = m->balance;
                return m;
            }
            return {};  //Returns default shared_ptr constructor without object thats why we need check if(m) in restore() method
        }
        friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj) {
            // Write obj to stream
            os << "balance: " << obj.balance;
            return os;
        }

    };  //End BankAccount2
    
    //Test Undo and Redo
    void testBankAccount2() {
        BankAccount2 ba{100};
        ba.deposit(50);
        ba.deposit(25);
        
        std::cout << "Initial " << ba << std::endl;
        ba.undo(); 
        std::cout << "Undo 1: " << ba << std::endl;
        ba.undo(); 
        std::cout << "Undo 2: " << ba << std::endl;
        ba.redo();
        std::cout << "Redo: " << ba << std::endl;
    }
}

#endif /* MEMENTO_H */

