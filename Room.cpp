/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Room.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Room::Room()
{
	// Blank Default Constructor
}

Room::Room(std::string name, std::string longDescription, std::string shortDescription)
{
	setName(name);
	setLongDescription(longDescription);
	setShortDescription(shortDescription);

	alreadyVisited = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Room::getName()
{
	return name;
}

std::string Room::getLongDescription()
{
	return longDescription;
}

std::string Room::getShortDescription()
{
	return shortDescription;
}

std::vector<Room*>* Room::getAttachedRooms()
{
	return &attachedRooms;
}

std::vector<Item*>* Room::getItemsInRoom()
{
	return &itemsInRoom;
}

std::vector<Feature*>* Room::getFeaturesInRoom()
{
	return &featuresInRoom;
}

bool Room::getAlreadyVisited()
{
	return this->alreadyVisited;
}	

Room* Room::getCardinalDirection(std::string direction)
{
	// test if direction leads to attached room.
	if(this->cardinalRooms.find(direction) != this->cardinalRooms.end())
	{
		return cardinalRooms[direction];
	}
	else
		return NULL;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Room::setName(std::string givenName)
{
	name = givenName;
}

void Room::setLongDescription(std::string givenLongDescription)
{
	longDescription = givenLongDescription;
}

void Room::setShortDescription(std::string givenShortDescription)
{
	shortDescription = givenShortDescription;
}

void Room::setAlreadyVisited(bool newVisit)
{
	this->alreadyVisited = newVisit;
}	

void Room::setCardinalDirection(std::string direction, Room* newRoom)
{
	cardinalRooms[direction] = newRoom;
}


/*******************************************************************************
*		ADD FUNCTIONS
*******************************************************************************/
void Room::addAttachedRoom(Room* newRoom)
{
	attachedRooms.push_back(newRoom);
}

void Room::addItemInRoom(Item* newItem)
{
	itemsInRoom.push_back(newItem);
}

void Room::addFeatureInRoom(Feature* newFeature)
{
	featuresInRoom.push_back(newFeature);
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Room::removeItemFromRoom(Item* removeThisItem)
{

	int index = findVectorIndex(removeThisItem);
	
	if(index != 999)
		itemsInRoom.erase(itemsInRoom.begin() + index);
	
}

void Room::removeAllItems()
{
	itemsInRoom.clear();
}

/*******************************************************************************
*		FIND VECTOR INDEX
*******************************************************************************/
int Room::findVectorIndex(Item* removeThisItem)
{
	int size = this->itemsInRoom.size();

	for (int i = 0; i <= size; i++)
	{
		if (removeThisItem->getName() == this->itemsInRoom[i]->getName())
		{
			return i;
		}
	}
	
	return 999;
}


/*******************************************************************************
*		TEST FUNCTIONS
*******************************************************************************/



bool Room::isRoomAttached(Room* roomIn)
{
	
	if(roomIn == NULL)
		return false;
	
	for(auto i : attachedRooms)
	{
		if(roomIn->getName() == i->getName())
			return true;
	}
	
	return false;
}

bool Room::isItemInRoom(Item* itemIn)
{
	for(auto i : itemsInRoom)
	{
		if(itemIn->getName() == i->getName())
			return true;
	}
	
	return false;
}

bool Room::isFeatureInRoom(Feature* featureIn)
{
	for(auto i : featuresInRoom)
	{
		if(featureIn->getName() == i->getName())
			return true;
	}
	
	return false;
}

bool Room::isFeatureExamined(Feature* featureIn)
{
	//featuresInRoom
	return featureIn->getAlreadyInspected();
}











/*******************************************************************************
*		PRINT FUNCTIONS
*******************************************************************************/
void Room::printAttachedRooms()
{
	std::cout << "You can see the following rooms from this one" << std::endl;
	std::cout << "----------------" << std::endl;
	
	std::string roomName;
	
	for(auto i : attachedRooms)
	{
			roomName = i->getName();
			
			if(roomName == "living")
			{
				std::cout << "| " << "living room" << std::endl;
			}
			else
			{
				std::cout << "| " << roomName << std::endl;
			}
	}
	std::cout << "----------------" << std::endl;
}

void Room::printItemsInRoom()
{
	std::cout << "You can see the following items" << std::endl;
	std::cout << "----------------" << std::endl;
	
	
	for(auto i : itemsInRoom)
	{
		if(i->getAvailable() == true)
		{
			std::cout << "| " << i->getName() << std::endl;
		}
	}
	std::cout << "----------------" << std::endl;
}

void Room::printFeaturesInRoom()
{
	std::cout << "You can see the following features" << std::endl;
	std::cout << "----------------" << std::endl;
	
	std::string featureName;
	
	for(auto i : featuresInRoom)
	{
			featureName = i->getName();
			
			if(featureName == "answering")
			{
				std::cout << "| " << "answering machine" << std::endl;
			}
			else
			{
				std::cout << "| " << featureName << std::endl;
			}
			
	}
	std::cout << "----------------" << std::endl;
}

