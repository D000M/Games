/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter6;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author default
 */
/**
 * This panel implements a simple arcade game in which the user tries to blow
 * up a "submarine" (a black oval) by dropping "depth charges" (a red disk) from 
 * a "boat" (a blue roundrect).  The user moves the boat with the left- and 
 * right-arrow keys and drops the depth charge with the down-arrow key.
 * The sub moves left and right erratically along the bottom of the panel.
 * This class contains a main() routine to allow it to be run as a program.
 */
public class SubKillerV2 extends JPanel{
    
    public static void runSubKiller() {
        JFrame window = new JFrame("SubKiller");
        SubKillerV2 content = new SubKillerV2();
        window.setContentPane(content);
        window.setSize(600, 480);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setVisible(true);
    }
    
    private Timer timer;    // Timer that drives the animation.
    
    private int width, height;  // The size of the panel -- the values are set
                                //    the first time the paintComponent() method
                                //    is called.  This class is not designed to
                                //    handle changes in size; once the width and
                                //    height have been set, they are not changed.
                                //    Note that width and height cannot be set
                                //    in the constructor because the width and
                                //    height of the panel have not been set at
                                //    the time that the constructor is called.
    
    private Boat boat;          // The boat, bomb, and sub objects are defined
    private Bomb bomb;          //    by nested classes Boat, Bomb, and Submarine,
    private Submarine sub;      //    which are defined later in this class.
                                //    Note that the objects are created in the
                                //    paintComponent() method, after the width
                                //    and height of the panel are known.
    private String gameStats;
    /**
     * The constructor sets the background color of the panel, creates the
     * timer, and adds a KeyListener, FocusListener, and MouseListener to the
     * panel.  These listeners, as well as the ActionListener for the timer
     * are defined by anonymous inner classes.  The timer will run only
     * when the panel has the input focus.
     */
    public SubKillerV2() {
        setBackground(new Color(0, 200, 0));
        
        ActionListener action = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Defines the action taken each time the timer fires.
                if(boat != null) {
                    boat.updateForNewFrame();
                    bomb.updateForNewFrame();
                    sub.updateForNewFrame();
                }
                repaint();
            }
        };  //end of ActionListener
        timer = new Timer(30, action);  // Fires every 30 milliseconds.
        
        addMouseListener(new MouseAdapter() {
            // The mouse listener simply requests focus when the user
            // clicks the panel.
            @Override
            public void mousePressed(MouseEvent e) {
                super.mousePressed(e); //To change body of generated methods, choose Tools | Templates.
                requestFocus();
            }
        } ); //end of addMouseListener()
        
        addFocusListener(new FocusListener() {
            // The focus listener starts the timer when the panel gains
            // the input focus and stops the timer when the panel loses
            // the focus.  It also calls repaint() when these events occur.
            @Override
            public void focusGained(FocusEvent e) {
                timer.start();
                repaint();
            }

            @Override
            public void focusLost(FocusEvent e) {
                timer.stop();
                repaint();
            }
        } ); //end of addFocusListener()
        
        
        addKeyListener(new KeyAdapter() {
            // The key listener responds to keyPressed events on the panel. Only
            // the left-, right-, and down-arrow keys have any effect.  The left- and
            // right-arrow keys move the boat while down-arrow releases the bomb.
            @Override
            public void keyPressed(KeyEvent e) {
                super.keyPressed(e); //To change body of generated methods, choose Tools | Templates.
                int code = e.getKeyCode();
                if(code == KeyEvent.VK_LEFT) {
                    // Move the boat left.  (If this moves the boat out of the frame, its
                    // position will be adjusted in the boat.updateForNewFrame() method.)
                    boat.centerX -= 15; 
                }
                else if(code == KeyEvent.VK_RIGHT) {
                    // Move the boat right.  (If this moves boat out of the frame, its
                    // position will be adjusted in the boat.updateForNewFrame() method.)
                    boat.centerX += 15; 
                }
                else if(code == KeyEvent.VK_DOWN) {
                    if(bomb.isFalling == false){
                        bomb.isFalling = true;
                    }
                }
            }
        } ); //end of addKeyListener
    } //Constructor

    @Override
    protected void paintComponent(Graphics g) {
        // Fill panel with background color, green.
        super.paintComponent(g); //To change body of generated methods, choose Tools | Templates.
        
        Graphics2D g2d = (Graphics2D)g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        if(boat == null) {
            
            // The first time that paintComponent is called, it assigns
            // values to the instance variables.
            width = getWidth();
            height = getHeight();
            boat = new Boat();
            sub = new Submarine();
            bomb = new Bomb();
            
        }
        if(hasFocus()) {
            g.setColor(Color.CYAN);
        }
        else {
            g.setColor(Color.BLACK);
            g.drawString("Click To Activate", 20, 30);
            g.setColor(Color.GRAY);
        }
        g.drawRect(0, 0, width - 1, height - 1);
        g.drawRect(1, 1, width - 3, height - 3);
        g.drawRect(2, 2, width - 5, height - 5);
        
        boat.draw(g);
        sub.draw(g);
        bomb.draw(g);
        if(hasFocus()) {
            g.setFont(new Font("Serif", Font.PLAIN, 18));
            g.setColor(Color.BLUE);
            g.drawString("Total Hits: " + bomb.hits + ", Total Misses: " + bomb.misses, 150, 25);
        }
    }   //end paintComponent()
    
    /**
     * This nested class defines the boat.  Note that its constructor cannot
     * be called until the width of the panel is known!
     */       
    private class Boat {
        int centerX, centerY;   // Current position of the center of the boat.

        public Boat() { // Constructor centers the boat horizontally, 80 pixels from top.
            centerX = width / 2;
            centerY = 80;
        }
        
        void updateForNewFrame() {  // Makes sure boat has not moved off screen.
            if(centerX < 0) {
                centerX = 0;
            }
            else if(centerY > width) {
                centerX = width;
            }
        }
        void draw(Graphics g) { // Draws the boat at its current location.
            g.setColor(Color.BLUE);
            g.fillRoundRect(centerX - 40, centerY - 20, 80, 40, 20, 20);
        }
    } //end nested class Boat
    
    private class Bomb {
        int centerX, centerY;   // Current position of the center of the bomb.
        
        boolean isFalling;      // If true, the bomb is falling; if false, it
                                // is attached to the boat.
        int hits = 0;
        int misses = 0;
        public Bomb() { // Constructor creates a bomb that is initially attached to boat.
            isFalling = false;
        }
        void updateForNewFrame() {  // If bomb is falling, take appropriate action.
            if(isFalling) {
                if(centerY > height) {
                    // Bomb has missed the submarine.  It is returned to its
                    // initial state, with isFalling equal to false.
                    isFalling = false;
                    misses++;
                }
                else if(Math.abs(centerX - sub.centerX) <= 36 && Math.abs(centerY - sub.centerY) <= 21) {
                    // Bomb has hit the submarine.  The submarine
                    // enters the "isExploding" state.
                    sub.isExploding = true;
                    sub.explosionFrameNumber = 1;
                    isFalling = false;
                    hits++;
                }
                else {
                    // If the bomb has not fallen off the panel or hit the
                    // sub, then it is moved down 10 pixels.
                    centerY += 10;
                }
            }
        }
        void draw(Graphics g) { // Draw the bomb.
            if(!isFalling) {    // If not falling, set centerX and centerY
                                // to show the bomb on the bottom of the boat.
                centerX = boat.centerX;
                centerY = boat.centerY;
            }
            g.setColor(Color.RED);
            g.fillOval(centerX - 8, centerY - 8, 16, 16);
        }
    } //end nested class Bomb
    
    /**
     * This nested class defines the sub.  Note that its constructor cannot
     * be called until the width of the panel is known!
     */
    private class Submarine {
        int centerX, centerY;   // Current position of the center of the sub.
        boolean isMovingLeft;   // Tells whether the sub is moving left or right
        boolean isExploding;    // Set to true when the sub is hit by the bomb.
        int explosionFrameNumber;   // If the sub is exploding, this is the number
                                    //   of frames since the explosion started.

        public Submarine() {    // Create the sub at a random location 40 pixels from bottom.
            centerX = (int)(Math.random() * width);
            centerY = height - 40;
            isExploding = false;
            isMovingLeft = (Math.random() < 0.5);
        } //end constructor
                
        void updateForNewFrame() {  // Move sub or increase explosionFrameNumber.
            if(isExploding) {
                // If the sub is exploding, add 1 to explosionFrameNumber.
                // When the number reaches 15, the explosion ends and the
                // sub reappears in a random position.
                explosionFrameNumber++;
                if(explosionFrameNumber == 15) {
                    centerX = (int)(Math.random() * width);
                    centerY = height - 40;
                    isExploding = false;
                    isMovingLeft = (Math.random() < 0.5);
                }
                    
            }
            else {  // Move the sub.
                if(Math.random() < 0.04) {
                    // In one frame out of every 25, on average, the sub
                    // reverses its direction of motion.
                    isMovingLeft = !isMovingLeft;
                }
                if(isMovingLeft) {
                    // Move the sub 5 pixels to the left.  If it moves off
                    // the left edge of the panel, move it back to the left
                    // edge and start it moving to the right.
                    centerX -= 5;
                    if(centerX == 0) {
                        centerX = 0;
                        isMovingLeft = false;
                    }
                }
                else {
                    // Move the sub 5 pixels to the right.  If it moves off
                    // the right edge of the panel, move it back to the right
                    // edge and start it moving to the left.
                    centerX += 5;
                    if(centerX > width) {
                        centerX = width;
                        isMovingLeft = true;
                    }
                }
            }
        }   //end updateForNewFrame()
        
        void draw(Graphics g) { // Draw sub and, if it is exploding, the explosion.
            g.setColor(Color.BLACK);
            g.fillOval(centerX - 30, centerY - 15, 60, 30);
            if(isExploding) {
                // Draw an "explosion" that grows in size as the number of
                // frames since the start of the explosion increases.
                g.setColor(Color.YELLOW);
                g.fillOval(centerX - 4 * explosionFrameNumber, centerY - 2 * explosionFrameNumber,
                        8 * explosionFrameNumber, 4 * explosionFrameNumber);
                g.setColor(Color.RED);
                g.fillOval(centerX - 2 * explosionFrameNumber, centerY - explosionFrameNumber / 2,
                        4 * explosionFrameNumber, explosionFrameNumber);
            }
        }
    } //end nested class Submarine
    
}   //end class SubKiller
