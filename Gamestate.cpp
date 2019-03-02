
#include "Gamestate.hpp"

/***************************************************************
***																													 ***
***                      Constructor                         ***
***																													 ***
****************************************************************/

Gamestate::Gamestate()
	: itemMap({});
	, roomMap({});
	, featureMap({});
	, suspectMap({});
	, witnessMap({});
	, roomTestVector();
	, RoomsFile = "Rooms.txt";
	, FeaturesFile = "Features.txt";
	, ItemsFile = "Items.txt";
	, VictimFile = "Victim.txt";
	, SuspectsFile = "Suspects.txt";
	, WitnessesFile = "Witnesses.txt";
	, MurderNotes = "MurderNotes.txt";
	, inputString = "";
	, actionsInCurrentMessage();
	, numberOfActions(0);
	, numberOfNouns(0);
	, exitStatus = false;
	, commandParser();
	, currentPlayer();
	, playerNotebook();
{
	
}




/***************************************************************
***																													 ***
***                      Destructor                          ***
***																													 ***
****************************************************************/


Gamestate::~Gamestate()
{
	
}



void Gamestate::playGame()
{
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
		
		clearScreen();
		
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
}




/*********************************************************************
***					      																								 ***
***                 Game Initializing Functions                    ***
***							      																						 ***
**********************************************************************/

void Gamestate::createGame()
{
	/*------------------------------------------------------------------------------
		INITIALIZE GAME
	------------------------------------------------------------------------------*/	
	//commandParser = new Parser();
	
	
	// Create Rooms
	createRooms();
	
	// create suspects
	createSuspects();
	
	// Create Items - requires rooms and suspects be completed
	createItems();
	

	// create features - requires rooms and items be completed	
	createFeatures();
	
	// create victim
	


	//this->currentPlayer = new Player("player 1", getRoom("bedroom"));
}

/*------------------------------------------------------------------------------
		CREATE ROOMS
------------------------------------------------------------------------------*/
void Gamestate::createRooms()
{
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(this->RoomsFile);

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
void Gamestate::createFeatures()
{
	std::ifstream inputFile;

	std::string fileLine;

	inputFile.open(this->FeaturesFile);

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
void Gamestate::createItems()
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
		std::string name, description, forensicAnalysis, location, suspectString;
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

		getline(inputFile, fileLine);
		suspectString = fileLine;
		checkLineEndings(&suspectString);

		Suspect* suspect = suspectMap[suspectString];
		
		room = getRoom(location);
		
		itemMap[name] = new Item(name, description, forensicAnalysis, suspect);

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
void Gamestate::createVictim()
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
void Gamestate::createSuspects()
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
void Gamestate::createWitnesses()
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
void Gamestate::createNotebook()
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

	playerNotebook.setEntry(name, entry);

	// Close inputFile.
	inputFile.close();
}



/*------------------------------------------------------------------------------
		GET ROOM
------------------------------------------------------------------------------*/
Room* Gamestate::getRoom(std::string roomName)
{
	if(roomName == "nonoun")
		return NULL;
	
	return this->roomMap[roomName];
}









/*------------------------------------------------------------------------------
		current Room Prompt
------------------------------------------------------------------------------*/
void Gamestate::currentRoomPrompt(Room* currentRoom)
{
	
	std::ifstream inFile;
  std::string input;
	
	//std::cout << std::endl;
	//std::cout << "You are in: " << currentRoom->getName() << std::endl;
	
	// test if room has been visited
	if(currentRoom->getAlreadyVisited() == true)
	{
		// if yes output short description
		inFile.open(currentRoom->getShortDescription(), std::ios::out);
		readFileDefault(inFile);
		inFile.close();
		
		// if yes output short description
		//std::cout << currentRoom->getShortDescription() << std::endl;
	}
	else
	{
		// if no output long description
		inFile.open(currentRoom->getLongDescription(), std::ios::out);
		readFileDefault(inFile);
		inFile.close();
		
		// if no output long description
		//std::cout << currentRoom->getLongDescription() << std::endl;
		
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
void Gamestate::featuresInRoomPrompt(Room* currentRoom)
{
	
}


/*------------------------------------------------------------------------------
		Items in Room Prompt
------------------------------------------------------------------------------*/
void Gamestate::itemsInRoomPrompt(Room* currentRoom)
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
void Gamestate::exeCommand(std::string verb, std::string noun)
{

	//clearScreen();
	
	int functionToCall = 0;
	
	// test verb to determine which function to call
		// pass noun to function called
	if(verb == "move" || verb == "go" || verb == "north" || verb == "south" || verb == "east" || verb == "west")
		functionToCall = 1;
	else if(roomMap.find(verb) != roomMap.end())
		functionToCall = 1;
	else if(verb == "drop" || verb == "remove")
		functionToCall = 2;
	else if(verb == "take" || verb == "pick")
		functionToCall = 3;
	else if(verb == "look" || verb == "inspect" || verb == "examine")
		functionToCall = 4;
	else if(verb == "inventory")
		functionToCall = 5;
	else if(verb == "test" || verb == "analyze")
		functionToCall = 6;
	else if(verb == "help")
		functionToCall = 7;

	
	
	switch(functionToCall) {
		
		case 1:	// change rooms
			movePlayer(verb, noun);
			break;
		case 2: // drop item
			dropItem(noun);
			break;
		case 3: // pick up item
			takeItem(noun);
			break;
		case 4: // inspect
			inspectObject(noun);
			break;
		case 5:	// inventory
			showInventory();
			break;
		case 6: // analyze
			analyzeItem(noun);
			break;
		case 7: // help
			helpPlayer();
			break;
		default: // message unclear then help
			helpPlayer();
	}
	
}



/*------------------------------------------------------------------------------
		Change Rooms
------------------------------------------------------------------------------*/
void Gamestate::movePlayer(std::string verbIn, std::string nounIn)
{
	
	// TODO: Add test for available room, either in this or getLocation
	//	function in the Player class
	Room* roomPtr = currentPlayer.getLocation();
	
	
	// Single word room name
	if(roomMap.find(verbIn) != roomMap.end())
	{
		if(roomPtr->isRoomAttached(getRoom(verbIn)) == true)
		{
			currentPlayer.setLocation(getRoom(verbIn));
		}
		else
		{
			std::cout << "You can not get there from " << roomPtr->getName() << "." << std::endl;
		}
		
		return;
	}
	// Single word direction
	else if(verbIn == "north" || verbIn == "south" || verbIn == "east" || verbIn == "west") 
	{
		Room* newRoom = roomPtr->getCardinalDirection(verbIn);
		
		if(newRoom != NULL)
			currentPlayer.setLocation(newRoom);
		else
			std::cout << "You can not go " << verbIn << " from " << roomPtr->getName() << "." << std::endl;
		
		return;
		
	}
	// cardinal direction as noun
	else if(nounIn == "north" || nounIn == "south" || nounIn == "east" || nounIn == "west") 
	{
		Room* newRoom = roomPtr->getCardinalDirection(nounIn);
		
		if(newRoom != NULL)
			currentPlayer.setLocation(newRoom);
		else
			std::cout << "You can not go " << nounIn << " from " << roomPtr->getName() << "." << std::endl;
		
		return;
	}
	// room name as noun
	else if(roomPtr->isRoomAttached(getRoom(nounIn)) == true)
	{
		currentPlayer.setLocation(getRoom(nounIn));
		
		return;
	}
	// counldn't find room name
	else
	{
		std::cout << "You can not get there from " << roomPtr->getName() << "." << std::endl;
		
		return;
	}
	
}

/*------------------------------------------------------------------------------
		Drop item
------------------------------------------------------------------------------*/
void Gamestate::dropItem(std::string nounIn)
{
	
	// test if item
	if(this->itemMap.find(nounIn) != this->itemMap.end())
		this->currentPlayer.dropItem(this->itemMap[nounIn]);
	else
		std::cout << "| you cannot drop " << nounIn << std::endl;
}

/*------------------------------------------------------------------------------
		pick up items
------------------------------------------------------------------------------*/
void Gamestate::takeItem(std::string nounIn)
{
	// test if item
	if(this->itemMap.find(nounIn) != this->itemMap.end())
		this->currentPlayer.pickUpItem(itemMap[nounIn]);
	else
		std::cout << "| you cannot pick up " << nounIn << std::endl;
}


/*------------------------------------------------------------------------------
		inspect 
------------------------------------------------------------------------------*/
void Gamestate::inspectObject(Player* currentPlayer, std::string nounIn)
{
	// cannot access item or feature descriptions from player/room/inventory class
	// because theire vectors contain only strings... will have to use map global 
	// variable.
	
	
	if(this->featureMap.find(nounIn) != this->featureMap.end()) // test if feature 
	{
		Room* roomPtr = this->currentPlayer.getLocation();
		
		Feature* featurePtr = this->featureMap[nounIn];
		
		// test if feature is present in the current room 
		if(roomPtr->isFeatureInRoom(featurePtr) == true)
		{
			// test if feature already inspected
			if(roomPtr->isFeatureExamined(featurePtr) == false)
			{
				std::ifstream inFile;
				
				inFile.open(featurePtr->getDescription(), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
				
				featurePtr->inspected();
			}
			else
			{
				std::cout << "| You've already examined " << featurePtr->getName() << "." << std::endl;
			}
		}
	}
	else if(this->itemMap.find(nounIn) != this->itemMap.end()) // test if item
	{
	// if item in room or players inventory
		// test if item is present in either the current room or inventory 
		Room* roomPtr = this->currentPlayer.getLocation();
		
		Item* itemPtr = itemMap[nounIn];
		
		// test if item is either in the room, or in your inventory
		if(this->currentPlayer.itemInInventory(itemPtr) == true || roomPtr->isItemInRoom(itemPtr) == true)
		{
			
			
			// test if item has gone to the lab yet to get mundane or analysis response
			/*
			if(itemPtr->getAnalyzed() == true)
				std::cout << itemPtr->getForensicAnalysis() << std::endl;
			else
				std::cout << itemPtr->getDescription() << std::endl;
			*/
			
			// test if item has gone to the lab yet to get mundane or analysis response			
			if(itemPtr->getAnalyzed() == true)
			{
				std::ifstream inFile;
				
				inFile.open(itemPtr->getForensicAnalysis(), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
			}
			else
			{
				std::ifstream inFile;
				
				inFile.open(itemPtr->getDescription(), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
			}
			
		}
		else
		{
			std::cout << "| You can not learn anything from that" << std::endl;
		}
	}
	else
	{
		std::cout << "| You can not learn anything from that" << std::endl;
	}		
}

/*------------------------------------------------------------------------------
		display inventory
------------------------------------------------------------------------------*/
void Gamestate::showInventory()
{
	// test if empty
		// prompt if so
	
	this->currentPlayer.showInventory();
}

/*------------------------------------------------------------------------------
		HACK COMPUTER 
------------------------------------------------------------------------------*/
void Gamestate::hackComputer(std::string nounIn)
{
	// If the player has the computer in inventory, they can hack it.
	if (this->currentPlayer.itemInInventory(this->itemMap[nounIn]))
	{
		std::cout << this->itemMap[nounIn]->getDescription() << std::endl << std::endl;
	}
}

/*------------------------------------------------------------------------------
		TAKE WITNESS STATEMENT
------------------------------------------------------------------------------*/
void Gamestate::getStatement(std::string name)
{
	// If the player is in the same room as the witness...
	if (this->currentPlayer.getLocation() == this->witnessMap[name]->getLocation())
	{
		std::string introduction = this->witnessMap[name]->getIntroduction();
		std::cout << introduction << std::endl << std::endl;
		std::cout << name << " tells you what they know." << std::endl << std::endl;
		std::string statement = this->witnessMap[name]->getAnswer1();
		std::cout << statement << std::endl << std::endl;

		std::cout << "You add this information to your notebook." << std::endl << std::endl;

		std::string entry = introduction + " " + statement;

		this->playerNotebook.setEntry(name, entry);
	}
	else
	{
		std::cout << "That witness is not here." << std::endl;
	}
}

/*------------------------------------------------------------------------------
		INTERROGATE SUSPECT
------------------------------------------------------------------------------*/
void Gamestate::interrogateSuspect(std::string name)
{
	// If the player is in the cell room...
	if (this->currentPlayer.getLocation() == this->roomMap["cells"])
	{
		if (this->suspectMap[name]->getSigItemFound() == true)
		{
			std::cout << "You press " << name << " about what you found in his home earlier." << std::endl;
			std::cout << this->suspectMap[name]->getAnswer2() << std::endl;
			std::cout << "You add this information to your notebook." << std::endl;
			std::string entry = this->suspectMap[name]->getAnswer1() + " " + this->suspectMap[name]->getAnswer2();
			this->playerNotebook.setEntry(name, entry);
		}
		else
		{
			std::cout << "You ask " << name << " about what he knows." << std::endl;
			std::cout << this->suspectMap[name]->getAnswer1() << std::endl;
			std::cout << "You add this information to your notebook." << std::endl;
			std::string entry = this->suspectMap[name]->getAnswer1();
			this->playerNotebook.setEntry(name, entry);
		}
	}
}



/*------------------------------------------------------------------------------
		ANALYZE ITEM
------------------------------------------------------------------------------*/
void Gamestate::analyzeItem(std::string nounIn)
{
	// test if in lab
	if(currentPlayer->getLocation() == roomMap["lab"])
	{
		// test if item
		if(itemMap.find(nounIn) != itemMap.end())
		{
			// test if in inventory or in room
			if(currentPlayer->itemInInventory(itemMap[nounIn]) == true || (currentPlayer->getLocation())->isItemInRoom(itemMap[nounIn]) == true)
			{
				// if so, test if analyzed
				if(itemMap[nounIn]->getAnalyzed() == false) // if item not analyzed yet, analyze
				{
					
					itemMap[nounIn]->analyzeItem();
					
					std::ifstream inFile;
				
					inFile.open(itemMap[nounIn]->getForensicAnalysis(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
				}
				else // if already analyzed, prompt
				{
					std::cout << "| " << nounIn << " has already been analyzed in the lab" << std::endl;
					std::cout << "| " << "examine " << nounIn << " to review labwork" << std::endl;
				}
				
			}
			else
			{
				// if not, prompt
				std::cout << "| " << nounIn << " is not available to analyze"  << std::endl;
				
			}
		
			
		}
		else // if not item
		{
			std::cout << "| " << nounIn << " cannot be analyzed" << std::endl;
		}

	}
	else
	{
		std::cout << "| You must be in the lab to analyze objects" << std::endl;
	}
}





/*------------------------------------------------------------------------------
		Help - Displays the list of actions that the player can take.
------------------------------------------------------------------------------*/

void Gamestate::helpPlayer()
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
	std::cout << "\t(N)Hack Computer - Search a suspect's computer for evidence. (Pick it up first!)" << std::endl;
	std::cout << "\t(N)Analyze <Object> - Submit an item for forensic analysis. Must be in Forensics Lab." << std::endl;
	std::cout << "\t(N)Hint - Get a hint for your current room." << std::endl;

}


void Gamestate::clearScreen()
{
	std::cout << "\033[2J\033[1;1H";
}



/*------------------------------------------------------------------------------
		cleanup
------------------------------------------------------------------------------*/

void Gamestate::cleanup(Parser* currentParser, Player* currentPlayer)
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
void Gamestate::checkLineEndings(std::string* thisString)
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



