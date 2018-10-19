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
 * A SimpleTrackMousePanel is a panel that displays information about mouse
 * events on the panel, including the type of event, the position of the mouse,
 * a list of modifier keys that were down when the event occurred, and an indication
 * of which mouse button was involved, if any.
 */
public class SimpleTrackMouse extends JPanel{
    
    public static void runSimpleTrackMouse() {
        JFrame window = new JFrame("Mouse Events");
        SimpleTrackMouse content = new SimpleTrackMouse();
        window.setContentPane(content);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(450, 300);
        window.setSize(450, 350);
        window.setVisible(true);
    }   //end of run subroutine
    
    private String eventType = null;        // If non-null, gives the type of the most recent mouse event.
    private String modifierKeys = "";       // If non-empty, gives special keys that are held down.
    private String button = "";             // Information about which mouse button was used.
    private int mouseX, mouseY;             // Position of mouse (at most recent mouse event).

    public SimpleTrackMouse() {
        // Set background color and arrange for the panel to listen for mouse events.
        setBackground(Color.WHITE);
        MouseHandler listener = new MouseHandler();
        addMouseListener(listener);             // Register mouse listener.
        addMouseMotionListener(listener);       // Register mouse motion listener.
    }
    
    private void setInfo(MouseEvent e, String eventType) {
        this.eventType = eventType;
        mouseX = e.getX();
        mouseY = e.getY();
        modifierKeys = "";
        
        if(e.isShiftDown()) {
            modifierKeys += "Shift  ";
        }
        if(e.isControlDown()) {
            modifierKeys += "Control  ";
        }
        if(e.isMetaDown()) {
            modifierKeys += "Meta  "; 
        }
        if(e.isAltDown()) {
            modifierKeys += "Alt  ";
        }
        
        switch(e.getButton()) {
            case MouseEvent.BUTTON1:
                button = "Left";
                break;
            case MouseEvent.BUTTON2:
                button = "Middle";
                break;
            case MouseEvent.BUTTON3:
                button = "Right";
                break;
            default:
                button = "";
        } //end switch;
        repaint();
    }
    /**
     * The paintComponent() method displays information about the most recent
     * mouse event on the panel (as set by the setInfo() method).
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        if(eventType == null) {
            // If eventType is null, no mouse event has yet occurred 
            // on the panel, so don't display any information.
            return;
        }
        
        g.setColor(Color.RED);  // Display information about the mouse event.
        g.drawString("Mouse event type: " + eventType, 6, 18);
        if(modifierKeys.length() > 0) {
            g.drawString("Modifier keys: " + modifierKeys, 6, 38);
        }
        else {
            g.drawString("Modifier keys: None", 6, 38);
        }
        
        if(button.length() > 0) {
            g.drawString("Button used: " + button, 6, 58);
        }
        g.setColor(Color.BLACK);
        g.drawString("(" + mouseX + "," + mouseY + ")", mouseX, mouseY);
        
    }
    
    
    
    /**
     * An object belonging to class MouseHandler listens for mouse events
     * on the panel.  (Listening is set up in the constructor for the
     * SimpleTrackMousePanel class.)  When a mouse event occurs, the listener
     * simply calls the setInfo() method in the SimpleMouseTrackPanel class
     * with information about the mouse event that has occurred.
     */
    private class MouseHandler implements MouseListener, MouseMotionListener {

        @Override
        public void mouseClicked(MouseEvent e) {
            setInfo(e, "mouseClicked");
        }

        @Override
        public void mousePressed(MouseEvent e) {
            setInfo(e, "mousePressed");
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            setInfo(e, "mouseReleased");
        }

        @Override
        public void mouseEntered(MouseEvent e) {
            setInfo(e, "mouseEntered");
        }

        @Override
        public void mouseExited(MouseEvent e) {
            setInfo(e, "mouseExited");
        }

        @Override
        public void mouseDragged(MouseEvent e) {
            setInfo(e, "mouseDragged");
        }

        @Override
        public void mouseMoved(MouseEvent e) {
            setInfo(e, "mouseMoved");
        }
        
    }   //end of nested class MouseHandler
}   //end of class SimpleTrackMouse
