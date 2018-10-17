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
public class PairOfDice {
    
    private int die1 = 1;
    private int die2 = 1;

    public PairOfDice() {
        roll();
    }

    public int getDie1() {
        return die1;
    }

    public void setDie1(int die1) {
        this.die1 = die1;
    }

    public int getDie2() {
        return die2;
    }

    public void setDie2(int die2) {
        this.die2 = die2;
    }
    
    public int getTotal() {
        return die1 + die2;
    }
    
    public void roll() {
        
        die1 = (int)(Math.random() * 6 + 1);
        die2 = (int)(Math.random() * 6 + 1);
        
    }
    
    @Override
    public String toString() {
        return getDie1() + " " + getDie2() + '\n';
    }
    
    
}
