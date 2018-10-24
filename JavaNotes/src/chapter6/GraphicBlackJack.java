/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import eckels.gui.text.BlackJackHand;
import eckels.gui.text.Card;
import eckels.gui.text.Deck;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author default
 */
public class GraphicBlackJack extends JPanel implements ActionListener{
    
    public static void runGraphicBlackJack() {
        JFrame window = new JFrame("Black Jack");
        GraphicBlackJack content = new GraphicBlackJack();
        window.setContentPane(content);
        window.setLocation(450, 350);
        window.pack();
        window.setResizable(false);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }

    JLabel dealerLabel, playerLabel, message, moneyLbl;
    JButton hitButton, standButton, newGameBtn;
    
    GamePanel gamePanel;
    
    private Deck gameDeck;
    private BlackJackHand dealerHand;
    private BlackJackHand playerHand;

    boolean isEndGame;
    boolean isPlayerWin;
    
    int playerMoney = 100;
    JTextField inputBet;
    
    public GraphicBlackJack() {
        setLayout(null);
        
        setBackground(new Color(155, 25, 25));
        setBorder(BorderFactory.createEtchedBorder());
        setPreferredSize(new Dimension(480, 320));
        
        gamePanel = new GamePanel();
        add(gamePanel);
        
        JPanel buttonBar = new JPanel();
        buttonBar.setLayout(new GridLayout(1, 5, 5, 5));
        buttonBar.setBackground(new Color(55, 0, 25));
        buttonBar.setBorder(BorderFactory.createLoweredBevelBorder());
        add(buttonBar);
        
        hitButton = new JButton("Hit");
        hitButton.addActionListener(this);
        buttonBar.add(hitButton);
        
        standButton = new JButton("Stand");
        standButton.addActionListener(this);
        buttonBar.add(standButton);
        
        newGameBtn = new JButton("New Game");
        newGameBtn.addActionListener(this);
        buttonBar.add(newGameBtn);
        
        inputBet = new JTextField("Bet: ", 10);
        inputBet.addActionListener(this);
        inputBet.setEnabled(false);
        buttonBar.add(inputBet);
        
        gamePanel.setBounds(2, 2, 476, 286);
        buttonBar.setBounds(0, 290, 480, 30);
        
        setUpStartGameButtons();
        
    }

    void doNewGame() {
        
        gameDeck = new Deck();
        playerHand = new BlackJackHand();
        dealerHand = new BlackJackHand();
        gameDeck.shuffle();
        
        playerHand.addCard(gameDeck.dealCard());
        playerHand.addCard(gameDeck.dealCard());
        dealerHand.addCard(gameDeck.dealCard());
        dealerHand.addCard(gameDeck.dealCard());
                
        isEndGame = false;
        isPlayerWin = true;
        
        dealerLabel.setText("Dealer Cards: ");
        playerLabel.setText("Player Cards: ");
        message.setText("You Have " + playerHand.getBlackJackValue() + ". Hit or Stand?");
        message.setBounds(10, 260, 480, 22);
        
        setUpPlayButtons();
        
        checkInitWin();
        
    }
    
    void hitCard() {
        playerHand.addCard(gameDeck.dealCard());
        if(loseDeal(playerHand)) {
            isPlayerWin = false;
            isEndGame = true;
            message.setText("You Lose " + playerHand.getBlackJackValue() + ". New Game or Exit?");
            setUpStartGameButtons();
        }
        else {
            if(playerHand.getBlackJackValue() <= 21 && playerHand.getCardCount() == 5) {
                message.setText("You Have Total cards: " + playerHand.getCardCount() + " You Win. New Game or Exit?");
                isPlayerWin = true;
                isEndGame = true;
                setUpStartGameButtons();
            }
            else {
                message.setText("You Have " + playerHand.getBlackJackValue() + ". Hit or Stand?");
            }
        }
        
    }
    
    void stand() {
        isEndGame = true;
        while(dealerHand.getBlackJackValue() <= 16) {
            dealerHand.addCard(gameDeck.dealCard());
        }
        dealerLabel.setText("Dealer Have " + dealerHand.getBlackJackValue() + ".");
        checkStandGameWin();
    }
    
    void checkInitWin() {
        if(dealerHand.getCardCount() == 21) {
            isPlayerWin = false;
            isEndGame = true;
            message.setText("You Lose! Dealer Has! Black Jack.");
            setUpStartGameButtons();
        }
        else if(playerHand.getBlackJackValue() == 21){
            isPlayerWin = true;
            isEndGame = true;
            message.setText("You Win! Black Jack.");
            setUpStartGameButtons();
        }
    }
    
    boolean loseDeal(BlackJackHand hand) {
        if(hand.getBlackJackValue() > 21) {
            return true;
        }
        return false;
    }
    
    void checkStandGameWin() {
        if(dealerHand.getBlackJackValue() > 21) {
            isPlayerWin = true;
        }
        else if(dealerHand.getBlackJackValue() >= playerHand.getBlackJackValue()) {
            isPlayerWin = false;
        }
        else {
            isPlayerWin = true;
        }
        if(isPlayerWin) {
            message.setText("You Win " + playerHand.getBlackJackValue() + ". New Game or Exit?");
        }
        else {
            message.setText("You Lose " + playerHand.getBlackJackValue() + ". New Game or Exit?");
        }
        setUpStartGameButtons();
    }
    
    void setUpStartGameButtons() {
        hitButton.setEnabled(false);
        standButton.setEnabled(false);
        inputBet.setEnabled(true);
        newGameBtn.setEnabled(true);
    }
    void setUpPlayButtons() {
        newGameBtn.setEnabled(false);
        hitButton.setEnabled(true);
        standButton.setEnabled(true);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        
        String command = e.getActionCommand();
        
        switch(command) {
            case "Hit":
                hitCard();
                break;
            case "Stand":
                stand();
                break;
            case "New Game":
                doNewGame();
                break;
        }
        repaint();
    }
            
    class GamePanel extends JPanel {
        
        Font cardFont;

        public GamePanel() {
            setLayout(null);
            
            setPreferredSize(new Dimension(476, 286));
            setBackground(new Color(0, 85, 0));
            
            cardFont = new Font("SansSerif", Font.PLAIN, 12);
            dealerLabel = new JLabel();
            add(dealerLabel);
            
            playerLabel = new JLabel();
            add(playerLabel);
            
            
            
            message = new JLabel("Press start New Game");
            add(message);
            
            dealerLabel.setBounds(10, 5, 200, 22);
            dealerLabel.setFont(new Font("Serif", Font.PLAIN, 18));
            dealerLabel.setForeground(new Color(120, 150, 180));
            playerLabel.setBounds(10, 140, 200, 22);
            playerLabel.setFont(new Font("Serif", Font.PLAIN, 18));
            playerLabel.setForeground(new Color(120, 150, 180));
            message.setBounds(476 / 2 - 100, 286 / 2 - 22, 480, 22);
            message.setFont(new Font("Serif", Font.PLAIN, 18));
            message.setForeground(new Color(120, 150, 180));
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
            g.setFont(cardFont);
            if(dealerHand == null || playerHand == null) {
                return;
            }
            for(int i = 0; i < dealerHand.getCardCount(); i++) {
                if(i == 0 && !isEndGame) {
                    drawCard(g, null, 10 + i * 90, 30);
                }
                else {
                    drawCard(g, dealerHand.getCard(i), 10 + i * 90, 30);
                }
            }
            for(int i = 0; i < playerHand.getCardCount(); i++) {
                drawCard(g, playerHand.getCard(i), 10 + i * 90, 160);
            }                    
        }   //end paintComponent()
        
        void drawCard(Graphics g, Card card, int x, int y) {
            if(card == null) {
                // Draw a face-down card
                g.setColor(Color.BLUE);
                g.fillRect(x, y, 80, 100);
                g.setColor(Color.WHITE);
                g.drawRect(x + 3, y + 3, 73, 93);
                g.drawRect(x + 4, y + 4, 71, 91);
            }
            else {
                g.setColor(Color.WHITE);
                g.fillRect(x, y, 80, 100);
                g.setColor(Color.GRAY);
                g.drawRect(x, y, 79, 99);
                g.drawRect(x + 1, y + 1, 77, 97);
                if(card.getSuit() == Card.DIAMONDS || card.getSuit() == Card.HEARTS) {
                    g.setColor(Color.RED);
                }
                else {
                    g.setColor(Color.BLACK);
                }
                g.drawString(card.getValueAsString(), x + 10, y + 30);
                g.drawString("of", x + 10, y + 50);
                g.drawString(card.getSuitAsString(), x + 10, y + 70);
            }
        }
        
    }
    
}
