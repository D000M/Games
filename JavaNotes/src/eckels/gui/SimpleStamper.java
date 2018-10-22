/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
/**
 * A simple demonstration of MouseEvents.  Shapes are drawn
 * on a black background when the user clicks the panel.  If
 * the user Shift-clicks, the panel is cleared.  If the user
 * right-clicks the panel, a blue oval is drawn.  Otherwise,
 * when the user clicks, a red rectangle is drawn.  The contents of
 * the panel are not persistent.  For example, they might disappear 
 * if the panel is resized.
 * This class has a main() routine to allow it to be run as an application.
 */
public class SimpleStamper extends JPanel implements MouseListener, MouseMotionListener{

    public static void runSimpleStamper() {
        JFrame window = new JFrame("Simple Stamper");
        SimpleStamper content = new SimpleStamper();
        window.setContentPane(content);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(350, 250);
        window.setSize(450, 350);
        window.setVisible(true);
    }

    int prevX, prevY;
    
    /**
    * This constructor simply sets the background color of the panel to be black
    * and sets the panel to listen for mouse events on itself.
    */
    public SimpleStamper() {
        setBackground(Color.BLACK);
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    
    @Override
    public void mouseClicked(MouseEvent e) {
    }

    /**
    *  Since this panel has been set to listen for mouse events on itself, 
    *  this method will be called when the user clicks the mouse on the panel.
    *  This method is part of the MouseListener interface.
    */
    @Override
    public void mousePressed(MouseEvent e) {
        if(e.isShiftDown()){
            // The user was holding down the Shift key.  Just repaint the panel.
            // Since this class does not define a paintComponent() method, the 
            // method from the superclass, JPanel, is called.  That method simply
            // fills the panel with its background color, which is black.  The 
            // effect is to clear the panel.
            repaint();
            return;
        }
        
        int x = e.getX();
        int y = e.getY();
        
        Graphics g = getGraphics();         // Graphics context for drawing directly.
                                            // NOTE: This is considered to be bad style!
        prevX = x;
        prevY = y;
        if(e.isMetaDown()) {
             // User right-clicked at the point (x,y). Draw a blue oval centered 
             // at the point (x,y). (A black outline around the oval will make it 
             // more distinct when shapes overlap.)
             g.setColor(Color.BLUE);
             g.fillOval(x - 30, y - 15, 60, 30);    //Blue interior
             g.setColor(Color.BLACK);
             g.drawOval(x - 30, y - 15, 60, 30);    //Black outline
        }
        else {
            // User left-clicked (or middle-clicked) at (x,y). 
            // Draw a red rectangle centered at (x,y).
            g.setColor(Color.RED);
            g.fillRect(x - 30, y - 15, 60, 30); //red interior
            g.setColor(Color.BLACK);
            g.drawRect(x - 30, y - 15, 60, 30); //black outline
        }
        
        g.dispose();    // We are finished with the graphics context, so dispose of it.
    }   //end of mouse Pressed

    // The next four empty routines are required by the MouseListener interface.
    // They don't do anything in this class, so their definitions are empty.
    @Override
    public void mouseReleased(MouseEvent e) {
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
                
        Graphics g = getGraphics();
        if(prevX < x - 5 || prevX > x + 5 || prevY > y + 5 || prevY < y - 5) {
            if(e.isMetaDown()) {
                 // User right-clicked at the point (x,y). Draw a blue oval centered 
                 // at the point (x,y). (A black outline around the oval will make it 
                 // more distinct when shapes overlap.)
                 g.setColor(Color.BLUE);
                 g.fillOval(x - 30, y - 15, 60, 30);    //Blue interior
                 g.setColor(Color.BLACK);
                 g.drawOval(x - 30, y - 15, 60, 30);    //Black outline
            }
            else {
                // User left-clicked (or middle-clicked) at (x,y). 
                // Draw a red rectangle centered at (x,y).
                g.setColor(Color.RED);
                g.fillRect(x - 30, y - 15, 60, 30); //red interior
                g.setColor(Color.BLACK);
                g.drawRect(x - 30, y - 15, 60, 30); //black outline
            }
            prevX = x;
            prevY = y;
        }
        g.dispose();
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        
    }
    
}
