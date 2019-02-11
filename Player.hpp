/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

#include "Inventory.hpp"
#include "Room.hpp"

using namespace std;

class Player
{
private:
	string name;
	Inventory playerInventory;
	Room* location;

public:
	//constructor
	Player(string, Room*);

	//get
	string getName();
	Room* getLocation();

	//set
	void setName(string);
	void setLocation(Room*);

	// Player actions
	void pickUpItem(string);
	void dropItem(string);
	void showInventory();
	
};

#endif