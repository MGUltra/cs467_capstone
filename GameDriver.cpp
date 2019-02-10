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
		Function Declarations
------------------------------------------------------------------------------*/
void createRooms(Parser*);
void createFeatures(Parser*);
void createItems(Parser*);
void createVictim(Parser*);
void createSuspects(Parser*);


int findArrayIndex(string);
Room* getRoom(string);
void printRooms();
void printRoom(Room*);

void currentRoomPrompt(Room*);
void executeCommand(std::string, std::string);


void cleanup(Parser*, Player*);

// TEST
void parserTest(Parser*);





/*------------------------------------------------------------------------------
		GAME VARIABLES
------------------------------------------------------------------------------*/

// Ideally we shouldn't use global variables

unordered_map<string, Item*> itemMap;
unordered_map<string, Room*> roomMap;
unordered_map<string, Feature*> featureMap;
unordered_map<string, Suspect*> suspectMap;
vector<string> roomTestVector;






/*********************************************************************
***					      																								 ***
***                             MAIN                               ***
***							      																						 ***
**********************************************************************/
int main()
{
	
	/*------------------------------------------------------------------------------
		GAME VARIABLES
	------------------------------------------------------------------------------*/
	std::string inputString;
	
	std::vector<Word*>* actionsInCurrentMessage;
	
	int numberOfActions, numberOfNouns;
	
	bool exitStatus = false;
	
	Parser* commandParser;
	
	Player* currentPlayer;
	
	/*------------------------------------------------------------------------------
		INITIALIZE GAME
	------------------------------------------------------------------------------*/	
	commandParser = new Parser();
	
	createRooms(commandParser);
	
	createItems(commandParser);

	currentPlayer = new Player("player 1", getRoom("bedroom"));

	
	/*------------------------------------------------------------------------------
		GAME LOOP
	------------------------------------------------------------------------------*/
	do
	{
		currentRoomPrompt(currentPlayer->getLocation());
		
		std::cout << "what would you like to do?" << std::endl;
		
		getline(cin, inputString);
		
		if(inputString == "exit")
		{
			break;
		}
		
		// Call newMessage to run parser on input
		commandParser->newMessage(inputString);
		
		// get pointer to vector of word pointers
		actionsInCurrentMessage = commandParser->getGameActions();
		
		// number of actions will be number of verbs
		// verbs may have multiple nouns
		numberOfActions = commandParser->getNumActions();
		
		// Iterate through verbs
		for(int x = 0; x < numberOfActions; x++)
		{
			// get number of nouns for current verb
			numberOfNouns = (((Verb*)((*actionsInCurrentMessage)[x]))->getNumberOfNouns());
			
			// iterate through nouns of current verb
			for(int y = 0; y < numberOfNouns; y++)
			{
				executeCommand((*actionsInCurrentMessage)[x]->getText(), (((Verb*)((*actionsInCurrentMessage)[x]))->getIndexNounText(y)));
			}
			
		}
		
		
		
	}while(exitStatus != true);


	//printRooms();
	//parserTest(commandParser);



	cleanup(commandParser, currentPlayer);
	


	return 0;
}






/*********************************************************************
***					      																								 ***
***                     Function Definitions                       ***
***							      																						 ***
**********************************************************************/



/*------------------------------------------------------------------------------
		CREATE ROOMS
------------------------------------------------------------------------------*/
void createRooms(Parser* commandParser)
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

		boost::algorithm::to_lower(name);
		
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

		boost::algorithm::to_lower(roomName1);
		boost::algorithm::to_lower(roomName2);
		
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
void createFeatures(Parser* commandParser)
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

		boost::algorithm::to_lower(name);
		
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
void createItems(Parser* commandParser)
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

		boost::algorithm::to_lower(name);
		
		getline(inputFile, fileLine);
		description = fileLine;

		getline(inputFile, fileLine);
		forensicAnalysis = fileLine;

		getline(inputFile, fileLine);
		location = fileLine;

		boost::algorithm::to_lower(location);
		
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
void createVictim(Parser* commandParser)
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

	boost::algorithm::to_lower(name);
	
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
void createSuspects(Parser* commandParser)
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

		boost::algorithm::to_lower(name);
		
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




/*------------------------------------------------------------------------------
		current Room Prompt
------------------------------------------------------------------------------*/
void currentRoomPrompt(Room* currentRoom)
{
	std::cout << "you are in: " << currentRoom->getName() << std::endl;
	
	// test if room has been visited
	
		// if yes output short description
		
		// if no output long description
		// and set visited alreadyVisited to true

		
}





/*------------------------------------------------------------------------------
		Execute Command
------------------------------------------------------------------------------*/

void executeCommand(std::string verb, std::string noun)
{
	std::cout << "Verb:" << verb << std::endl;
	std::cout << "Noun:" << noun << std::endl;
	
	// test verb to determine which function to call
	
		// pass noun to function called
	
	
	
}



/*------------------------------------------------------------------------------
		Change Rooms
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
		Drop item
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
		pick up items
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
		display inventory
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
		inspect 
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
		help
------------------------------------------------------------------------------*/








/*------------------------------------------------------------------------------
		cleanup
------------------------------------------------------------------------------*/

void cleanup(Parser* currentParser, Player* currentPlayer)
{
	// Deletes all instantiated class Word derived objects
	currentParser->clearMessage();
	
	delete currentParser;
	delete currentPlayer;
	
	// TODO:: FINISH CLEANUP FUNCTION
	
}



/*------------------------------------------------------------------------------
		Test Functions
------------------------------------------------------------------------------*/

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


void parserTest(Parser* commandParser)
{
	commandParser->setVerbSet("drop");
	commandParser->setVerbSet("take");
	commandParser->setVerbSet("move");
	commandParser->setVerbSet("go");
	
	commandParser->setNounSet("controller");
	commandParser->setNounSet("cigarette");
	commandParser->setNounSet("photograph");
	commandParser->setNounSet("taco");
	
	std::string inputMessage = "  Go to basement  Drop the cigarette, and then take the taco, photograph and controller. Move to basement    ";
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Input string" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << inputMessage << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	commandParser->newMessage(inputMessage);
	
	std::cout << std::endl;
	
	std::cout << "input string after Boost library tolower and trim" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << commandParser->getMessageIn() << std::endl;
	
	std::cout << std::endl;
	
	std::cout << "input string after being parsed by words" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	
	commandParser->printParsedStrings();
	
	std::cout << std::endl;
	
	std::cout << "input string after being Grouped by Verb/Noun Associations" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	
	commandParser->printVerbNounGroupings();
	
	std::cout << std::endl;
	
	commandParser->clearMessage();
	
}

