/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui.text.shapes;

import java.awt.Color;
import java.awt.Graphics;

/**
 *
 * @author default
 */
// This class represents rectangle shapes.
public class RectShape extends Shape{

    @Override
    void draw(Graphics g) {
        g.setColor(color);
        g.fillRect(left, top, width, height);
        g.setColor(Color.BLACK);
        g.drawRect(left, top, width, height);
    }
    
}
