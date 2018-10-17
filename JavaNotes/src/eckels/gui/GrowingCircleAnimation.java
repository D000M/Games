/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author default Bruce
 */
/**
 * This program shows an animation where 100 semi-transparent disks of
 * various sizes grow continually, disappearing before they get too big.
 * When a disk disappears, it is replaced by a new disk at another location.
 */
public class GrowingCircleAnimation extends JPanel implements ActionListener{

    private CircleInfo[] circleData;
    
    /**
     *  Draw one frame of the animation.  If there is no disk data (which is
     *  true for the first frame), 100 disks with random locations, colors,
     *  and radii are created.  In each frame, all the disks grow by
     *  one pixel per frame.  Disks sometimes disappear at random, or when
     *  their radius reaches 100.  when a disk disappears, a new disk appears
     *  with radius 1 and with a random location and color
     */
    private void drawFrame(Graphics g, int frameNumber, int width, int height) {
        if(circleData == null) {
            circleData = new CircleInfo[100];
            for(int i = 0; i < circleData.length; i++) {
                circleData[i] = new CircleInfo(
                        (int)(width * Math.random()), 
                        (int)(height * Math.random()), 
                        (int)(100 * Math.random()));
            }
        }
        for(int i = 0; i < circleData.length; i++) {
            circleData[i].radius++;
            circleData[i].draw(g);
            if(Math.random() < 0.01 || circleData[i].radius > 100) {
                // replace circle number i with a new circle
                circleData[i] = new CircleInfo(
                        (int)(width * Math.random()), 
                        (int)(height * Math.random()), 1);
            } 
        }
        g.setColor(Color.BLACK);
        g.drawRect(0, 0, width - 1, height - 1);    // Draw a frame (for the screenshot).
    }
    
    private int frameNum;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        drawFrame(g, frameNum, getWidth(), getHeight());
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        frameNum++;
        repaint();
    }
    
    public static void runCircles() {
        JFrame window = new JFrame("Falling Circles");
        GrowingCircleAnimation drawingArea = new GrowingCircleAnimation();
        drawingArea.setBackground(Color.WHITE);
        window.setContentPane(drawingArea);
        drawingArea.setPreferredSize(new Dimension(600,480));
        window.pack();
        window.setLocation(100,50);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        Timer frameTimer = new Timer(20,drawingArea);
        window.setVisible(true);
        frameTimer.start();
    } // end main
    
}
