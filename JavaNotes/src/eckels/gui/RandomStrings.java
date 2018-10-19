/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import javax.swing.JFrame;

/**
 *
 * @author default
 */
public class RandomStrings {
    
    public static void runRandomStrings() {
        JFrame window = new JFrame("Random Strings");
        RandomStringsPanel content = new RandomStringsPanel();
        RepaintOnClick listener = new RepaintOnClick(); // Create MouseListener object.
        content.addMouseListener(listener);
        window.setContentPane(content);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(350, 250);
        window.setSize(350, 250);
        window.setVisible(true);
    }
    
}
