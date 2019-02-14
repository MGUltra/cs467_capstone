/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef ROOM_HPP
#define ROOM_HPP

/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>

#include "Item.hpp"
#include "Feature.hpp"


struct Room
{
	private:
	std::string name;
	std::string longDescription;
	std::string shortDescription;

	bool alreadyVisited;

	std::vector<Room*> attachedRooms;

	std::vector<Item*> itemsInRoom;

	std::vector<Feature*> featuresInRoom;

	public:
	// constructor
	Room();
	Room(std::string, std::string, std::string);
	// destructor
	//~Room();

	// get
	std::string getName();
	std::string getLongDescription();
	std::string getShortDescription();
	
	std::vector<Room*>* getAttachedRooms();
	std::vector<Item*>* getItemsInRoom();
	std::vector<Feature*>* getFeaturesInRoom();

	bool getAlreadyVisited();

	// set
	void setName(std::string);
	void setLongDescription(std::string);
	void setShortDescription(std::string);
	
	void setAlreadyVisited(bool);
	
	// add
	void addAttachedRoom(Room*);
	void addItemInRoom(Item*);
	void addFeatureInRoom(Feature*);
	
	void removeItemFromRoom(Item*);
	int findVectorIndex(Item*);
	

	// Test Functions
	bool isRoomAttached(Room*);
	bool isItemInRoom(Item*);
	bool isFeatureInRoom(Feature*);
	bool isFeatureExamined(Feature*);
	
	// print
	void printAttachedRooms();
	void printItemsInRoom();
	void printFeaturesInRoom();
	
	
};
#endif