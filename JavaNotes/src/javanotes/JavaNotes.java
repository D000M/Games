/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javanotes;

import chapter2.ExcersicesCh2;
import chapter3.ExcersicesCh3;
import chapter4.ExcersicesCh4;
import chapter5.DiceRollStats2;
import chapter5.TestProgram;
import eckels.gui.GrowingCircleAnimation;
import eckels.gui.RandomMosaicWalk2;
import eckels.gui.RunGUI;
import eckels.gui.text.BlackJackGame;
import eckels.gui.text.TestBlackJackEx;
import eckels.gui.text.shapes.ShapeDraw;
import timers.ElapsedTime;

/**
 *
 * @author default
 */
public class JavaNotes {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        ElapsedTime.startTime();

        BlackJackGame bjGame = new BlackJackGame(100);

        ElapsedTime.stopTime();
        ElapsedTime.measuredTimeSeconds();
    }
    
}
