/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package timers;

/**
 *
 * @author GS-D000M
 */
public class ElapsedTime {
    
    static long start = 0;
    static long end = 0;
    static double difference = 0;
    
    /**
     * Starting the timer
     * set start - member variable to System.currentTimeMillis().
     */
    public static void startTime() {
        start = System.currentTimeMillis();
    }

    /**
     * Stop the timer
     * set end - member variable to System.currentTimeMillis().
     */
    public static void stopTime() {
        end = System.currentTimeMillis();
    }
    
    /**
     * Calculate the time between start and end variables.
     * print the difference in milliseconds.
     */
    public static void measuredTimeMillis() {
        difference = end - start;
        System.out.println("Total Time: " + difference + "ms");
    }

    /**
     * Calculate the time between start and end variables
     * print the time difference in seconds.
     */
    public static void measuredTimeSeconds() {
        difference = (end - start) / 1000.0;
        System.out.println("Total Time: " + difference + "s");
    }
}

