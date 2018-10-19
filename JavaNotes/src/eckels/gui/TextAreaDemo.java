/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Insets;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 *
 * @author default
 */
public class TextAreaDemo extends JPanel{
    
    public static void runTextAreaDemo() {
        JFrame window = new JFrame("Text Area");
        TextAreaDemo content = new TextAreaDemo();
        window.setContentPane(content);
        window.setSize(400, 250);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }

    public TextAreaDemo() {
        String text = "So, naturalists observe, a flea\n"
                    + "Has smaller fleas that on him prey;\n"
                    + "And these have smaller still to bite 'em;\n"
                    + "And so proceed ad infinitum.\n\n"
                    + "                              --Jonathan Swift";
        JTextArea textArea = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(textArea);
        
        textArea.setText(text);
        textArea.setFont(new Font("Serif", Font.PLAIN, 24));
        textArea.setMargin(new Insets(7, 7, 7, 7));
        
        setLayout(new BorderLayout());
        setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
        add(scrollPane, BorderLayout.CENTER);
    }
        
}
