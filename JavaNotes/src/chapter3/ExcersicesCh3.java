/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter3;

import eckels.gui.text.TextIO;

/**
 *
 * @author default
 */
public class ExcersicesCh3 {
    
    public static void sneakEyes() {
        int firstDice = 0;
        int secondDice = 0;
        
        int count = 0;
        while(true) {
            firstDice = (int)((Math.random() * 6) + 1);
            secondDice = (int)((Math.random() * 6) + 1);
            count++;
            System.out.println("Count: " + count + ", Dices: " + firstDice + " " + secondDice);
            if(firstDice == 1 && secondDice == 1) {
                break;
            }
        }
    }
    
    public static void largestNumOfDivisiors() {
        
        int divisors = 0;
        int currMax = 0;
        int number = 0;
        int result[] = new int[100];
        int pos = 0;
        for(int i = 1; i < 10000; i++) {
//            System.out.print(i + ": ");
            for(int j = 1; j <= i; j++) {
                if(i % j == 0) {
                    divisors++;
//                    System.out.print(j + ", ");
                }
            }
            if(divisors >= currMax) {
                currMax = divisors;
                number = i;
                result[pos] = i;
                pos++;
            }
            divisors = 0;
//            System.out.println("");
        }
        System.out.println(currMax);
        for(int i = 0; i < result.length; i++) {
            System.out.println(result[i]);
            if(result[i] == currMax) {
                System.out.println("The numbers with the most divisors is: " + result[i] + ", and they are: " + currMax);
            }
        }
//        System.out.println("The number with the most divisors is: " + number + ", and they are: " + currMax);
    }
    
    public static void simpleCalc() {
        while(true) {
            System.out.print("Enter the expresion in format double number, char(+-/*), double: ");
            double first;
            char c;
            double second;
            try {
                first = TextIO.getDouble();
                if(first == 0) {
                    System.out.println("Exit Program.");
                    break;
                }
                c = TextIO.getChar();
                second = TextIO.getDouble();
                double result = computeExpression(c, first, second);
                System.out.println(first + " " + c + " " + second + " = " + result);
            }
            catch(IllegalArgumentException e) {
                System.out.println("Illegal Argument Exception..." + e.getMessage());
            }
        }
    }
    private static double computeExpression(char c, double d, double d2) {
        switch(c) {
            case '+':
                return d + d2;
            case '-':
                return d - d2;
            case '*':
                return d * d2;
            case '/':
                return d / d2;
        }
        return 0;
    }
    
    public static void printSentenceWords() {
        String str = "";
        try {
            System.out.print("Input sentence: ");
            str = TextIO.getln();
            String word = "";
            for(int i = 0; i < str.length(); i++) {
                if(Character.isLetter(str.charAt(i))) {
                    word += str.charAt(i);
                }
                else {
                    if(!word.equals("")) {
                        System.out.println(word);
                    }
                    word = "";
                }
            }
        }
        catch(IllegalArgumentException e) {
            System.out.println("Should not enter here");
        }
    }
    
    public static void readAndCompute() {
        try {
            TextIO.readFile("/home/default/NetBeansProjects/Games/JavaNotes/src/files/cities.dat");
        }
        catch(IllegalArgumentException e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
        double salesTotal = 0;
        int missingCount = 0;
        
        while(!TextIO.eof()) {
            char c;
            String dataString;
            double sales;
            
            do {
                c = TextIO.getChar();
            }
            while(c != ':');
            
            dataString = TextIO.getln();
            
            try {
                sales = Double.parseDouble(dataString);
                salesTotal += sales;
            }
            catch(IllegalArgumentException e) {
//                System.err.println("Error: " + e.getMessage());
                missingCount++;
            }
        }
        
        System.out.printf("Total sales recorded from all cities: $%1.2f\n\n", salesTotal);
    }
}
