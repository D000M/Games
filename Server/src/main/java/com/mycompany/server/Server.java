/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;
import java.lang.Thread;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 *
 * @author default
 */
public class Server {
    
    static Vector<ClientHandler> clients = new Vector<>();
    static int totalClients = 0;
    final static int port = 1234;
    
    
    public static void main(String[] args) throws IOException {
        //server is listening for port 1234;
        ServerSocket serverSocket = new ServerSocket(port);
        
        Socket socket;
        
        
        //Running infinte loop to get client requests
        while(true) {
            socket = serverSocket.accept();
            
            System.out.println("New client request received: " + socket);
            
            //obtain input and output streams
            DataInputStream dataInput = new DataInputStream(socket.getInputStream());
            DataOutputStream dataOutput = new DataOutputStream(socket.getOutputStream());
            
            System.out.println("Creating a new handler for this client...");
            
            //Create a new handler object for handling this request
            ClientHandler clientHndlr = new ClientHandler(socket, "client" + totalClients, dataInput, dataOutput);
            
            //Create new thread for this handler object
            Thread thread = new Thread(clientHndlr);
            
            System.out.println("Adding this client to the active client list");
            
            clients.add(clientHndlr);
            
            thread.start();
            
            //increment total clients
            totalClients++;
        }
    }   //end of main method
    
    
} //end of Server class

class ClientHandler implements Runnable {
    
        Scanner scanner = new Scanner(System.in);
        private String clientName;
        final DataInputStream dataInput;
        final DataOutputStream dataOutput;
        Socket socket;
        boolean isLoggedIn;
        
        public ClientHandler(Socket socket, String name, DataInputStream input, DataOutputStream output) {
            this.clientName = name;
            System.out.println(name);
            this.socket = socket;
            this.dataInput = input;
            this.dataOutput = output;
            this.isLoggedIn = true;
        }

    @Override
    public void run() {
        String received;
        
        while(true) {
            try {
                //receive the string
                received = dataInput.readUTF();
                System.out.println(received);
                
                if(received.equals("logout")) {
                    this.isLoggedIn = false;
                    this.socket.close();
                    break;
                }
                
                // break the string into message and recipient part 
                StringTokenizer tokenizer = new StringTokenizer(received, "#");
                String msgToSend = tokenizer.nextToken();
                String recipent = tokenizer.nextToken();
                
                // search for the recipient in the connected devices list. 
                // ar is the vector storing client of active users 
                for(ClientHandler client : Server.clients) {
                    // if the recipient is found, write on its 
                    // output stream 
                    
                    if(client.clientName.equals(recipent) && client.isLoggedIn == true) {
                        client.dataOutput.writeUTF(this.clientName + ": " + msgToSend);
                        break;
                    }
                }
            }
            catch(IOException e) {
                e.printStackTrace();
            }
        }   //end of while loop
        
        try {
            dataInput.close();
            dataOutput.close();
            
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }
        
        
}   //end of class Client handler