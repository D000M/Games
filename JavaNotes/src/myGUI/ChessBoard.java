/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myGUI;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class ChessBoard extends JPanel implements ActionListener{
    
    private int frameNum;
    
    public static void drawFrame(Graphics g, int frameNumber, int width, int height) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if((i + j) % 2 == 0) {
                    g.setColor(Color.red);
                }
                else {
                    g.setColor(Color.black);
                }
                g.fillRect(50 * i, 50 * j, 50, 50);
            }
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
