/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myGUI;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import javax.swing.AbstractAction;
import javax.swing.ActionMap;
import javax.swing.BorderFactory;
import javax.swing.InputMap;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.KeyStroke;

/**
 *
 * @author default
 */
public class CalculatorV2 extends JPanel implements ActionListener, KeyListener{
    
    public static void runCalc() {
        JFrame window = new JFrame();
        CalculatorV2 content = new CalculatorV2();
        window.setContentPane(content);
        window.pack();
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(true);
        window.setVisible(true);
    }
    
    JTextField m_inputField;
    JLabel totalOperations;
    ArrayList<JButton> m_buttons;
    
    String currResult;
    String prevResult;
    String finalResult;
    String prevOperation;
    StringBuilder label;
    boolean isNegativeNumber;
    
    public CalculatorV2() {
        
        setLayout(null);
        setBackground(Color.LIGHT_GRAY);
        currResult = "";
        prevResult = "";
        finalResult = "";
        prevOperation = "";
        isNegativeNumber = false;
        label = new StringBuilder();
        
        setPreferredSize(new Dimension(320, 340));
        
        totalOperations = new JLabel();
        totalOperations.setFont(new Font(Font.MONOSPACED, Font.ITALIC, 18));
        totalOperations.setBorder(BorderFactory.createEtchedBorder(Color.BLACK, Color.DARK_GRAY));
        add(totalOperations);
        totalOperations.setBounds(5, 5, 310, 25);
        
        m_inputField = new JTextField(10);
        m_inputField.setBorder(BorderFactory.createEtchedBorder(Color.BLACK, Color.DARK_GRAY));
        add(m_inputField);
        m_inputField.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 22));
        m_inputField.setBounds(20, 38, 280, 35);
        
        m_buttons = new ArrayList<JButton>();
        
        setButtons();
        //Set Buttons Position
        int yPos = 130;
        int xPos = 48;
        int count = 0;
        for(int i = 0; i < m_buttons.size(); i++) {
            add(m_buttons.get(i));
            setButtonStyle(m_buttons.get(i));
            m_buttons.get(i).addActionListener(this);
            
            if(i < 11 && count == 3) {
                yPos += 48;
                count = 0;
            }
            m_buttons.get(i).setBounds(20 + count * xPos, yPos, 45, 45);
            if(m_buttons.get(i).getText().equals("0")) {
                m_buttons.get(i).setBounds(20 + count * xPos, yPos, 94, 45);
            }
            if(m_buttons.get(i).getText().equals(".")) {
                m_buttons.get(i).setBounds(20 + count * xPos * 2, yPos, 45, 45);
            }
            if(i == 11) {
                count = 0;
                yPos = 48;
            }
            if(i > 10 && i < 15) {
                 m_buttons.get(i).setBounds(20 + count * xPos, 82, 45, 45);
            }
            if(m_buttons.get(i).getText().equals("+")) {
                m_buttons.get(i).setBounds(20 + count * xPos, 130, 45, 93);
            }
            if(m_buttons.get(i).getText().equals("=")) {
                m_buttons.get(i).setBounds(20 + count * xPos, 226, 45, 93);
            }
            if(i < 14) {
                count++;
            }
            if(i > 16) {
                m_buttons.get(i).setBounds(20 + count * xPos + 55, yPos + 34, 45, 45);
                yPos += 48;
            }
            
        }   //end for for buttons positons setup       
        m_inputField.addKeyListener(this);
        
    }   //end Constructor().
    
    private void setButtons() {
        for(int i = 1; i < 10; i++) {
            m_buttons.add(new JButton("" + i));
            
        }
        m_buttons.add(new JButton("0"));
        m_buttons.add(new JButton("."));
        m_buttons.add(new JButton("%"));
        m_buttons.add(new JButton("/"));
        m_buttons.add(new JButton("*"));
        m_buttons.add(new JButton("-"));
        m_buttons.add(new JButton("+"));
        m_buttons.add(new JButton("="));
        m_buttons.add(new JButton("C"));
        m_buttons.add(new JButton("AC"));
        m_buttons.add(new JButton("("));
        m_buttons.add(new JButton(")"));
        m_buttons.add(new JButton("+/-"));
        setKeyBindings();
    } //end Method setButtons()
    
    private void setKeyBindings() {
        addKeyBinding(m_buttons.get(0), "1", KeyEvent.VK_1);
        addKeyBinding(m_buttons.get(0), "1", KeyEvent.VK_NUMPAD1);
        
        addKeyBinding(m_buttons.get(1), "2", KeyEvent.VK_2);
        addKeyBinding(m_buttons.get(1), "2", KeyEvent.VK_NUMPAD2);
        
        addKeyBinding(m_buttons.get(2), "3", KeyEvent.VK_3);
        addKeyBinding(m_buttons.get(2), "3", KeyEvent.VK_NUMPAD3);
        
        addKeyBinding(m_buttons.get(3), "4", KeyEvent.VK_4);
        addKeyBinding(m_buttons.get(3), "4", KeyEvent.VK_NUMPAD4);
        
        addKeyBinding(m_buttons.get(4), "5", KeyEvent.VK_5);
        addKeyBinding(m_buttons.get(4), "5", KeyEvent.VK_NUMPAD5);
        
        addKeyBinding(m_buttons.get(5), "6", KeyEvent.VK_6);
        addKeyBinding(m_buttons.get(5), "6", KeyEvent.VK_NUMPAD6);
        
        addKeyBinding(m_buttons.get(6), "7", KeyEvent.VK_7);
        addKeyBinding(m_buttons.get(6), "7", KeyEvent.VK_NUMPAD7);
        
        addKeyBinding(m_buttons.get(7), "8", KeyEvent.VK_8);
        addKeyBinding(m_buttons.get(7), "8", KeyEvent.VK_NUMPAD8);
        
        addKeyBinding(m_buttons.get(8), "9", KeyEvent.VK_9);
        addKeyBinding(m_buttons.get(8), "9", KeyEvent.VK_NUMPAD9);
        
        addKeyBinding(m_buttons.get(9), "0", KeyEvent.VK_0);
        addKeyBinding(m_buttons.get(9), "0", KeyEvent.VK_NUMPAD0);
        
        addKeyBinding(m_buttons.get(10), ".", KeyEvent.VK_PERIOD);
//        addKeyBinding(m_buttons.get(11), "%", KeyEvent.VK_);
        addKeyBinding(m_buttons.get(12), "/", KeyEvent.VK_SLASH);
        addKeyBinding(m_buttons.get(12), "/", KeyEvent.VK_DIVIDE);
        addKeyBinding(m_buttons.get(13), "*", KeyEvent.VK_MULTIPLY);
        addKeyBinding(m_buttons.get(14), "-", KeyEvent.VK_MINUS);
        addKeyBinding(m_buttons.get(14), "-", KeyEvent.VK_SUBTRACT);
        addKeyBinding(m_buttons.get(15), "+", KeyEvent.VK_PLUS);
        addKeyBinding(m_buttons.get(15), "+", KeyEvent.VK_ADD);
        addKeyBinding(m_buttons.get(16), "=", KeyEvent.VK_EQUALS);
        addKeyBinding(m_buttons.get(16), "=", KeyEvent.VK_ENTER);
//        addKeyBinding(m_buttons.get(17), "0", KeyEvent.VK_0);
//        addKeyBinding(m_buttons.get(18), "0", KeyEvent.VK_0);
//        addKeyBinding(m_buttons.get(19), "0", KeyEvent.VK_0);
//        addKeyBinding(m_buttons.get(20), "0", KeyEvent.VK_0);
//        addKeyBinding(m_buttons.get(21), "0", KeyEvent.VK_0);
    }
    
    private void setButtonStyle(JButton button) {
        button.setFont(new Font("Serif", Font.BOLD, 14));
        button.setBorder(BorderFactory.createRaisedBevelBorder());
    } //end Method setButtonStyle()

    boolean isPointSet() {
        for(int i = 0; i < currResult.length(); i++) {
            if(currResult.charAt(i) == '.') {
                return true;
            }
        }
        return false;
    }
    
    private void setNumber(String s) {

        switch(s) {
            case "-":
                if(currResult.equals("")) {
                    currResult += "-";
                    isNegativeNumber = true;
                }
            break;
            case "0":
                if(currResult.equals("")) {
                    currResult += "0.";
                }
                else {
                    currResult += "0";
                }
                break;
            case "1":
                isNegativeNumber = false;
                currResult += "1";
                break;
            case "2":
                isNegativeNumber = false;
                currResult += "2";
                break;
            case "3":
                isNegativeNumber = false;
                currResult += "3";
                break;
            case "4":
                isNegativeNumber = false;
                currResult += "4";
                break;
            case "5":
                isNegativeNumber = false;
                currResult += "5";
                break;
            case "6":
                isNegativeNumber = false;
                currResult += "6";
                break;
            case "7":
                isNegativeNumber = false;
                currResult += "7";
                break;
            case "8":
                isNegativeNumber = false;
                currResult += "8";
                break;
            case "9":
                isNegativeNumber = false;
                currResult += "9";
                break;
            case ".":
                isNegativeNumber = false;
                if(currResult.equals("")) {
                    currResult += "0.";
                }
                else {
                    if(!isPointSet()) {
                        currResult += ".";
                    }
                }
                break;
            default:
                break;
        }
        m_inputField.setText(currResult);
    } //end Method setNumber()
    
    private void setOperation(String op) {
        switch(op) {
            case "+":
                proceedOperation(op);
                break;
            case "-":
                proceedOperation(op);
                break;
            case "*":
                proceedOperation(op);
                break;
            case "/":
                proceedOperation(op);
                break;
            case "=":
                if(!prevResult.equals("")) {
                    proceedFinalResult();
                }
                break;
            default:
                break;
        }
        
    }
    
    private void setTypedOperation(char c) {
        switch(c) {
            case '+':
                proceedOperation(String.valueOf('+'));
                break;
            case '-':
                proceedOperation(String.valueOf('-'));
                break;
            case '*':
                proceedOperation(String.valueOf('*'));
                break;
            case '/':
                proceedOperation(String.valueOf('/'));
                break;
            case '=':
                if(!prevResult.equals("")) {
                    proceedFinalResult();
                }
                break;
            default:
                break;
        }
    }
    
    void proceedFinalResult() {
        if(prevOperation.equals("+")) {
            finalResult = "" + doSum();
        }
        else if(prevOperation.equals("-")) {
            finalResult = "" + doSubstraction();
        }
        else if(prevOperation.equals("*")) {
            finalResult = "" + doMultiply();
        }
        else if(prevOperation.equals("/")) {
            finalResult = "" + doDivision();
        }
        setLabel();
        
        totalOperations.setText(label.toString());
        m_inputField.setText(finalResult);
        currResult = "";
        prevResult = "";
    }
    
    void proceedOperation(String s) {
        if(!prevResult.equals("")) {
            if(prevOperation.equals("+")) {
                finalResult = Double.toString(doSum());
                setLabel();
            }
            else if(prevOperation.equals("-")) {
                finalResult = Double.toString(doSubstraction());
                setLabel();
            }
            else if(prevOperation.equals("*")) {
                finalResult = Double.toString(doMultiply());
                setLabel();
            }
            else if(prevOperation.equals("/")) {
                finalResult = Double.toString(doDivision());
                setLabel();
            }
            prevResult = finalResult;
            m_inputField.setText(finalResult);
        }
        else {
            prevResult = currResult;
            currResult = "";
        }
        if(!prevOperation.equals("=")) {
            prevOperation = s;
        }
        currResult = "";
        totalOperations.setText(label.toString());
                
    }
    
    private void setLabel() {
        if(label.length() != 0) {
            label.delete(0, label.length() - 1);
        }
        label.append(prevResult);
        label.append(" ");
        label.append(prevOperation);
        label.append(" ");
        label.append(currResult);
        label.append(" = ");
        label.append(finalResult);
        label.append(" ");
    }
    
    double doSum() {
        return Double.parseDouble(prevResult) + Double.parseDouble(currResult);
    }
    
    double doSubstraction() {
        return Double.parseDouble(prevResult) - Double.parseDouble(currResult);
    }
    
    double doMultiply() {
        return Double.parseDouble(prevResult) * Double.parseDouble(currResult);
    }
    
    double doDivision() {
        double result = 0.0;
        try {
            result = Double.parseDouble(prevResult) / Double.parseDouble(currResult);
        }
        catch(IllegalArgumentException e) {
            return 0;
        }
        return result;
    }
    
    private void setTypedNumber(char c) {

        if(currResult.equals("")) {
            m_inputField.setText("");
        }
        switch(c) {
            case '-':
                if(currResult.equals("")) {
                    currResult += "-";
                    isNegativeNumber = true;
                }
                break;
            case '0':
                if(currResult.equals("")) {
                    currResult += "0.";
                }
                else {
                    currResult += "0";
                }
                isNegativeNumber = false;
                break;
            case '1':
                isNegativeNumber = false;
                currResult += "1";
                break;
            case '2':
                isNegativeNumber = false;
                currResult += "2";
                break;
            case '3':
                isNegativeNumber = false;
                currResult += "3";
                break;
            case '4':
                isNegativeNumber = false;
                currResult += "4";
                break;
            case '5':
                isNegativeNumber = false;
                currResult += "5";
                break;
            case '6':
                isNegativeNumber = false;
                currResult += "6";
                break;
            case '7':
                isNegativeNumber = false;
                currResult += "7";
                break;
            case '8':
                isNegativeNumber = false;
                currResult += "8";
                break;
            case '9':
                isNegativeNumber = false;
                currResult += "9";
                break;
            case '.':
                isNegativeNumber = false;
                if(currResult.equals("")) {
                    m_inputField.setText("0");
                    currResult += "0.";
                }
                else {
                    if(!isPointSet()) {
                        currResult += ".";
                    }
                }
                break;
            default:
                break;
                
        }

    }

    void reset() {
        currResult = "";
        prevResult = "";
        finalResult = "";
        prevOperation = "";
        if(label.length() != 0) {
            label.delete(0, label.length() - 1);
        }
        m_inputField.setText("");
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        
        String command = e.getActionCommand();
        setNumber(command);
        if(command.equals("C") || command.equals("AC")) {
            reset();
        }
        if(!m_inputField.getText().equals("") && !isNegativeNumber) {
            setOperation(command);
        }
        m_inputField.requestFocusInWindow();
    }

    @Override
    public void keyTyped(KeyEvent e) {  
        char c = e.getKeyChar();
        if(!(Character.isDigit(c) || c == KeyEvent.VK_BACK_SPACE || 
                c == KeyEvent.VK_DELETE || c == KeyEvent.VK_PLUS || c == KeyEvent.VK_EQUALS || c == KeyEvent.VK_MINUS
                || c == KeyEvent.VK_MULTIPLY || c == KeyEvent.VK_DIVIDE || c == KeyEvent.VK_SUBTRACT 
                || c == KeyEvent.VK_SLASH || c == KeyEvent.VK_PERIOD) || c == KeyEvent.VK_ENTER) {
            e.consume();
        }
        if(m_inputField.getText().equals("") && !(Character.isDigit(c))) {
            if(c == KeyEvent.VK_MINUS || c == KeyEvent.VK_PERIOD) {
            }
            else {
                e.consume();
                return;
            }
        }
        if(isNegativeNumber && c == KeyEvent.VK_MINUS) {
            e.consume();
        }
        if(isPointSet() && c == KeyEvent.VK_PERIOD) {
            e.consume();
        }
        setTypedNumber(c);
        if(!m_inputField.getText().equals("") && !isNegativeNumber  && !(Character.isDigit(c))) {
            if(c == KeyEvent.VK_ENTER) {
                c = '=';
            }
            setOperation(String.valueOf(c));
            if(isPointSet() && c == KeyEvent.VK_PERIOD) {
            }
            else {
                e.consume();
            }
        }
        
    }

    @Override
    public void keyPressed(KeyEvent e) {
        
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
    
    protected void addKeyBinding(JButton btn, String name, int virtualKey) {
        ActionMap am = getActionMap();
        InputMap im = getInputMap(WHEN_IN_FOCUSED_WINDOW);
        
        im.put(KeyStroke.getKeyStroke(virtualKey, 0, false), name + ".pressed");
        im.put(KeyStroke.getKeyStroke(virtualKey, 0, true), name + ".released");
        
        am.put(name + ".pressed", new KeyAction(btn, true));
        am.put(name + ".released", new KeyAction(btn, false));
    }
    
    private class KeyAction extends AbstractAction {

        private JButton button;
        private boolean highlight;
        
        public KeyAction(JButton btn, boolean highlight) {
            this.button = btn;
            this.highlight = highlight;
        }
               
        @Override
        public void actionPerformed(ActionEvent e) {
            if(highlight) {
                button.getModel().setPressed(true);
            }
            else {
                button.getModel().setPressed(false);
            }
        }
    }
    
}
