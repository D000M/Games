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
public abstract class Shape {
    // A class representing shapes that can be displayed on a ShapeCanvas.
    // The subclasses of this class represent particular types of shapes.
    // When a shape is first constructed, it has height and width zero
    // and a default color of white.
    
    int left, top;  // Position of top left corner of rectangle that bounds this shape.
    int width, height;  // Size of the bounding rectangle.
    Color color = Color.WHITE;  // Color of this shape.
    
    void reshape(int left, int top, int width, int height) {
        // Set the position and size of this shape.
        this.left = left;
        this.top = top;
        this.width = width;
        this.height = height;
    }
    
    void moveBy(int dx, int dy) {
        // Move the shape by dx pixels horizontally and dy pixels vertically
        // (by changing the position of the top-left corner of the shape).
        left += dx;
        top += dy;
    }
    
    void setColor(Color color) {
        // Set the color of this shape
        this.color = color;
    }
    
    boolean containsPoint(int x, int y) {
        // Check whether the shape contains the point (x,y).
        // By default, this just checks whether (x,y) is inside the
        // rectangle that bounds the shape.  This method should be
        // overridden by a subclass if the default behavior is not
        // appropriate for the subclass.
        if((x >= left && x < left + width) && (y >= top && y < height + top)) {
            return true;
        }
        else {
            return false;
        }
    }
    // Draw the shape in the graphics context g.
    // This must be overriden in any concrete subclass.
    abstract void draw(Graphics g);
}
