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
public class RoundRectShape extends Shape{

    @Override
    void draw(Graphics g) {
        // This class represents rectangle shapes with rounded corners.
        // (Note that it uses the inherited version of the 
        // containsPoint(x,y) method, even though that is not perfectly
        // accurate when (x,y) is near one of the corners.)
        g.setColor(color);
        g.fillRoundRect(left, top, width, height, width / 3, height / 3);
        g.setColor(Color.BLACK);
        g.drawRoundRect(left, top, width, height, width / 3, height / 3);
    }
    
}
