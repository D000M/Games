/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter4;

/**
 *
 * @author default
 */
public class ExcersicesCh4 {
    
    public static void printCapitalised(String sentence) {
        char c;
        for(int i = 0; i < sentence.length(); i++) {
            c = sentence.charAt(i);
            if(Character.isLetter(c) && (i == 0 || sentence.charAt(i - 1) == ' ')) {
                System.out.print(Character.toUpperCase(c));
            }
            else {
                System.out.print(c);
            }
        }
    }
    
    public static void printHexToDecimal(String str) {
        int number = 0;
        for(int i = 0; i < str.length(); i++) {
            if((int)str.charAt(i) < 48 || (int)str.charAt(i) > 57 
                    && (int)str.charAt(i) < 65 || (int)str.charAt(i) > 70 
                    && (int)str.charAt(i) < 97 || (int)str.charAt(i) > 102) {
                System.err.println("The imputed number is not hexadecimal!");
                System.exit(1);
            }
            number = number * 16 +  convertHexToDec(str.charAt(i));
        }
        System.out.println(str + " = " + number + " decimal.");
    }
    private static int convertHexToDec(char c) {
        int number = 0;
        switch(c) {
            case '0':
                number = 0;
                break;
            case '1':
                number = 1;
                break;
            case '2':
                number = 2;
                break;
            case '3':
                number = 3;
                break;
            case '4':
                number = 4;
                break;
            case '5':
                number = 5;
                break;
            case '6':
                number = 6;
                break;
            case '7':
                number = 7;
                break;
            case '8':
                number = 8;
                break;
            case '9':
                number = 9;
                break;
            case 'a':
            case 'A':
                number = 10;
                break;
            case 'b':
            case 'B':
                number = 11;
                break;
            case 'c':
            case 'C':
                number = 12;
                break;
            case 'd':
            case 'D':
                number = 13;
                break;
            case 'e':
            case 'E':
                number = 14;
                break;
            case 'f':
            case 'F':
                number = 15;
                break;
        }
        return number;
    }
    
    public static int totalRolls(int n) {
        int totRolls = 0;
        
        if(n < 2 || n > 12) {
            throw new IllegalArgumentException("The Number must be between 2 and 12.");
        }
        int firstDice = 0;
        int secondDice = 0;
        while((firstDice + secondDice) != n) {
            firstDice = (int)(Math.random() * 6 + 1);
            secondDice = (int)(Math.random() * 6 + 1);
            totRolls++;
        }
        return totRolls;
    }
    public static void testRolls() {
        System.out.println("Total rolls: " + totalRolls(12));
    }
    
    public static void printRollsStatistics(int n) {
        System.out.println("\t\t  Total on Dice\t\tAverage Number Of Rolls");
        for(int i = 2; i <= 12; i++) {
            double average = 0;
            System.out.print("\t\t\t" + i);
            for(int j = 0; j < n; j++) {
                average += totalRolls(i);
            }
            System.out.println("\t\t\t" + average / n);
        }
    }
}
