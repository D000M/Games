/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.HeadlessException;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class SquaresMoving extends JPanel implements MouseListener, MouseMotionListener{

    public static void runSquaresMoving() {
        JFrame window = new JFrame("Simple Square Moving");
        SquaresMoving content = new SquaresMoving();
        window.setContentPane(content);
        window.setLocation(450, 350);
        window.setSize(640, 480);
        window.setResizable(false);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }
    
    boolean isRedSquare;
    boolean isBlueSquare;
    Square red;
    Square blue;
    
    int currX, currY;
    
    public SquaresMoving(){
        isRedSquare = false;
        isBlueSquare = false;
        red = new Square(50, 50, 100, 100);
        blue = new Square(250, 250, 70, 70);
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
        if(x > red.getX() && x < red.getX() + red.getWidth() && y > red.getY() && y < red.getY() + red.getHeight()) {
            isRedSquare = true;
            currX = x - red.getX();
            currY = y - red.getY();
        }
        if( x > blue.getX() && x < blue.getX() + blue.getWidth() && y > blue.getY() && y < blue.getY() + blue.getHeight()) {
            isBlueSquare = true;
            currX = x - blue.getX();
            currY = y - blue.getY();
        }

    }

    @Override
    public void mouseReleased(MouseEvent e) {
        isRedSquare = false;
        isBlueSquare = false;
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        int x = e.getX();
        int y = e.getY();
        
        if(isRedSquare) {
            red.setX(x - currX);
            red.setY(y - currY);
        }
        else if(isBlueSquare) {
            blue.setX(x - currX);
            blue.setY(y - currY);
        }
        repaint();
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        
        g.setColor(Color.RED);
        g.drawRect(red.getX(), red.getY(), red.getWidth(), red.getHeight());
        g.setColor(Color.BLUE);
        g.drawRect(blue.getX(), blue.getY(), blue.getWidth(), blue.getHeight());
        
    }

    
}
