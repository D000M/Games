/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CompositeCommand.h
 * Author: default
 *
 * Created on May 15, 2019, 3:10 PM
 */

#ifndef COMPOSITECOMMAND_H
#define COMPOSITECOMMAND_H

#include <vector>


//Composite Design Pattern + Command Design Pattern
namespace CompositeCommand {
    
    struct BankAccount {
        int balance{0};
        int overdraftLimit{-500};
        
        void deposit(int amount) {
            balance += amount;
            std::cout << "deposited: " << amount 
                    << ", balance is now: " << balance << std::endl; 
        }
        bool withdraw(int amount) { //Undo Part change to bool, default is void
            if(balance - amount >= overdraftLimit) {
                balance -= amount;
                std::cout << "withdrew: " << amount 
                    << ", balance is now: " << balance << std::endl;
                return true;    //Undo Part
            }
            return false;   //Undo Part
        }
        friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj) {
            // Write obj to stream
            os << "balance: " << obj.balance;
            return os;
        }

    }; //End BankAccount
    
    struct Command {
        bool succeeded;
        virtual void call() = 0;
        virtual void undo() = 0;    //Undo Part
    };
    
    struct BankAccountCommand : Command {
        BankAccount& account;
        enum Action { deposit, withdraw } action;
        int amount;
        
        BankAccountCommand(BankAccount& account, Action action, int amount)
            : account(account), action(action), amount(amount) {
            succeeded = false; //Undo Part
        }
        void call() override {
            switch(action) {
                case deposit:
                    account.deposit(amount);
                    succeeded = true;  //Undo Part
                    break;
                case withdraw: 
                    succeeded = account.withdraw(amount);   //Undo Part default is withoud bool
                    break;
            }
        }
        
        //Undo Part, Problem when user try to withdraw 1 000 000 so we need some flag for success operation.
        void undo() override {
            if(!succeeded) { //Undo Part
                return; //Undo Part
            } //Undo Part
            switch(action) {
                case deposit:
                    account.withdraw(amount);
                    break;
                case withdraw: 
                    account.deposit(amount);
                    break;
            }
        }

    };
    
    struct CompositeBankAccountCommand 
        : std::vector<BankAccountCommand>, Command {
        
        //Constructor
        CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand>& list)
            : std::vector<BankAccountCommand>(list) {
        }
        void call() override{
            for(auto& cmd : *this) {    //This Class is now vector so just iterate over itself
                cmd.call();
            }
        }
        void undo() override {
            for(auto it = rbegin(); it != rend(); ++it) {   //Because is a vector we can use member methods from base class std::vector
                it->undo();
            }   //Undo Part
        }

    };
    
    struct DependandCompositeCommand : CompositeBankAccountCommand {
        DependandCompositeCommand(const std::initializer_list<BankAccountCommand>& list)
            : CompositeBankAccountCommand(list) {
        }
        void call() override {
            bool ok = true;
            for(auto& cmd : *this) {
                if(ok) {
                    cmd.call();
                    ok = cmd.succeeded;
                }
                else {
                    cmd.succeeded = false;
                }
            }
        }

    };
    
    struct MoneyTransferCommand : DependandCompositeCommand {
        MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount) 
                : DependandCompositeCommand( 
            {    //We use std::initializer_list here.
                BankAccountCommand{ from, BankAccountCommand::withdraw, amount },
                BankAccountCommand{ to, BankAccountCommand::deposit, amount } 
            } ) //End of Base class Constructor
            { }
    };
    
    void testCommandPatternEx() {
        BankAccount account1, account2;
        account1.deposit(100);
        
        MoneyTransferCommand cmd{account1, account2, 5000};
        cmd.call();
        std::cout << "Account1: " << account1 << std::endl << "Account2: " << account2 << std::endl;
        
        cmd.undo();
        std::cout << "Account1: " << account1 << std::endl << "Account2: " << account2 << std::endl;
    }
}

#endif /* COMPOSITECOMMAND_H */

