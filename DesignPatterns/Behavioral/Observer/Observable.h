/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Observable.h
 * Author: default
 *
 * Created on May 21, 2019, 11:23 AM
 */

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <string>
#include <vector>
#include <algorithm>

template<typename T> class Observer;
/**
 * T is object which going to be observed
 * Using Currioslly recurring design pattern once again class Name : Observable<Name> 
 */
template<typename T>
class Observable {
    std::vector<Observer<T>*> observers;
public:
    
    /**
     * 
     * @param source of the object which provide notfication.
     * @param fieldName changed filed in the object.
     */
    void notify(T& source, const std::string& fieldName) {
        for(auto observer : observers) {
            observer->fieldChange(source, fieldName);
        }
    }
    
    /**
     * Subscribe to this particular Observable.
     */
    void subscribe(Observer<T>& observer) {
        observers.push_back(&observer);
    }
    
    /**
     * The object Leave the observable component
     * @param observer 
     */
    void unsubscribe(Observer<T>& observer) {
        //Erase and remove from vector.
        observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
    }
};

#endif /* OBSERVABLE_H */

