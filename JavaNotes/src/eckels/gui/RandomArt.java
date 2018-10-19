/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author default
 */
/**
 * A RandomArtPanel draws random pictures which might be taken to have
 * some vague resemblance to abstract art.  A new picture is produced every
 * four seconds.  There are three types of pictures:  random lines,
 * random circles, and random 3D rects.  The figures are drawn in
 * random colors on a background that is a random shade of gray.
 * A main() routine allows this class to be run as a program
 */
public class RandomArt extends JPanel{
    
    public static void runRandomArt() {
        JFrame window = new JFrame("Random Art");
        RandomArt content = new RandomArt();
        window.setContentPane(content);
        window.setSize(400, 400);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    } //end run subroutine.
    
//    private class RepaintAction implements ActionListener {
//
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            repaint();  // Call the repaint() method in the panel class.
//        }
//        
//    } //end private nested class RepaintAction

    /**
     * The constructor creates a timer with a delay time of four seconds
     * (4000 milliseconds), and with a RepaintAction object as its
     * ActionListener.  It also starts the timer running.
     */
    public RandomArt() {
//        RepaintAction action = new RepaintAction();
        Timer timer = new Timer(4000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaint();
            }
        });
        timer.start();
    }

    /**
     * The paintComponent() method fills the panel with a random shade of
     * gray and then draws one of three types of random "art".  The type
     * of art to be drawn is chosen at random.
     */
    @Override
    protected void paintComponent(Graphics g) {
        // Note:  Since the next three lines fill the entire panel with
        // gray, there is no need to call super.paintComponent(g), since
        // any drawing that it does will only be covered up anyway.
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        
        Color randomGray = Color.getHSBColor(1.0f, 1.0f, (float)Math.random());
        g.setColor(randomGray);
        g.fillRect(0, 0, getWidth(), getHeight());
        
        int artType = (int)(Math.random() * 3);
        switch(artType) {
            case 0:
                for(int i = 0; i < 500; i++) {
                    int x1 = (int)(Math.random() * getWidth());
                    int y1 = (int)(Math.random() * getHeight());
                    int x2 = (int)(Math.random() * getWidth());
                    int y2 = (int)(Math.random() * getHeight());
                    Color randomHue = Color.getHSBColor((float)Math.random(), 1.0f, 1.0f);
                    g.setColor(randomHue);
                    g.drawLine(x1, y1, x2, y2);
                }
                break;
            case 1:
                for(int i = 0; i < 200; i++) {
                    int centerX = (int)(Math.random() * getWidth());
                    int centerY = (int)(Math.random() * getHeight());
                    Color randomHue = Color.getHSBColor((float)Math.random(), 1.0f, 1.0f);
                    g.setColor(randomHue);
                    g.drawOval(centerX - 50, centerY - 50, 100, 100);
                }
                break;
            case 2:
                for(int i = 0; i < 25; i++) {
                    int centerX = (int)(Math.random() * getWidth());
                    int centerY = (int)(Math.random() * getHeight());
                    int size = 30 + (int)(170 * Math.random());
                    Color randomColor = new Color((int)(Math.random() * 256), (int)(Math.random() * 256), (int)(Math.random() * 256));
                    g.setColor(randomColor);
                    g.fill3DRect(centerX - size / 2, centerY - size / 2, size, size, true);
                }
                break;
        }
    }   //end paintComponent()
        
}
