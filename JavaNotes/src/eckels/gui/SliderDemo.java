/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 *
 * @author default
 */
public class SliderDemo extends JPanel implements ChangeListener{
    
    public static void runSliderDemo() {
        JFrame window = new JFrame("Slider Demo");
        SliderDemo content = new SliderDemo();
        window.setContentPane(content);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(350, 200);
        window.setLocation(450, 350);
        window.setVisible(true);
    }

    JSlider slider1, slider2, slider3;  // The sliders.
    JLabel label;                       // A label for reporting changes in the sliders' values.
    
    public SliderDemo() {
        setLayout(new GridLayout(4,1));
        setBorder(BorderFactory.createCompoundBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2), BorderFactory.createEmptyBorder(8,8,8,8)));
        
        label = new JLabel("Try dragging the sliders", JLabel.CENTER);
        add(label);
        
        slider1 = new JSlider(0, 10, 0);
        slider1.addChangeListener(this);
        add(slider1);
        
        slider2 = new JSlider();
        slider2.addChangeListener(this);
        slider2.setMajorTickSpacing(25);
        slider2.setMinorTickSpacing(5);
        slider2.setPaintTicks(true);
        add(slider2);
        
        slider3 = new JSlider(2000, 2100, 2014);
        slider3.addChangeListener(this);
        slider3.setLabelTable(slider3.createStandardLabels(50));
        slider3.setPaintLabels(true);
        add(slider3);
    }   //end constructor

    @Override
    public void stateChanged(ChangeEvent e) {
        if(e.getSource() == slider1) {
            label.setText("Slider One Changed To: " + slider1.getValue());
        }
        else if(e.getSource() == slider2) {
            label.setText("Slider Two Changed To: " + slider2.getValue());
        }
        else if(e.getSource() == slider3) {
            label.setText("Slider Three Changed To: " + slider3.getValue());
        }
    }
               
}
