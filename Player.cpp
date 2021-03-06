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
Player::Player()
{
	playerInventory = Inventory();
}



Player::Player(std::string name, Room* currentLocation)
{
	setName(name);
	setLocation(currentLocation);
	playerInventory = Inventory();
	
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Player::getName()
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
void Player::setName(std::string givenName)
{
	name = givenName;
}

void Player::setLocation(Room* currentLocation)
{
	location = currentLocation;
	

}


bool Player::itemInInventory(Item* currentItem)
{
	if(playerInventory.isItemInInventory(currentItem) == true)
		return true;
	else
		return false;
}




/*******************************************************************************
*		PLAYER ACTIONS
*******************************************************************************/
void Player::pickUpItem(Item* currentItem, Notebook* notebook)
{
	if(location->isItemInRoom(currentItem) == true && currentItem->getAvailable() == true)
	{
		playerInventory.addItemToInventory(currentItem);
		
		location->removeItemFromRoom(currentItem);
	
		notebook->setItemLocations(currentItem->getName(), "inventory");

		std::cout << currentItem->getName() << " has been added to you inventory." << std::endl;
	
	}
	else
	{
			std::cout << currentItem->getName() << " not found in " << location->getName() << "." << std::endl;
			std::cout << std::endl;
	}		
}

/*******************************************************************************
*		LOAD ITEMS INTO INVENTORY
*******************************************************************************/
void Player::loadItemInventory(Item* currentItem, Notebook* notebook)
{
	playerInventory.addItemToInventory(currentItem);

	notebook->setItemLocations(currentItem->getName(), "inventory");
}


void Player::dropItem(Item* currentItem, Notebook* notebook)
{
	if(playerInventory.isItemInInventory(currentItem) == true)
	{
		playerInventory.removeItemFromInventory(currentItem);
		
		location->addItemInRoom(currentItem);
		
		notebook->setItemLocations(currentItem->getName(), this->location->getName());

		std::cout << currentItem->getName() << " has been dropped in your current location." << std::endl;
	
	}
	else
	{
			std::cout << currentItem->getName() << " not found in inventory" << std::endl;
			std::cout << std::endl;
	}
	
}

void Player::changeLocation(Room* locationIn, Notebook* notebook)
{
	setLocation(locationIn);
	
	notebook->setCurrentRoom(this->location->getName());
}


void Player::showInventory()
{
	this->playerInventory.printCurrentInventory();
}

void Player::deleteInventory()
{
	this->playerInventory.removeAllItems();
}