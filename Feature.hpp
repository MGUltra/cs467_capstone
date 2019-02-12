/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef FEATURE_HPP
#define FEATURE_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

#include "Room.hpp"

using namespace std;

class Feature
{
private:
	string name;
	string description;
	string location;
	bool alreadyInspected;

public:
	//constructor
	Feature(string, string, string);

	// get
	string getName();
	string getDescription();
	string getLocation();

	// set
	void setName(string);
	void setDescription(string);
	void setLocation(string);
	void setAlreadyInspected(bool);
};

#endif