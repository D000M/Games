/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package myGUI;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author default
 */
public class Calculator extends JPanel implements ActionListener{
    
    public static void runCalculator() {
        JFrame window = new JFrame();
        Calculator content = new Calculator();
        window.setContentPane(content);
        window.setSize(330, 390);
        window.setLocation(450, 350);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setVisible(true);
    }
    
    JButton[] buttons;
    JTextField inputField;
    double firstNum;
    double secondNum;
    boolean isFirstNum;
    char operation;
    String result;
    boolean isOperationOn;
    public Calculator() {
        
        setLayout(null);
        inputField = new JTextField();
        add(inputField);
        firstNum = 0;
        secondNum = 0;
        isFirstNum = true;
        result = "";
        isOperationOn = false;
        JPanel buttonPanel = new JPanel();
        buttons = new JButton[15];
        
        buttonPanel.setLayout(new GridLayout(3, 4, 5, 5));
        add(buttonPanel);
        setButtons();
        for(int i = 0; i < buttons.length; i++) {
            buttons[i].addActionListener(this);
            buttonPanel.add(buttons[i]);
        }
        
        inputField.setBounds(20, 30, 280, 30);
        buttonPanel.setBounds(5, 80, 310, 260);
        
    }
    
    void setButtons() {
        if(buttons.length == 0) {
            return;
        }
        for(int i = 0; i < 10; i++) {
            if(i < 10) {
                buttons[i] = new JButton("" + i);
            }
        }
        buttons[10] = new JButton("+");
        buttons[11] = new JButton("-");
        buttons[12] = new JButton("*");
        buttons[13] = new JButton("/");
        buttons[14] = new JButton("=");
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        boolean processResult = false;
        switch(command) {
            case "0": result += "0";
                isOperationOn = false;
                break;
            case "1": result += "1"; 
                isOperationOn = false;
                break;
            case "2": result += "2";
                isOperationOn = false;
                break;
            case "3": result += "3";
                isOperationOn = false;
                break;
            case "4": result += "4";
                isOperationOn = false;
                break;
            case "5": result += "5";
                isOperationOn = false;
                break;
            case "6": result += "6";
                isOperationOn = false;
                break;
            case "7": result += "7";
                isOperationOn = false;
                break;
            case "8": result += "8";
                isOperationOn = false;
                break;
            case "9": result += "9";
                isOperationOn = false;
                break;
            case "+": operation = '+';
                setNumbers();
                isFirstNum = !isFirstNum;
                result = "";
                if(firstNum != 0 && secondNum != 0) {
                    processResult();
                }
                isOperationOn = true;
                break;
            case "-": operation = '-';
                setNumbers();
                isFirstNum = !isFirstNum;
                result = "";
                if(firstNum != 0 && secondNum != 0) {
                    processResult();
                }
                isOperationOn = true;
                break;
            case "*": operation = '*';
                setNumbers();
                isFirstNum = !isFirstNum;
                result = "";
                if(firstNum != 0 && secondNum != 0) {
                    processResult();
                }
                isOperationOn = true;
                break;
            case "/": operation = '/';
                setNumbers();
                isFirstNum = !isFirstNum;
                result = "";
                if(firstNum != 0 && secondNum != 0) {
                    processResult();
                }
                isOperationOn = true;
                break;
            case "=": 
                processResult();
                result = "";
                if(firstNum != 0 && secondNum != 0) {
                    processResult();
                }
                isOperationOn = true;
                break;
            default: break;
        }
        if(isOperationOn == false) {
            inputField.setText(result);
        }
    } //end ActionPerformed
    
    private void processResult() {
        switch(operation) {
            case '+':
                System.out.println(firstNum + " " + secondNum + " = " + (firstNum + secondNum));
                String sum = " " + doSum();
                inputField.setText(sum);
                System.out.println("InputField: " + inputField.getText());
                break;
            case '-':
                inputField.setText("" + doSubstraction());
                break;
            case '/':
                inputField.setText("" + doDivide());
                break;
            case '*':
                inputField.setText("" + doMultiply());
                break;
        }
        System.out.println("Operation: " + operation);
    } //end processResult()
    
    private double doSum() {
        return firstNum + secondNum;
    }
    
    private double doSubstraction() {
        return firstNum - secondNum;
    }
    
    private double doMultiply() {
        return firstNum * secondNum;
    }
    
    private double doDivide() {
        return firstNum / secondNum;
    }
    
    private void setNumbers() {
        if(isFirstNum) {
            firstNum = Double.parseDouble(result);
        }
        else {
            secondNum = Double.parseDouble(result);
        }
    }
}
