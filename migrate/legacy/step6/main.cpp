/****************************************************************************
 * main.cpp
 * This file contains the definition of the main() function which just calls 
 * into the payroll.dll's payroll() function.  This example is used to show 
 * how to migrate your VisualAge C++ 3.x application by steps
 * - a) rebuilding just your EXE with VisualAge C++ 4.0, and still using the 
 *      payroll.dll built with Version 3.x (via the forwarding DLLs)
 * - b) then rebuilding the payroll.dll using Version 4.0, but using the 
 *      compatability mode on the compiler
 * - c) then final conversion to full ANSI C++ stream library
 ****************************************************************************/
#include <stdio.h>

#include "payroll.hpp"


int main(void) {
  char * s = new char[6];
  printf("In main.exe\n");
  payroll(s);
  return 0;
}
