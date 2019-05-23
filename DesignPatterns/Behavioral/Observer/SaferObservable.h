/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SaferObservable.h
 * Author: default
 *
 * Created on May 21, 2019, 1:20 PM
 */

#ifndef SAFEROBSERVABLE_H
#define SAFEROBSERVABLE_H


#include <string>
#include <vector>
#include <algorithm>
//#include <boost/thread/m>
#include <condition_variable>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iterator>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>

template<typename T> class Observer;
/**
 * T is object which going to be observed
 * Using Currioslly recurring design pattern once again class Name : Observable<Name> 
 */
template<typename T>
class SaferObservable {
    std::vector<Observer<T>*> observers;
    using mutex_t  = boost::interprocess::interprocess_recursive_mutex;
    // or using mutex_t = boost::interpocess::interprocess_mutex;
    mutex_t mtx;
public:
    
    /**
     * 
     * @param source of the object which provide notfication.
     * @param fieldName changed filed in the object.
     */
    void notify(T& source, const std::string& fieldName) {
        
//        std::unique_lock<mutex_t> lock{mtx};    //Lock for thread safety
//        std::scoped_lock<mutex_t> lock{mtx};    //C++17
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_recursive_mutex> lock{mtx};
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock{mtx};
        for(auto observer : observers) {
            if(observer) {
                observer->fieldChange(source, fieldName);
            }
        }
    }
    
    /**
     * Subscribe to this particular Observable.
     */
    void subscribe(Observer<T>& observer) {
        
//        std::unique_lock<mutex_t> lock{mtx};    //Lock for thread safety
        //        std::scoped_lock<mutex_t> lock{mtx};    //C++17
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_recursive_mutex> lock{mtx};
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock{mtx};
        observers.push_back(&observer);
    }
    
    /**
     * The object Leave the observable component
     * @param observer 
     */
    void unsubscribe(Observer<T>& observer) {
        auto it = std::find(std::begin(observers), std::end(observers), &observer);
        if(it != std::end(observers)) {
            *it = nullptr;
        }
//        std::unique_lock<mutex_t> lock{mtx};    //Lock for thread safety
        //        std::scoped_lock<mutex_t> lock{mtx};    //C++17
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock{mtx};
//        //Erase and remove from vector.
//        observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
    }
};

#endif /* SAFEROBSERVABLE_H */

