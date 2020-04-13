/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.client;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
import java.lang.Thread;
/**
 *
 * @author default
 */
public class Client {
    
    private static final int SERVER_PORT = 1234;
    
    public static void main(String[] args) throws UnknownHostException, IOException{
        Scanner scanner = new Scanner(System.in);
        
        //Geting host ip
        InetAddress ip = InetAddress.getByName("localhost");
        
        Socket socket = new Socket(ip, SERVER_PORT);
        
        DataInputStream dataInput = new DataInputStream(socket.getInputStream());
        DataOutputStream dataOutput = new DataOutputStream(socket.getOutputStream());
        
        //Send message thread
        //using lambda
        Thread sendMessage = new Thread(new Runnable() {
            @Override
            public void run() {
                while(true) {
                    //read the message to deliver
                    String message = scanner.nextLine();
                    
                    try {
                        dataOutput.writeUTF(message);
                    }
                    catch(IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        
        //read message thread
        Thread readMessage = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    String message = dataInput.readUTF();
                    System.out.println(message);
                }
                catch(IOException e) {
                    e.printStackTrace();
                }
            }
        });
        
        sendMessage.start();
        readMessage.start();
    } 
    
}
