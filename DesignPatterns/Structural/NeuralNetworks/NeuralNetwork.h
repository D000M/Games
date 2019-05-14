/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NeuralNetwork.h
 * Author: default
 *
 * Created on April 25, 2019, 2:06 PM
 */

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <ostream>
#include <iostream>

namespace Neural {
    
    struct Neuron;
    //CRTP << Curious Recurring Template Pattern CRTP
    //Interface for able to create just once function to connect neurons.
    template<typename Self>
    struct SomeNeurons {
        
        template<typename T> 
        void connectTo(T& other) {
            //Right now this pointer points to some Neurons which isnt helpful
            //so we will static_cast this pointer to the Self pointer and de reference
            for(auto& from : *static_cast<Self*>(this)) { //left part of the connection
                for(auto& to : other) {   //right part of the connection
                    from.out.emplace_back(&to);
                    to.in.emplace_back(&from);
                }
            }
            ///^^^^^^ This wont work because Neuron class doesnt have begin and end methods. Its not Container.
            //We should create those methods inside the class
        }
    };
    
    //Single neuron     ,,After SomeNeurons, Neuron has to actualy inherit this stuff
    struct Neuron : SomeNeurons<Neuron>{
        
        std::vector<Neuron*> in, out;   //in - Ingoing connections, out - Outgoing Connections.
        unsigned int id;
        
        Neuron() {
            static int id{1};
            this->id = id++;
        }
//        
//        void connectTo(Neuron& other ) {
//            out.emplace_back(&other);
//            other.in.emplace_back(this);
//        }
        
        //Create methods for for range loops.
        //this is not begin and this + 1 will point 1 element past the end.
        Neuron* begin() {return this; }
        Neuron* end() {return this + 1;}
        
        friend std::ostream& operator<<(std::ostream& os, const Neuron& obj) {
            // Write obj to stream
            for(Neuron* n : obj.in) {
                std::cout << n->id << "\t-->\t[" << obj.id << "]" <<std::endl;
            }
            for(Neuron* n : obj.out) {
                std::cout << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
            }
            return os;
        }

    };  //End struct Neuron
    
    //Inherit from STL is very big sin cause STL doesnt have virtual Destructors. Used only for this example
    struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer> {      //Bunch of neurons
        NeuronLayer(int count) {
            while(count-- > 0) {
                emplace_back(Neuron{});
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& obj) {
            // Write obj to stream
            for(auto& n : obj) {
                std::cout << n;
            }
            return os;
        }

    };
    
    void testNeural() {
        Neuron n1, n2;
        n1.connectTo(n2);   // 1
        std::cout << n1 << n2 << std::endl;
        
        NeuronLayer layer1{2}, layer2{3};
//        std::cout << layer1 << layer2 << std::endl;
        n1.connectTo(layer1);
        layer2.connectTo(n2);
        layer1.connectTo(layer2);
        std::cout << layer1 << std::endl;
    }
}


#endif /* NEURALNETWORK_H */

