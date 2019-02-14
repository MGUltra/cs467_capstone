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

	std::vector<std::string> itemsInRoom;

	std::vector<std::string> featuresInRoom;

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
	std::vector<std::string>* getItemsInRoom();
	std::vector<std::string>* getFeaturesInRoom();

	bool getAlreadyVisited();

	// set
	void setName(std::string);
	void setLongDescription(std::string);
	void setShortDescription(std::string);
	
	void setAlreadyVisited(bool);
	
	// add
	void addAttachedRoom(Room*);
	void addItemInRoom(std::string);
	void addFeatureInRoom(std::string);
	
	void removeItemFromRoom(std::string);
	int findVectorIndex(std::string, std::vector<std::string>);
	

	// Test Functions
	bool isRoomAttached(Room*);
	bool isItemInRoom(std::string);
	bool isFeatureInRoom(std::string);
	bool isFeatureExamined(std::string);
	
	// print
	void printAttachedRooms();
	void printItemsInRoom();
	void printFeaturesInRoom();
	
	
};
#endif