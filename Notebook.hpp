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
	bool getFeatureActioned(std::string);
	bool getRoomVisited(std::string);
	std::string getItemLocations(std::string);
	std::string getCurrentRoom();	

	std::unordered_map<std::string, bool>* getGameFlags();
	std::unordered_map<std::string, bool>* getItemAvailable();
	std::unordered_map<std::string, bool>* getItemAnalyzed();
	std::unordered_map<std::string, bool>* getFeatureInspected();
	std::unordered_map<std::string, bool>* getFeatureActioned();
	std::unordered_map<std::string, bool>* getRoomVisited();
	std::unordered_map<std::string, std::string>* getItemLocations();

	// add
	void setGameFlags(std::string, bool);
	
	void setItemAvailable(std::string, bool);
	void setItemAnalyzed(std::string, bool);
	void setFeatureInspected(std::string, bool);
	void setFeatureActioned(std::string, bool);
	void setRoomVisited(std::string, bool);
	void setItemLocations(std::string, std::string);	
	void setCurrentRoom(std::string);
	
	
	// change flags
	void changeEntry(std::string, bool);
	
	
	// check specific status
	bool vinceCanInterrogate();
	bool vinceCanClear();
	bool carlCanInterrogate();
	bool carlCanClear();
	bool danCanInterrogate();
	bool danCanAccuse();
	bool royCanInterrogate();
	bool louiseCanInterrogate();
	bool herbertCanInterrogate();
	
	
	void saveGame();
	
	void loadGame();
	
	
	// test functions
	void printGameFlags();
	void printAll();
	
};
#endif