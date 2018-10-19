/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
/**
 * This program demonstrates Focus events and Key events.  A colored square
 * is drawn on the panel.  By pressing the arrow keys, the user can move
 * the square up, down, left, or right.  By pressing the keys
 * R, G, B, or K, the user can change the color of the square to red,
 * green, blue, or black, respectively. The panel changes appearance when 
 * it has the input focus; a cyan-colored border is drawn around it.  
 * When it does not have the input focus, the message "Click to Activate" 
 * is displayed and the border is gray.  The panel should have focus
 * whenever the program window is active.
 * This class contains a main() routine so that it can be run as a program
 */
public class KeyBoardAndFocusDemo extends JPanel {
    
    /**
     * The main program just opens a window that shows an object of type
     * KeyboardAndFocusDemo.  Note that it requests focus for the panel.
     * This has to be done after the window is made visible for it to have
     * any effect.
     */
    public static void runKeyBoardDemo() {
        JFrame window = new JFrame("Moving Square");
        KeyBoardAndFocusDemo content = new KeyBoardAndFocusDemo();
        window.setContentPane(content);
        window.setSize(400, 400);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
        content.requestFocusInWindow();
    }
    
    /**
     * This nested class is used to define a keyboard and focus listener that
     * will listen for events on the panel.
     */
    private class Listener implements KeyListener, FocusListener {

        
        /**
         * This method is called when the user types a character on the keyboard
         * while the panel has the input focus.  If the character is R, G, B, or K
         * (or the corresponding lower case characters), then the color of the
         * square is changed to red, green, blue, or black, respectively.
         */
        @Override
        public void keyTyped(KeyEvent e) {
            char key = e.getKeyChar();
            if(key == 'B' || key == 'b') {
                squareColor = Color.BLUE;
                repaint();
            }
            else if(key == 'G' || key == 'g') {
                squareColor = Color.GREEN;
                repaint();
            }
            else if(key == 'R' || key == 'r') {
                squareColor = Color.RED;
                repaint();
            }
            else if(key == 'K' || key == 'k') {
                squareColor = Color.BLACK;
                repaint();
            }
        }   //end keyTyped()

         /**
         * This is called each time the user presses a key while the panel has
         * the input focus.  If the key pressed was one of the arrow keys,
         * the square is moved (except that it is not allowed to move off the
         * edge of the panel).
         */
        @Override
        public void keyPressed(KeyEvent e) {
            
            int key = e.getKeyCode();
            
            if(key == KeyEvent.VK_LEFT) {
                squareLeft -= 8;
                if(squareLeft < 3) {
                    squareLeft = 3;
                }
                repaint();
            }
            else if(key == KeyEvent.VK_RIGHT) {
                squareLeft += 8;
                if(squareLeft > getWidth() - 3 - SQUARE_SIZE) {
                    squareLeft = getWidth() - 3 - SQUARE_SIZE;
                }
                repaint();
            }
            else if(key == KeyEvent.VK_UP) {
                squareTop -= 8;
                if(squareTop < 3) {
                    squareTop = 3;
                }
                repaint();
            }
            else if(key == KeyEvent.VK_DOWN) {
                squareTop += 8;
                if(squareTop > getHeight()- 3 - SQUARE_SIZE) {
                    squareTop = getHeight()- 3 - SQUARE_SIZE;
                }
                repaint();
            }
        } //end keyPressed()

        /**
         * This is called each time the user releases a key while the panel
         * has the input focus.  In this class, it does nothing, but it is
         * required to be here by the KeyListener interface.
         */
        @Override
        public void keyReleased(KeyEvent e) {
        }

        /**
         * This will be called when the panel gains the input focus.  It just
         * calls repaint().  The panel will be redrawn with a cyan-colored border
         * and with a message about keyboard input.
         */
        @Override
        public void focusGained(FocusEvent e) {
            repaint();
        }

        /**
         * This will be called when the panel loses the input focus.  It just
         * calls repaint().  The panel will be redrawn with a gray-colored border
         * and with the message "Click to activate."
         */
        @Override
        public void focusLost(FocusEvent e) {
            repaint();
        }
        
    }   //end of Listener nested private class
    
    private static final int SQUARE_SIZE = 50;
    private Color squareColor;
    private int squareTop, squareLeft;

    /**
     * The constructor sets the initial position and color of the square
     * and registers itself to act as a listener for Key, Focus, and 
     * Mouse events.
     */
    public KeyBoardAndFocusDemo() {
        squareTop = 100;    // Initial position of top-left corner of square.
        squareLeft = 100;
        squareColor = Color.RED;
        
        setBackground(Color.WHITE);
        Listener listener = new Listener();
        addKeyListener(listener);
        addFocusListener(listener);
        
    }   //end constructor

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        // Fills the panel with its
        // background color, which is white.

        /* Draw a 3-pixel border, colored cyan if the panel has the
               keyboard focus, or in light gray if it does not. */
        
        if(hasFocus()) {
            g.setColor(Color.CYAN);
        }
        else {
            g.setColor(Color.GRAY);
        }
        
        int width = getSize().width;    // Width of the panel.
        int height = getSize().height;  // Height of the panel.
        g.drawRect(0, 0, width - 1, height -1);
        g.drawRect(1, 1, width - 3, height -3);
        g.drawRect(2, 2, width - 5, height -5);
        
        /* Draw the square. */
        
        g.setColor(squareColor);
        g.fillRect(squareLeft, squareTop, SQUARE_SIZE, SQUARE_SIZE);
        
        /* Print a message that depends on whether the panel has the focus. */
        g.setColor(Color.MAGENTA);
        if(hasFocus()) {
            g.drawString("Arrow Keys Move Square", 7, 20);
            g.drawString("K, R, G, B Change Color", 7, 40);
        }
        else {
            g.drawString("Click To Activate", 7, 20);
        }
    }   //end paintComponent()
    
}
