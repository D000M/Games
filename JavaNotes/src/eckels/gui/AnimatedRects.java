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
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class AnimatedRects extends JPanel implements ActionListener{

    private int frameNum;
    
    public void drawFrame(Graphics g, int frameNum, int width, int height) {
        
        int inset;
        
        int rectWidth, rectHeight;
        g.setColor(Color.lightGray);
        g.fillRect(0, 0, width, height);
        
        g.setColor(Color.BLACK);
        inset = frameNum % 15;
        
        rectWidth = width - 2 * inset;
        rectHeight = height - 2 * inset;
        
        while(rectWidth >= 0 && rectHeight >= 0) {
            g.drawRect(inset, inset, rectWidth, rectHeight);
            inset += 15;
            rectWidth -= 30;
            rectHeight -= 30;
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
