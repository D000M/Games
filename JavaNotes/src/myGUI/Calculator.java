/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myGUI;

import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class Calculator extends JPanel {
    
    public static void runCalculator() {
        JFrame window = new JFrame();
        Calculator content = new Calculator();
        window.setContentPane(content);
        window.setSize(640, 480);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setVisible(true);
    }
    
    JButton[] buttons;
    
    public Calculator() {
        
        buttons = new JButton[12];
        
        setLayout(new GridLayout(4, 3, 3, 3));
        setBorder(BorderFactory.createRaisedBevelBorder());
        setButtons();
        
        for(int i = 0; i < buttons.length; i++) {
            add(buttons[i]);
        }
    }
    
    void setButtons() {
        if(buttons.length == 0) {
            return;
        }
        for(int i = 0; i < buttons.length; i++) {
            buttons[i] = new JButton("" + i);
        }
    }
}
