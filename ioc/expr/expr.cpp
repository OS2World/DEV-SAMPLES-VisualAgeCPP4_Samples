/******************************************************************************
* .FILE:         expr.cpp                                                     *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1997 - All Rights Reserved                 *
*                                                                             *
* .DISCLAIMER:                                                                *
*   The following [enclosed] code is sample code created by IBM               *
*   Corporation.  This sample code is not part of any standard IBM product    *
*   and is provided to you solely for the purpose of assisting you in the     *
*   development of your applications.  The code is provided 'AS IS',          *
*   without warranty of any kind.  IBM shall not be liable for any damages    *
*   arising out of your use of the sample code, even if they have been        *
*   advised of the possibility of such damages.                               *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/
/*----------------------------------------------------*\
| expr.CPP  -  An example of using a Multiway Tree     |
| Construct a tree for the following expression:       |
|      (8+2) * (2+4) / (7-5) ==> result: 30            |
| This is done explicitly for the following reasons:   |
| - no parser is available                             |
| - program demonstrates the use of some common        |
|   functions for multiway trees.                      |
| This programm also calculates the result from the    |
| expression. A subtree (with two operands and one     |
| operator) is calculated and replaced by the result.  |
| Note that the code does not respect                  |
| precedence of "/" and "*" over "+" and "-".          |
\*----------------------------------------------------*/

#include <imwt.h>
#include <istring.hpp>
#include <iostream.h>

////////////////////////////////////////////////////////////
// The tree for this expression looks like follows:       //
//                                                        //
//                              /                         //
//                                                        //
//                     *                -                 //
//                                                        //
//                +         +      7         5            //
//                                                        //
//              8   2     2   4                           //
////////////////////////////////////////////////////////////

typedef IMultiwayTree <2, IString> BinaryTree;

/*******************  functions  **************************/

IBoolean printNode(IString const& node, void* dummy)
/**** prints one node of a multiway tree ****/
 {
   cout << node << "|";
   return  True;
 }

void prefixedNotation(BinaryTree const& binTree)
/* prints an binary tree in prefixed notation */
 {
   binTree.allElementsDo(printNode , IPreorder);
   cout << endl;
 }


void identifyChildren  (IString &child1,
                        IString &child2,
                        BinaryTree &binTree,
                        ITreeCursor &binTreeCursor)
/********************************************************/
/****     identifies the children of a node          ****/
/********************************************************/
 {

  binTree.setToNext(binTreeCursor, IPreorder);
  child1 = binTree.elementAt(binTreeCursor);
  binTree.setToNextExistingChild(binTreeCursor);
  child2 = binTree.elementAt(binTreeCursor);
  binTree.setToParent(binTreeCursor);
 }


IBoolean isNumber(IString child)
/**********************************************************/
/****  checks whether a node contains a number         ****/
/**********************************************************/
{
  if ((child != '+') &&
      (child != '-') &&
      (child != '*') &&
      (child != '/'))
     { return True; }
  else { return False; }
}


void lookForNextOperator(BinaryTree &binTree,
                         ITreeCursor &binTreeCursor)
/********************************************************/
/****  looks for the next operator in the tree       ****/
/********************************************************/

 {
   IBoolean operatorFound = False;

   do
   {
    if (!isNumber(binTree.elementAt(binTreeCursor)))
       {
         operatorFound = True;
       }
    else
       {
         binTree.setToNext(binTreeCursor, IPreorder);
       }
   }
   while (! operatorFound);
 }


void calculateSubtree(double &result, double &operand1,
                      double &operand2, IString &operatorSign)
/**********************************************************/
/**** calculates the result from a subtree in the      ****/
/****                complete tree                     ****/
/**********************************************************/
 {
   switch (*(char*)operatorSign)
     {
       case '+':
       result = operand1+operand2;
       break;
       case '-':
       result = operand1-operand2;
       break;
       case '/':
       result = operand1/operand2;
       break;
       case '*':
       result = operand1*operand2;
       break;
     } /* endswitch */
 }


/************************ main ****************************/
int main ()

 {

  //////////////////////////////////////////////////////////
  // Constructing the tree:                               //
  //////////////////////////////////////////////////////////

  BinaryTree  binTree;
  BinaryTree::Cursor binTreeCursor(binTree);
  BinaryTree::Cursor binTreeSaveCursor(binTree);


  binTree.addAsRoot("/");
  binTree.setToRoot(binTreeCursor);
  binTree.addAsChild(binTreeCursor, 1, "*");
  binTree.setToChild(1, binTreeCursor);
  binTree.addAsChild(binTreeCursor, 1, "+");
  binTree.setToChild(1, binTreeCursor);
  binTree.addAsChild(binTreeCursor, 1, "8");
  binTree.addAsChild(binTreeCursor, 2, "2");
  binTree.setToParent(binTreeCursor);
  binTree.addAsChild(binTreeCursor, 2, "+");
  binTree.setToChild(2, binTreeCursor);
  binTree.addAsChild(binTreeCursor, 1, "2");
  binTree.addAsChild(binTreeCursor, 2, "4");
  binTree.setToRoot(binTreeCursor);
  binTree.addAsChild(binTreeCursor, 2, "-");
  binTree.setToChild(2, binTreeCursor);
  binTree.addAsChild(binTreeCursor, 1, "7");
  binTree.addAsChild(binTreeCursor, 2, "5");


  //////////////////////////////////////////////////////////
  // print complete tree in prefix notation               //
  //////////////////////////////////////////////////////////

  cout << "Printing the original tree in prefixed notation:"
       << endl;
  prefixedNotation(binTree);
  cout << " " << endl;

  //////////////////////////////////////////////////////////
  // Calculate tree                                       //
  //////////////////////////////////////////////////////////

  double      operand1 = 0;
  double      operand2 = 0;
  double      result = 0;
  INumber     replacePosition;
  IString     operatorSign, child1, child2;

  binTree.setToRoot(binTreeCursor);
  do
  {
   lookForNextOperator(binTree, binTreeCursor);
   operatorSign = binTree.elementAt(binTreeCursor);
   identifyChildren  (child1, child2, binTree, binTreeCursor);
   if ((isNumber(child1)) && (isNumber(child2)))
      {
        operand1 = child1.asDouble();
        operand2 = child2.asDouble();
        calculateSubtree(result, operand1, operand2,
                         operatorSign);
        if (binTree.numberOfElements() > 3)
        {
        // if tree contains more than three elements, replace
        // the calculated subtree by its result like follows:
         //save the cursor, because it will become invalidated after
         //removeSubtree
         binTreeSaveCursor = binTreeCursor;
         binTree.setToParent(binTreeSaveCursor);
         replacePosition = binTree.position(binTreeCursor);
         binTree.removeSubtree(binTreeCursor);
         binTree.addAsChild(binTreeSaveCursor,
                            replacePosition,
                            (IString)result);
        cout << "Tree with calculated subtree replaced: "
             << endl;
        prefixedNotation(binTree);
        binTree.setToRoot(binTreeCursor);
        }
        else
        {
        // if tree contains root with two children only,replace
        // this calculated subtree by its result like follows:
         binTree.removeAll();
         binTree.addAsRoot(IString(result));
         cout << "Now the tree contains the result only:" << endl;
         prefixedNotation(binTree);
        }
      }
   else
      {
      binTree.setToNext(binTreeCursor, IPreorder);
      }
  }
  while (binTree.numberOfElements() > 1);

  return 0;
 }
