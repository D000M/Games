/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nakovAlgorithms.Mathmatics;

/**
 *
 * @author default
 */
public class Mathmatics {
    
    /**
     * Iterative Algorithm for finding Biggest common divisor of 2 numbers
     * @param m first number.
     * @param n second number.
     * return the biggest common divisor.
     */
    public static int EuclidiusBCD(int m, int n) {
        
        while(m != 0) {
            if(m < n) {
                int temp = m;
                m = n;
                n = temp;
            }
            m %= n;
        }
        return n;
    }
    
}
