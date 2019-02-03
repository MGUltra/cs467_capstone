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
	playerInventory.addItemToInventory(currentItem);
	location->removeItemFromRoom(currentItem);
}

void Player::dropItem(string currentItem)
{
	playerInventory.removeItemFromInventory(currentItem);
	location->addItemInRoom(currentItem);
}