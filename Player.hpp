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


class Player
{
private:
	std::string name;
	Inventory playerInventory;
	Room* location;

public:
	//constructor
	Player(std::string, Room*);

	//get
	std::string getName();
	Room* getLocation();

	//set
	void setName(std::string);
	void setLocation(Room*);

	
	bool itemInInventory(std::string);
	
	// Player actions
	void pickUpItem(std::string);
	void dropItem(std::string);
	void inspectItem(std::string);
	void showInventory();
	
};

#endif