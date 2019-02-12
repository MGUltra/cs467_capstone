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

bool Room::getAlreadyVisited()
{
	return this->alreadyVisited;
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

void Room::setAlreadyVisited(bool newVisit)
{
	this->alreadyVisited = newVisit;
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


/*******************************************************************************
*		TEST FUNCTIONS
*******************************************************************************/



bool Room::isRoomAttached(std::string stringIn)
{
	for(auto i : attachedRooms)
	{
		if(stringIn == i)
			return true;
	}
	
	return false;
}

bool Room::isItemInRoom(std::string stringIn)
{
	for(auto i : itemsInRoom)
	{
		if(stringIn == i)
			return true;
	}
	
	return false;
}

bool Room::isFeatureInRoom(std::string stringIn)
{
	for(auto i : featuresInRoom)
	{
		if(stringIn == i)
			return true;
	}
	
	return false;
}

bool Room::isFeatureExamined(std::string stringIn)
{
	//featuresInRoom
}

bool Room::getAlreadyVisited(std::string stringIn)
{
	return alreadyVisited;
}









/*******************************************************************************
*		PRINT FUNCTIONS
*******************************************************************************/
void Room::printAttachedRooms()
{
	std::cout << "You can see the following rooms from this one" << std::endl;
	std::cout << "----------------" << std::endl;
	for(auto i : attachedRooms)
	{
		std::cout << "| " << i << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

void Room::printItemsInRoom()
{
	std::cout << "You can see the following items" << std::endl;
	std::cout << "----------------" << std::endl;
	
	for(auto i : itemsInRoom)
	{
		std::cout << "| " << i << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

void Room::printFeaturesInRoom()
{
	std::cout << "You can see the following features" << std::endl;
	std::cout << "----------------" << std::endl;
	
	for(auto i : featuresInRoom)
	{
		std::cout << "| " << i << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

