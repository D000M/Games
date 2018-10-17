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
public class BlackJackGame {
    
    private final Deck gameDeck;
    private final BlackJackHand playerHand;
    private final BlackJackHand dealerHand;
    
    private boolean userWin;
    private int playerMoney;
    
    public BlackJackGame(int startingMoney) {
        gameDeck = new Deck();
        playerHand = new BlackJackHand();
        dealerHand = new BlackJackHand();
        userWin = true;
        
        playerMoney = startingMoney;
        gameDeck.shuffle();
        
        runGame();
    }
    
    private void runGame() {
        System.out.println("The Game Has Started The player has: " + playerMoney + "$");
        
        while(playerMoney > 0) {
            userWin = true;
            playerMoney -= 10;
            playerHand.addCard(gameDeck.dealCard());
            playerHand.addCard(gameDeck.dealCard());
            printHand("Player", playerHand, playerHand.getCardCount(), true);
            dealerHand.addCard(gameDeck.dealCard());
            dealerHand.addCard(gameDeck.dealCard());
            printHand("Dealer", dealerHand, 1, false);
            checkInitialWin();
            if(dealerHand.getBlackJackValue() != 21 && playerHand.getBlackJackValue() != 21) {
                gamePlayPhase();
            }
            playerHand.clear();
            dealerHand.clear();
            gameDeck.shuffle();
            System.out.println("The Game Has Started The player has: " + playerMoney + "$");
            System.out.println("Do You Want to play More Games? 'y' or 'n'");
            char c = TextIO.getChar();
            if(!playMoreGames(c)) {
                break;
            }
        }
        
        System.out.println("The Game Has Ended the player finished with: " + playerMoney + "$.");
    }
    
    private static void printHand(String player, BlackJackHand hand, int cards, boolean revealCards) {
        System.out.println(player + " hand: ");
        for(int i = 0; i < cards; i++) {
            System.out.println(hand.getCard(i).toString());
        }
        if(revealCards) {
            System.out.println("Total Value: " + hand.getBlackJackValue());
        }
    }
    
    private void checkInitialWin() {
        if(dealerHand.getBlackJackValue() == 21) {
            System.out.println("Dealer BlackJack");
            userWin = false;
        }
        else if(playerHand.getBlackJackValue() == 21) {
            playerMoney += 20;
            System.out.println("Player BlackJack");
            userWin = true;
        }
    }
    
    private void gamePlayPhase() {
        boolean addCards = true;
        while(addCards) {
            System.out.println("Do you Want to add more cards? 'Hit' or 'Stand' ?");
            String s = TextIO.getlnWord();
            
            if(addMoreCards(s)) {
                playerHand.addCard(gameDeck.dealCard());
            }
            
            printHand("Player", playerHand, playerHand.getCardCount(), true);
            printHand("Dealer", dealerHand, 1, false);
            if(playerHand.getBlackJackValue() > 21) {
                userWin = false;
                addCards = false;
            }
            if(!addMoreCards(s)) {
                while(dealerHand.getBlackJackValue() <= 16) {
                    System.out.println("Reveal delear cards: ");
                    char c = TextIO.getChar();
                    dealerHand.addCard(gameDeck.dealCard());
                    printHand("Dealer", dealerHand, dealerHand.getCardCount(), true);
                }
                addCards = false;
            }
            if(addCards == false) {
                printHand("Player", playerHand, playerHand.getCardCount(), true);
                printHand("Dealer", dealerHand, dealerHand.getCardCount(), true);
                if(userWin) {
                    checkEndGame();
                }
                endGameMessage();
            }
        }
    }
    
    private static boolean addMoreCards(String s) {
        if(s.equalsIgnoreCase("Hit")) {
            return true;
        }
        return false;
    }
    
    private void checkEndGame() {
        if(dealerHand.getBlackJackValue() > 21) {
            userWin = true;
        }
        else if(dealerHand.getBlackJackValue() >= playerHand.getBlackJackValue()) {
            userWin = false;
        }
        else {
            userWin = true;
        }
    }
    private void endGameMessage() {
        if(userWin) {
            playerMoney += 20;
            System.out.println("You WIN!");
        }
        else {
            System.out.println("You LOSE!");
        }
    }
    private boolean playMoreGames(char c) {
        switch(c) {
            case 'y':
            case 'Y':
                return true;
        }
        return false;
    }
}
