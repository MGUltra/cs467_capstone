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
#include "parser.hpp"

using namespace std;

/*------------------------------------------------------------------------------
		TEXT FILES
------------------------------------------------------------------------------*/
string RoomsFile = "Rooms.txt";
string FeaturesFile = "Features.txt";
string ItemsFile = "Items.txt";
string VictimFile = "Victim.txt";
string SuspectsFile = "Suspects.txt";

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
unordered_map<string, Item*> itemMap;
unordered_map<string, Room*> roomMap;
unordered_map<string, Feature*> featureMap;
unordered_map<string, Suspect*> suspectMap;
vector<string> roomTestVector;

Parser* commandParser;

/*------------------------------------------------------------------------------
									MAIN
------------------------------------------------------------------------------*/
int main()
{
	// instantiate parser object
	commandParser = new Parser();
	
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

	inputFile.open(RoomsFile);

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
	int numRooms = 0;
	// Stream line into an integer.
	currentLine >> numRooms;

	for (int i = 0; i < numRooms; i++)
	{
		string name, longDescription, shortDescription;
		
		// Get the current line as a string.
		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		longDescription = fileLine;

		getline(inputFile, fileLine);
		shortDescription = fileLine;

		roomMap[name] = new Room(name, longDescription, shortDescription);
		
		// populate parser noun set
		commandParser->setNounSet(name);
		
		// Debug
		roomTestVector.push_back(name);
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
		string roomName1, roomName2;

		// Get the current line as a string.
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

	string fileLine;

	inputFile.open(FeaturesFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Features.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	stringstream currentLine(fileLine);
	int numFeatures = 0;
	// Stream line into an integer.
	currentLine >> numFeatures;

	for (int i = 0; i < numFeatures; i++)
	{
		string name, description, location;
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
		
		// populate parser noun set
		commandParser->setNounSet(name);
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

	inputFile.open(ItemsFile);

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

	for (int i = 0; i < numItems; i++)
	{
		string name, description, forensicAnalysis, location;
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
		
		// populate parser noun set
		commandParser->setNounSet(name);
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

	inputFile.open(VictimFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Victim.txt', could not be opened.\n";
		return;
	}

	string name, description;

	getline(inputFile, fileLine);
	name = fileLine;

	getline(inputFile, fileLine);
	description = fileLine;

	Victim newVictim = Victim(name, description);
	
	// populate parser noun set
	commandParser->setNounSet(name);

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

	inputFile.open(SuspectsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		cout << "The file,'Suspects.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	stringstream currentLine(fileLine);
	int numSuspects = 0;
	// Stream line into an integer.
	currentLine >> numSuspects;

	for (int i = 0; i < numSuspects; i++)
	{
		string name, description, answer1, answer2;

		getline(inputFile, fileLine);
		name = fileLine;

		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		answer1 = fileLine;

		getline(inputFile, fileLine);
		answer2 = fileLine;

		suspectMap[name] = new Suspect(name, description, answer1, answer2);
		
		// populate parser noun set
		commandParser->setNounSet(name);		
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
		GET ROOM
------------------------------------------------------------------------------*/
Room* getRoom(string roomName)
{
	return roomMap[roomName];
}



void printRooms()
{
	int numRooms = roomTestVector.size();
	cout << "There are a total of " << numRooms << " rooms." << endl;
	
	for (int i = 0; i < numRooms; i++)
	{
		printRoom(roomMap[roomTestVector[i]]);
	}
}

void printRoom(Room* room)
{
	cout << "You are in the " << room->getName() << "." << endl;
	cout << room->getLongDescription() << endl;
	cout << room->getShortDescription() << endl;
	cout << "The following rooms are attached: " << endl;

	vector<string>* attachedRooms = room->getAttachedRooms();

	int numAttachedRooms = attachedRooms->size();

	for (int i = 0; i < numAttachedRooms; i++)
	{
		cout << attachedRooms->at(i) << endl;
	}
}