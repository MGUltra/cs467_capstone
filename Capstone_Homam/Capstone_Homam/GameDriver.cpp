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
#include <unordered_map>

#include "Room.hpp"
#include "Player.hpp"
#include "Victim.hpp"
#include "Suspect.hpp"

using namespace std;

/*------------------------------------------------------------------------------
		TEXT FILES
------------------------------------------------------------------------------*/
std::string RoomsFile = "Rooms.txt";
std::string FeaturesFile = "Features.txt";
std::string ItemsFile = "Items.txt";
std::string VictimFile = "Victim.txt";
std::string SuspectsFile = "Suspects.txt";

/*------------------------------------------------------------------------------
		DEFINITIONS
------------------------------------------------------------------------------*/
void createRooms();
void createFeatures();
void createItems();
void createVictim();
void createSuspects();
int findArrayIndex(std::string);
Room* getRoom(std::string);
void printRooms();
void printRoom(Room*);

/*------------------------------------------------------------------------------
		GAME VARIABLES
------------------------------------------------------------------------------*/
std::unordered_map<std::string, Item*> itemMap;
std::unordered_map<std::string, Room*> roomMap;
std::unordered_map<std::string, Feature*> featureMap;
std::unordered_map<std::string, Suspect*> suspectMap;
std::vector<std::string> roomTestVector;

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

	std::string fileLine;

	inputFile.open(RoomsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Rooms.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a std::string.
	getline(inputFile, fileLine);
	// Turn the std::string into a stream.
	std::stringstream currentLine(fileLine);
	int numRooms = 0;
	// Stream line into an integer.
	currentLine >> numRooms;

	for (int i = 0; i < numRooms; i++)
	{
		std::string name, longDescription, shortDescription;
		
		// Get the current line as a std::string.
		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		longDescription = fileLine;

		getline(inputFile, fileLine);
		shortDescription = fileLine;

		roomMap[name] = new Room(name, longDescription, shortDescription);

		// Debug
		roomTestVector.push_back(name);
	}

/*------ATTACH ROOMS----------------------------------------------------------*/
	// Get next line as a std::string.
	getline(inputFile, fileLine);
	// Turn the std::string into a stream.
	std::stringstream currentLine1(fileLine);
	int numRoomPairings = 0;
	// Stream line into an integer.
	currentLine1 >> numRoomPairings;

	for (int i = 0; i < numRoomPairings; i++)
	{
		std::string roomName1, roomName2;

		// Get the current line as a std::string.
		getline(inputFile, fileLine);
		roomName1 = fileLine;

		getline(inputFile, fileLine);
		roomName2 = fileLine;

		// Get each rooms' index.
		Room* room1 = getRoom(roomName1);
		Room* room2 = getRoom(roomName2);

		// Attach each room to one another.
		room1->addAttachedRoom(roomName2);
		room2->addAttachedRoom(roomName1);
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

	std::string fileLine;

	inputFile.open(FeaturesFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Features.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a std::string.
	getline(inputFile, fileLine);
	// Turn the std::string into a stream.
	std::stringstream currentLine(fileLine);
	int numFeatures = 0;
	// Stream line into an integer.
	currentLine >> numFeatures;

	for (int i = 0; i < numFeatures; i++)
	{
		std::string name, description, location;
		Room* room;

		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		location = fileLine;

		room = getRoom(location);

		featureMap[name] = new Feature(name, description, location);

		room->addFeatureInRoom(name);
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

	std::string fileLine;

	inputFile.open(ItemsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Items.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a std::string.
	getline(inputFile, fileLine);
	// Turn the std::string into a stream.
	std::stringstream currentLine(fileLine);
	int numItems = 0;
	// Stream line into an integer.
	currentLine >> numItems;

	for (int i = 0; i < numItems; i++)
	{
		std::string name, description, forensicAnalysis, location;
		Room* room;
		
		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		forensicAnalysis = fileLine;

		getline(inputFile, fileLine);
		location = fileLine;

		room = getRoom(location);

		itemMap[name] = new Item(name, description, forensicAnalysis);

		room->addItemInRoom(name);
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

	std::string fileLine;

	inputFile.open(VictimFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Victim.txt', could not be opened.\n";
		return;
	}

	std::string name, description;

	getline(inputFile, fileLine);
	name = fileLine;

	getline(inputFile, fileLine);
	description = fileLine;

	Victim newVictim = Victim(name, description);

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		CREATE SUSPECTS
------------------------------------------------------------------------------*/
void createSuspects()
{
	ifstream inputFile;

	std::string fileLine;

	inputFile.open(SuspectsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Suspects.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a std::string.
	getline(inputFile, fileLine);
	// Turn the std::string into a stream.
	std::stringstream currentLine(fileLine);
	int numSuspects = 0;
	// Stream line into an integer.
	currentLine >> numSuspects;

	for (int i = 0; i < numSuspects; i++)
	{
		std::string name, description, answer1, answer2;

		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		answer1 = fileLine;

		getline(inputFile, fileLine);
		answer2 = fileLine;

		suspectMap[name] = new Suspect(name, description, answer1, answer2);
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		GET ROOM
------------------------------------------------------------------------------*/
Room* getRoom(std::string roomName)
{
	return roomMap[roomName];
}



void printRooms()
{
	int numRooms = roomTestVector.size();
	std::cout << "There are a total of " << numRooms << " rooms." << endl;
	
	for (int i = 0; i < numRooms; i++)
	{
		printRoom(roomMap[roomTestVector[i]]);
	}
}

void printRoom(Room* room)
{
	std::cout << "You are in the " << room->getName() << "." << endl;
	std::cout << room->getLongDescription() << endl;
	std::cout << room->getShortDescription() << endl;
	std::cout << "The following rooms are attached: " << endl;

	std::vector<std::string>* attachedRooms = room->getAttachedRooms();

	int numAttachedRooms = attachedRooms->size();

	for (int i = 0; i < numAttachedRooms; i++)
	{
		std::cout << attachedRooms->at(i) << endl;
	}
}