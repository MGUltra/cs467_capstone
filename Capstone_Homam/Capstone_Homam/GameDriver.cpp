/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Item.hpp"
#include "Room.hpp"

using namespace std;

/*------------------------------------------------------------------------------
		TEXT FILES
------------------------------------------------------------------------------*/
string Rooms = "Rooms.txt";
string Features = "Features.txt";
string Items = "Items.txt";
string Victim = "Victim.txt";
string Suspects = "Suspects.txt";

/*------------------------------------------------------------------------------
		DEFINITIONS
------------------------------------------------------------------------------*/
void createRooms();
void createFeatures();
void createItems();
void createVictim();
void createSuspects();
int findArrayIndex(string);
Room* getRoom(string);
void printRooms();
void printRoom(Room*);

/*------------------------------------------------------------------------------
		GAME VARIABLES
------------------------------------------------------------------------------*/
Room** roomArray;
int numRooms;
Item** itemArray;

/*------------------------------------------------------------------------------
									MAIN
------------------------------------------------------------------------------*/
int main()
{
	createRooms();
	printRooms();

	return 0;
}

/*------------------------------------------------------------------------------
		CREATE ROOMS
------------------------------------------------------------------------------*/
void createRooms()
{
	ifstream inputFile;

	string fileLine;

	inputFile.open(Rooms);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Rooms.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	stringstream currentLine(fileLine);
	numRooms = 0;
	// Stream line into an integer.
	currentLine >> numRooms;

	roomArray = new Room*[numRooms];

	for (int i = 0; i < numRooms; i++)
	{
		string name, longDescription, shortDescription;
		
		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		longDescription = fileLine;

		getline(inputFile, fileLine);
		shortDescription = fileLine;

		roomArray[i] = new Room(name, longDescription, shortDescription, numRooms);
	}

/*------ATTACH ROOMS----------------------------------------------------------*/
	// Get next line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	stringstream currentLine1(fileLine);
	int numRoomPairings = 0;
	// Stream line into an integer.
	currentLine1 >> numRoomPairings;

	for (int i = 0; i < numRoomPairings; i++)
	{
		// Get the current line as a string.
		getline(inputFile, fileLine);
		// Turn the string into a stream.
		stringstream nextLine(fileLine);

		string roomName1, roomName2;
		nextLine >> roomName1;
		nextLine >> roomName2;

		// Get each rooms' index.
		Room* room1 = getRoom(roomName1);
		Room* room2 = getRoom(roomName2);

		// Attach each room to one another.
		room1->addAttachedRoom(room2);
		room2->addAttachedRoom(room1);
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		CREATE FEATURES
------------------------------------------------------------------------------*/
void createFeatures()
{
	ifstream inputFile;

	string fileLine;

	inputFile.open(Features);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Features.txt', could not be opened.\n";
		return;
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		CREATE ITEMS
------------------------------------------------------------------------------*/
void createItems()
{
	ifstream inputFile;

	string fileLine;

	inputFile.open(Items);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Items.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	stringstream currentLine(fileLine);
	int numItems = 0;
	// Stream line into an integer.
	currentLine >> numItems;

	itemArray = new Item*[numItems];

	for (int i = 0; i < numItems; i++)
	{
		string name, description, forensicAnalysis, stringRoom;
		Room* room;
		
		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		forensicAnalysis = fileLine;

		getline(inputFile, fileLine);
		stringRoom = fileLine;

		room = getRoom(stringRoom);

		itemArray[i] = new Item(name, description, forensicAnalysis);

		room->addItemInRoom(itemArray[i]);
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		CREATE VICTIM
------------------------------------------------------------------------------*/
void createVictim()
{
	ifstream inputFile;

	string fileLine;

	inputFile.open(Victim);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Victim.txt', could not be opened.\n";
		return;
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		CREATE SUSPECTS
------------------------------------------------------------------------------*/
void createSuspects()
{
	ifstream inputFile;

	string fileLine;

	inputFile.open(Suspects);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Suspects.txt', could not be opened.\n";
		return;
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		FIND ROOM ARRAY INDEX
------------------------------------------------------------------------------*/
int findArrayIndex(string givenName)
{
	// Loop through all rooms until the name is found.
	for (int i = 0; i < numRooms; i++)
	{
		if (roomArray[i]->getName() == givenName)
		{
			return i;
		}
	}
}

Room* getRoom(string roomName)
{
	return roomArray[findArrayIndex(roomName)];
}

void printRooms()
{
	cout << "There are a total of " << numRooms << " rooms." << endl;
	
	for (int i = 0; i < numRooms; i++)
	{
		printRoom(roomArray[i]);
	}
}

void printRoom(Room* room)
{
	cout << "You are in the " << room->getName() << "." << endl;
	cout << room->getLongDescription() << endl;
	cout << room->getShortDescription() << endl;
	cout << "The following rooms are attached: " << endl;

	Room** attachedRooms = room->getAttachedRooms();

	for (int i = 0; i < room->getNumAttachedRooms(); i++)
	{
		cout << attachedRooms[i]->getName() << endl;
	}
}