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





/*------------------------------------------------------------------------------
		TEXT FILES
------------------------------------------------------------------------------*/
std::string RoomsFile = "Rooms.txt";
std::string FeaturesFile = "Features.txt";
std::string ItemsFile = "Items.txt";
std::string VictimFile = "Victim.txt";
std::string SuspectsFile = "Suspects.txt";





/*------------------------------------------------------------------------------
		Function Declarations
------------------------------------------------------------------------------*/

// Game Initialization functions
void createRooms(Parser*);
void createFeatures(Parser*);
void createItems(Parser*);
void createVictim(Parser*);
void createSuspects(Parser*);


int findArrayIndex(std::string);
Room* getRoom(string);
void printRooms();
void printRoom(Room*);



// Game Prompts
void currentRoomPrompt(Room*);
void featuresInRoomPrompt(Room*);
void itemsInRoomPrompt(Room*);


// GAME ACTIONS
void exeCommand(std::string, std::string, Player*);
void movePlayer(Player*, std::string);
void dropItem(Player*, std::string);
void takeItem(Player*, std::string);
void inspectObject(Player*, std::string);
void showInventory(Player*);
void helpPlayer(Player*);





void cleanup(Parser*, Player*);

// TEST
void parserTest(Parser*);





/*------------------------------------------------------------------------------
		GAME VARIABLES
------------------------------------------------------------------------------*/

// Ideally we shouldn't use global variables

std::unordered_map<std::string, Item*> itemMap;
std::unordered_map<std::string, Room*> roomMap;
std::unordered_map<std::string, Feature*> featureMap;
std::unordered_map<std::string, Suspect*> suspectMap;
std::vector<std::string> roomTestVector;






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
			
			if(numberOfNouns > 0)
			{
				// iterate through nouns of current verb
				for(int y = 0; y < numberOfNouns; y++)
				{
					exeCommand((*actionsInCurrentMessage)[x]->getText(), (((Verb*)((*actionsInCurrentMessage)[x]))->getIndexNounText(y)), currentPlayer);
				}
			}
			else
			{
				exeCommand((*actionsInCurrentMessage)[x]->getText(), "nonoun", currentPlayer);
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
***                 Game Initializing Functions                    ***
***							      																						 ***
**********************************************************************/



/*------------------------------------------------------------------------------
		CREATE ROOMS
------------------------------------------------------------------------------*/
void createRooms(Parser* commandParser)
{
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(RoomsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Rooms.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	// Turn the string into a stream.
	std::stringstream currentLine(fileLine);
	int numRooms = 0;
	// Stream line into an integer.
	currentLine >> numRooms;

	for (int i = 0; i < numRooms; i++)
	{
		std::string name, longDescription, shortDescription;
		
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
	std::stringstream currentLine1(fileLine);
	
	int numRoomPairings = 0;
	
	// Stream line into an integer.
	currentLine1 >> numRoomPairings;

	for (int i = 0; i < numRoomPairings; i++)
	{
		std::string roomName1, roomName2;

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
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(FeaturesFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Features.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	
	// Turn the string into a stream.
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
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(ItemsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Items.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	
	// Turn the string into a stream.
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
	std::ifstream inputFile;

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
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(SuspectsFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Suspects.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);
	
	// Turn the string into a stream.
	std::stringstream currentLine(fileLine);
	
	int numSuspects = 0;
	
	// Stream line into an integer.
	currentLine >> numSuspects;

	for (int i = 0; i < numSuspects; i++)
	{
		std::string name, description, answer1, answer2;

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
Room* getRoom(std::string roomName)
{
	return roomMap[roomName];
}









/*------------------------------------------------------------------------------
		current Room Prompt
------------------------------------------------------------------------------*/
void currentRoomPrompt(Room* currentRoom)
{
	std::cout << std::endl;
	std::cout << "you are in: " << currentRoom->getName() << std::endl;
	
	// test if room has been visited
	if(currentRoom->getAlreadyVisited() == true)
	{
		// if yes output short description
		std::cout << currentRoom->getShortDescription() << std::endl;
	}
	else
	{
		// if no output long description
		std::cout << currentRoom->getLongDescription() << std::endl;
		
		// and set visited alreadyVisited to true
		currentRoom->setAlreadyVisited(true);
	}
	
}


/*------------------------------------------------------------------------------
		Features in Room Prompt
------------------------------------------------------------------------------*/

void featuresInRoomPrompt(Room* currentRoom)
{
	
}


/*------------------------------------------------------------------------------
		Items in Room Prompt
------------------------------------------------------------------------------*/

void itemsInRoomPrompt(Room* currentRoom)
{
	
}




/*********************************************************************
***					      																								 ***
***                    Game Action Functions                       ***
***							      																						 ***
**********************************************************************/


/*------------------------------------------------------------------------------
		Execute Command
------------------------------------------------------------------------------*/

void exeCommand(std::string verb, std::string noun, Player* currentPlayer)
{
	//std::cout << "Verb:" << verb << std::endl;
	//std::cout << "Noun:" << noun << std::endl;
	
	int functionToCall = 0;
	
	// test verb to determine which function to call
		// pass noun to function called
	if(verb == "move" || verb == "go")
		functionToCall = 1;
	else if(verb == "drop")
		functionToCall = 2;
	else if(verb == "take" || verb == "pick")
		functionToCall = 3;
	else if(verb == "look" || verb == "inspect")
		functionToCall = 4;
	else if(verb == "inventory")
		functionToCall = 5;
	else if(verb == "help")
		functionToCall = 6;

	
	
	switch(functionToCall) {
		
		case 1:	// change rooms
			movePlayer(currentPlayer, noun);
			break;
		case 2: // drop item
			dropItem(currentPlayer, noun);
			break;
		case 3: // pick up item
			takeItem(currentPlayer, noun);
			break;
		case 4: // inspect
			inspectObject(currentPlayer, noun);
			break;
		case 5:	// inventory
			showInventory(currentPlayer);
			break;
		case 6: // help
			helpPlayer(currentPlayer);
			break;
		default: // message unclear then help
			helpPlayer(currentPlayer);
	}
	
}



/*------------------------------------------------------------------------------
		Change Rooms
------------------------------------------------------------------------------*/

void movePlayer(Player* currentPlayer, std::string nounIn)
{
	
	// TODO: Add test for available room, either in this or getLocation
	//	function in the Player class
	
	currentPlayer->setLocation(getRoom(nounIn));
}

/*------------------------------------------------------------------------------
		Drop item
------------------------------------------------------------------------------*/

void dropItem(Player* currentPlayer, std::string nounIn)
{
	
	// TODO: Add test for available Item, either in this or dropItem
	//	function in the Player class
	
	currentPlayer->dropItem(nounIn);
}

/*------------------------------------------------------------------------------
		pick up items
------------------------------------------------------------------------------*/

void takeItem(Player* currentPlayer, std::string nounIn)
{
	// TODO: Add test for available Item, either in this or pickUpItem
	//	function in the Player class
	
	currentPlayer->pickUpItem(nounIn);
}



/*------------------------------------------------------------------------------
		inspect 
------------------------------------------------------------------------------*/

void inspectObject(Player* currentPlayer, std::string nounIn)
{
	// if feature in room
		// test if feature is present in the current room 
		
	// if item in room or players inventory
		// test if item is present in either the current room or inventory 

}


/*------------------------------------------------------------------------------
		display inventory
------------------------------------------------------------------------------*/

void showInventory(Player* currentPlayer)
{
	currentPlayer->showInventory();
}


/*------------------------------------------------------------------------------
		help
------------------------------------------------------------------------------*/

void helpPlayer(Player* currentPlayer)
{
	
}






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
	std::cout << "There are a total of " << numRooms << " rooms." << std::endl;
	
	for (int i = 0; i < numRooms; i++)
	{
		printRoom(roomMap[roomTestVector[i]]);
	}
}



void printRoom(Room* room)
{
	std::cout << "You are in the " << room->getName() << "." << std::endl;
	std::cout << room->getLongDescription() << std::endl;
	std::cout << room->getShortDescription() << std::endl;
	std::cout << "The following rooms are attached: " << std::endl;

	std::vector<std::string>* attachedRooms = room->getAttachedRooms();

	int numAttachedRooms = attachedRooms->size();

	for (int i = 0; i < numAttachedRooms; i++)
	{
		std::cout << attachedRooms->at(i) << std::endl;
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

