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
void readFileDefault(std::ifstream &fileName);


/*******************************************************************************
**                     readFileChar
** Description: Uses getchar to read in and display a file by char
** instead of by line - allows more customization for displaying text
*******************************************************************************/
void readFileChar(std::ifstream &fileName);


/*******************************************************************************
**                     calcWindowSize
** Description: Ensures terminal window is of sufficient size to
** fully enjoy the game. Prompts user to adjust terminal if size
** does not meet minimum requirements.
*******************************************************************************/
int calcWindowSize();


#endif