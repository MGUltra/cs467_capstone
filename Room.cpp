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

std::vector<std::string>* Room::getAttachedRooms()
{
	return &attachedRooms;
}

std::vector<std::string>* Room::getItemsInRoom()
{
	return &itemsInRoom;
}

std::vector<std::string>* Room::getFeaturesInRoom()
{
	return &featuresInRoom;
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

/*******************************************************************************
*		ADD FUNCTIONS
*******************************************************************************/
void Room::addAttachedRoom(std::string newRoom)
{
	attachedRooms.push_back(newRoom);
}

void Room::addItemInRoom(std::string newItem)
{
	itemsInRoom.push_back(newItem);
}

void Room::addFeatureInRoom(std::string newFeature)
{
	featuresInRoom.push_back(newFeature);
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Room::removeItemFromRoom(std::string removeThisItem)
{
	int index = findVectorIndex(removeThisItem, itemsInRoom);
	itemsInRoom.erase(itemsInRoom.begin() + index);
}

/*******************************************************************************
*		FIND VECTOR INDEX
*******************************************************************************/
int Room::findVectorIndex(std::string thisString, std::vector<std::string> thisVector)
{
	int size = thisVector.size();

	for (int i = 0; i <= size; i++)
	{
		if (thisString == thisVector[i])
		{
			return i;
		}
	}
}