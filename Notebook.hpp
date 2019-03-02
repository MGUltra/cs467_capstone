/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <unordered_map>

class Notebook
{
private:
	std::unordered_map<std::string, bool> gameFlags;

public:
	// constructor
	Notebook();
	// destructor
	//~Notebook();

	// get
	bool getEntry(std::string);

	// add
	void setEntry(std::string, std::string);
	
	// change flags
	void changeEntry(std::string, bool);
	
	
};
#endif