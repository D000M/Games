/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class SelectableSquares extends JPanel implements ActionListener{

    
    CheckBoard board;
    
    public static void runSelectableSquares() {
        JFrame window = new JFrame();
        SelectableSquares content = new SelectableSquares();
        window.setContentPane(content);
        window.setResizable(false);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(450, 350);
        window.pack();
        window.setVisible(true);
    }

    public SelectableSquares() {
        setLayout(null);
        
        setBackground(new Color(200, 30, 30));
        setBorder(BorderFactory.createEtchedBorder(Color.lightGray, Color.yellow));
        setPreferredSize(new Dimension(640, 480));
        
        board = new CheckBoard();
        add(board);
        
        board.setBounds(20, 20, 164, 164);
    }
           
    @Override
    public void actionPerformed(ActionEvent e) {
    }
    
    private static class CheckBoard extends JPanel {

        int row, col;
        boolean isActiveSquare;
        public CheckBoard() {
            isActiveSquare = false;
            setPreferredSize(new Dimension(164, 164));
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {   
                    super.mousePressed(e); //To change body of generated methods, choose Tools | Templates.
                    int x = e.getX();
                    int y = e.getY();
                    drawMarkedSquare(x / 20, y / 20);
                    row = x / 20;
                    col = y / 20;
                }

                @Override
                public void mouseReleased(MouseEvent e) {
                    super.mouseReleased(e); //To change body of generated methods, choose Tools | Templates.
                }
               
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
            
            g.setColor(Color.BLACK);
            g.drawRect(0, 0, getSize().width - 1, getSize().height - 1);
            g.drawRect(1, 1, getSize().width - 3, getSize().height - 3);
            
            for(int row = 0; row < 8; row++){
                for(int col = 0; col < 8; col++) {
                    if(row % 2 == col % 2) {
                        g.setColor(Color.LIGHT_GRAY);
                    }
                    else {
                        g.setColor(Color.GRAY);
                    }
                    g.fillRect(2 + col * 20, 2 + row * 20, 20, 20);
                    
                }
            }
            if(isActiveSquare) {
                g.setColor(Color.RED);
                g.drawRect(1 + this.row * 20, 1 + col * 20, 20, 20);
            }
        }
        
        void drawMarkedSquare(int row, int col) {
            if(this.row == row && this.col == col && isActiveSquare) {
                isActiveSquare = false;
                repaint();
                return;
            }
            isActiveSquare = true;
            repaint();
        }
                        
    }
    
}
