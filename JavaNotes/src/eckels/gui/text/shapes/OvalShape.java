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
// This class represents oval shapes.
public class OvalShape extends Shape{

    @Override
    void draw(Graphics g) {
        g.setColor(color);
        g.fillOval(left, top, width, height);
        g.setColor(Color.black);
        g.drawOval(left, top, width, height);
    }
    
    @Override
    boolean containsPoint(int x, int y) {
        // Check whether (x,y) is inside this oval, using the
        // mathematical equation of an ellipse.  This replaces the
        // definition of containsPoint that was inherited from the
        // Shape class.
        double radiusX = width / 2.0;    // horizontal radius of ellipse
        double radiusY = height / 2.0;   // vertical radius of ellipse
        double centerX = left + radiusX;      // x-coord of center of ellipse
        double centerY = top + radiusY;       // y-coord of center of ellipse
        if( (radiusX * (x - centerX)) * (radiusY * ( x - centerX)) + (radiusX * (y - centerY)) * ( radiusX * (y - centerY)) <= radiusX * radiusX * radiusY * radiusY ) {
            return true;
        }
        else {
            return false;
        }
    }
}
