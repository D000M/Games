/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter2;

import eckels.gui.text.TextIO;

/**
 *
 * @author default
 */
public class ExcersicesCh2 {
    public static void rollADice() {
        int diceOne = (int)(Math.random() * 6) + 1;
        int diceTwo = (int)(Math.random() * 6) + 1;
        System.out.println("The first die come with: " + diceOne);
        System.out.println("The second die come with: " + diceTwo);
        System.out.println("Total result is: " + (diceOne + diceTwo));
    }
    
    public static void countEggs() {
        System.out.println("Input how many eggs do you have: ");
        int eggs = TextIO.getInt();
        System.out.println("You have total: " + (eggs / 144) + " gross, " + ((eggs % 144) / 12) + " dozens, and " + (((eggs % 144) % 12) % 12) + " eggs.");
    }
}
