/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceManager.h
 * Author: default
 *
 * Created on June 25, 2019, 10:59 AM
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>

//Template Base class for Resources.
//Should be implemented in the header, for
//compilator to be able to create derived Template classes.

template<typename Derived, typename T>
class ResourceManager {
    public:
        /**
         * Constructor to load resources from given path
         * @param lPathsFile path to the resources files
         */
        ResourceManager(const std::string& lPathsFile) {
            loadPaths(lPathsFile);
        }
        /**
         * Destructor to release allocated resources.
         * Should be virtual cause inheritance
         */
        virtual ~ResourceManager() {
            purgeResources();
        }
        
        /**
         * 
         * @param lId std::string argument to search for particular resource in the mResource map.
         * @return std::pair<>* to the element in mResource map if element is found. nullptr otherwise
         */
        T* getResource(const std::string& lId) {
            auto res = findResource(lId);
            return (res ? res->first : nullptr);
        }
        
        /**
         * Retrieve the path to the given resource.
         * @param lId std::string of the resource ID.
         * @return std::string of the path to the resource by lId, empty std::string otherwise.
         */
        std::string getPath(const std::string& lId) {
            auto path = mPaths.find(lId);
            return (path != mPaths.end() ? path->second : "");
        }
        
        /**
         * Method that register the usage of given resource. 
         * Its the way to guarantee that the given resource is not de-allocated when is still used.
         * @param lId resource name.
         * @return true if the resource is used, false otherwise.
         */
        bool requireResource(const std::string& lId) {
            auto res = findResource(lId);
            if(res) {   //Resource is found 
                ++res->second;  //Increase resource count usage. In the mResource map
                return true;
            }
            
            auto path = mPaths.find(lId);
            if(path == mPaths.end()) {
                return false;       //Resource not used.
            }
            
            T* resource = load(path->second);
            //Resource not found return false.
            if(!resource) {
                return false;
            }
            //Add resource to the map with key lId, resource type and usage count 1.
            mResources.emplace(lId, std::make_pair(resource, 1));
            return true;
        }
        
        /**
         * This Method release the resource if is no longer needed.
         * @param lId std::string name of the resource
         * if resource usage count reach 0, the memory for the resource can be de-allocated.
         * @return true if resource is released, false otherwise.
         */
        bool releaseResource(const std::string& lId) {
            auto res = findResource(lId);
            
            if(!res) {  //Resource not found return false;
                return false;
            }
            --res->second;  //Decrease mResource.second usage count by 1.
            if(!res->second) {  //Count reach 0, free the resource.
                unload(lId);
            }
            return true;
        }
        
        /**
         * load method which going to be used in every Derived Class
         * In order to avoid run-time polymorphism, we will use 
         * Curriously Recurring template pattern 
         * @param lPath relative Path to the file with the resources.
         * @return 
         */
        T* load(const std::string& lPath) {
            return static_cast<Derived*>(this)->load(lPath);
        }
    private:
        
        /**
         * mResource map.
         * first = std::string key
         * 
         * second = std::pair<T*, unsigned int> - pair.first = Template type of the resource, 
         *                                        pair.second = unsigned int count of how many places this resources is used.
         */
        std::unordered_map<std::string, std::pair<T*, unsigned int>> mResources;
        std::unordered_map<std::string, std::string> mPaths;
        
        /**
         * Delete all resources from the Resource Manager.
         * 
         */
        void purgeResources() {
            while(mResources.begin() != mResources.end()) {
                delete mResources.begin()->second.first;
                mResources.erase(mResources.begin());
            }
        }
        
        /**
         * Method to find particular resource in the mResource map.
         * @param lId std::string name of the resource in mResource map.
         * @return std::pair<T*, unsinged int>* if the resource is found in the map, nullptr otherwise.
         */
        std::pair<T*, unsigned int>* findResource(const std::string& lId) {
            auto it = mResources.find(lId);
            
            return (it != mResources.end() ? &it->second : nullptr);
        }
        
        /**
         * Method to unload particular resource
         * @param lId std::string name of the resource.
         * @return true if the resource is deleted, false if resource is not found in the map.
         */
        bool unload(const std::string& lId) {
            auto it = mResources.find(lId);
            if(it == mResources.end()) {
                return false;
            }
            delete it->second.first;
            mResources.erase(it);
            return true;
        }
        
        void loadPaths(const std::string& lPathFile) {
            std::ifstream paths;
            paths.open(lPathFile);
            
            if(paths.is_open()) {
                std::string line;
                while(std::getline(paths, line)) {
                    std::stringstream keystream{line};
                    std::string pathName;
                    std::string path;
                    keystream >> pathName;
                    keystream >> path;
                    mPaths.emplace(pathName, path);
                }
                paths.close();
                return;
            }
            std::cerr << "! Failed to load path file: " << lPathFile << std::endl;
        }
};

#endif /* RESOURCEMANAGER_H */

