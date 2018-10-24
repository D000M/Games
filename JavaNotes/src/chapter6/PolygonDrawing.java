/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
public class PolygonDrawing extends JPanel implements MouseListener{

    public static void runPolygonDrawing() {
        JFrame window = new JFrame("Polygon Drawing");
        PolygonDrawing content = new PolygonDrawing();
        window.setContentPane(content);
        window.setLocation(450, 350);
        window.setSize(640, 480);
        window.setResizable(false);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);
    }
    
    int pointCount;
    int xCoords[];
    int yCoords[];
    boolean isPolygon;
    JLabel message;
    
    public PolygonDrawing() {
        
        setBackground(Color.WHITE);
        
        message = new JLabel("Click on the screen to draw polygon max 20 clicks allowed.");
        isPolygon = false;
        add(message);
        
        JButton drawButton = new JButton("Draw");
        drawButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                isPolygon = true;
                repaint();
            }
        });
        add(drawButton);
        
        JButton clearButton = new JButton("Clear");
        clearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                for(int i = 0; i < 20; i++) {
                    xCoords[i] = -1;
                    yCoords[i] = -1;
                }
                pointCount = 0;
                repaint();
            }
        });
        add(clearButton);
        
        pointCount = 0;
        xCoords = new int[20];
        yCoords = new int[20];
        for(int i = 0; i < 20; i++) {
            xCoords[i] = -1;
            yCoords[i] = -1;
        }
        addMouseListener(this);
        
    }
       
    @Override
    public void mouseClicked(MouseEvent e) {
        
        
        
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if(pointCount < 20) {
            if(isPolygon) {
                for(int i = 0; i < 20; i++) {
                    xCoords[i] = -1;
                    yCoords[i] = -1;
                }
                pointCount = 0;
                isPolygon = false;
            }
            xCoords[pointCount] = e.getX();
            yCoords[pointCount] = e.getY();
            pointCount++;
            repaint();
        }
        else {
            message.setText("Maximum number of point reached! Press Draw or Clear");
        }
        
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        if(pointCount == 0) {
            return;
        }
        Graphics2D g2d = (Graphics2D)g;
        g2d.setStroke(new BasicStroke(2));
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        if(pointCount == 1) {
            g.drawRect(xCoords[0], yCoords[0], 2, 2);
        }
        else if(isPolygon) {
            g.setColor(Color.RED);
            g.fillPolygon(xCoords, yCoords, pointCount);
            g.setColor(Color.BLACK);
            g.drawPolygon(xCoords, yCoords, pointCount);
        }
        else {
            for(int i = 0; i < pointCount - 1; i++ ) {
                g.setColor(Color.BLACK);
                g.drawLine(xCoords[i], yCoords[i], xCoords[i + 1], yCoords[i + 1]);
            }
        }
            
    }
        
}
