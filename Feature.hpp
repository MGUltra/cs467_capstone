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

//#include "Room.hpp"
#include "Item.hpp"


class Feature
{
private:
	std::string name;
	std::string description;
	std::string location;
	bool alreadyInspected;
	Item* itemAffected;

public:
	//constructor
	Feature(std::string, std::string, std::string, Item*);

	// get
	std::string getName();
	std::string getDescription();
	std::string getLocation();
	bool getAlreadyInspected();

	// set
	void setName(std::string);
	void setDescription(std::string);
	void setLocation(std::string);
	void setAlreadyInspected(bool);
	void setItemAffected(Item*);
	
	void inspected();
};

#endif