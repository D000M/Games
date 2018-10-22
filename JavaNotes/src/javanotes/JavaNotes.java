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
import chapter6.GraphicDices;
import chapter6.GraphicStatCalc;
import chapter6.SelectableSquares;
import chapter6.SquaresMoving;
import chapter6.SubKillerV2;
import eckels.gui.ClickableRandomStrings2;
import eckels.gui.GrowingCircleAnimation;
import eckels.gui.HighLowGUI;
import eckels.gui.KeyBoardAndFocusDemo;
import eckels.gui.MosaicDraw;
import eckels.gui.NullLayoutDemo;
import eckels.gui.RandomArt;
import eckels.gui.RandomMosaicWalk2;
import eckels.gui.RandomStrings;
import eckels.gui.RunGUI;
import eckels.gui.SimpleCalc;
import eckels.gui.SimpleColorChooser;
import eckels.gui.SimpleDialogDemo;
import eckels.gui.SimplePaint;
import eckels.gui.SimpleStamper;
import eckels.gui.SimpleTrackMouse;
import eckels.gui.SliderAndDemoButton;
import eckels.gui.SliderDemo;
import eckels.gui.SubKiller;
import eckels.gui.TextAreaDemo;
import eckels.gui.text.BlackJackGame;
import eckels.gui.text.TestBlackJackEx;
import eckels.gui.text.shapes.ShapeDraw;
import java.awt.TextArea;
import myGUI.Calculator;
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

        GraphicStatCalc.runGraphicStatCalc();
        
        ElapsedTime.stopTime();
        ElapsedTime.measuredTimeSeconds();
    }
    
}
