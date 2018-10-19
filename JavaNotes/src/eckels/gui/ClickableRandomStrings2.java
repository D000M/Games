/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JFrame;

/**
 *
 * @author default
 */
public class ClickableRandomStrings2 {
    
    public static void runRandomStrings2() {
        JFrame window = new JFrame("Random Strings");
        RandomStringsPanel content = new RandomStringsPanel();
        
        content.addMouseListener(new MouseAdapter(){ 
            // Register a mouse listener that is defined by an anonymous subclass
            // of MouseAdapter.  This replaces the RepaintOnClick class that was
            // used in the original version.
            public void mousePressed(MouseEvent e) {
                Component source = (Component)e.getSource();
                source.repaint();
            }
        }); //end of addMouseListener 
        
        window.setContentPane(content);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(450,350);
        window.setSize(300,240);
        window.setVisible(true);
    }
    
}
