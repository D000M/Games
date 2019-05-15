/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Command.h
 * Author: default
 *
 * Created on May 15, 2019, 1:57 PM
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>


namespace Command {
    
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
    
    void testCommandPattern() {
        BankAccount account;
        std::vector<BankAccountCommand> commands {
          BankAccountCommand{account, BankAccountCommand::deposit, 100},
          BankAccountCommand{account, BankAccountCommand::withdraw, 200}
        };
        
        std::cout << account << std::endl;
        for(auto& cmd : commands) {
            cmd.call();
        }
        
        //Undo Part
        for(auto it = commands.rbegin(); it != commands.rend(); ++it) {
            it->undo();
        }   //Undo Part
        
        std::cout << account << std::endl;
    }
}

#endif /* COMMAND_H */

