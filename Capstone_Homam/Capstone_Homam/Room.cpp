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

Room::Room(string name, string longDescription, string shortDescription, int numRooms)
{
	setName(name);
	setLongDescription(longDescription);
	setShortDescription(shortDescription);

	alreadyVisited = false;
	numAttachedRooms = 0;
	attachedRooms = new Room*[numRooms];
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

int Room::getNumAttachedRooms()
{
	return numAttachedRooms;
}

Room** Room::getAttachedRooms()
{
	return attachedRooms;
}

Item** Room::getItemsInRoom()
{
	return itemsInRoom;
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

void Room::setNumAttachedRooms(int givenNumAttachedRooms)
{
	numAttachedRooms = givenNumAttachedRooms;
}

void Room::addAttachedRoom(Room* newRoom)
{
	attachedRooms[numAttachedRooms] = newRoom;
	numAttachedRooms++;
}

void Room::addItemInRoom(Item* newItem)
{
	itemsInRoom[numItemsInRoom] = newItem;
	numItemsInRoom++;
}