/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter5;

/**
 *
 * @author default
 */
public class DiceRollStats2 {
    
    static final int NUMBER_OF_EXPERIMENTS = 10000;
    
    private static PairOfDice dices = new PairOfDice();
    
    public static void runDicesExperiment() {
        System.out.println("Dice total   Avg # of Rolls   Stand. Deviation   Max # of Rolls");
        System.out.println("----------   --------------   ----------------   --------------");
        
        for(int total = 2; total <= 12; total++) {
            StatCalc calc = new StatCalc();
            for(int j = 0; j < NUMBER_OF_EXPERIMENTS; j++) {
                calc.enter(rollFor(total));
            }
            System.out.printf("%6d", total);
            System.out.printf("%18.3f", calc.getMean());
            System.out.printf("%19.3f", calc.getStandardDeviation());
            System.out.printf("%14.3f", calc.getMax());
            System.out.println();
        }
    }
    
    static int rollFor(int n) {
        int rollCt = 0;
        do {
            dices.roll();
            rollCt++;
        }
        while(dices.getTotal() != n);
        
        return rollCt;
    }
}
