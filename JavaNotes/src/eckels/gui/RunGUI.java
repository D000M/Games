/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
import myGUI.ChessBoard;
import myGUI.MovingRects;

/**
 *
 * @author default
 */
public class RunGUI extends JPanel {
    
    public static void runGUI() {
        
//        JFrame window = new JFrame("Random Circles");
//        MovingRects drawingArea = new MovingRects();
//        drawingArea.setBackground(Color.white);
//        window.setContentPane(drawingArea);
//        
//        drawingArea.setPreferredSize(new Dimension(400, 400));
//        window.pack();
//        window.setLocation(500, 300);
//        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        window.setResizable(false);
//        
//        Timer frameTimer = new Timer(10, drawingArea);
//        window.setVisible(true);
//        frameTimer.start();
        RandomMosaicWalk.runMosaic();
        
    }
    
}
