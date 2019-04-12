/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenClosedPrTemplates.h
 * Author: default
 *
 * Created on April 11, 2019, 11:52 AM
 */

#ifndef OPENCLOSEDPRTEMPLATES_H
#define OPENCLOSEDPRTEMPLATES_H

#include <vector>
      
//Specification Interface
template<typename T>
class IMySpecification {
public:
    virtual bool isSatisfied(T* obj) const = 0; 
};

//Filter Interface
template<typename T>
class IMyFilter {
public:
    virtual std::vector<T*> filterItems(const std::vector<T*> items, const IMySpecification<T>& specification) = 0;
};

template<typename T>
class MyAndSpecification : public IMySpecification<T> {
    
    const IMySpecification<T>& mFirst; 
    const IMySpecification<T>& mSecond;
    
    public:
        MyAndSpecification(const IMySpecification<T>& lFirst, const IMySpecification<T>& lSecond) 
                : mFirst{lFirst},
                  mSecond{lSecond} {}
    
    bool isSatisfied(T* obj) const override;

};


template<typename T>
bool MyAndSpecification<T>::isSatisfied(T* obj) const {
    return mFirst.isSatisfied(obj) && mSecond.isSatisfied(obj);
}

//Overload operator && to use specification of the type typeOne && typeTwo, instead of creating objects
template<typename T> 
MyAndSpecification<T> operator && (const IMySpecification<T>& lFirst, const IMySpecification<T>& lSecond) {
    return {lFirst, lSecond};
}


//For operator ||
template<typename T>
class MyOrSpecification : public IMySpecification<T> {
    const IMySpecification<T>& mFirst;
    const IMySpecification<T>& mSecond;
public:
    MyOrSpecification(const IMySpecification<T>& lFirst, const IMySpecification<T>& lSecond) 
            : mFirst{lFirst},
              mSecond{lSecond} {}
              
    bool isSatisfied(T* obj) const override;

};
template<typename T>
bool MyOrSpecification<T>::isSatisfied(T* obj) const {
    return mFirst.isSatisfied(obj) || mSecond.isSatisfied(obj);
}


template<typename T>
MyOrSpecification<T> operator || (const IMySpecification<T>& lFirst, const IMySpecification<T>& lSecond) {
    return {lFirst, lSecond};
}

#endif /* OPENCLOSEDPRTEMPLATES_H */

