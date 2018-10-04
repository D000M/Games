/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package timers;

/**
 *
 * @author default
 */
public class ElapsedTime {
    
    static long start = 0;
    static long end = 0;
    static double difference = 0;
    
    public static void startTime() {
        start = System.currentTimeMillis();
    }
    public static void stopTime() {
        end = System.currentTimeMillis();
    }
    
    public static void measuredTimeMillis() {
        difference = end - start;
        System.out.println("Total Time: " + difference + "ms");
    }
    public static void measuredTimeSeconds() {
        difference = (end - start) / 1000.0;
        System.out.println("Total Time: " + difference + "s");
    }
}

