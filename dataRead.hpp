/******************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Kendal Droddy (Rozalija Zibrat, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has 
** to interrogate suspects, investigate the crime scene, search 
** for evidence, and ultimately decide who committed the murder.
*******************************************************************/
#ifndef DATAREAD_HPP
#define DATAREAD_HPP

#include <iostream>
#include <fstream>

/*********************************************************************
**                     readFileDefault
** Description: Uses getline to read in and display a file exactly
** as its typed in the text file
*********************************************************************/
void readFileDefault(std::ifstream &fileName)
{
  std::string input;

  getline(fileName, input);
  while(fileName)
  {
    std::cout << input << std::endl;
    getline(fileName, input);
  }
  //Rewind the file
  fileName.clear();
  fileName.seekg(0, std::ios::beg);
}

/*********************************************************************
**                     readFileChar
** Description: Uses getchar to read in and display a file by char
** instead of by line - allows more customization for displaying text
*********************************************************************/
void readFileChar(std::ifstream &fileName)
{
  char ch;

  //char = fileName.get();
  while(ch != EOF)
  {
    std::cout << ch;
    ch = fileName.get();
  }
  //Rewind the file
  fileName.clear();
  fileName.seekg(0, std::ios::beg);
}

#endif