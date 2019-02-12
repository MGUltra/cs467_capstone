/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Player.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Player::Player(string name, Room* currentLocation)
{
	setName(name);
	setLocation(currentLocation);
	playerInventory = Inventory();
	
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Player::getName()
{
	return name;
}

Room* Player::getLocation()
{
	return location;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Player::setName(string givenName)
{
	name = givenName;
}

void Player::setLocation(Room* currentLocation)
{
	location = currentLocation;
}

/*******************************************************************************
*		PLAYER ACTIONS
*******************************************************************************/
void Player::pickUpItem(string currentItem)
{
	if(location->isItemInRoom(currentItem) == true)
	{
		playerInventory.addItemToInventory(currentItem);
		
		location->removeItemFromRoom(currentItem);
	
	}
	else
	{
			std::cout << currentItem << " not found in " << location->getName() << "." << std::endl;
			std::cout << std::endl;
	}		
}


void Player::dropItem(string currentItem)
{
	if(playerInventory.isItemInInventory(currentItem) == true)
	{
		playerInventory.removeItemFromInventory(currentItem);
		
		location->addItemInRoom(currentItem);
	
	}
	else
	{
			std::cout << currentItem << " not found in inventory" << std::endl;
			std::cout << std::endl;
	}
	
}

void inspectItem(std::string currentItem)
{
	
}



void Player::showInventory()
{
	this->playerInventory.printCurrentInventory();
}
