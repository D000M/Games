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
public class MovingRects extends JPanel implements ActionListener{

    private int frameNum;

    public static void drawFrame(Graphics g, int frameNumber, int width, int height) {

        for(int i = 0; i < 10; i++) {
            g.drawLine(0, 40 * i, width, 40 * i);
        }
        drawCycleRects(g, frameNumber, width, height);
    }
    
    public static void drawCycleRects(Graphics g, int frameNumber, int width, int height) {
        
        int cycleFrameNumber;
        int oscilationFrameNum;

        for(int i = 0; i < 10; i++) {
            switch(i) {
                case 0:
                    cycleFrameNumber = frameNumber % 400;
                    g.fillRect(cycleFrameNumber, 40 * i, 40, 40);
                    g.setColor(Color.BLUE);
                    break;
                case 1:
                    cycleFrameNumber = frameNumber % 200;
                    g.fillRect(2 * cycleFrameNumber, 40 * i, 40, 40);
                    g.setColor(Color.ORANGE);
                    break;
                case 2:
                    cycleFrameNumber = frameNumber % 100;
                    g.fillRect(4 * cycleFrameNumber, 40 * i, 40, 40);
                    g.setColor(Color.GREEN);
                    break;
                case 3:
                    cycleFrameNumber = frameNumber % 400;
                    g.fillRect(2 * cycleFrameNumber, 40 * i, 40, 40);
                    g.setColor(Color.cyan);
                    break;
                case 4:
                    cycleFrameNumber = frameNumber % 100;
                    g.fillRect(4 * cycleFrameNumber, 40 * i, 40, 40);
                    g.setColor(Color.RED);
                    break;
                case 5:
                    oscilationFrameNum = frameNumber % 800;
                    if(oscilationFrameNum > 400) {
                        oscilationFrameNum = 800 - oscilationFrameNum;
                    }
                    g.fillRect(oscilationFrameNum, 40 * i, 40, 40);
                    g.setColor(Color.BLUE);
                    break;
                case 6:
                    oscilationFrameNum = frameNumber % 400;
                    if(oscilationFrameNum > 200) {
                        oscilationFrameNum = 400 - oscilationFrameNum;
                    }
                    g.fillRect(2 * oscilationFrameNum, 40 * i, 40, 40);
                    g.setColor(Color.ORANGE);
                    break;
                case 7:
                    oscilationFrameNum = frameNumber % 200;
                    if(oscilationFrameNum > 100) {
                        oscilationFrameNum = 200 - oscilationFrameNum;
                    }
                    g.fillRect(4 * oscilationFrameNum, 40 * i, 40, 40);
                    g.setColor(Color.GREEN);
                    break;
                case 8:
                    oscilationFrameNum = frameNumber % 400;
                    if(oscilationFrameNum > 200) {
                        oscilationFrameNum = 400 - oscilationFrameNum;
                    }
                    g.fillRect(2 * oscilationFrameNum, 40 * i, 40, 40);
                    g.setColor(Color.cyan);
                    break;
                case 9:
                    oscilationFrameNum = frameNumber % 800;
                    if(oscilationFrameNum > 400) {
                        oscilationFrameNum = 800 - oscilationFrameNum;
                    }
                    g.fillRect(oscilationFrameNum, 40 * i, 40, 40);
                    g.setColor(Color.RED);
                    break;
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
