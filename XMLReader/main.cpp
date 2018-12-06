/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on December 6, 2018, 9:16 AM
 */
#include <vector>
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

using namespace boost::system;
namespace filesys = boost::filesystem;

#ifndef USING_BOOST
#define USING_BOOST
#endif

/*
 * in Linux - path to boost lib usr\lib\x86_64-linux-gnu\
 * Need to include lboost_filesyste.a and lboost_system.a in Linker Library
 * 
 * Igrite ne sa napraveni
 * extremely_hot.xml
 * fhd_almighty_ramses.xml
 * fhd_lepricaun_hot.xml
 * fhd_mighty_sparta.xml
 * great_27.xml
 * juggle_fruits_5.xml
 * vampire_night.xml
 */

std::vector<std::string> getAllFilesInDir(const std::string &dirPath, 	const std::vector<std::string> dirSkipList = { }) {
    
    // Create a vector of string
	std::vector<std::string> listOfFiles;
    
    try {
        // Check if given path exists and points to a directory
        if(filesys::exists(dirPath) && filesys::is_directory(dirPath)) {
            // Create a Recursive Directory Iterator object and points to the starting of directory
            filesys::recursive_directory_iterator beginIter{dirPath};
            
            // Create a Recursive Directory Iterator object pointing to end.
            filesys::recursive_directory_iterator endIter;
            
            // Iterate till end
            while(beginIter != endIter) {
                // Check if current entry is a directory and if exists in skip list
                if(filesys::is_directory(beginIter->path()) && 
                    (std::find(dirSkipList.begin(), dirSkipList.end(), beginIter->path().filename()) != dirSkipList.end())) {
                    
                    // Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
                    // Boost Fileystsem  API to skip current directory iteration
                    beginIter.no_push();
#else 
                    // c++17 Filesystem API to skip current directory iteration
                    beginIter.disable_recursion_pending();
#endif
                }
                else {
                    // Add the name in vector
                    listOfFiles.push_back(beginIter->path().string());
                }
                
                error_code ec;
                // Increment the iterator to point to next entry in recursive iteration
                beginIter.increment(ec);
                if(ec) {
                    std::cerr << "Errow while accessing: " << beginIter->path().string() << " :: " << ec.message() << std::endl;
                }
            }
        }
    }
    catch(std::system_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return listOfFiles;
}

bool bIsWintable = false;
bool bIsFreeSpins = false;
bool bIsDoubleUp = false;
bool bIsRules = false;
    
void isWinTable(std::string& currStr, const std::string& s) {
    if(s == "<wintable>") {
        bIsWintable = true;
    }
    if(s == "</wintable>") {
        currStr += s + "\n";
        bIsWintable = false;
    }
}

inline std::string removeWhiteSpaces(const std::string& s) {
    if(s.length() == 0) {
        return s;
    }
    int begin = s.find_first_not_of(" \a\b\f\n\r\t");
    int end = s.find_last_not_of(" \a\b\f\n\r\t");
    
    if(begin == std::string::npos) {    //No Non-space
        return "";
    }
    return std::string(s, begin, end - begin + 1);
}

void formatWinTable(std::string& toFormat) {
    std::string result = "";
    std::size_t findPic = toFormat.find("{");
    std::size_t findVal = toFormat.find("}", findPic);
    
    std::string picStr = toFormat.substr(findPic + 1, findVal - 1 - findPic);
    
    picStr = removeWhiteSpaces(picStr);
    std::string temp = "";
    std::string remSpaces = "";
    
    bool bAddTemp = false;
    for(int i = 0; i < picStr.size(); i++) {
        remSpaces += picStr.at(i);
        if(picStr.at(i) == '\n' || i == picStr.size() - 1) {
//            std::cout << i << std::endl;
            temp += removeWhiteSpaces(remSpaces) + " ";
            remSpaces = "";
            bAddTemp = true;
        }
    }
    if(bAddTemp) {
        picStr = temp;
    }
//    std::cout << picStr << std::endl;
    
    std::vector<std::string> words;
    
    std::string word = "";
    
    char c = ' ';
    
    std::string font = "";
    std::size_t findFont = toFormat.find("font = ");
    std::size_t endFont = toFormat.find_first_of("/>\n", findFont + 1);
    font = toFormat.substr(findFont + 7, endFont - 7 - findFont);
    font = removeWhiteSpaces(font);
//    std::cout << font << std::endl;
    
    std::string strType = "standard";

    
//    std::cout << strType << std::endl;
    
    for(int i = 0; i < picStr.size(); i++) {
        if(picStr.at(i) != c) {
            word += picStr.at(i);
        }
        if(picStr.at(i) == c || i == picStr.size() - 1) {
            words.push_back(word);
            word = "";
        }
    }
    result += "<wintable>\n";
    result += "    <Scene order = \"0\" font = " + font + " >\n";
    result += "        <" + strType + ">\n";
    
    for(int i = 0; i < words.size(); i++) {
        result += "           <SceneElement name = \"" + words.at(i) + "\" />\n"; 
    }
    result += "           <SceneElement name = \"MACRO_ALL_FIGURES\" />\n";
    result += "        </" + strType + ">\n";
    result += "    </Scene>\n";
    result += "</wintable>\n";
    toFormat = result;
//    std::cout << result << std::endl;
}

void isFreeSpins(std::string& currStr, const std::string& s) {
    if(s == "<freespins>") {
        bIsFreeSpins = true;
    }
    if(s == "</freespins>") {
        currStr += s + "\n";
        bIsFreeSpins = false;
    }
}

void formatFreeSpins(std::string& toFormat) {
    std::string result = "";
    std::size_t findPic = toFormat.find("{");
    std::size_t findVal = toFormat.find("}", findPic);
    
    std::string picStr = toFormat.substr(findPic + 1, findVal - 1 - findPic);
    
    picStr = removeWhiteSpaces(picStr);
    std::string temp = "";
    std::string remSpaces = "";
    
    bool bAddTemp = false;
    for(int i = 0; i < picStr.size(); i++) {
        remSpaces += picStr.at(i);
        if(picStr.at(i) == '\n' || i == picStr.size() - 1) {
//            std::cout << i << std::endl;
            temp += removeWhiteSpaces(remSpaces) + " ";
            remSpaces = "";
            bAddTemp = true;
        }
    }
    if(bAddTemp) {
        picStr = temp;
    }
    
    bool bAddSerialNumber = false;
    if(toFormat.find("values") != std::string::npos) {
        bAddSerialNumber = true;
    }
    
    std::vector<std::string> words;
    
    std::string word = "";
    
    char c = ' ';
    
    for(int i = 0; i < picStr.size(); i++) {
        if(picStr.at(i) != c) {
            word += picStr.at(i);
        }
        if(picStr.at(i) == c || i == picStr.size() - 1) {
            words.push_back(word);
            word = "";
        }
    }
    result += "<freespins>\n";
    result += "    <Scene order = \"1\" >\n";
    result += "        <standard>\n";
    
    for(int i = 0; i < words.size(); i++) {
        result += "           <SceneElement name = \"" + words.at(i) + "\" />\n"; 
    }
    if(bAddSerialNumber) {
        result += "           <SceneElement name = \"SERIAL_NUMBER\" />\n";
    }
    result += "        </standard>\n";
    result += "    </Scene>\n";
    result += "</freespins>\n";
    toFormat = result;
}

void writeToFile(const std::string& toWrite, const std::string& path) {
    std::ofstream writeTo;
    writeTo.open("tempRes/result1.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    
    if(!writeTo.is_open()) {
        std::cerr << "File not found!\n";
        writeTo.close();
        return;
    }
    
    writeTo << "###########       " << path << "     ############\n";
    writeTo << toWrite << std::endl;
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "\n";
    writeTo.close();
}

void writeFreeSpinsToFile(const std::string& toWrite, const std::string& path) {
    std::ofstream writeTo;
    writeTo.open("tempRes/resultFreeSpins.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    
    if(!writeTo.is_open()) {
        std::cerr << "File not found!\n";
        writeTo.close();
        return;
    }
    
    writeTo << "###########       " << path << "     ############\n";
    writeTo << toWrite << std::endl;
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "\n";
    writeTo.close();
}


void writeRulesToFile(const std::string& toWrite, const std::string& path) {
    std::ofstream writeTo;
    writeTo.open("tempRes/resultRules.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    
    if(!writeTo.is_open()) {
        std::cerr << "File not found!\n";
        writeTo.close();
        return;
    }
    
    writeTo << "###########       " << path << "     ############\n";
    writeTo << toWrite << std::endl;
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "\n";
    writeTo.close();
}
void isRules(std::string& currStr, const std::string& s) {
    if(s == "<rules>") {
        bIsRules = true;
    }
    else if(s == "</rules>") {
        currStr += s + "\n";
        bIsRules = false;
    }
}

void formatRules(std::string& toFormat) {
    std::string result = "";
    std::size_t findPic = toFormat.find("{");
    std::size_t findVal = toFormat.find("}", findPic);
    
    std::string picStr = toFormat.substr(findPic + 1, findVal - 1 - findPic);
    
    picStr = removeWhiteSpaces(picStr);
    std::string temp = "";
    std::string remSpaces = "";
    
    bool bAddTemp = false;
    for(int i = 0; i < picStr.size(); i++) {
        remSpaces += picStr.at(i);
        if(picStr.at(i) == '\n' || i == picStr.size() - 1) {
//            std::cout << i << std::endl;
            temp += removeWhiteSpaces(remSpaces) + " ";
            remSpaces = "";
            bAddTemp = true;
        }
    }
    if(bAddTemp) {
        picStr = temp;
    }
    
    bool bAddSerialNumber = false;
    if(toFormat.find("values") != std::string::npos) {
        bAddSerialNumber = true;
    }
    
    std::string strType = "standard";
    if(toFormat.find("doubleup_and_jackpot") != std::string::npos) {
        strType = "doubleup_and_jackpot";
    }
    else if(toFormat.find("jackpot") != std::string::npos) {
        strType = "jackpot";
    }
//    std::cout << strType << " ";
    std::string num = "";
    if(toFormat.find("Scene order = ") != std::string::npos) {
        num = toFormat.substr(toFormat.find("Scene order = ") + 14, 3);
//        std::cout << num << std::endl;
    }
    
    std::vector<std::string> words;
    
    std::string word = "";
    
    char c = ' ';
    
    for(int i = 0; i < picStr.size(); i++) {
        if(picStr.at(i) != c) {
            word += picStr.at(i);
        }
        if(picStr.at(i) == c || i == picStr.size() - 1) {
            words.push_back(word);
            word = "";
        }
    }
    result += "<rules>\n";
    result += "    <Scene order = " + num + ">\n";
    result += "        <" + strType + ">\n";
    
    for(int i = 0; i < words.size(); i++) {
        result += "           <SceneElement name = \"" + words.at(i) + "\" />\n"; 
    }
    if(bAddSerialNumber) {
        result += "           <SceneElement name = \"SERIAL_NUMBER\" />\n";
    }
    result += "        </" + strType + ">\n";
    result += "    </Scene>\n";
    result += "</rules>\n";
    toFormat = result;
}

///DOUBLE UP
void writeDoubleUpToFile(const std::string& toWrite, const std::string& path) {
    std::ofstream writeTo;
    writeTo.open("tempRes/resultDoubleUp.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    
    if(!writeTo.is_open()) {
        std::cerr << "File not found!\n";
        writeTo.close();
        return;
    }
    
    writeTo << "###########       " << path << "     ############\n";
    writeTo << toWrite << std::endl;
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "==============================================\n";
    writeTo << "\n";
    writeTo.close();
}
void isDoubleUp(std::string& currStr, const std::string& s) {
    if(s == "<doubleup>") {
        bIsDoubleUp = true;
    }
    else if(s == "</doubleup>") {
        currStr += s + "\n";
        bIsDoubleUp = false;
    }
}

void formatDoubleUp(std::string& toFormat) {
    std::string result = "";
    std::size_t findPic = toFormat.find("{");
    std::size_t findVal = toFormat.find("}", findPic);
    
    std::string picStr = toFormat.substr(findPic + 1, findVal - 1 - findPic);
    
    picStr = removeWhiteSpaces(picStr);
    std::string temp = "";
    std::string remSpaces = "";
    
    bool bAddTemp = false;
    for(int i = 0; i < picStr.size(); i++) {
        remSpaces += picStr.at(i);
        if(picStr.at(i) == '\n' || i == picStr.size() - 1) {
//            std::cout << i << std::endl;
            temp += removeWhiteSpaces(remSpaces) + " ";
            remSpaces = "";
            bAddTemp = true;
        }
    }
    if(bAddTemp) {
        picStr = temp;
    }
    
    bool bAddSerialNumber = false;
    if(toFormat.find("values") != std::string::npos) {
        bAddSerialNumber = true;
    }
    
    std::string strType = "standard";
    if(toFormat.find("doubleup_and_jackpot") != std::string::npos) {
        strType = "doubleup_and_jackpot";
    }
    else if(toFormat.find("jackpot") != std::string::npos) {
        strType = "jackpot";
    }
//    std::cout << strType << " ";
    std::string num = "";
    if(toFormat.find("Scene order = ") != std::string::npos) {
        num = toFormat.substr(toFormat.find("Scene order = ") + 14, 3);
//        std::cout << num << std::endl;
    }
    
    std::vector<std::string> words;
    
    std::string word = "";
    
    char c = ' ';
    
    for(int i = 0; i < picStr.size(); i++) {
        if(picStr.at(i) != c) {
            word += picStr.at(i);
        }
        if(picStr.at(i) == c || i == picStr.size() - 1) {
            words.push_back(word);
            word = "";
        }
    }
    result += "<rules>\n";
    result += "    <Scene order = " + num + ">\n";
    result += "        <" + strType + ">\n";
    
    for(int i = 0; i < words.size(); i++) {
        result += "           <SceneElement name = \"" + words.at(i) + "\" />\n"; 
    }
    if(bAddSerialNumber) {
        result += "           <SceneElement name = \"SERIAL_NUMBER\" />\n";
    }
    result += "        </" + strType + ">\n";
    result += "    </Scene>\n";
    result += "</rules>\n";
    toFormat = result;
}
//END DOUBLE UP

void readFile(const std::string& path) {
    std::ifstream file{path};
    
    bIsWintable = false;
    bIsFreeSpins = false;
    bIsDoubleUp = false;
    bIsRules = false;
    
    if(!file.is_open()) {
        std::cerr << "File could not be opened: " << path << std::endl;
        return;
    }
    
    std::string line;
    std::string wintable = "";
    
    std::string freespins = "";
    
    std::string rules = "";
    
    std::string doubleUp = "";
    
    std::string fileToWrite = "newGeneral/" + path;
    
    std::ofstream writeTo{fileToWrite, std::fstream::in | std::fstream::out | std::fstream::trunc};
    
    bool writeLine = false;
    while(std::getline(file, line)) {
        
        std::stringstream keystream{line};
        std::string type;
        keystream >> type;
//        writeLine = true;
        if(!bIsWintable && !bIsFreeSpins && !bIsRules) {
//            std::cout <<"aaa\n";
            writeLine = true;
            
        }
        isWinTable(wintable, type);
        
        if(bIsWintable) {
            wintable += line + "\n";
            writeLine = false;
        }
        
        isFreeSpins(freespins, type);
        
        if(bIsFreeSpins) {
            writeLine = false;
            freespins += line + "\n";
        }
        
        isRules(rules, type);
        
        if(bIsRules) {
            writeLine = false;
            rules += line + "\n";
        }
        
        
//        isDoubleUp(doubleUp, type);
//        if(bIsDoubleUp) {
//            doubleUp += line + "\n";
//        }
        if(writeLine && line != "</GameInfoScreen>" && line != "</compmgr>") {
            writeTo << line << std::endl;
        }
    }      

    file.close();
    if(freespins != "") {
        formatFreeSpins(freespins);
    }
    if(wintable != "") {
        formatWinTable(wintable);
    }
 
    if(rules != "") {
        formatRules(rules);
    }
    std::string result = wintable + "\n" + freespins + "\n" + rules + "\n";
    writeTo << result << std::endl;
    writeTo << "</GameInfoScreen>" << std::endl << "</compmgr>" << std::endl;
    writeTo.close();
//    std::cout << result << std::endl;
    
}


void getAllFiles() {
    std::string directoryPath = "general/";
    std::vector<std::string> listOfAllFiles = getAllFilesInDir(directoryPath);
    
    //Start all files here
//    for(auto a : listOfAllFiles) {
//        readFile(a);
//    }
    /**
     *  * Igrite ne sa napraveni
 * extremely_hot.xml
 * fhd_almighty_ramses.xml
 * fhd_leprecaun_hot.xml
 * fhd_mighty_sparta.xml
 * great_27.xml
 * juggle_fruits_5.xml
 * vampire_night.xml
     */
    
    for(int i = 0; i < listOfAllFiles.size(); i++) {

        if(listOfAllFiles.at(i) != "general/extremely_hot.xml" && 
            listOfAllFiles.at(i) != "general/fhd_almighty_ramses.xml" &&
            listOfAllFiles.at(i) != "general/fhd_leprechaun_hot.xml" &&
            listOfAllFiles.at(i) != "general/fhd_mighty_sparta.xml" &&
            listOfAllFiles.at(i) != "general/great_27.xml" &&
            listOfAllFiles.at(i) != "general/juggle_fruits_5.xml" &&
            listOfAllFiles.at(i) != "general/vampire_night.xml" &&
            listOfAllFiles.at(i) != "general/hat_mgr.xml" && 
            listOfAllFiles.at(i) != "general/versailles_gold.xml" &&
            listOfAllFiles.at(i) != "general/olympus_glory.xml" &&
            listOfAllFiles.at(i) != "general/fortune_spells.xml" &&
            listOfAllFiles.at(i) != "general/blue_oceans.xml" ) {
            
            std::cout << listOfAllFiles.at(i) <<"##################################\n";
            readFile(listOfAllFiles.at(i)); 
            
        }
    }
    ///////////////
//    readFile("general/rise_of_ra.xml");
}



int main(int argc, char** argv) {

    getAllFiles();
    
    return 0;
}

