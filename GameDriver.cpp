/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat, Matthew Garner, Kendal Droddy
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
#include "Witness.hpp"
#include "Item.hpp"
#include "Notebook.hpp"
#include "parser.hpp"




/*------------------------------------------------------------------------------
		TEXT FILES
------------------------------------------------------------------------------*/

//should not be global
std::string RoomsFile = "Rooms.txt";
std::string FeaturesFile = "Features.txt";
std::string ItemsFile = "Items.txt";
std::string VictimFile = "Victim.txt";
std::string SuspectsFile = "Suspects.txt";
std::string WitnessesFile = "Witnesses.txt";
std::string MurderNotes = "MurderNotes.txt";





/*------------------------------------------------------------------------------
		Function Declarations
------------------------------------------------------------------------------*/

// Game Initialization functions
void createRooms(Parser*);
void createFeatures(Parser*);
void createItems(Parser*);
void createVictim(Parser*);
void createSuspects(Parser*);
void createWitnesses(Parser*);
void createNotebook();


int findArrayIndex(std::string);
Room* getRoom(string);
void printRooms();
void printRoom(Room*);
void checkLineEndings(std::string*);



// Game Prompts
void currentRoomPrompt(Room*);
void featuresInRoomPrompt(Room*);
void itemsInRoomPrompt(Room*);
void clearScreen();


// GAME ACTIONS
void exeCommand(std::string, std::string, Player*);
void movePlayer(Player*, std::string);
void dropItem(Player*, std::string);
void takeItem(Player*, std::string);
void inspectObject(Player*, std::string);
void showInventory(Player*);
void helpPlayer();

// Cleanup function
void cleanup(Parser*, Player*);







/*------------------------------------------------------------------------------
		GAME VARIABLES
------------------------------------------------------------------------------*/

// Ideally we shouldn't use global variables

std::unordered_map<std::string, Item*> itemMap;
std::unordered_map<std::string, Room*> roomMap;
std::unordered_map<std::string, Feature*> featureMap;
std::unordered_map<std::string, Suspect*> suspectMap;
std::unordered_map<std::string, Witness*> witnessMap;
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
	
	// create features
	
	createFeatures(commandParser);
	
	// create victim
	
	// create suspects

	currentPlayer = new Player("player 1", getRoom("bedroom"));

	
	/*------------------------------------------------------------------------------
		GAME LOOP
	------------------------------------------------------------------------------*/
	do
	{
		
		currentRoomPrompt(currentPlayer->getLocation());
		
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(Type 'help' if you need a list of actions you can take!)" << std::endl;
		
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
		checkLineEndings(&name);

		getline(inputFile, fileLine);
		longDescription = fileLine;
		checkLineEndings(&longDescription);

		getline(inputFile, fileLine);
		shortDescription = fileLine;
		checkLineEndings(&shortDescription);

		roomMap[name] = new Room(name, longDescription, shortDescription);
		
		// populate parser noun set
		commandParser->setNounSet(name);
		commandParser->setLocationSet(name);

		
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
		std::string direction1, direction2;

		// Get the current line as a string.
		getline(inputFile, fileLine);
		roomName1 = fileLine;
		checkLineEndings(&roomName1);

		getline(inputFile, fileLine);
		direction1 = fileLine;
		checkLineEndings(&direction1);

		getline(inputFile, fileLine);
		roomName2 = fileLine;
		checkLineEndings(&roomName2);

		getline(inputFile, fileLine);
		direction2 = fileLine;
		checkLineEndings(&direction2);

		boost::algorithm::to_lower(roomName1);
		boost::algorithm::to_lower(roomName2);
		
		// Get each rooms' index.
		Room* room1 = getRoom(roomName1);
		Room* room2 = getRoom(roomName2);

		// Attach each room to one another.
		room1->addAttachedRoom(room2);
		room2->addAttachedRoom(room1);

		room1->setCardinalDirection(direction2, room2);
		room2->setCardinalDirection(direction1, room1);
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
		std::string name, description, location, itemName;
		Room* room;
		Item* item;

		// feature name
		getline(inputFile, fileLine);
		name = fileLine;
		boost::algorithm::to_lower(name);
		checkLineEndings(&name);
		
		// feature description
		getline(inputFile, fileLine);
		description = fileLine;
		checkLineEndings(&description);

		// room/location name
		getline(inputFile, fileLine);
		location = fileLine;
		checkLineEndings(&location);

		// room pointer
		room = getRoom(location);

		
		// item reveal name
		getline(inputFile, fileLine);
		itemName = fileLine;
		checkLineEndings(&itemName);

		// item pointer
		item = itemMap[itemName];
		
		// create new feature
		featureMap[name] = new Feature(name, description, location, item);

		Feature* newFeature = featureMap[name];
		
		room->addFeatureInRoom(newFeature);
		
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
		Item* item;
		
		getline(inputFile, fileLine);
		name = fileLine;
		boost::algorithm::to_lower(name);
		checkLineEndings(&name);
		
		getline(inputFile, fileLine);
		description = fileLine;
		checkLineEndings(&description);

		getline(inputFile, fileLine);
		forensicAnalysis = fileLine;
		checkLineEndings(&forensicAnalysis);

		getline(inputFile, fileLine);
		location = fileLine;
		checkLineEndings(&location);

		boost::algorithm::to_lower(location);
		
		room = getRoom(location);
		
		itemMap[name] = new Item(name, description, forensicAnalysis);

		// item pointer
		item = itemMap[name];
		
		room->addItemInRoom(item);
		
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
	checkLineEndings(&name);
	
	getline(inputFile, fileLine);
	description = fileLine;
	checkLineEndings(&description);

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
		checkLineEndings(&name);
		
		getline(inputFile, fileLine);
		description = fileLine;
		checkLineEndings(&description);

		getline(inputFile, fileLine);
		answer1 = fileLine;
		checkLineEndings(&answer1);

		getline(inputFile, fileLine);
		answer2 = fileLine;
		checkLineEndings(&answer2);

		suspectMap[name] = new Suspect(name, description, answer1, answer2);
		
		// populate parser noun set
		commandParser->setNounSet(name);		
	}

	// Close inputFile.
	inputFile.close();
}


/*------------------------------------------------------------------------------
CREATE WITNESSES
------------------------------------------------------------------------------*/
void createWitnesses(Parser* commandParser)
{
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(WitnessesFile);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'Witnesses.txt', could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(inputFile, fileLine);

	// Turn the string into a stream.
	std::stringstream currentLine(fileLine);

	int numWitnesses = 0;

	// Stream line into an integer.
	currentLine >> numWitnesses;

	for (int i = 0; i < numWitnesses; i++)
	{
		std::string name, location, description, answer1, answer2;
		Room* room;

		getline(inputFile, fileLine);
		name = fileLine;
		boost::algorithm::to_lower(name);
		checkLineEndings(&name);

		getline(inputFile, fileLine);
		location = fileLine;
		checkLineEndings(&location);

		getline(inputFile, fileLine);
		description = fileLine;
		checkLineEndings(&description);

		getline(inputFile, fileLine);
		answer1 = fileLine;
		checkLineEndings(&answer1);

		getline(inputFile, fileLine);
		answer2 = fileLine;
		checkLineEndings(&answer2);

		room = getRoom(location);

		witnessMap[name] = new Witness(name, description, answer1, answer2, room);

		// populate parser noun set
		commandParser->setNounSet(name);
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
CREATE NOTEBOOK
------------------------------------------------------------------------------*/
void createNotebook()
{
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(MurderNotes);

	// Open the given file.
	if (!inputFile.is_open())
	{
		std::cout << "The file,'MurderNotes.txt', could not be opened.\n";
		return;
	}
	
	std::string name, entry;
	
	// Get the current line as a string.
	getline(inputFile, fileLine);
	name = fileLine;
	checkLineEndings(&name);

	getline(inputFile, fileLine);
	entry = fileLine;
	checkLineEndings(&entry);

	Notebook playerNotebook;
	playerNotebook.setEntry(name, entry);

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
	std::cout << "You are in: " << currentRoom->getName() << std::endl;
	
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
	
	
	// display rooms
	currentRoom->printAttachedRooms();
	
	// display features
	currentRoom->printFeaturesInRoom();
	
	// display items
	currentRoom->printItemsInRoom();
	
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

	clearScreen();
	
	int functionToCall = 0;
	
	// test verb to determine which function to call
		// pass noun to function called
	if(verb == "move" || verb == "go")
		functionToCall = 1;
	else if(verb == "drop" || verb == "remove")
		functionToCall = 2;
	else if(verb == "take" || verb == "pick")
		functionToCall = 3;
	else if(verb == "look" || verb == "inspect" || verb == "examine")
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
			helpPlayer();
			break;
		default: // message unclear then help
			helpPlayer();
	}
	
}



/*------------------------------------------------------------------------------
		Change Rooms
------------------------------------------------------------------------------*/
void movePlayer(Player* currentPlayer, std::string nounIn)
{
	
	// TODO: Add test for available room, either in this or getLocation
	//	function in the Player class
	Room* roomPtr = currentPlayer->getLocation();
	
	if(roomPtr->isRoomAttached(getRoom(nounIn)) == true)
	{
		currentPlayer->setLocation(getRoom(nounIn));
	}
	else
	{
		std::cout << "You can not get there from " << roomPtr->getName() << "." << std::endl;
	}
	
}

/*------------------------------------------------------------------------------
		Drop item
------------------------------------------------------------------------------*/
void dropItem(Player* currentPlayer, std::string nounIn)
{
	currentPlayer->dropItem(itemMap[nounIn]);
}

/*------------------------------------------------------------------------------
		pick up items
------------------------------------------------------------------------------*/
void takeItem(Player* currentPlayer, std::string nounIn)
{
	currentPlayer->pickUpItem(itemMap[nounIn]);

}


/*------------------------------------------------------------------------------
		inspect 
------------------------------------------------------------------------------*/
void inspectObject(Player* currentPlayer, std::string nounIn)
{
	// cannot access item or feature descriptions from player/room/inventory class
	// because theire vectors contain only strings... will have to use map global 
	// variable.
	
	
	if(featureMap.find(nounIn) != featureMap.end()) // test if feature 
	{
		Room* roomPtr = currentPlayer->getLocation();
		
		Feature* featurePtr = featureMap[nounIn];
		
		// test if feature is present in the current room 
		if(roomPtr->isFeatureInRoom(featurePtr) == true)
		{
			// test if feature already inspected
			if(roomPtr->isFeatureExamined(featurePtr) == false)
			{
				featurePtr->inspected();
			}
			else
			{
				std::cout << "You've already examined " << featurePtr->getName() << "." << std::endl;
			}
		}
	}
	else if(itemMap.find(nounIn) != itemMap.end()) // test if item
	{
	// if item in room or players inventory
		// test if item is present in either the current room or inventory 
		Room* roomPtr = currentPlayer->getLocation();
		
		Item* itemPtr = itemMap[nounIn];
		
		if(currentPlayer->itemInInventory(itemPtr) == true || roomPtr->isItemInRoom(itemPtr) == true)
		{
			
			
			// test if item has gone to the lab yet to get mundane or analysis response
			
			if(itemPtr->getAnalyzed() == true)
				std::cout << itemPtr->getForensicAnalysis() << std::endl;
			else
				std::cout << itemPtr->getDescription() << std::endl;
			
		}
		else
		{
			std::cout << "You can not learn anything from that" << std::endl;
		}
	}
	else
	{
		std::cout << "You can not learn anything from that" << std::endl;
	}		
}

/*------------------------------------------------------------------------------
		display inventory
------------------------------------------------------------------------------*/
void showInventory(Player* currentPlayer)
{
	// test if empty
		// prompt if so
	
	currentPlayer->showInventory();
}


/*------------------------------------------------------------------------------
		Help - Displays the list of actions that the player can take.
------------------------------------------------------------------------------*/

void helpPlayer()
{
	std::cout << "Here is the lits of actions you are able to take:\n" << std::endl;

	std::cout << "\t(N) = Not yet implemented.\n" << std::endl;

	std::cout << "\t\tBasic Actions." << std::endl;
	std::cout << "\tLook - repeats the long description of the current room." << std::endl;
	std::cout << "\tLook At <Object> - prints a description of the object (including inventory items!)." << std::endl;
	std::cout << "\tGo <Room> - Player moves to the given location if possible." << std::endl;
	std::cout << "\tTake <Object> - Adds the item to your inventory." << std::endl;
	std::cout << "\tHelp - Brings up this list of actions!" << std::endl;
	std::cout << "\tInventory - Displays the list of items you currently have in your inventory.\n" << std::endl;
	
	std::cout << "\t\tOther Actions." << std::endl;
	std::cout << "\tDrop <Object> - Drops the item in your current room." << std::endl;
	std::cout << "\t(N)Interrogate <Suspect> - Ask the hard hitting questions." << std::endl;
	std::cout << "\t(N)Take Statement - Take notes from a witness." << std::endl;
	std::cout << "\t(N)Take Sample - Take a sample of hair/blood/saliva." << std::endl;
	std::cout << "\t(N)Magnify <Object> - Take a closer look at an object." << std::endl;
	std::cout << "\t(N)Hack Computer - Search a suspect's computer for evidence." << std::endl;
	std::cout << "\t(N)Analyze <Object> - Submit an item for forensic analysis. Must be in Forensics Lab." << std::endl;
	std::cout << "\t(N)Hint - Get a hint for your current room." << std::endl;

}


void clearScreen()
{
	std::cout << "\033[2J\033[1;1H";
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
		CHECK LINE ENDINGS
------------------------------------------------------------------------------*/
void checkLineEndings(std::string* thisString)
{
	int length = thisString->length();

	// CHECK EOL AND REMOVE
	if (thisString->at(length - 2) == '\r')
	{
		thisString->erase(thisString->at(length - 2));
		//std::cout << "\\r removed" << std::endl;
	}
	//else
		//std::cout << "Nothing removed" << std::endl;
}

/*------------------------------------------------------------------------------
		Test Functions
------------------------------------------------------------------------------*/
/*
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

	std::vector<Room*>* attachedRooms = room->getAttachedRooms();

	int numAttachedRooms = attachedRooms->size();

	for (int i = 0; i < numAttachedRooms; i++)
	{
		std::cout << attachedRooms->at(i) << std::endl;
	}
}
*/


