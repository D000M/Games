/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter5;

import eckels.gui.text.TextIO;

/**
 *
 * @author default
 */
public class TestProgram {
    
    public static void runTest() {
        PairOfDice dices = new PairOfDice();
        int count = 0;
        System.out.println("Before While: " + dices);
        do {
            dices.roll();
            count++;
            System.out.println(count + ": " + " " + dices);
        }
        while(dices.getDie1() + dices.getDie2() != 2);
    }
    
    public static void runEx2() {
        StatCalc calc = new StatCalc();
        double input = -1;
        do {
            try {
                System.out.print("Input 0 to exit or Input an Double: ");
                input = TextIO.getDouble();
                if(input == 0) {
                    break;
                }
                calc.enter(input);
            }
            catch(IllegalArgumentException e) {
                System.err.println("The inputed number isnt correct try again!");
            }
        }while(input != 0);
        
        System.out.println(calc);
    }
}
