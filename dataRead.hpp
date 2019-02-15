/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef DATAREAD_HPP
#define DATAREAD_HPP

/*------------------------------------------------------------------------------
    LIBRARIES
------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

/*******************************************************************************
**                     readFileDefault
** Description: Uses getline to read in and display a file exactly
** as its typed in the text file
*******************************************************************************/
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

/*******************************************************************************
**                     readFileChar
** Description: Uses getchar to read in and display a file by char
** instead of by line - allows more customization for displaying text
*******************************************************************************/
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

/*******************************************************************************
**                     calcWindowSize
** Description: Ensures terminal window is of sufficient size to
** fully enjoy the game. Prompts user to adjust terminal if size
** does not meet minimum requirements.
*******************************************************************************/
int calcWindowSize()
{
  int cols = 80;
  int lines = 24;
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    cols = ts.ts_cols;
    lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    cols = ts.ws_col;
    lines = ts.ws_row;
#endif /* TIOCGSIZE */

    if(cols < 79)
    {
      printf("| Terminal Too Narrow - Please Resize For Optimal Viewing Experience |");
      return 0;
    }
    if(lines < 42)
    {
      printf("| Terminal Too Short  - Please Resize For Optimal Viewing Experience |");
      return 0;
    }
  return 1;
}

#endif