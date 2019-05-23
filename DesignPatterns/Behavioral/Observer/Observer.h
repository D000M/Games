/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Observer.h
 * Author: default
 *
 * Created on May 21, 2019, 11:07 AM
 */

#ifndef OBSERVER_H
#define OBSERVER_H


#include <string>


template<typename T>
class Observer {
    public:
        /**
         * 
         * @param source Reference to the object we actually change
         * @param fieldName name of the field that change
         */
        virtual void fieldChange(T& source, const std::string& fieldName) = 0;
};

#endif /* OBSERVER_H */

