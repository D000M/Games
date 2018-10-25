/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.Border;

/**
 *
 * @author default
 */
public final class TextInfo extends JPanel{
    
    public static void runTextInfo() {
        JFrame window = new JFrame("Text Info");
        TextInfo content = new TextInfo();
        window.setContentPane(content);
        window.setSize(360, 500);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }

    JTextArea textArea;
    JButton procButton;
    JLabel linesLbl, wordsLbl, charsLbl;
    
    public TextInfo() {
        
        setBackground(Color.DARK_GRAY);
        
        textArea = new JTextArea();
        textArea.setBackground(Color.WHITE);
        
        JPanel southPanel = new JPanel();
        southPanel.setBackground(Color.DARK_GRAY);
        southPanel.setLayout(new GridLayout(4, 1, 2, 2));
        
        procButton = new JButton("Process the Text");
        procButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                proccessLogic();
            }
        });
        southPanel.add(procButton);     
        linesLbl = new JLabel("Number of lines: ");
        setLabelColors(linesLbl, Color.BLUE, Color.WHITE, true);
        southPanel.add(linesLbl);
        
        wordsLbl = new JLabel("Number of words: ");
        setLabelColors(wordsLbl, Color.BLUE, Color.WHITE, true);
        southPanel.add(wordsLbl);
        
        charsLbl = new JLabel("Number of chars: ");
        setLabelColors(charsLbl, Color.BLUE, Color.WHITE, true);
        southPanel.add(charsLbl);
        
        setLayout(new BorderLayout(2, 2));
        setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));
        
                
        JScrollPane scrollPanel = new JScrollPane(textArea);
        add(scrollPanel, BorderLayout.CENTER);
        add(southPanel, BorderLayout.SOUTH);
    }
    
    void setLabelColors(JLabel label, Color foreGround, Color backGround, boolean isOpagque) {
        label.setForeground(foreGround);
        label.setBackground(backGround);
        label.setOpaque(isOpagque);
    }
    
    void proccessLogic() {
        if(textArea.getText().equals("") || textArea == null) {
            return;
        }
        int lines = 1;
        int words = 0;
        String text = textArea.getText();
        text = text.trim();
        
        for(int i = 0; i < text.length(); i++) {
            if(text.charAt(i) == '\n') {
                lines++;
            }
            if(i == 0 || text.charAt(i) == ' ') {
                words++;
            }
        }
        linesLbl.setText("Number of lines: " + lines);
        wordsLbl.setText("Number of words: " + words);
        charsLbl.setText("Number of chars: " + text.length());
    }
}
