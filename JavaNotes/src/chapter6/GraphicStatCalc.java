/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import chapter5.StatCalc;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author default
 */
public class GraphicStatCalc extends JPanel {
    
    JLabel lEntries, lSum, lAverage, lStdDeviation;
    
    JLabel message;
    
    JTextField inputField;
    
    public static void runGraphicStatCalc() {
        JFrame window = new JFrame();
        GraphicStatCalc content = new GraphicStatCalc();
        window.setContentPane(content);
        window.setLocation(450, 350);
        window.pack();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }
    StatCalc calc;
    
    public GraphicStatCalc() {
        
        calc = new StatCalc();
        
        setLayout(null);
        setBackground(new Color(155, 185, 205));
        setPreferredSize(new Dimension(320, 220));
        
        message = new JLabel("Enter a number, press enter");
        add(message);
        inputField = new JTextField();
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(1, 3, 3, 3));
        buttonPanel.setBorder(BorderFactory.createEmptyBorder(3, 3, 3, 3));
        buttonPanel.add(inputField);
        
        JButton enterButt = new JButton("Enter");
        enterButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                double num;
                try {
                    num = Double.parseDouble(inputField.getText());
                }
                catch(NumberFormatException exs) {
                    message.setText("\"" + inputField.getText() + "\" is not a legal number. " );
                    inputField.selectAll();
                    inputField.requestFocus();
                    return;
                }
                calc.enter(num);
                lEntries.setText("Number of Entries:     " + calc.getCount());
                lSum.setText("Sum:                             " + calc.getSum());
                lAverage.setText("Average:                     " + calc.getMean());
                lStdDeviation.setText("Standard Deviation: " + calc.getStandardDeviation());
                message.setText("Enter a number, press enter");
                inputField.selectAll();
                inputField.requestFocus();
            }
        });
        buttonPanel.add(enterButt);
        
        JButton clearButt = new JButton("Clear");
        clearButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                calc = new StatCalc();
                lEntries.setText("Number of Entries:    0 ");
                lSum.setText("Sum:                            0.0 ");
                lAverage.setText("Average:                     Undefined ");
                lStdDeviation.setText("Standard Deviation: Undefined");
                message.setText("Enter a number, press enter");
                inputField.selectAll();
                inputField.requestFocus();
            }
        });
        buttonPanel.add(clearButt);
        add(buttonPanel);
        
        lEntries = new JLabel("Number of Entries:    0 ");
        lSum = new JLabel("Sum:                            0.0 ");
        lAverage = new JLabel("Average:                     Undefined ");
        lStdDeviation = new JLabel("Standard Deviation: Undefined");
        add(lEntries);
        add(lSum);
        add(lAverage);
        add(lStdDeviation);
        message.setBounds(60, 10, 320, 25);
        buttonPanel.setBounds(0, 40, 320, 25);
        lEntries.setBounds(10, 70, 320, 25);
        lSum.setBounds(10, 100, 320, 25);
        lAverage.setBounds(10, 130, 320, 25);
        lStdDeviation.setBounds(10, 160, 320, 25);
    }    
}
