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
/**
 *  An object of type Deck represents a deck of playing cards.  The deck
 *  is a regular poker deck that contains 52 regular cards and that can
 *  also optionally include two Jokers.
 */
public class Deck {
    
    /**
     * An array of 52 or 54 cards.  A 54-card deck contains two Jokers,
     * in addition to the 52 cards of a regular poker deck.
     */
    private Card[] deck;
    
    /**
     * Keeps track of the number of cards that have been dealt from
     * the deck so far.
     */
    private int cardUsed;

    /**
     * Constructs a regular 52-card poker deck.  Initially, the cards
     * are in a sorted order.  The shuffle() method can be called to
     * randomize the order.  (Note that "new Deck()" is equivalent
     * to "new Deck(false)".)
     */
    public Deck() {
        this(false);
    }

    public Deck(boolean includeJokers) {
        if(includeJokers) {
            deck = new Card[54];
        }
        else {
            deck = new Card[52];
        }
        int cardCt = 0;
        for(int suit = 0; suit <= 3; suit++) {
            for(int value = 1; value <= 13; value++) {
                deck[cardCt] = new Card(value, suit);
                cardCt++;
            }
        }
        if(includeJokers) {
            deck[53] = new Card(1, Card.JOKER);
            deck[54] = new Card(2, Card.JOKER);
        }
        cardUsed = 0;
    }
    
    /**
     * Put all the used cards back into the deck (if any), and
     * shuffle the deck into a random order.
     */
    public void shuffle() {
        for(int i = deck.length - 1; i > 0; i--) {
            int rand = (int)(Math.random() * (i + 1));
            Card temp = deck[i];
            deck[i] = deck[rand];
            deck[rand] = temp;
        }
        cardUsed = 0;
    }
    
    /**
     * As cards are dealt from the deck, the number of cards left
     * decreases.  This function returns the number of cards that
     * are still left in the deck.  The return value would be
     * 52 or 54 (depending on whether the deck includes Jokers)
     * when the deck is first created or after the deck has been
     * shuffled.  It decreases by 1 each time the dealCard() method
     * is called.
     */
    public int cardsLeft() {
        return deck.length - cardUsed;
    }
    
    /**
     * Removes the next card from the deck and return it.  It is illegal
     * to call this method if there are no more cards in the deck.  You can
     * check the number of cards remaining by calling the cardsLeft() function.
     * @return the card which is removed from the deck.
     * @throws IllegalStateException if there are no cards left in the deck
     */
    public Card dealCard() {
        if(cardUsed == deck.length) {
            throw new IllegalArgumentException("No cards are left in the deck.");
        }
        cardUsed++;
        return deck[cardUsed - 1];
    }
    
    /**
     * Test whether the deck contains Jokers.
     * @return true, if this is a 54-card deck containing two jokers, or false if
     * this is a 52 card deck that contains no jokers.
     */
    public boolean hasJokers() {
        return (deck.length == 54);
    }
}
