/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui.text;

import java.util.ArrayList;

/**
 *
 * @author default
 */
/**
 * An object of type Hand represents a hand of cards.  The
 * cards belong to the class Card.  A hand is empty when it
 * is created, and any number of cards can be added to it.
 */
public class Hand {
    
    private ArrayList<Card> hand;

    /**
     * Create a hand that is initially empty.
     */
    public Hand() {
        hand = new ArrayList<Card>();
    }
    
    /**
     * Remove all cards from the hand, leaving it empty.
     */
    public void clear(){
        hand.clear();
    }
        
    public void addCard(Card c) {
        if(c == null) {
            throw new NullPointerException("Can't add null to a card");
        }
        hand.add(c);
    }
    
    /**
     * Remove a card from the hand, if present.
     * @param c the card to be removed.  If c is null or if the card is not in 
     * the hand, then nothing is done.
     */
    public void removeCard(Card c) {
        hand.remove(c);
    }
    
    /**
     * Remove the card in a specified position from the hand.
     * @param position the position of the card that is to be removed, where
     * positions are starting from zero.
     * @throws IllegalArgumentException if the position does not exist in
     * the hand, that is if the position is less than 0 or greater than
     * or equal to the number of cards in the hand.
     */
    public void removeCard(int position) {
        if(position < 0 || position >= hand.size()) {
            throw new IllegalArgumentException("Position does not exist in the hand: " + position);
        }
        hand.remove(position);
    }
    
    /**
     * Returns the number of cards in the hand.
     */
    public int getCardCount() {
        return hand.size();
    }
    
     /**
     * Gets the card in a specified position in the hand.  (Note that this card
     * is not removed from the hand!)
     * @param position the position of the card that is to be returned
     * @throws IllegalArgumentException if position does not exist in the hand
     */
    public Card getCard(int position) {
        if(position < 0 || position >= hand.size()) {
            throw new IllegalArgumentException("Position does not exist in the hand: " + position);
        }
        return hand.get(position);
    }
    
    /**
     * Sorts the cards in the hand so that cards of the same suit are
     * grouped together, and within a suit the cards are sorted by value.
     * Note that aces are considered to have the lowest value, 1.
     */
    public void sortBySuit() {
        ArrayList<Card> newHand = new ArrayList<Card>();
        while(hand.size() > 0) {
            int pos = 0;    //position of the minimal card.
            Card c = hand.get(pos);
            for(int i = 1; i < hand.size(); i++) {
                Card c1 = hand.get(i);
                if(c1.getSuit() < c.getSuit() || (c1.getSuit() == c.getSuit() && c1.getValue() < c.getValue())) {
                    pos = i;
                    c = c1;
                }
            }
            hand.remove(pos);
            newHand.add(c);
        }
        hand = newHand;
    }
    
    /**
     * Sorts the cards in the hand so that cards of the same value are
     * grouped together.  Cards with the same value are sorted by suit.
     * Note that aces are considered to have the lowest value, 1.
     */
    public void sortByValue() {
        ArrayList<Card> newHand = new ArrayList<Card>();
        while(hand.size() > 0) {
            int pos = 0;
            Card c = hand.get(pos);
            for(int i = 1; i < hand.size(); i++) {
                Card c1 = hand.get(i);
                if(c1.getValue() < c.getValue() || (c1.getValue() == c.getValue() && c1.getSuit() < c.getSuit())) {
                    pos = i;
                    c = c1;
                }
            }
            hand.remove(pos);
            newHand.add(c);
        }
        hand = newHand;
    }
}
