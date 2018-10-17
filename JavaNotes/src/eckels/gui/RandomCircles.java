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

/**
 *
 * @author default
 */
public class RandomCircles extends JPanel implements ActionListener{
    
    private int frameNum;
    
    public void drawFrame(Graphics g, int frameNumber, int width, int height) {
        int centerX;
        int centerY;
        int colorChoice;
        int count;
        
        for(count = 0; count < 500; count++) {
            
            colorChoice = (int)(3 * Math.random());
            
            switch(colorChoice) {
                case 0:
                    g.setColor(Color.red);
                    break;
                case 1:
                    g.setColor(Color.green);
                    break;
                case 2:
                    g.setColor(Color.blue);
                    break;
            }
            centerX = (int)(Math.random() * width);
            centerY = (int)(Math.random() * height);
            
            g.fillOval(centerX - 50, centerY - 50, 100, 100);
            g.setColor(Color.black);
            g.drawOval(centerX - 50, centerY - 50, 100, 100);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        frameNum++;
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        drawFrame(g, frameNum, getWidth(), getHeight());
    }

}
