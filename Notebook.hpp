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
	
	
	//item flags - for each item
	// itemnameAvailable
	// itemnameAnalyzed
	std::unordered_map<std::string, bool> itemFlags;
	
	
	// feature flags - for each feature
	// featurenameAlreadyInspected
	// featurenameAlreadySampled
	// featurenameAlreadyActioned
	std::unordered_map<std::string, bool> featureFlags;
	
	// room flags - for each room
	// roomnameAlreadyVisited
	std::unordered_map<std::string, bool> roomFlags;
	
	
	std::unordered_map<std::string, bool> suspectFlags;
	
	std::unordered_map<std::string, bool> witnessFlags;
	
	std::unordered_map<std::string, bool> chiefFlags;
	
	// key is item name, value is either room name or inventory;
	std::unordered_map<std::string, std::string> itemLocations;
	
	std::string playerLocation;
	
public:
	// constructor
	Notebook();
	// destructor
	//~Notebook();

	// get
	bool getEntry(std::string);

	// add
	void setEntry(std::string, bool);
	
	// change flags
	void changeEntry(std::string, bool);
	
	
	void saveGame();
	
	void loadGame();
	
	
};
#endif