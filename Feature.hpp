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

#include "Notebook.hpp"
#include "Item.hpp"


class Feature
{
private:
	std::string name;							// name of feature
	std::string displayName;      // display name of feature
	std::string descriptionFirst; // description sent when first examined or acted upon
	std::string descriptionAfter; // description sent after examined or acted upon
	std::string location;					// location of feature
	std::string useItem;					// item that can affect this feature
	bool canSample;								// if the feature can be sampled.
	bool canHack;									// if the feature can be hacked.
	bool actionAble;							// if the feature capable of being acted on directly by an item through Use
	bool alreadyInspected;				// has the feature been inspected
	bool alreadyActioned;					// has the feature been acted on already - sample, Hacked, or use item on
	Item* itemAffected;						// item revealed or added to inventory from this feature

	

public:
	//constructor
	Feature(std::string, std::string, std::string, std::string, Item*, bool, bool, bool, std::string);

	// get
	std::string getName();
	std::string getDescriptionFirst();
	std::string getDescriptionAfter();
	std::string getLocation();
	std::string getUseItem();
	
	bool getAlreadyInspected();
	bool getAlreadyActioned();
	bool getCanSample();
	bool getCanHack();
	bool getActionAble();
	Item* getitemAffected();
	
	
	// set
	void setName(std::string);
	void setDescriptionFirst(std::string);
	void setDescriptionAfter(std::string);
	void setLocation(std::string);
	void setAlreadyInspected(bool);
	void setItemAffected(Item*);
	void setAlreadyActioned(bool);
	void setCanSample(bool);
	void setCanHack(bool);
	void setActionAble(bool);
	void setUseItem(std::string);
	
	// other
	void inspected(Notebook*);
	void hacked(Notebook*);
	void sampled(Notebook*);
	void itemUsed(Notebook*);
	void listened(Notebook*);
};

#endif