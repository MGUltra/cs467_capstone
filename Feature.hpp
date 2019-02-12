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


class Feature
{
private:
	std::string name;
	std::string description;
	std::string location;
	bool alreadyInspected;

public:
	//constructor
	Feature(std::string, std::string, std::string);

	// get
	std::string getName();
	std::string getDescription();
	std::string getLocation();

	// set
	void setName(std::string);
	void setDescription(std::string);
	void setLocation(std::string);
	void setAlreadyInspected(bool);
};

#endif