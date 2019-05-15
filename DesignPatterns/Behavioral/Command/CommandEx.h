/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommandEx.h
 * Author: default
 *
 * Created on May 15, 2019, 3:57 PM
 */

#ifndef COMMANDEX_H
#define COMMANDEX_H

/**
Command Coding Exercise

Implement the Account::process()  function to process different account commands. The rules are obvious:

    success  indicates whether the operation was successful
    You can only withdraw money if you have enough in your account
 */
namespace CommandEx {
    
    struct Command {
        enum Action { deposit, withdraw } action;
        int amount{0};
        bool success{false};
    };
    
    struct Account {
        int balance{0};
        
        void process(Command& cmd) {
            switch(cmd.action) {
                case Command::Action::deposit:
                    balance += cmd.amount;
                    cmd.success = true;
                    std::cout << "Deposit Success!\n";
                    break;
                case Command::Action::withdraw:
                    if(balance - cmd.amount > 0) {
                        balance -= cmd.amount;
                        cmd.success = true;
                        std::cout << "Withdrew Success!\n";
                    }
                    else {
                        cmd.success = false;
                        std::cout << "Withdrew Fail!\n";
                    }
                    break;
            }
        }
    };
    
    void testCommandEx() {
        Account myAcc;
        Command deposit{Command::Action::deposit, 1000};
        myAcc.process(deposit);
        Command withdraw{Command::Action::withdraw, 1001};
        myAcc.process(withdraw);
    }
}

#endif /* COMMANDEX_H */

