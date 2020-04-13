/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on December 2, 2019, 2:17 PM
 */

#include <cstdlib>
#include <iostream>
#include "Files/ReadingWritingFiles.h"
#include "Files/ExcerciseC02.h"
#include "C03CinCpp/WorkingWithChars.h"
#include "C03CinCpp/BinaryOperations.h"
#include "C03CinCpp/ExcercisesC03.h"
#include "C07FuncOverload/C07Excercises.h"
#include "C09InlineFunctions/C09Preprocessor.h"
#include "C12OperatorOverload/OOSyntax.h"
#include "C12OperatorOverload/BinaryOpsTest.h"
#include "C12OperatorOverload/SmartPointer.h"
#include "C12OperatorOverload/IOStreamOverload.h"
#include "C12OperatorOverload/CopyingWithPointers.h"
#include "C12OperatorOverload/OperatorOverloadingConversion.h"
#include "C12OperatorOverload/StringToCChar.h"
#include "C12OperatorOverload/C12Excercises.h"
//#include "OperatorNewAndDelete/OverloadGlobalNewAndDelete.h"  //Uncomment for global new / delete
#include "OperatorNewAndDelete/OverloadingMemberNewAndDelete.h"
#include "OperatorNewAndDelete/OperatorNewAndDeleteMemberForArrays.h"
#include "OperatorNewAndDelete/C13Excercises.h"
#include "C14InheritanceAndComposition/FileNameExample.h"
#include "C15Polymorphism/AllowedPureVirtualFunc.h"
#include "C15Polymorphism/OperatorOverloadingAndInheritance.h"
#include "C15Polymorphism/ExcercisesC15.h"
#include "C16Templates/IntStack.h"
#include "C16Templates/TemplateArray.h"
#include "C16Templates/ConstantsInTemplates.h"
#include "C16Templates/StackTemplate.h"
#include "C16Templates/AutoCounterTest.h"
#include "C16Templates/IterStackTemplate.h"
#include "C16Templates/RealStack.h"
#include "C16Templates/TestRealStash.h"
#include "C16Templates/Drawing.h"
#include "C16Templates/excercises/ExcercisesC16.h"
#include "C16Templates/excercises/ObjectCounter.h"
#include "Volume2/exceptionC01/ExceptionExamples.h"
#include "Volume2/exceptionC01/StandardException.h"
#include "Volume2/exceptionC01/SafeAssign.h"

/*
 * 
 */
int main(int argc, char** argv) {

//    testStringToCChar();
//    Ex8TestArrCounted();
//    testDrawing();
//    testObjectCounterExample();
    
    //Volume 2
    testSafeAssignment();
    
    return 0;
}

