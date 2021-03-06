/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
//#include <X11/Xlibint.h>
#include <algorithm>
#include <valarray>
#include <fstream>

#include "Externs.h"
#include "Recursive.h"


void digitsOfNumber(int n) {
    std::cout << "The number: " << n << " has ";
    int digits = 0;
    for(; n > 0; n /= 10, digits++);
    std::cout << digits << " digits." << std::endl;
}

void calculateDivisionAndMod(int n, int m) {
    std::cout << n << " / " << m << " = ";
    std::cout << (n / m) << std::endl;
    std::cout << n << " % " << m << " = ";
    std::cout << (n % m) << std::endl;
}

int recSum(int n) {
    if(n == 0) {
        return 0;
    }
    return recSum(n - 1) + n;
}

void sumOfFirstNNumbers(int n) {
    int res = recSum(n);
    std::cout << "S = " << res << std::endl;
}

int NOD(int m, int n) {
    if(n == 0) {
        return m;
    }
    return NOD(n, m % n);
}

void binoms() {
    const int MAXN = 1000;
    const int n = 10;
    const int k = 3;
    
    long lastLine[MAXN + 1];
    
    lastLine[0] = 1;
    std::cout << lastLine[0] << std::endl;
    for(int i = 1; i <= n; i++ ) {
        lastLine[i] = 1;
        std::cout << lastLine[i] << "\t";
        for(int j = i - 1; j >= 1; j--) {
            lastLine[j] += lastLine[j - 1];
            std::cout << lastLine[j] << "\t";
        }
        std::cout << lastLine[i] << "\t";
        std::cout << std::endl;
    }
//    printf("C(%u,%u) = %lu\n", n, k, lastLine[k]);
}

bool isBinary(const std::string& str) {
    for(int i = 0; i < str.length(); i++) {
        if(str.at(i) != '0' && str.at(i) != '1') {
            return false;
        }
    }
    return true;
}

char returnHex(const std::string& fourBits) {
    int result = 0;
    if(fourBits.at(0) == '1') {
        result += 8;
    }
    if(fourBits.at(1) == '1') {
        result += 4;
    }
    if(fourBits.at(2) == '1') {
        result += 2;
    }
    if(fourBits.at(3) == '1') {
        result += 1;
    }
    
    switch(result) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3'; 
        case 4: return '4'; 
        case 5: return '5'; 
        case 6: return '6'; 
        case 7: return '7'; 
        case 8: return '8'; 
        case 9: return '9'; 
        case 10: return 'A'; 
        case 11: return 'B';
        case 12: return 'C'; 
        case 13: return 'D';
        case 14: return 'E'; 
        case 15: return 'F'; 
    }
}

void binaryToHex(const std::string& binary) {
    
    std::string result = binary;
    if(!isBinary(result)) {
        std::cerr << "The input isnt binary number! exit\n";
        return;
    }
    
    while(result.length() % 4 != 0) {
        result = "0" + result;
    }
    int symbols = result.length() / 4;
    
    std::string hexResult = "";
    
    for(int i = 0; i < symbols; i++) {
        std::string temp = "";
        for(int j = i * 4; j < i * 4 + 4; j++ ) {
            temp += result.at(j);
        }
        hexResult += returnHex(temp);
    }
    hexResult.erase(0, hexResult.find_first_not_of('0'));
    std::cout << hexResult << std::endl;
}

void testBinaryToHex(const std::string& number) {
    binaryToHex(number);
}

char returnOct(const std::string& binary) {
    int result = 0;
    if(binary.at(0) == '1') {
        result += 4;
    }
    if(binary.at(1) == '1') {
        result += 2;
    }
    if(binary.at(2) == '1') {
        result += 1;
    }
    switch(result) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
    }
}

void binaryToOctal(const std::string& binary) {
    std::string result = binary;
    
    while(result.length() % 3 != 0) {
        result = "0" + result;
    }
    
    int symbols = result.length() / 3;
    std::string octReslt = "";
    
    for(int i = 0; i < symbols; i++) {
        std::string temp = "";
        for(int j = i * 3; j < i * 3 + 3; j++) {
            temp += result.at(j);
        }
        octReslt += returnOct(temp);
    }
    octReslt.erase(0, octReslt.find_first_not_of('0'));
    std::cout << octReslt << std::endl;
}

void testBinaryToOct(const std::string& number) {
    binaryToOctal(number);
}

void decToBinary(int decimal) {
    std::string result = "";
    bool addMinus = false;
    if(decimal < 0) {
        addMinus = true;
        decimal = abs(decimal);
    }
    else if(decimal == 0) {
        result = "0";
    }
    while(decimal > 0) {
        int bin = decimal % 2;
        decimal = decimal / 2;
        result += std::to_string(bin);
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

void decToOctal(int number) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    while(number > 0) {
        int octal = number % 8;
        number = number / 8;
        result += std::to_string(octal);
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

char getChar(char n) {
    return (n < 10) ? (n + '0') : (n + 'A' - 10);
}

void decToHex(int number) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    while(number > 0) {
        result += getChar((char)(number % 16));
        number = number / 16;
        
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}

void decToPTypeSystem(int number, int base) {
    std::string result = "";
    bool addMinus = false;
    if(number < 0) {
        addMinus = true;
        number = abs(number);
    }
    else if(number == 0) {
        result = "0";
    }
    
    while(number > 0) {
        result += getChar((char)(number % base));
        number = number / base;
    }
    std::reverse(result.begin(), result.end());
    if(addMinus) {
        result = "-" + result;
    }
    std::cout << result << std::endl;
}


//Excercises
//Ex 1.157
/**
 * Да се напише програма намираща всички числа, равни на сумата от факториелите 
 * на своите цифри. 
 * 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 
 */
int sum = 0;
int arrFact[] = {
    1, 2, 6, 24, 120, 720, 5040, 40320, 362880
};
void exampleOne(int n) {
    if(n > 0) {
        if(n % 10 != 0) {
            sum += arrFact[(n % 10) - 1];
        }
        else {
            sum += 1;
        }
        exampleOne(n / 10);
    }
}
void testEx1() {
    for(int i = 0; i < 3628800; i++) {
        sum = 0;
        exampleOne(i);
        if(sum == i) {
            std::cout << i << " = " << sum << std::endl;
        }
    }
}

//Ex 1.158
/** 
 * A)
 * Две прости числа P и Q се наричат "близнаци" ако P = Q + 2;
 * Доказано е че съществуват безброй много близнаци.
 * Първите 4 от тя са {3, 5}, {5, 7}, {11, 13}, {17, 19}  
 * 
 * B)
 * Сумата на редицата от реципрочните стойности на числата близнаци:
 * S = 1/3 + 1/5 + 1/5 + 1/7 + 1/11 + 1/13 + 1/17 + 1/19 .. 
 * Е известна като константа на Бран, и е равна на 1.902160578
 * Намерете сумата на реципрочните стойности на числата близнаци.
 */
void sievePrimes(int nums) {
    constexpr int size = 10000;
    int count = 0;
    bool primes[size];
    for(int i = 0; i < size; i++) {
        primes[i] = true;
    }
    int currNum = 2;
    int removeNum;
    
    while(currNum < size) {
        if(primes[currNum] == true) {
            removeNum = currNum * currNum;
            while(removeNum < size) {
                primes[removeNum] = false;
                removeNum += currNum;
            }
        }
        currNum++;
    }
    double branSum = 0;
    for(int i = 2; i < size - 2; i++) {
        if(primes[i] && primes[i + 2]) {
            count++;
            branSum += double(1 / double(i)) + double(1 / double(i + 2));
            std::cout << branSum << std::endl;
//            std::cout << "{ " << i << ", " << i + 2 << " }\n";
            if(count == nums) {
                break;
            }
        }
    }
}

//Ex 1.161
void countNumbers(bool primes[], int n);
int countNumbersRec(bool primes[], int n);
bool isLessThan(bool primes[], int n) {
    for(int i = 2; i <= n / 2; i++) {
        if(primes[i]) {
            for(int j = n - 1; j >= 2; j--) {
                if(primes[j]) {
                    if(i * j == n) {
                        std::cout << i << " * " << j << " = " << i * j << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int count = 0;
void testEx1161(int n) {
    constexpr int size = 10000;
    bool primes[size];
    for(int i = 0; i < size; i++) {
        primes[i] = true;
    }
    int currNum = 2;
    int removeNum;
    
    while(currNum < size) {
        if(primes[currNum] == true) {
            removeNum = currNum * currNum;
            while(removeNum < size) {
                primes[removeNum] = false;
                removeNum += currNum;
            }
        }
        currNum++;
    }
//    for(int i = 2; i < 40; i++) {
//        if(primes[i]) {
//            std::cout << i << std::endl;
//        }
//    }
//    searchedNumber = n;
    std::cout << countNumbersRec(primes, n - 1) << std::endl;
    std::cout << "Броят на числата по малки от " << n <<", който могат да се представят като пройзведение от 2 прости са: " << count << "\n";
}
/**
 * 40
 * 39 = 3 * 13        27
 * 38 = 2 * 19        26
 * 37 = 1 * 37 prosto 25
 * 36 ne
 * 35 = 5 * 7         24
 * 34 = 2 * 17        23
 * 33 = 2 * 11        22
 * 32 ne 
 * 31 = 1 * 31 prosto 21
 * 30 ne  
 * 29 = 1 * 29 prosto 20
 * 28 ne
 * 27 ne
 * 26 = 2 * 13        19
 * 25 = 5 * 5         18
 * 24 ne  
 * 23 = 1 * 23 prosto 17
 * 22 = 2 * 11        16
 * 21 = 3 * 7         15
 * 20 ne
 * 19 = 1 * 19 prosto 14
 * 18 = ne            
 * 17 = 1 * 17 prosto 13
 * 16 = ne           
 * 15 = 3 * 5         12
 * 14 = 2 * 7         11
 * 13 = 1 * 13 prosto 10
 * 12 = ne
 * 11 = 1 * 11 prosto 9
 * 10 = 2 * 5         8
 * 9 = 3 * 3          7 
 * 8 = ne  
 * 7 = 1 * 7 prosto   6
 * 6 = 2 * 3          5
 * 5 = 1 * 5 prosto   4
 * 4 = 2 * 2          3
 * 3 = 1 * 3 prosto   2
 * 2 = 1 * 2 prosto   1
 * 1 = ne
 * @param n
 * @return 
 */

int countNumbersRec(bool arr[], int n) {
    if(n < 2) {
        return count;
    } 
    
    if(arr[n] || isLessThan(arr, n)) {
        count++;
    }
    
    return countNumbersRec(arr, n - 1);
}

/**
 * 
 * Ex 1.162
 * За дадено естествено число N, да се намери минималното естествено число M,
 * M > N, което има сума от цифрите, равна на сумата от цифрите на N.
 * Цифрите на N се задават като елементи на масив и могат да бъдат до 2000.
 * N = 11 , M = 20.
 */
int toInt(char c) {
    return c - '0';
}
char nextChar(char c) {
    if(c > '9'){
        return '0';
    }
    std::cout << c << std::endl;
    return nextChar(c + 1);
}
void testEx1162(const std::string& s) {
    constexpr int MAX = 2000;
    char number[MAX];
    int sum = 0;
    number[0] = '0';
    for(int i = 0; i < s.length(); i++) {

        number[i + 1] = s.at(i);
        sum += toInt(s.at(i));
    }
    std::cout << "Sum: " << sum << std::endl;
    int pos = s.length();
    int temp = 0;
    while(true) {
        if(pos >= 0) {
            if(number[s.length()] == '0') {
                number[s.length()]++;
            }
        }
    }
    
    sum = 0;
    for(int i = 0; i <= s.length(); i++) {
        std::cout << number[i] << " ";
        sum += toInt(number[i]);
    }

    std::cout << "New Sum: " << sum << std::endl;
}
std::ofstream file("records.txt");
void iterativeVariant(int n) {
    
    int sum = 0;
    int num = n;
    file << "---------------\n";
    file << n << " ";
    while(n > 0) {
        sum += n % 10;
        n /= 10;
    }
    int newSum = 0;
    
    for(int i = num + 1; i < 1000; i++) {
        newSum = 0;
        int temp = i;
        while(temp > 0) {
            newSum += temp % 10;
            temp /= 10;
        }
        if(sum == newSum) {
            num = i;
            break;
        }
    }
    file << sum << std::endl;
    file << num << " " << newSum << std::endl;
    
}

/**
 * 10
 * 11 12 13 14 15 16 17 18 19 
 * 20 21 22 23 24 25 26 27 28 29
 * 30 31 32 33 34 35 36 37 38 39
 * 
 */

//Ex 1.165
void printLuckyNumbers(int n, int steps) {
    
    bool numbers[n];
    for(int i = 0; i < n; i++) {
        numbers[i] = true;
    }
    
    int currPos = 2;
    int removeNum;
    int tempArr[(n / currPos)];
    
    int count = 0;
    while(count < steps) {
        
        count++;
    }
}

void printTribonaci(int n) {
    
    int a = 1;
    int b = 1;
    int c = 1;
    std::cout << "1: " << a << std::endl << "2: " << b << std::endl << "3: " <<c << std::endl;
    for(int i = 4; i <= n; i++) {
        int trib = a + b + c;
        c = b;
        b = a;
        a = trib;
        std::cout << i << ": " << trib << std::endl;
    }
}

void printFibFromRow(unsigned int row, unsigned long n) {
    int first = row;
    int second = first;
    std::cout << "1: " << first << std::endl << "2: " << second << std::endl;
    for(int i = 2; i < n; i++) {
        int fibRow = first + second;
        second = first;
        first = fibRow;
        std::cout << i << ": " << fibRow << std::endl;
    }
}

void sumOfSquares(int n) {
    
    double sum = 0;
    for(int i = 1; i < n; i++) {
        sum += double(double(1) / std::sqrt(double(i)));
        std::cout << "Sum: " << sum << std::endl;
    }
    
}

void sumInInterval(int n) {
    int sum = 0;
    for(int i = 1; i < n / 2; i++) {
        sum = i;
        for(int j = i + 1; j < (n / 2) + 1; j++) {
            sum += j;
            if(sum == n) {
                std::cout << "[" << i << "," << j << "]\n";
            }
        }
    }
}

void pitagorNumbers(int n) {
    
    int maxSize = 1000;
    int count = 0;
//    while(count < n) {
        for(int i = 1; i < maxSize / 2; i++) {
            for(int j = i; j < maxSize / 5; j++) {
                for(int k = j; k < maxSize / 10; k++) {
                    for(int m = k; m < maxSize / 20; m++) {
                        if(m * m == (k * k) + (j * j) + (i * i)) {
                            count++;
                            std::cout << "( " << i << "," << j << "," << k << "," << m << " )\n";
                            if(count == n) {
                                return;
                            }
                        }
                    }
                }
            }
        }
//    }
}

//Ex 1.182 Pyramids Iterative
void printIterPyramid(int n, bool bType) {
    int count = 1;
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j < n; j++) {
            std::cout << " ";
        }
        for(int k = 0; k < count; k++) {
            std::cout << n - i + k;
        }
        for(int k = bType == true ? 1 : 0; k < count; k++) {
            std::cout << n - k;
        }
        count++;
        std::cout << std::endl;
    }
}

//Ex 1.183
void printIterKare(int n) {
    int num = 1;
    for(int i = 0; i < n; i++) {
        num = 1;
        for(int j = i; j < n; j++) {
            std::cout << " ";
        }
        for(int j = num; j < i * 2; j++) {
            std::cout << num;
            if(j < i) {
                num++;
            }
            else {
                num--;
            }
        }
        std::cout << std::endl;
    }
    num = 1;
    for(int outer = 0; outer < n; outer++) {
        for(int i = 1; i < n * 2; i++) {
            if(num <= 0) {
                std::cout << " ";
            }
            else { 
                std::cout << num;
            }
            if(i < n) {
                num++;
            }
            else {
                num--;
            }
        }
        std::cout << std::endl;
    }
}

//Ex 1.184
void printArr(int **arr, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
void magicSquare(int n) {
    int num = 1;
    int arr[n][n];
    

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    
    int row = 0;
    int col = n / 2;
    
    int prevRow = row;
    int prevCol = col;
    while(true) {
        if(num > n * n) {
            break;
        }

        arr[row][col] = num++;      
        prevRow = row;
        prevCol = col;
        row--;
        col++;
        
        if(row < 0) {
            row = n - 1;
        }
        if(col > n - 1) {
            col = 0;
        }
        if(arr[row][col] != 0) {
            row = prevRow;
            col = prevCol;
            row++;
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

/**
 * M x N
 * Carici
 * 0 1 0
 * 0 0 0
 * 0 0 1
 * 1 0 0
 * 
 * Top
 * 1 0 0
 * 0 1 0
 * 0 0 1
 * 0 0 0
 * 
 * Kon
 * k k k
 * 0 k 0
 * 0 0 0
 * 0 k 0
 * 
 * oficer
 * f f f
 * 0 0 0
 * 0 0 0
 * f f f
 * 
 * 
 */
void transpondMatrix() {
    int n = 5;
    int a[n][n] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    
    int b[n][n];
    int count = 1;
    for(int i = 0; i < n; i++){
        for(int j = count; j < n; j++) {
            int temp = a[j][i];
            a[j][i] = a[i][j];
            a[i][j] = temp;
        }
        count++;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}