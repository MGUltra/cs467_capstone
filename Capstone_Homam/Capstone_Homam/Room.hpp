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

#include "Item.hpp"

using namespace std;

struct Room
{
	private:
	string name;
	string longDescription;
	string shortDescription;

	bool alreadyVisited;

	Room** attachedRooms;
	int numAttachedRooms;

	Item** itemsInRoom;
	int numItemsInRoom;

	public:
	//constructor
	Room();
	Room(string, string, string, int);
	//destructor
	//~Room();

	//get
	string getName();
	string getLongDescription();
	string getShortDescription();
	int getNumAttachedRooms();
	Room** getAttachedRooms();
	Item** getItemsInRoom();

	//set
	void setName(string);
	void setLongDescription(string);
	void setShortDescription(string);
	void setNumAttachedRooms(int);
	void addAttachedRoom(Room*);
	void addItemInRoom(Item*);
};
#endif