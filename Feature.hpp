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
	
	// if the feature can be sampled.
	bool canSample;
	
	// has the feature been acted on already 
	bool alreadySampled;
	
	// if the feature capable of being acted on directly by an item
	bool actionAble;
	
	// has the feature been acted on already 
	bool alreadyActioned;
	
	// item that can affect this feature
	std::string itemToUse;
	
	// item revealed or added to inventory from this feature
	Item* itemAffected;
	

public:
	//constructor
	Feature(std::string, std::string, std::string, Item*);

	// get
	std::string getName();
	std::string getDescription();
	std::string getLocation();
	
	bool getAlreadyInspected();
	bool getAlreadySampled();
	bool getCanSample();
	bool getActionAble();
	bool getAlreadyActioned();
	Item* getAffectedItem();

	// set
	void setName(std::string);
	void setDescription(std::string);
	void setLocation(std::string);
	void setAlreadyInspected(bool);
	void setItemAffected(Item*);
	void setAlreadySampled();
	void setAlreadyActioned();
	
	void inspected();
};

#endif