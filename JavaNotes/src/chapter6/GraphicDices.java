/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import chapter5.PairOfDice;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author default
 */
public class GraphicDices extends JPanel{

    public static void runGraphicDices() {
        JFrame window = new JFrame();
        GraphicDices content = new GraphicDices();
        window.setContentPane(content);
        window.setSize(250, 250);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setVisible(true);
    }
    public GraphicDices() {
        setBackground(Color.LIGHT_GRAY);
        dices = new PairOfDice();
        JButton rollButton = new JButton("Roll");
        rollButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                animatedRoll();
            }
        });
        add(rollButton);
    }
    PairOfDice dices;
    Timer timer;
    
    private void animatedRoll() {
        if(timer != null) {
            return;
        }
        timer = new Timer(100, new ActionListener() {
            int frames = 1; 
            @Override
            public void actionPerformed(ActionEvent e) {
                dices.roll();
                repaint();
                frames++;
                if(frames == 10) {
                    timer.stop();
                    timer = null;
                }
            }
        } );
        timer.start();
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        Graphics2D g2d = (Graphics2D)g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        drawDie(g, dices.getDie1(), 10, 100);
        drawDie(g, dices.getDie2(), 70, 100);
    }
    
    void drawDie(Graphics g, int val, int x, int y) {
        g.setColor(Color.WHITE);
        g.fillRect(x, y, 50, 50);
        g.setColor(Color.BLACK);
        g.drawRect(x, y, 50, 50);
        switch(val) {
            case 1:
                g.fillOval(x + 22, y + 22, 8, 8);
                break;
            case 2:
                g.fillOval(x + 5, y + 5, 8, 8);
                g.fillOval(x + 38, y + 38, 8, 8);
                break;
            case 3:
                g.fillOval(x + 5, y + 5, 8, 8);
                g.fillOval(x + 20, y + 20, 8, 8);
                g.fillOval(x + 38, y + 38, 8, 8);
                break;
            case 4:
                g.fillOval(x + 5, y + 5, 8, 8);
                g.fillOval(x + 40, y + 5, 8, 8);
                g.fillOval(x + 5, y + 40, 8, 8);
                g.fillOval(x + 40, y + 40, 8, 8);
                break;
            case 5:
                g.fillOval(x + 22, y + 22, 8, 8);
                g.fillOval(x + 5, y + 5, 8, 8);
                g.fillOval(x + 40, y + 5, 8, 8);
                g.fillOval(x + 5, y + 40, 8, 8);
                g.fillOval(x + 40, y + 40, 8, 8);
                break;
            case 6:
                g.fillOval(x + 5, y + 5, 8, 8);
                g.fillOval(x + 5, y + 20, 8, 8);
                g.fillOval(x + 5, y + 40, 8, 8);
                g.fillOval(x + 40, y + 5, 8, 8);
                g.fillOval(x + 40, y + 20, 8, 8);
                g.fillOval(x + 40, y + 40, 8, 8);
                break;
        }
    }
}
