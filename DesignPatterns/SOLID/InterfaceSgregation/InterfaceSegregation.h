/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InterfaceSegregation.h
 * Author: default
 *
 * Created on April 11, 2019, 1:39 PM
 */

#ifndef INTERFACESEGREGATION_H
#define INTERFACESEGREGATION_H

namespace InterfaceSegregation {
    struct Document;
    
    //Wrong way
    //Interface for machines
    struct IMachine {
        virtual void print(Document& doc) = 0;
        virtual void scan(Document& doc) = 0;
        virtual void fax(Document& doc) = 0;
    };
    //Now we can create multi function divice 
    struct MFP : IMachine {
        void print(Document& doc) override {} //Ok
        void scan(Document& doc) override {}  //Ok
        void fax(Document& doc) override {}   //Ok
    };
    //What about if we want to create only printer or fax?
    struct Fax : IMachine {
        void print(Document& doc) override {}   //? maybe exception? or empty method? or return? 
        void scan(Document& doc) override {}    //? maybe exception? or empty method? or return?
        void fax(Document& doc) override {}     //Ok
    };
    ///////////////////////////// End Wrong Way
    
    //We should create different interfaces for every type of machine. Interface Segregation Principle
    struct IPrint {
        virtual void print(Document& doc) = 0;
    };
    struct IScanner {
        virtual void scan(Document& doc) = 0;
    };
    struct IFax {
        virtual void fax(Document& doc) = 0;
    };
    
    //Now we can implement scanner
    struct Scanner : IScanner {
        void scan(Document& doc) override {}    //Ok we override only scan method
    };
    
    //Now if we want to implement a printer
    struct Printer : IPrint {
        void print(Document& doc) override {}   //Now we have only print method OK
    };
    
    //Or for more complex machine we can create another interface
    struct IMachine : IPrint, IScanner {
    };
    struct PrinterAndScanner : IMachine {
        //We use Decorator pattern here
        IPrint& printer;
        IScanner& scanner;
        
        PrinterAndScanner(IPrint& print, IScanner& scan) :
            printer(print), scan(scan) {
        }

        void print(Document& doc) override {
            printer.print(doc);
        } //Ok we can Print
        void scan(Document& doc) override {
            scanner.scan(doc);
        }  //Ok we can Scan
    };
}


#endif /* INTERFACESEGREGATION_H */

