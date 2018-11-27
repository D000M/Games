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
public class Digits {
    
    public static void numberOfDigits(int n) {
        int digits = 0;
        System.out.print("The number: " + n + " has ");
        for(; n > 0; n /= 10, digits++);
        System.out.println( digits + " digits.");
    }
    
    private static int recFactoriel(int n) {
        if(n <= 1) {
            return 1;
        }
        return n * recFactoriel(n - 1);
    }
    
    public static void testRecFactoriel(int n) {
        int factoriel = recFactoriel(n);
        System.out.println(n + "! = " + factoriel);
    }
    
    private static double recPower(double x, int y) {
        if(y == 0) {
            return 1;
        }
        return x * recPower(x, y - 1);
    }
    
    public static void testRecPower() {
        double power = recPower(1.5, 2);
        System.out.println(power);
    }
}
