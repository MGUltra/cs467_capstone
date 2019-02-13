/******************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Kendal Droddy (Rozalija Zibrat, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has 
** to interrogate suspects, investigate the crime scene, search 
** for evidence, and ultimately decide who committed the murder.
*******************************************************************/
#include "dataRead.hpp"
#include <iostream>
#include <fstream>

//Going to tweak this a bit so that it will send the file name
//instead of the ifstream to the function. 
int main()
{
  int num = 0;
  std::ifstream inFile;
  std::string input;

  if (calcWindowSize() == 0)
    return 0;

  inFile.open("roomText/cellLong.txt", std::ios::out);
  readFileDefault(inFile);
  inFile.close();
  inFile.open("roomText/cellShort.txt", std::ios::out);
  readFileDefault(inFile);
  inFile.close();

  return 0;
}