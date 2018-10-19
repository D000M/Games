/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
/**
 * This panel displays 25 copies of a message.  The color and 
 * position of each message is selected at random.  The font
 * of each message is randomly chosen from among five possible
 * fonts.  The messages are displayed on a black background.
 * Note:  The style of drawing used here is poor, because every
 * time the paintComponent() method is called, new random values are
 * used.  This means that a different picture will be drawn each time.  
 */
public class RandomStringsPanel extends JPanel {
    
    private String message;     // The message to be displayed.  This can be set in
                                // the constructor.  If no value is provided in the
                                // constructor, then the string "Java!" is used.
    
    private Font font1, font2, font3, font4, font5;     // The five fonts.

    /**
     * Default constructor creates a panel that displays the message "Java!".
     */
    public RandomStringsPanel() {
        this(null);     // Call the other constructor, with parameter null.
    }

    public RandomStringsPanel(String message) {
        this.message = message;
        if(this.message == null) {
            this.message = "Java!";
        }
        this.font1 = new Font("Serif", Font.BOLD, 14);
        this.font2 = new Font("SansSerif", Font.BOLD + Font.ITALIC, 24);
        this.font3 = new Font("Monospaced", Font.PLAIN, 30);
        this.font4 = new Font("Dialog", Font.PLAIN, 36);
        this.font5 = new Font("Serif", Font.ITALIC, 48);
        
        setBackground(Color.BLACK);
    }

    /**
     * The paintComponent method is responsible for drawing the content of the panel.
     * It draws 25 copies of the message string, using a random color, font, and
     * position for each string.
     */
    
    @Override
    protected void paintComponent(Graphics g) {
        // Call the paintComponent method from the 
        // superclass, JPanel.  This simply fills the 
        // entire panel with the background color, black.
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        
        Graphics2D g2d = (Graphics2D)g; // (To make the text smoother.)
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        int width = getWidth();
        int height = getHeight();
        
        for(int i = 0; i < 25; i++) {
            // Draw one string.  First, set the font to be one of the five
            // available fonts, at random.  
            int fontNum = (int)(Math.random() * 5 + 1);
            switch(fontNum) {
                case 1:
                    g2d.setFont(font1);
                    break;
                case 2:
                    g2d.setFont(font2);
                    break;
                case 3:
                    g2d.setFont(font3);
                    break;
                case 4:
                    g2d.setFont(font4);
                    break;
                case 5:
                    g2d.setFont(font5);
                    break;
            }   //end switch
            
            float hue = (float)Math.random();
            g2d.setColor(Color.getHSBColor(hue, 1.0f, 1.0f));
            
            // Select the position of the string, at random.
            int x, y;
            x = -50 + (int)(Math.random() * width + 40);
            y = (int)(Math.random() * (height + 20));
            
            //Draw the message
            g.drawString(message, x, y);
        } //end for
    } //end paintComponent()
           
}
