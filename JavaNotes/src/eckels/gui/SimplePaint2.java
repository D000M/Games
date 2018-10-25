/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eckels.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Menu;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import javax.swing.BorderFactory;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

/**
 *
 * @author default
 */
/**
 * A SimplePaint2 panel is a drawing surface on which the user can
 * sketch curves.  The class has a createMenuBar() method that can
 * be used to get a menu bar containing drawing commands and options.
 * It has a main() routine that enables the class to be run as a
 * standalone application; the program just opens a window that 
 * shows a SimplePaint2 panel and its menu bar.
 * 
 * The real point of this example is to demonstrate ArrayList.
 */
public class SimplePaint2 extends JPanel{
    
    public static void runPaint() {
        JFrame window = new JFrame("Paint");
        SimplePaint2 content = new SimplePaint2();
        window.setContentPane(content);
        window.setJMenuBar(content.createMenuBar());
        window.pack();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocation(450, 350);
        window.setResizable(false);
        window.setVisible(true);
    }
    
    /**
     * An object of type CurveData represents the data required to redraw one
     * of the curves that have been sketched by the user.
     */
    private static class CurveData {
        Color color;                // The color of the curve.
        boolean symmetric;           // Are horizontal and vertical reflections also drawn?
        ArrayList<Point> points;    // The points on the curve.
    }
    
    // A list of all curves in the picture.
    private ArrayList<CurveData> curves;
    
    // When a curve is created, its color is taken
    // from this variable.  The value is changed
    // using commands in the "Color" menu.
    private Color currentColor;
    
    // When a curve is created, its "symmetric"
    // property is copied from this variable.  Its
    // value is set by the "Use Symmetry" command in
    // the "Control" menu.
    private boolean useSymmetry;

     /**
     * Constructor.  Sets background color to white, adds a gray border, sets up
     * a listener for mouse and mouse motion events, and sets the preferred size
     * of the panel to be 500-by-500.
     */
    public SimplePaint2() {
        curves = new ArrayList<>();
        setBackground(Color.WHITE);
        setBorder(BorderFactory.createLineBorder(Color.GRAY, 2));
        MouseHandler listener = new MouseHandler();
        addMouseListener(listener);
        addMouseMotionListener(listener);
        setPreferredSize(new Dimension(500, 500));
    }
    
    /**
    * This class defines the object that is used as a mouse listener and mouse
    * motion listener on this panel.  When the user presses the mouse, a new
    * CurveData object is created and is added to the ArrayList, curves. The
    * color of the curve is copied from currentColor, and the symmetric property
    * of the curve is copied from useSymmetry.  As the user drags the mouse, points
    * are added to the curve.  If the user doesn't move the mouse, there will only
    * be one point in the list of points; since this is not really a curve, the
    * CurveData object is removed in this case from the curves list.  This is
    * done in the mouseReleased method.
    */
    private class MouseHandler implements MouseListener, MouseMotionListener {
        CurveData currentCurve;
        boolean dragging;
        @Override
        public void mouseClicked(MouseEvent e) {
        }

        @Override
        public void mousePressed(MouseEvent e) {
            if(dragging) {
                return;
            }
            dragging = true;
            currentCurve = new CurveData();
            currentCurve.color = currentColor;
            currentCurve.symmetric = useSymmetry;
            currentCurve.points = new ArrayList<Point>();
            currentCurve.points.add(new Point(e.getX(), e.getY()));
            curves.add(currentCurve);
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            if(!dragging) {
                return;
            }
            dragging = false;
            if(currentCurve.points.size() < 2) {
                curves.remove(currentCurve);
            }
            currentCurve = null;
        }

        @Override
        public void mouseEntered(MouseEvent e) {
        }

        @Override
        public void mouseExited(MouseEvent e) {
        }

        @Override
        public void mouseDragged(MouseEvent e) {
            if(!dragging) {
                return;
            }
            currentCurve.points.add(new Point(e.getX(), e.getY()));
            repaint();
        }

        @Override
        public void mouseMoved(MouseEvent e) {
        }
        
    }

    /**
     * Fills the panel with the current background color and draws all the
     * curves that have been sketched by the user.  (Antialiasing is
     * turned on to make the lines look nicer.)
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        Graphics2D g2d = (Graphics2D)g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        for(CurveData curve : curves) {
            g.setColor(curve.color);
            for(int i = 1; i < curve.points.size(); i++) {
                // Draw a line segment from point number i-1 to point number i.
                int x1 = curve.points.get(i - 1).x;
                int y1 = curve.points.get(i - 1).y;
                int x2 = curve.points.get(i).x;
                int y2 = curve.points.get(i).y;
                g.drawLine(x1, y1, x2, y2);
                if(curve.symmetric) {
                    // Also draw the horizontal and vertical reflections
                    // of the line segment.
                    int w = getWidth();
                    int h = getHeight();
                    g.drawLine(w - x1, y1, w - x2, y2);
                    g.drawLine(x1, h - y1, x2, h - y2);
                    g.drawLine(w - x1, h - y1, w - x2, h - y2);
                }
            }
        }
    }
       
    /**
     * Creates a menu bar for use with this panel.  It contains
     * three menus: "Control", "Color", and "BackgroundColor".
     */
    private JMenuBar createMenuBar() {
        /* Create the menu bar object */
        JMenuBar menuBar = new JMenuBar();
        
        /* Create the menus and add them to the menu bar. */
        menuBar.add(controlMenuSetUp());
        menuBar.add(colorMenu());
        menuBar.add(bgColorMenu());

        return menuBar;
    }
    
    /* Add commands to the "Control" menu.  It contains an Undo
    * command that will remove the most recently drawn curve
    * from the list of curves; a "Clear" command that removes
    * all the curves that have been drawn; and a "Use Symmetry"
    * checkbox that determines whether symmetry should be used.
    */
    private JMenu controlMenuSetUp() {
        JMenu controlMenu = new JMenu("Control");
        JMenuItem undo = new JMenuItem("Undo");
        controlMenu.add(undo);
        undo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(curves.size() > 0) {
                    curves.remove(curves.size() - 1);
                    repaint();
                }
            }
        });
        
        JMenuItem clear = new JMenuItem("Clear");
        controlMenu.add(clear);
        clear.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                curves = new ArrayList<CurveData>();
                repaint();
            }
        });
        
        JCheckBoxMenuItem sym = new JCheckBoxMenuItem("Use Symmetry");
        controlMenu.add(sym);
        sym.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                useSymmetry = ((JCheckBoxMenuItem)e.getSource()).isSelected();
                // This does not affect the current drawing; it affects
                // curves that are drawn in the future.
            }
        });
        
        return controlMenu;
    }   //end controlMenuSetUp();
    
    /* Add commands to the "Color" menu.  The menu contains commands for
    * setting the current drawing color.  When the user chooses one of these
    * commands, it has no immediate effect on the drawing.  It justs sets
    * the color that will be used for future drawing.
    */
    private JMenu colorMenu() {
        JMenu colorMenu = new JMenu("Color");
        colorMenu.add(makeColorMenuItem("Black", Color.BLACK));
        colorMenu.add(makeColorMenuItem("White", Color.WHITE));
        colorMenu.add(makeColorMenuItem("Red", Color.RED));
        colorMenu.add(makeColorMenuItem("Green", Color.GREEN));
        colorMenu.add(makeColorMenuItem("Blue", Color.BLUE));
        colorMenu.add(makeColorMenuItem("Cyan", Color.CYAN));
        colorMenu.add(makeColorMenuItem("Magenta", Color.MAGENTA));
        colorMenu.add(makeColorMenuItem("Yellow", Color.YELLOW));
        
        JMenuItem customColor = new JMenuItem("Custom...");
        colorMenu.add(customColor);
        customColor.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color c = JColorChooser.showDialog(SimplePaint2.this, "Select Drawing Color", currentColor);
                if(c != null) {
                    currentColor = c;
                }
            }
        });
        
        return colorMenu;
    }
    
    private JMenu bgColorMenu() {
        JMenu bgColorMenu = new JMenu("BackgroundColor");
        bgColorMenu.add(makeBgColorMenuItem("Black", Color.BLACK));
        bgColorMenu.add(makeBgColorMenuItem("White", Color.WHITE));
        bgColorMenu.add(makeBgColorMenuItem("Red", Color.RED));
        bgColorMenu.add(makeBgColorMenuItem("Green", Color.GREEN));
        bgColorMenu.add(makeBgColorMenuItem("Blue", Color.BLUE));
        bgColorMenu.add(makeBgColorMenuItem("Cyan", Color.CYAN));
        bgColorMenu.add(makeBgColorMenuItem("Magenta", Color.MAGENTA));
        bgColorMenu.add(makeBgColorMenuItem("Yellow", Color.YELLOW));
        
        JMenuItem customColor = new JMenuItem("Custom...");
        bgColorMenu.add(customColor);
        
        customColor.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color c = JColorChooser.showDialog(SimplePaint2.this, "Select Background Color", currentColor);
                if(c != null) {
                    setBackground(c);
                }
            }
        });
        
        return bgColorMenu;
    }
    
    /**
     * This utility method is used to create a JMenuItem that sets the
     * current drawing color.
     * @param command  the text that will appear in the menu
     * @param color  the drawing color that is selected by this command.  (Note that
     *    this parameter is "final" for a technical reason: This is a requirement for
     *    a local variable that is used in an anonymous inner class.)
     * @return  the JMenuItem that has been created.
     */
    private JMenuItem makeBgColorMenuItem(String command, final Color color) {
        JMenuItem item = new JMenuItem(command);
        item.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setBackground(color);
            }
        });
        return item;
    }
    
    /**
     * This utility method is used to create a JMenuItem that sets the
     * background color of the panel.
     * @param command  the text that will appear in the menu
     * @param color  the background color that is selected by this command.
     * @return  the JMenuItem that has been created.
     */
    private JMenuItem makeColorMenuItem(String command, final Color color) {
        JMenuItem item = new JMenuItem(command);
        item.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                currentColor = color;
            }
        });
        return item;
    }
}
