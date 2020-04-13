/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RealStash.h
 * Author: default
 *
 * Created on December 21, 2019, 2:48 PM
 */

#ifndef REALSTASH_H
#define REALSTASH_H

#include <string.h>

#include "../utils/require.h"

template<class T, int increment = 20>
class Stash {
    int quantity;
    int next;
    T** storage;
    void inflate(int increase = increment);
    
    public:
        Stash() : quantity{0}, next{0}, storage{nullptr} {}
        ~Stash();
        
        int add(T* elem);
        inline T* operator [] (int index) const;
        T* remove(int index);
        int count() const {return next;}
        
        //Nested iterator class
//        class iterator;
//        friend class iterator;
        class iterator {
            Stash& ps;
            int index;
        public:
            iterator(Stash& s) : ps{s}, index{0} {}
            iterator(Stash& s, bool) : ps{s}, index{ps.count()} {}
            
            iterator(const iterator& rv) : ps{rv.ps}, index{rv.index} {}
            
            iterator& operator = (const iterator& rv) {
                ps = rv.ps;
                index = rv.index;
                return *this;
            }
            
            iterator& operator ++ () {
                require(++index <= ps.next, "Stash::iterator::operator ++ () moves index out of bounds");
                return *this;
            }
            iterator& operator ++ (int) {
                return operator ++ ();
            }
            
            iterator& operator -- () {
                require(--index >= 0, "Stash::iterator::operator -- () moves index out of bounds");
                return *this;
            }
            iterator& operator -- (int) {
                return operator -- ();
            }
            
            //Jump iterator forward of backward
            iterator& operator += (int amount) {
                require(((index + amount) < ps.count()) && ((index + amount) >= 0), "Stash::iterator::operator += () moves out of bounds");
                index += amount;
                return *this;
            }
            iterator& operator -= (int amount) {
                require(((index - amount) < ps.count()) && ((index - amount) >= 0), "Stash::iterator::operator -= () moves out of bounds");
                index -= amount;
                return *this;
            }
            //Creates new iterator that moves forward
            iterator operator + (int amount) const {
                iterator ret(*this);
                ret += amount;  // op += does bound check
                return ret;
            }
            T* current() const {
                return ps.storage[index];
            }
            T* operator * () const {
                return current();
            }
            T* operator -> () const {
                require(ps.storage[index] != nullptr, "Stash::iterator::operator -> () returns null");
                return current();
            }
            //Remove current element
            T* remove() {
                return ps.remove(index);
            }
            //Comparision test for end
            bool operator == (const iterator& rv) const {
                return index == rv.index;
            }
            bool operator != (const iterator& rv) const {
                return index != rv.index;
            }
        };  //end class iterator
        
        iterator begin() {
            return iterator(*this);
        }
        iterator end() {
            return iterator(*this, true);
        }
};

//Destruction of contained objects
template<class T, int increment> 
Stash<T, increment>::~Stash() {
    for(int i = 0; i < next; i++) {
        delete storage[i];
        storage[i] = nullptr;
    }
    delete [] storage;
}

template<class T, int increment>
int Stash<T, increment>::add(T* elem) {
    if(next >= quantity) {
        inflate();
    }
    storage[next++] = elem;
    return (next - 1);
}

template<class T, int increment>
inline T* Stash<T, increment>::operator [](int index) const {
    require(index >= 0, "Stash::operator [] () Index negative");
    if(index >= next) {
        return nullptr; //indicates the end
    }
    require(storage[index] != nullptr, "Stash::operator [] () returns nullptr");
    return storage[index];
}

template<class T, int increment>
T* Stash<T, increment>::remove(int index) {
    //operator [] performs validity check
    T* v = operator [] (index);
    //Remove the pointer
    storage[index] = nullptr;
    return v;
}

template<class T, int increment>
void Stash<T, increment>::inflate(int increase) {
    const int psz = sizeof(T*);
    
    T** st = new T*[quantity + increase];
    memset(st, 0, (quantity + increase) * psz);
    memcpy(st, storage, quantity * psz);
    quantity += increase;
    delete [] storage;
    storage = st;
}
#endif /* REALSTASH_H */

