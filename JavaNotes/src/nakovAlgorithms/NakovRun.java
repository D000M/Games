/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nakovAlgorithms;

import nakovAlgorithms.Mathmatics.Digits;
import nakovAlgorithms.Mathmatics.Mathmatics;

/**
 *
 * @author default
 */
public class NakovRun {
    
    public static void runIterativeEuclid() {
        System.out.println(Mathmatics.EuclidiusBCD(48, 16));
    }
    
    public static void runCountDigits() {
        Digits.numberOfDigits(214512);
    }
}
