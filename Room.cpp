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

Room::Room(string name, string longDescription, string shortDescription)
{
	setName(name);
	setLongDescription(longDescription);
	setShortDescription(shortDescription);

	alreadyVisited = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Room::getName()
{
	return name;
}

string Room::getLongDescription()
{
	return longDescription;
}

string Room::getShortDescription()
{
	return shortDescription;
}

vector<string>* Room::getAttachedRooms()
{
	return &attachedRooms;
}

vector<string>* Room::getItemsInRoom()
{
	return &itemsInRoom;
}

vector<string>* Room::getFeaturesInRoom()
{
	return &featuresInRoom;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Room::setName(string givenName)
{
	name = givenName;
}

void Room::setLongDescription(string givenLongDescription)
{
	longDescription = givenLongDescription;
}

void Room::setShortDescription(string givenShortDescription)
{
	shortDescription = givenShortDescription;
}

/*******************************************************************************
*		ADD FUNCTIONS
*******************************************************************************/
void Room::addAttachedRoom(string newRoom)
{
	attachedRooms.push_back(newRoom);
}

void Room::addItemInRoom(string newItem)
{
	itemsInRoom.push_back(newItem);
}

void Room::addFeatureInRoom(string newFeature)
{
	featuresInRoom.push_back(newFeature);
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Room::removeItemFromRoom(string removeThisItem)
{
	int index = findVectorIndex(removeThisItem, itemsInRoom);
	itemsInRoom.erase(itemsInRoom.begin() + index);
}

/*******************************************************************************
*		FIND VECTOR INDEX
*******************************************************************************/
int Room::findVectorIndex(string thisString, vector<string> thisVector)
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