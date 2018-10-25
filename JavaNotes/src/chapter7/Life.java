/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chapter7;

import eckels.gui.MosaicPanel;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author default
 */
/**
 * This program is a very simple implementation of John H. Conway's famous "Game of Life".
 * In this game, the user sets up a board that contains a grid of cells, where each cell can be 
 * either "living" or "dead".  Once the board is set up and the game is started, it runs itself.
 * The board goes through a sequence of "generations."  In each generation, every cell can
 * change its state from living to dead or vice versa, depending on the number of neighbors
 * that it has.  The rules are:
 * 
 *     1.  If a cell is dead, and if it has exactly 3 living neighbors, then the cell comes
 *         to life; if the number of neighbors is less than or greater than 3, then the dead 
 *         cell remains dead.  (That is, three living neighbors give birth to a new cell.)
 *         
 *     2.  If a cell is alive, and if it has exactly 2 or 3 living neighbors, then the cell
 *         remains alive; otherwise, it dies.  (If a cell has 0 or 1 neighbors, it dies of
 *         loneliness; if it has 4 or more neighbors, it dies of overcrowding.)
 *         
 * It is important that all these changes happen simultaneously in each generation.  When
 * counting neighbors, the 8 cells that are next to a given cell horizontally, vertically,
 * and diagonally are considered.  Ideally, the board would be infinite.  On a finite board,
 * special consideration must be given to cells that lie along the boundary.  In this program, 
 * the approach is to consider the left edge to be next to the right edge and the top edge
 * to be next to the bottom edge.  This effectively turns the board into a "torus" (the shape
 * of the surface of a doughnut), which is finite but has no boundary.
 * 
 * This class has a main() routine, so it can be run as a stand-alone application.  The main
 * program simply opens a window that shows a Life board with some control buttons along the
 * bottom.  The user creates the initial board by clicking and dragging on the board to create
 * living cells.  Clicking and dragging while holding down the right mouse button will change
 * living cells back to dead.  There is also a button that will set the state of each cell to
 * be a random value.
 */
public class Life extends JPanel implements ActionListener, MouseListener, MouseMotionListener{

    /**
     * Main program opens a window whose content pane is a JPanel belonging to class Life.
     */
    public static void runLife() {
        JFrame window = new JFrame("Life");
        JPanel panel = new Life();
        window.setContentPane(panel);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.pack();
        window.setLocation(450, 350);
        window.setVisible(true);
    }
    
    // Number of squares along each side of the board
    // (Should probably not be less than 10 or more than 200,)
    private final int GRID_SIZE = 100;
    
    // Represents the board.  alive[r][c] is true if the cell in row r, column c is alive.
    private boolean[][] alive;
    
    // Displays the game to the user..  White squares are alive; black squares are dead.
    private MosaicPanel display;
    
    // Drives the game when the user presses the "Start" button.
    private Timer timer;
    
    private JButton stopGoButton;   // Button for starting and stopping the running of the game.
    private JButton nextButton;     // Button for computing just the next generation.
    private JButton randomButton;   // Button for filling the board randomly with each cell having a 25% chance of  being alive.
    private JButton clearButton;    // Button for clearing the board, that is setting all the cells to "dead".
    private JButton quitButton;     // Button for ending the program.

    /**
     * Create a life game board, initially empty.  The number of cells on each side of the grid is GRID_SIZE.
     */
    public Life() {
        alive = new boolean[GRID_SIZE][GRID_SIZE];
        
        setLayout(new BorderLayout(3, 3));
        setBackground(Color.GRAY);
        setBorder(BorderFactory.createLineBorder(Color.GRAY, 3));
        
        int cellSize = 600 / GRID_SIZE;     // Aim for about a 600-by-600 pixel board.
        display = new MosaicPanel(GRID_SIZE, GRID_SIZE, cellSize, cellSize);
        
        if(cellSize < 5) {
            display.setGroutingColor(null);
        }
        display.setUse3D(false);
        
        add(display, BorderLayout.CENTER);
        
        JPanel bottom = new JPanel();
        add(bottom, BorderLayout.SOUTH);
        
        clearButton = new JButton("Clear");
        stopGoButton = new JButton("Start");
        quitButton = new JButton("Quit");
        nextButton = new JButton("One Step");
        randomButton = new JButton("Random Fill");
        bottom.add(stopGoButton);
        bottom.add(nextButton);
        bottom.add(randomButton);
        bottom.add(clearButton);
        bottom.add(quitButton);
        
        clearButton.addActionListener(this);
        stopGoButton.addActionListener(this);
        quitButton.addActionListener(this);
        nextButton.addActionListener(this);
        randomButton.addActionListener(this);
        
        display.addMouseListener(this);
        display.addMouseMotionListener(this);
        timer = new Timer(500, this);
    }
    
    /**
     * Compute the next generation of cells.  The "alive" array is modified to reflect the
     * state of each cell in the new generation.  (Note that this method does not actually
     * draw the new board; it only sets the values in the "alive" array.  The board is
     * redrawn in the showBoard() method.)
     */
    private void doFrame() {
        boolean[][] newboard = new boolean[GRID_SIZE][GRID_SIZE];
        for(int row = 0; row < GRID_SIZE; row++) {
            int above, below;   // rows considered above and below row
            int left, right;    // columns considered left and right of column col
            
            above = row > 0 ? (row - 1) : (GRID_SIZE - 1);
            below = row < GRID_SIZE - 1 ? row + 1 : 0;
            
            for(int col = 0; col < GRID_SIZE; col++) {
                left = col > 0 ? (col - 1) : GRID_SIZE - 1;
                right = col < GRID_SIZE - 1 ? col + 1 : 0;
                
                int n = 0;  // number of alive cells in the 8 neighboring cells
                if(alive[above][left]) {
                    n++;
                }
                if(alive[above][col]) {
                    n++;
                }
                if(alive[above][right]) {
                    n++;
                }
                if(alive[row][left]) {
                    n++;
                }
                if(alive[row][right]) {
                    n++;
                }
                if(alive[below][left]) {
                    n++;
                }
                if(alive[below][col]) {
                    n++;
                }
                if(alive[below][right]) {
                    n++;
                }
                
                newboard[row][col] = n == 3 || (alive[row][col] && n == 2);
            }
        }
        alive = newboard;
    }
    
    /**
     *  Sets the color of every square in the display to show whether the corresponding
     *  cell on the Life board is alive or dead. 
     */
    private void showBoard() {
        display.setAutopaint(false); // For efficiency, prevent redrawing of individual squares.
        for(int r = 0; r < GRID_SIZE; r++) {
            for(int c = 0; c < GRID_SIZE; c++) {
                if(alive[r][c] == true) {
                    display.setColor(r, c, Color.WHITE);
                } 
                else {
                    display.setColor(r, c, null);  // Shows the background color, black.
                }
            }
        }
        display.setAutopaint(true); // Redraw the whole board, and turn on drawing of individual squares.
    }
    
    /**
     * Respond to an ActionEvent from one of the control buttons or from the timer.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();     // The object that caused the event.
        
        if(obj == clearButton) {    // Clear the board.
            alive = new boolean[GRID_SIZE][GRID_SIZE];
            display.clear();
        }
        else if(obj == nextButton) {    // Compute and display the next generation.
            doFrame();
            showBoard();
        }
        else if(obj == stopGoButton) {  // Start or stop the game, depending on whether or not it is currenty running.
            if(timer.isRunning()) { // If the game is currently running, stop it.
                timer.stop();
                clearButton.setEnabled(true);
                randomButton.setEnabled(true);
                nextButton.setEnabled(true);
                stopGoButton.setText("Start");  // Change text of button to "Start", since it can be used to start the game again.
            }
            else {  // If the game is not currently running, start it.
                timer.start();  // This starts the game by turning the timee that will drive the game.
                clearButton.setEnabled(false);
                randomButton.setEnabled(false);
                nextButton.setEnabled(false);
                stopGoButton.setText("Stop");  // Change text of button to "Stop", since it can be used to stop the game.
            }
        }
        else if(obj == randomButton) {  // Fill the board randomly.
            for(int r = 0; r < GRID_SIZE; r++){
                for(int c = 0; c < GRID_SIZE; c++) {
                    alive[r][c] = (Math.random() < 0.25);   // 25% probability that the cell is alive.
                }
                showBoard();
            }
        }
        else if(obj == timer) { // Each time the timer fires, a new frame is computed and displayed.
            doFrame();
            showBoard();
        }
    } 

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    /**
     * The square containing the mouse comes to life or, if the right-mouse button is down, dies.
     */
    @Override
    public void mousePressed(MouseEvent e) {
        if(timer.isRunning()) {
            return;
        }
        int row = display.yCoordToRowNumber(e.getY());
        int col = display.yCoordToRowNumber(e.getX());
        
        if (row >= 0 && row < display.getRowCount() && col >= 0 && col < display.getColumnCount()) {
            if(e.isMetaDown() || e.isControlDown()) {
                display.setColor(row, col, null);
                alive[row][col] = false;
            }
            else {
                display.setColor(row, col, Color.WHITE);
                alive[row][col] = false;
            }
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

    /**
     * The square containing the mouse comes to life or, if the right-mouse button is down, dies.
     */
    @Override
    public void mouseDragged(MouseEvent e) {
        mousePressed(e);
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }
    
}
