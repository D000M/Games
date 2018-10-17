/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui.text.shapes;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
/**
 * A very simple drawing program that lets the user add shapes to a drawing area
 * and drag them around. An abstract Shape class is used to represent shapes in
 * general, with subclasses to represent particular kinds of shape. (These are
 * implemented as nested classes inside the main class.) This program is an
 * illustration of class hierarchy, inheritance, polymorphism, and abstract
 * classes. (Note that this program will fail if you add more than 500 shapes,
 * since it uses an array of length 500 to store the shapes.)
 */
public class ShapeDraw extends JPanel {

    /**
     * A main routine that allows this class to be run as an application. It
     * simply opens a window displaying a ShapeDraw panel.
     */
    public static void runShapeDraw() {
        JFrame window = new JFrame("Window Title");
        window.setContentPane(new ShapeDraw());
        window.setSize(500, 400);

        window.setLocation(150, 100);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);

    }

    /**
     * Set up the GUI, with a drawing area plus a row of controls below the
     * drawing area. The controls include three buttons which are used to add
     * shapes to the drawing area and a menu that is used to select the color of
     * the shape when it is created. The constructor also sets up listeners to
     * handle events from the controls.
     */
    public ShapeDraw() {
        setBackground(Color.LIGHT_GRAY);

        DrawingArea canvas = new DrawingArea(); //create the canvas

        colorChoice = new JComboBox<String>();
        colorChoice.addItem("Red");
        colorChoice.addItem("Green");
        colorChoice.addItem("Blue");
        colorChoice.addItem("Cyan");
        colorChoice.addItem("Magenta");
        colorChoice.addItem("Yellow");
        colorChoice.addItem("Black");
        colorChoice.addItem("White");
        colorChoice.addActionListener(canvas);

        JButton rectButton = new JButton("Rect");   // buttons for adding shapes
        rectButton.addActionListener(canvas);

        JButton ovalButton = new JButton("Oval");
        ovalButton.addActionListener(canvas);

        JButton roundRectButton = new JButton("RoundRect");
        roundRectButton.addActionListener(canvas);

        JPanel bottom = new JPanel();   // a Panel to hold the control buttons
        bottom.setLayout(new GridLayout(1, 4, 3, 3));
        bottom.add(rectButton);
        bottom.add(ovalButton);
        bottom.add(roundRectButton);
        bottom.add(colorChoice);

        setLayout(new BorderLayout(3, 3));
        add(canvas, BorderLayout.CENTER);   // add canvas and controls to the panel
        add(bottom, BorderLayout.SOUTH);

    }

    public JComboBox<String> colorChoice;    // The color selection menu

    // This class represents a "canvas" that can display colored shapes and
// let the user drag them around.  It uses an off-screen images to 
// make the dragging look as smooth as possible.
    public class DrawingArea extends JPanel implements ActionListener, MouseListener, MouseMotionListener {

        Shape[] shapes = new Shape[500];    // holds a list of up to 500 shapes
        int shapeCount = 0;                 // the actual number of shapes
        Color currentColor = Color.RED;     // current color; when a shape is created, this is its color

        public DrawingArea() {
            // Constructor: set background color to white set up listeners to respond to mouse actions
            setBackground(Color.WHITE);
            addMouseListener(this);
            addMouseMotionListener(this);
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
            // In the paint method, all the shapes in ArrayList are
            // copied onto the canvas.
            g.setColor(Color.WHITE);
            g.fillRect(0, 0, getSize().width, getSize().height);
            for (int i = 0; i < shapeCount; i++) {
                Shape s = shapes[i];
                s.draw(g);
            }
            g.setColor(Color.BLACK);  // draw a black border around the edge of the drawing area
            g.drawRect(0, 0, getWidth() - 1, getHeight() - 1);
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            // Called to respond to action events.  The three shape-adding
            // buttons have been set up to send action events to this canvas.
            // Respond by adding the appropriate shape to the canvas.
            if (e.getSource() == colorChoice) {
                switch(colorChoice.getSelectedIndex()) {
                    case 0: currentColor = Color.RED; break;
                    case 1: currentColor = Color.GREEN; break;
                    case 2: currentColor = Color.BLUE; break;
                    case 3: currentColor = Color.CYAN; break;
                    case 4: currentColor = Color.MAGENTA; break;
                    case 5: currentColor = Color.YELLOW; break;
                    case 6: currentColor = Color.BLACK; break;
                    case 7: currentColor = Color.WHITE; break;
                }
            }
            else {
                String command = e.getActionCommand();
                if(command.equals("Rect")) {
                    addShape(new RectShape());
                }
                else if(command.equals("Oval")) {
                    addShape(new OvalShape());
                }
                else if(command.equals("RoundRect")) {
                    addShape(new RoundRectShape());
                }
            }
        } //end of actionPerformed method
        
        void addShape(Shape shape) {
            // Add the shape to the canvas, and set its size/position and color.
            // The shape is added at the top-left corner, with size 80-by-50.
            // Then redraw the canvas to show the newly added shape.
            shape.setColor(currentColor);
            shape.reshape(3, 3, 80, 50);
            shapes[shapeCount] = shape;
            shapeCount++;
            repaint();
        }

        // -------------------- This rest of this class implements dragging ----------------------
        Shape shapeBeingDragged = null;  // This is null unless a shape is being dragged.
                                    // A non-null value is used as a signal that dragging
                                    // is in progress, as well as indicating which shape
                                    // is being dragged.
        
        int prevDragX;          // During dragging, these record the x and y coordinates of the
        int prevDragY;          //    previous position of the mouse.
        
        @Override
        public void mouseClicked(MouseEvent e) {
        }

        @Override
        public void mousePressed(MouseEvent e) {
            // User has pressed the mouse.  Find the shape that the user has clicked on, if
            // any.  If there is a shape at the position when the mouse was clicked, then
            // start dragging it.  If the user was holding down the shift key, then bring
            // the dragged shape to the front, in front of all the other shapes.
            int x = e.getX();   // x-coordinate of point where mouse was clicked
            int y = e.getY();   // y-coordinate of point
            
            for(int i = shapeCount - 1; i >= 0; i--) {  // check shapes from front to back
                Shape s = shapes[i];
                if(s.containsPoint(x, y)) {
                    shapeBeingDragged = s;
                    prevDragX = x;
                    prevDragY = y;
                    if(e.isShiftDown()) {   // s should be moved on top of all the other shapes
                        for(int j = i; j < shapeCount; j++) {
                            shapes[j] = shapes[j + 1];  // move the shapes following s down in the list
                        }
                        shapes[shapeCount - 1] = s;     // put s at the end of the list
                        repaint();  // repaint canvas to show s in front of other shapes
                    }
                    return;
                }
            }
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            // User has released the mouse.  Move the dragged shape, then set
            // shapeBeingDragged to null to indicate that dragging is over.
            int x = e.getX();
            int y = e.getY();
            if(shapeBeingDragged != null) {
                shapeBeingDragged.moveBy(x - prevDragX, y - prevDragY);
                shapeBeingDragged = null;
                repaint();
            }
        }

        @Override
        public void mouseEntered(MouseEvent e) {
        }

        @Override
        public void mouseExited(MouseEvent e) {
        }

        @Override
        public void mouseDragged(MouseEvent e) {
             // User has moved the mouse.  Move the dragged shape by the same amount.
             int x = e.getX();
             int y = e.getY();
             if(shapeBeingDragged != null) {
                 shapeBeingDragged.moveBy(x - prevDragX, y - prevDragY);
                 prevDragX = x;
                 prevDragY = y;
                 repaint();
             }
        }

        @Override
        public void mouseMoved(MouseEvent e) {
        }

    }   //end of class DrawingArea

}
