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

using namespace std;

struct Room
{
	private:
	string name;
	string longDescription;
	string shortDescription;

	bool alreadyVisited;

	vector<string> attachedRooms;

	vector<string> itemsInRoom;

	vector<string> featuresInRoom;

	public:
	// constructor
	Room();
	Room(string, string, string);
	// destructor
	//~Room();

	// get
	string getName();
	string getLongDescription();
	string getShortDescription();
	
	vector<string>* getAttachedRooms();
	vector<string>* getItemsInRoom();
	vector<string>* getFeaturesInRoom();

	bool getAlreadyVisited();
	

	
	
	// set
	void setName(string);
	void setLongDescription(string);
	void setShortDescription(string);
	
	void setAlreadyVisited(bool);
	
	// add
	void addAttachedRoom(string);
	void addItemInRoom(string);
	void addFeatureInRoom(string);
	
	void removeItemFromRoom(string);
	int findVectorIndex(string, vector<string>);
	
	// print
	void printAttachedRooms();
	void printItemsInRoom();
	void printFeaturesInRoom();
	
	
};
#endif