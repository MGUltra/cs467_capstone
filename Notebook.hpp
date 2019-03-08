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
	std::unordered_map<std::string, bool> itemAvailable;
	std::unordered_map<std::string, bool> itemAnalyzed;	
	
	// feature flags - for each feature
	// featurenameAlreadyInspected
	// featurenameAlreadySampled
	// featurenameAlreadyActioned
	std::unordered_map<std::string, bool> featureInspected;
	std::unordered_map<std::string, bool> featureSampled;
	std::unordered_map<std::string, bool> featureActioned;
	
	// room flags - for each room
	// roomnameAlreadyVisited
	std::unordered_map<std::string, bool> roomVisited;
	
	// key is item name, value is either room name or inventory;
	std::unordered_map<std::string, std::string> itemLocations;

	std::string playerLocation;
	
public:
	// constructor
	Notebook();
	// destructor
	//~Notebook();

	// get
	bool getGameFlags(std::string);
	
	bool getItemAvailable(std::string);
	bool getItemAnalyzed(std::string);
	bool getFeatureInspected(std::string);
	bool getFeatureSampled(std::string);
	bool getFeatureActioned(std::string);
	bool getRoomVisited(std::string);
	std::string getCurrentRoom();	

	// add
	void setGameFlags(std::string, bool);
	
	void setItemAvailable(std::string, bool);
	void setItemAnalyzed(std::string, bool);
	void setFeatureInspected(std::string, bool);
	void setFeatureSampled(std::string, bool);
	void setFeatureActioned(std::string, bool);
	void setRoomVisited(std::string, bool);
	
	void setCurrentRoom(std::string);
	
	// change flags
	void changeEntry(std::string, bool);
	
	
	// check specific status
	bool vinceInterrogate();
	bool vinceClear();
	bool carlInterrogate();
	bool carlClear();
	bool danInterrogate();
	bool danAccuse();
	bool royInterrogate();
	bool louiseInterrogate();
	bool herbertInterrogate();
	
	
	void saveGame();
	
	void loadGame();
	
	
};
#endif