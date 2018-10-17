/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui.text;

/**
 *
 * @author default
 */
public class TestBlackJackEx {
    
    public static void runBJHandTest() {
        
        Deck myDeck = new Deck();
        BlackJackHand myHand = new BlackJackHand();

        while(true) {
            try {
                System.out.println("Do you want to play another game? Press 'y' for yes or 'n' for exit! ");
                char c = TextIO.getChar();
                
                if(!playGame(c)) {
                    break;
                }
                int cards = (int)(Math.random() * 4 + 2);
                for(int i = 0; i < cards; i++) {
                    myHand.addCard(myDeck.dealCard());
                }
                for(int i = 0; i < myHand.getCardCount(); i++) {
                    System.out.println(myHand.getCard(i).toString());
                }
                System.out.println("Total Value: " + myHand.getBlackJackValue());
                myHand.clear();
                myDeck.shuffle();
            }
            catch(IllegalArgumentException e) {
                System.err.println("Wrong argument, type 'y' or 'n'!");
            }
        }
    }
    
    static boolean playGame(char c) {
        switch(c) {
            case 'y':
            case 'Y':
                return true;
        }
        return false;
    }
    
    
}
