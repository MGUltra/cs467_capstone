
#include "Gamedriver.hpp"

/***************************************************************
***																													 ***
***                      Constructor                         ***
***																													 ***
****************************************************************/

Gamestate::Gamestate()
	: itemMap()
	, roomMap()
	, featureMap()
	, suspectMap()
	, witnessMap()
	, roomTestVector()
	, RoomsFile("Rooms.txt")
	, FeaturesFile("Features.txt")
	, ItemsFile("Items.txt")
	, VictimFile("Victim.txt")
	, SuspectsFile("Suspects.txt")
	, WitnessesFile("Witnesses.txt")
	, MurderNotes("MurderNotes.txt")
	, inputString("")
	, actionsInCurrentMessage()
	, numberOfActions(0)
	, numberOfNouns(0)
	, exitStatus(false)
	, commandParser()
	, currentPlayer()
	, playerNotebook()
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
	std::string currentVerb;
	
	do
	{
		
		currentVerb.clear();
		
		this->nounVector.clear();
		
		currentRoomPrompt(this->currentPlayer.getLocation());
		
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(Type 'help' if you need a list of actions you can take!)" << std::endl;
		
		getline(std::cin, inputString);
		
		if(inputString == "exit" || inputString == "quit")
		{
			break;
		}
		
		clearScreen();
		playerNotebook.printGameFlags();
		
		// Call newMessage to run parser on input
		commandParser.newMessage(inputString);
		
		// get pointer to vector of word pointers
		actionsInCurrentMessage = commandParser.getGameActions();
		
		// number of actions will be number of verbs
		// verbs may have multiple nouns
		numberOfActions = commandParser.getNumActions();
		
		// Iterate through verbs
		for(int x = 0; x < numberOfActions; x++)
		{
			currentVerb.clear();
			
			this->nounVector.clear();
			
			// get number of nouns for current verb
			numberOfNouns = (((Verb*)((*actionsInCurrentMessage)[x]))->getNumberOfNouns());
			
			currentVerb = (*actionsInCurrentMessage)[x]->getText();
			
			if(numberOfNouns > 0)
			{
				if(currentVerb == "ask" || currentVerb == "use")
				{
					if(numberOfNouns == 2)
					{
						for(int y = 0; y < numberOfNouns; y++)
						{
							this->nounVector.push_back((((Verb*)((*actionsInCurrentMessage)[x]))->getIndexNounText(y)));
						}
						
						exeCommand(currentVerb);
						continue;
					}
					else
					{
						exeCommand("help");
						continue;
					}
				}
				else
				{
					// iterate through nouns of current verb
					for(int y = 0; y < numberOfNouns; y++)
					{
						
						this->nounVector.clear();
						
						this->nounVector.push_back(((Verb*)((*actionsInCurrentMessage)[x]))->getIndexNounText(y));
						
						exeCommand((*actionsInCurrentMessage)[x]->getText());
					}
				}
			}
			else
			{
				
				this->nounVector.push_back("nonoun");
				this->nounVector.push_back("nonoun");
				
				exeCommand((*actionsInCurrentMessage)[x]->getText());
			}
		}
	
	
	// test if game won
	
		
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
	
	
	// create notebook
	createNotebook();
	
	// Create Rooms
	createRooms();
	
	// create suspects
	createSuspects();
	
	// Create Items - requires rooms and suspects be completed
	createItems();
	
	// create features - requires rooms and items be completed	
	createFeatures();
	
	// create witnesses
	createWitnesses();
	
	
	this->currentPlayer.setLocation(this->getRoom("station"));
	
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
		this->checkLineEndings(&name);

		getline(inputFile, fileLine);
		longDescription = fileLine;
		this->checkLineEndings(&longDescription);

		getline(inputFile, fileLine);
		shortDescription = fileLine;
		this->checkLineEndings(&shortDescription);

		this->roomMap[name] = new Room(name, longDescription, shortDescription);
		
		// populate parser noun set
		this->commandParser.setNounSet(name);
		this->commandParser.setLocationSet(name);

		
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
		this->checkLineEndings(&roomName1);

		getline(inputFile, fileLine);
		direction1 = fileLine;
		this->checkLineEndings(&direction1);

		getline(inputFile, fileLine);
		roomName2 = fileLine;
		this->checkLineEndings(&roomName2);

		getline(inputFile, fileLine);
		direction2 = fileLine;
		this->checkLineEndings(&direction2);

		boost::algorithm::to_lower(roomName1);
		boost::algorithm::to_lower(roomName2);
		
		// Get each rooms' index.
		Room* room1 = this->getRoom(roomName1);
		Room* room2 = this->getRoom(roomName2);

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
		std::string name, descriptionFirst, descriptionAfter, location, itemName, canSampleStr, canHackStr, actionAbleStr, useName;
		Room* room;
		Item* item;
		bool canSample, canHack, actionAble;
		
		
		// feature name
		getline(inputFile, fileLine);
		name = fileLine;
		boost::algorithm::to_lower(name);
		this->checkLineEndings(&name);
		
		// feature descriptionFirst
		getline(inputFile, fileLine);
		descriptionFirst = fileLine;
		this->checkLineEndings(&descriptionFirst);
		
		// feature descriptionAfter
		getline(inputFile, fileLine);
		descriptionAfter = fileLine;
		this->checkLineEndings(&descriptionAfter);

		// room/location name
		getline(inputFile, fileLine);
		location = fileLine;
		this->checkLineEndings(&location);

		// room pointer
		room = this->getRoom(location);

		
		// item reveal name
		getline(inputFile, fileLine);
		itemName = fileLine;
		this->checkLineEndings(&itemName);

		// item pointer
		item = this->itemMap[itemName];
		
		// canSample Value
		
		getline(inputFile, fileLine);
		canSampleStr = fileLine;
		this->checkLineEndings(&canSampleStr);
		
		if(canSampleStr == "true")
			canSample = true;
		else
			canSample = false;
		
		// canHack Value
		
		getline(inputFile, fileLine);
		canHackStr = fileLine;
		this->checkLineEndings(&canHackStr);
		
		if(canHackStr == "true")
			canHack = true;
		else
			canHack = false;
		
		// actionAble value -- for "use" command
		
		getline(inputFile, fileLine);
		actionAbleStr = fileLine;
		this->checkLineEndings(&actionAbleStr);		

		if(actionAbleStr == "true")
			actionAble = true;
		else
			actionAble = false;
		
		// useName -- item for "use" command
		getline(inputFile, fileLine);
		useName = fileLine;
		this->checkLineEndings(&useName);		
		

		
		// create new feature
		this->featureMap[name] = new Feature(name, descriptionFirst, descriptionAfter, location, item, canSample, canHack, actionAble, useName);

		Feature* newFeature = this->featureMap[name];
		
		room->addFeatureInRoom(newFeature);
		
		// populate parser noun set
		this->commandParser.setNounSet(name);
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
		std::string name, description, forensicAnalysis, location, useString;
		Room* room;
		Item* item;
		bool useBool;
		
		// name
		getline(inputFile, fileLine);
		name = fileLine;
		boost::algorithm::to_lower(name);
		this->checkLineEndings(&name);
		
		// description filepath
		getline(inputFile, fileLine);
		description = fileLine;
		this->checkLineEndings(&description);

		// forensicAnalysis filepath
		getline(inputFile, fileLine);
		forensicAnalysis = fileLine;
		this->checkLineEndings(&forensicAnalysis);

		// location
		getline(inputFile, fileLine);
		location = fileLine;
		this->checkLineEndings(&location);

		boost::algorithm::to_lower(location);

		// item useable
		getline(inputFile, fileLine);
		useString = fileLine;
		this->checkLineEndings(&useString);
		
		if(useString == "true")
			useBool = true;
		else
			useBool = false;
		
		room = this->getRoom(location);
		
		this->itemMap[name] = new Item(name, description, forensicAnalysis, useBool);

		// item pointer
		item = this->itemMap[name];
		
		room->addItemInRoom(item);
		
		// populate parser noun set
		this->commandParser.setNounSet(name);
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
	this->checkLineEndings(&name);
	
	getline(inputFile, fileLine);
	description = fileLine;
	this->checkLineEndings(&description);

	// this will be destroyed as soon as it goes out of scope
	Victim newVictim = Victim(name, description);
	
	// populate parser noun set
	this->commandParser.setNounSet(name);

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
		std::string nameIn, inspectResponseIn, talkResponseIn, interrogateResponseIn, accuseResponseTrueIn, 
								accuseResponseFalseIn, itemResponse1In, itemResponse2In, itemResponse3In, itemResponseGenericIn, isGuiltyIn,
								item1In, item2In, item3In;
		bool isGuiltyBool;
		
		// name
		getline(inputFile, fileLine);
		nameIn = fileLine;
		boost::algorithm::to_lower(nameIn);
		this->checkLineEndings(&nameIn);
		
		// inspect Response In
		getline(inputFile, fileLine);
		inspectResponseIn = fileLine;
		this->checkLineEndings(&inspectResponseIn);

		// talkResponseIn
		getline(inputFile, fileLine);
		talkResponseIn = fileLine;
		this->checkLineEndings(&talkResponseIn);

		// interrogateResponseIn
		getline(inputFile, fileLine);
		interrogateResponseIn = fileLine;
		this->checkLineEndings(&interrogateResponseIn);
	
		// accuseResponseTrueIn
		getline(inputFile, fileLine);
		accuseResponseTrueIn = fileLine;
		this->checkLineEndings(&accuseResponseTrueIn);
		
		// accuseResponseFalseIn
		getline(inputFile, fileLine);
		accuseResponseFalseIn = fileLine;
		this->checkLineEndings(&accuseResponseFalseIn);
		
		// itemResponse1In
		getline(inputFile, fileLine);
		itemResponse1In = fileLine;
		this->checkLineEndings(&itemResponse1In);
		
		// itemResponse2In
		getline(inputFile, fileLine);
		itemResponse2In = fileLine;
		this->checkLineEndings(&itemResponse2In);
		
		// itemResponse3In
		getline(inputFile, fileLine);
		itemResponse3In = fileLine;
		this->checkLineEndings(&itemResponse3In);
		
		// itemResponseGenericIn
		getline(inputFile, fileLine);
		itemResponseGenericIn = fileLine;
		this->checkLineEndings(&itemResponseGenericIn);
		
		// isGuiltyIn
		getline(inputFile, fileLine);
		isGuiltyIn = fileLine;
		this->checkLineEndings(&isGuiltyIn);
		
		if(isGuiltyIn == "true")
			isGuiltyBool == true;
		else
			isGuiltyBool == false;
		
		
		// item1
		getline(inputFile, fileLine);
		item1In = fileLine;
		this->checkLineEndings(&item1In);
		
		// item2
		getline(inputFile, fileLine);
		item2In = fileLine;
		this->checkLineEndings(&item2In);		
		
		// item3
		getline(inputFile, fileLine);
		item3In = fileLine;
		this->checkLineEndings(&item3In);
		
		
		this->suspectMap[nameIn] = new Suspect(nameIn, 
																					inspectResponseIn,
																					talkResponseIn,
																					interrogateResponseIn,
																					accuseResponseTrueIn, 
																					accuseResponseFalseIn,
																					itemResponse1In,
																					itemResponse2In,
																					itemResponse3In,
																					itemResponseGenericIn,
																					isGuiltyBool,
																					item1In,
																					item2In,
																					item3In);
		
		// populate parser noun set
		this->commandParser.setNounSet(nameIn);		
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
		std::string nameIn, location, inspectResponseIn, talkResponseIn, interrogateResponseIn, accuseResponseIn, 
								itemResponse1In, itemResponse2In, itemResponse3In, itemResponseGenericIn, item1In, item2In, item3In;
		Room* room;

		// name
		getline(inputFile, fileLine);
		nameIn = fileLine;
		boost::algorithm::to_lower(nameIn);
		this->checkLineEndings(&nameIn);
		
		// location
		getline(inputFile, fileLine);
		location = fileLine;
		this->checkLineEndings(&location);

		// inspectResponseIn
		getline(inputFile, fileLine);
		inspectResponseIn = fileLine;
		this->checkLineEndings(&inspectResponseIn);

		// talkResponseIn
		getline(inputFile, fileLine);
		talkResponseIn = fileLine;
		this->checkLineEndings(&talkResponseIn);

		// interrogateResponseIn
		getline(inputFile, fileLine);
		interrogateResponseIn = fileLine;
		this->checkLineEndings(&interrogateResponseIn);
		
		// accuseResponseIn
		getline(inputFile, fileLine);
		accuseResponseIn = fileLine;
		this->checkLineEndings(&accuseResponseIn);
		
		// itemResponse1In
		getline(inputFile, fileLine);
		itemResponse1In = fileLine;
		this->checkLineEndings(&itemResponse1In);
		
		// itemResponse2In
		getline(inputFile, fileLine);
		itemResponse2In = fileLine;
		this->checkLineEndings(&itemResponse2In);
		
		// itemResponse3In
		getline(inputFile, fileLine);
		itemResponse3In = fileLine;
		this->checkLineEndings(&itemResponse3In);
		
		// itemResponseGenericIn
		getline(inputFile, fileLine);
		itemResponseGenericIn = fileLine;
		this->checkLineEndings(&itemResponseGenericIn);
		
		// item1
		getline(inputFile, fileLine);
		item1In = fileLine;
		this->checkLineEndings(&item1In);
		
		// item2
		getline(inputFile, fileLine);
		item2In = fileLine;
		this->checkLineEndings(&item2In);		
		
		// item3
		getline(inputFile, fileLine);
		item3In = fileLine;
		this->checkLineEndings(&item3In);	

		
		room = this->getRoom(location);

		this->witnessMap[nameIn] = new Witness(nameIn, 
																				inspectResponseIn, 
																				talkResponseIn, 
																				interrogateResponseIn, 
																				accuseResponseIn, 
																				itemResponse1In, 
																				itemResponse2In, 
																				itemResponse3In, 
																				itemResponseGenericIn, 
																				room,
																				item1In,
																				item2In,
																				item3In);

		// populate parser noun set
		
		this->commandParser.setNounSet(nameIn);
		
	}

	// Close inputFile.
	inputFile.close();
}

/*------------------------------------------------------------------------------
CREATE NOTEBOOK
------------------------------------------------------------------------------*/
void Gamestate::createNotebook()
{




	// vince asked
	this->playerNotebook.setGameFlags("vinceLocketAsk", false);
	this->playerNotebook.setGameFlags("vinceCashAsk", false);
	this->playerNotebook.setGameFlags("vinceTicketsAsk", false);
	
	
	// carl asked
	this->playerNotebook.setGameFlags("carlLettersAsk", false);
	this->playerNotebook.setGameFlags("carlSpreadsheetAsk", false);
	this->playerNotebook.setGameFlags("carlFlutesAsk", false);
	
	// dan asked
	
	
	// roy asked
	this->playerNotebook.setGameFlags("royRecordingAsk", false);
	this->playerNotebook.setGameFlags("royCashAsk", false);
	
	
	// herbert asked
	
	
	// louise asked
	this->playerNotebook.setGameFlags("louiseLettersAsk", false);
	this->playerNotebook.setGameFlags("louiseSpreadsheetAsk", false);
	this->playerNotebook.setGameFlags("louiseFlutesAsk", false);
	
	// interrogated
	this->playerNotebook.setGameFlags("vinceInterrogated", false);
	this->playerNotebook.setGameFlags("carlInterrogated", false);
	this->playerNotebook.setGameFlags("danInterrogated", false);
	this->playerNotebook.setGameFlags("royInterrogated", false);
	this->playerNotebook.setGameFlags("louiseInterrogated", false);
	this->playerNotebook.setGameFlags("herbertInterrogated", false);
	
	// cleared
	this->playerNotebook.setGameFlags("vinceCleared", false);
	this->playerNotebook.setGameFlags("carlCleared", false);
	
	// accused
	this->playerNotebook.setGameFlags("danAccused", false);
	
	
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
GET SUSPECT
------------------------------------------------------------------------------*/
Suspect* Gamestate::getSuspect(std::string suspectName)
{
	if (suspectName == "nonoun")
		return NULL;

	return this->suspectMap[suspectName];
}

/*------------------------------------------------------------------------------
GET FEATURE
------------------------------------------------------------------------------*/
Feature* Gamestate::getFeature(std::string featureName)
{
	if (featureName == "nonoun")
		return NULL;

	return this->featureMap[featureName];
}

/*------------------------------------------------------------------------------
GET Witness
------------------------------------------------------------------------------*/
Witness* Gamestate::getWitness(std::string witnessName)
{
	return this->witnessMap[witnessName];
}

/*------------------------------------------------------------------------------
GET ITEM
------------------------------------------------------------------------------*/
Item* Gamestate::getItem(std::string itemName)
{
	if (itemName == "nonoun")
		return NULL;

	return this->itemMap[itemName];
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
		playerNotebook.setRoomVisited(currentRoom->getName(), true);
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
void Gamestate::exeCommand(std::string verb)
{

	//clearScreen();
	
	int functionToCall = 0;
	
	// test verb to determine which function to call
		// pass noun to function called
	if(verb == "move" || verb == "go" || verb == "north" || verb == "south" || verb == "east" || verb == "west")
		functionToCall = 1;
	else if(this->roomMap.find(verb) != this->roomMap.end())
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
	else if(verb == "hack")
		functionToCall = 8;
	else if(verb == "interrogate")
		functionToCall = 9;
	else if(verb == "sample")
		functionToCall = 10;
	else if(verb == "ask")
		functionToCall = 11;
	else if(verb == "use")
		functionToCall = 12;
	else if(verb == "drink")
		functionToCall = 13;
	else if(verb == "listen" || verb == "play")
		functionToCall = 14;
	else if(verb == "talk")
		functionToCall = 15;
	else if(verb == "reflect")
		functionToCall = 16;
	else if(verb == "clear")
		functionToCall = 17;
	else if(verb == "accuse")
		functionToCall = 18;
	else if(verb == "save")
		functionToCall = 19;
	else if(verb == "load")
		functionToCall = 20;
	
	
	switch(functionToCall) {
		
		case 1:	// change rooms
			this->movePlayer(verb, this->nounVector[0]);
			break;
		case 2: // drop item
			this->dropItem(this->nounVector[0]);
			break;
		case 3: // pick up item
			this->takeItem(this->nounVector[0]);
			break;
		case 4: // inspect
			this->inspectObject(this->nounVector[0]);
			break;
		case 5:	// inventory
			this->showInventory();
			break;
		case 6: // analyze
			this->analyzeItem(this->nounVector[0]);
			break;
		case 7: // help
			this->helpPlayer();
			break;
		case 8: // hack
			this->hackComputer(this->nounVector[0]);
			break;
		case 9: // interrogate
			this->interrogate(this->nounVector[0]);
			break;
		case 10: // sample
			this->sampleFeature(this->nounVector[0]);
			break;	
		case 11: // ask
			this->askAboutItem(this->nounVector[0], this->nounVector[1]);
			break;
		case 12: // use
			this->useItemOnFeature(this->nounVector[0], this->nounVector[1]);
			break;
		case 13: // drink
			this->drinkFeature(this->nounVector[0]);
			break;
		case 14: // listen/play
			this->listenToRecording(this->nounVector[0]);
			break;
		case 15: // talk
			this->talkToPerson(this->nounVector[0]);
			break;
		case 16: // reflect
			this->reflectOnCase();
			break;	
		case 17: // clear
			this->clearSuspect(this->nounVector[0]);
			break;	
		case 18: // accuse
			this->accuseSuspect(this->nounVector[0]);
			break;
		case 19: // save
			this->saveGame();
			break;
		case 20: // load
			this->loadGame();
			break;	
		default: // message unclear then help
			this->helpPlayer();
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
	if(this->roomMap.find(verbIn) != this->roomMap.end())
	{
		if(roomPtr->isRoomAttached(this->getRoom(verbIn)) == true)
		{
			this->currentPlayer.changeLocation(this->getRoom(verbIn), &playerNotebook);
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
			this->currentPlayer.changeLocation(newRoom, &playerNotebook);
		else
			std::cout << "You can not go " << verbIn << " from " << roomPtr->getName() << "." << std::endl;
		
		return;
		
	}
	// cardinal direction as noun
	else if(nounIn == "north" || nounIn == "south" || nounIn == "east" || nounIn == "west") 
	{
		Room* newRoom = roomPtr->getCardinalDirection(nounIn);
		
		if(newRoom != NULL)
			this->currentPlayer.changeLocation(newRoom, &playerNotebook);
		else
			std::cout << "You can not go " << nounIn << " from " << roomPtr->getName() << "." << std::endl;
		
		return;
	}
	// room name as noun
	else if(roomPtr->isRoomAttached(this->getRoom(nounIn)) == true)
	{
		this->currentPlayer.changeLocation(this->getRoom(nounIn), &playerNotebook);
		
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
	{
		this->currentPlayer.dropItem(getItem(nounIn), &playerNotebook);
	}
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
		this->currentPlayer.pickUpItem(getItem(nounIn), &playerNotebook);
	else
		std::cout << "| you cannot pick up " << nounIn << std::endl;
}


/*------------------------------------------------------------------------------
		inspect 
------------------------------------------------------------------------------*/
void Gamestate::inspectObject(std::string nounIn)
{
	// cannot access item or feature descriptions from player/room/inventory class
	// because theire vectors contain only strings... will have to use map global 
	// variable.
	
	if(nounIn == "nonoun")
	{
		Room* roomPtr = this->currentPlayer.getLocation();
		
		roomPtr->setAlreadyVisited(false);
		playerNotebook.setRoomVisited(roomPtr->getName(), false);
		
		return;
	}
	
	
	
	if(this->featureMap.find(nounIn) != this->featureMap.end()) // test if feature 
	{
		Room* roomPtr = this->currentPlayer.getLocation();
		
		Feature* featurePtr = this->featureMap[nounIn];
		
		// test if feature is present in the current room 
		if(roomPtr->isFeatureInRoom(featurePtr) == true)
		{
			
			// test if canSample || canHack || actionAble are true
			if(featurePtr->getCanSample() == true || featurePtr->getCanHack() == true || featurePtr->getActionAble() == true || nounIn == "answering")
			{
				// if any of the above - test if already actioned
				if(featurePtr->getAlreadyActioned() == false)
				{
					// output descriptionFirst
					std::ifstream inFile;
				
					inFile.open(featurePtr->getDescriptionFirst(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
					
					// do not update alreadyInspected
				}
				else // if not already actioned
				{
					// output descriptionAfter
					std::ifstream inFile;
				
					inFile.open(featurePtr->getDescriptionAfter(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();					
				}
			
			}
			// if not 
			// test if feature already inspected
			else if(roomPtr->isFeatureExamined(featurePtr) == false)
			{
				std::ifstream inFile;
				
				inFile.open(featurePtr->getDescriptionFirst(), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
				
				featurePtr->inspected(&playerNotebook);
				
				// TODO: UPDATE NOTEBOOK
				// TODO: set feature inspected true
				// TODO: set item affected to revealed
			}
			else
			{
				std::ifstream inFile;
				
				inFile.open(featurePtr->getDescriptionAfter(), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
			}
		}
	}
	else if(this->itemMap.find(nounIn) != this->itemMap.end()) // test if item
	{
	// if item in room or players inventory
		// test if item is present in either the current room or inventory 
		Room* roomPtr = this->currentPlayer.getLocation();
		
		Item* itemPtr = this->itemMap[nounIn];
		
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
	if(this->featureMap.find(nounIn) != this->featureMap.end()) // test if feature
	{
		Feature* currentFeature = featureMap[nounIn];
		Room* currentRoom = this->currentPlayer.getLocation();
		
		
		// test if feature is in room
		if(currentRoom->isFeatureInRoom(currentFeature) == true) // if in room
		{
			
			
			// test if feature is hackable - canHack
			if(currentFeature->getCanHack() == true) // if it is hackable
			{									
				// test if already hacked - alreadyActioned
				if(currentFeature->getAlreadyActioned() == false)	// if not already hacked
				{
					// hack computer
					currentFeature->hacked(&playerNotebook);
					
					// add item					
					this->currentPlayer.pickUpItem(currentFeature->getitemAffected(), &playerNotebook);

					// TODO: In Notebook
					// TODO: set feature alreadyActioned
					// TODO: set item location to inventory
					// TODO: set item affected to revealed
					
					
				}			
				else	// if already hacked	
				{
					// prompt
					std::cout << "| You have already Hacked " << nounIn << "." << std::endl;
				}			
			}	
			else // if it is not hackable
			{
				// prompt
				std::cout << "| You can not hack " << nounIn << "." << std::endl;
			}
		}
		else // if not in room
		{
			// prompt
			std::cout << "| " << nounIn << " doesn't seem to be in this room." << std::endl;
		}
	}
	else
	{
		std::cout << "| " << nounIn << " can not be Hacked" << std::endl;
	}
}


/*------------------------------------------------------------------------------
		INTERROGATE
------------------------------------------------------------------------------*/
void Gamestate::interrogate(std::string name)
{

	Room* currentRoom = this->currentPlayer.getLocation();

	if(this->witnessMap.find(name) != this->witnessMap.end()) // witnesses
	{
		// test if in station
		if(currentRoom->getName() == "station")		
		{
				// roy
				if(name == "roy")
				{
					if(this->playerNotebook.royCanInterrogate() == true)
					{
						// output interrogationResponse
						std::ifstream inFile;
							
						inFile.open(witnessMap[name]->getInterrogateResponse(), std::ios::out);
						readFileDefault(inFile);
						inFile.close();
						
						if(this->playerNotebook.getGameFlags("royInterrogated") == false)
						{
							this->playerNotebook.setGameFlags("royInterrogated", true);
						}
						// TODO: In Notebook
						// TODO: set royInterrogate to true						
					}
					else
					{
						std::cout << "'I've got nothing to say, Detective.'" << std::endl;
						
						std::cout << "You may need to ask Roy about more evidence before he can be successfully interrogated" << std::endl;
					}
				}
				// louise
				else if(name == "louise")
				{
					if(this->playerNotebook.louiseCanInterrogate() == true)
					{
						// output interrogationResponse
						std::ifstream inFile;
							
						inFile.open(witnessMap[name]->getInterrogateResponse(), std::ios::out);
						readFileDefault(inFile);
						inFile.close();
						
						if(this->playerNotebook.getGameFlags("louiseInterrogated") == false)
						{
							this->playerNotebook.setGameFlags("louiseInterrogated", true);
						}						
						// TODO: In Notebook
						// TODO: set louiseInterrogate to true

						
					}
					else
					{
						std::cout << "'I've dont have any information, Detective.'" << std::endl;
						
						std::cout << "You may need to ask louise about more evidence before he can be successfully interrogated" << std::endl;
					}
				}	
				// herbert
				else if(name == "herbert")
				{
					if(this->playerNotebook.herbertCanInterrogate() == true)
					{
						// output interrogationResponse
						std::ifstream inFile;
							
						inFile.open(witnessMap[name]->getInterrogateResponse(), std::ios::out);
						readFileDefault(inFile);
						inFile.close();
						
						if(this->playerNotebook.getGameFlags("herbertInterrogated") == false)
						{
							this->playerNotebook.setGameFlags("herbertInterrogated", true);
						}								
						// TODO: In Notebook
						// TODO: set herbertInterrogate to true
						
					}
					else
					{
						std::cout << "'I don't think I can help, Detective.'" << std::endl;
						
						std::cout << "You may need to ask herbert about more evidence before he can be successfully interrogated" << std::endl;
					}
				}
			// test any interrogation conditions
			

		}
	}
	else if(this->suspectMap.find(name) != this->suspectMap.end()) // suspects
	{
		// test if in cells
		if(currentRoom->getName() == "cells")		
		{
				// test any interrogation conditions
			if(name == "vince")
			{
				if(this->playerNotebook.vinceCanInterrogate() == true)
				{
					std::ifstream inFile;
						
					inFile.open(suspectMap[name]->getInterrogateResponse(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
					
					if(this->playerNotebook.getGameFlags("vinceInterrogated") == false)
					{
						this->playerNotebook.setGameFlags("vinceInterrogated", true);
					}	
					
				}
				else
				{
					std::cout << "'I don't have any more information, Detective.'" << std::endl;
					
					std::cout << "You may need to ask vince about more evidence before he can be successfully interrogated" << std::endl;
				}
			}
			else if(name == "carl")
			{
				if(this->playerNotebook.carlCanInterrogate() == true)
				{
					std::ifstream inFile;
						
					inFile.open(suspectMap[name]->getInterrogateResponse(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
					
					if(this->playerNotebook.getGameFlags("carlInterrogated") == false)
					{
						this->playerNotebook.setGameFlags("carlInterrogated", true);
					}	
				}
				else
				{
					std::cout << "'I don't have any more information, Detective.'" << std::endl;
					
					std::cout << "You may need to ask carl about more evidence before he can be successfully interrogated" << std::endl;
				}
			}
			else if(name == "dan")
			{
				if(this->playerNotebook.danCanInterrogate() == true)
				{
					std::ifstream inFile;
						
					inFile.open(suspectMap[name]->getInterrogateResponse(), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
					
					if(this->playerNotebook.getGameFlags("danInterrogated") == false)
					{
						this->playerNotebook.setGameFlags("danInterrogated", true);
					}	
				}
				else
				{
					std::cout << "'I don't have any more information, Detective.'" << std::endl;
					
					std::cout << "You may need to ask dan about more evidence before he can be successfully interrogated" << std::endl;
				}
			}

			
			
			
		}
	}
	else if(name == "chief") // chief
	{
		// test if in station
		if(currentRoom->getName() == "station")		
		{
				// test any interrogation conditions
			
				// output interrogationResponse
				std::cout << "I'm not someone you should be trying to interrogate. Get back to work, Detective." << std::endl;

		}
	}
	else
	{
		std::cout << "" << std::endl;
	}
}



/*------------------------------------------------------------------------------
		ANALYZE ITEM
------------------------------------------------------------------------------*/
void Gamestate::analyzeItem(std::string nounIn)
{
	// test if in lab
	if(this->currentPlayer.getLocation() == this->roomMap["lab"])
	{
		// test if item
		if(this->itemMap.find(nounIn) != this->itemMap.end())
		{
			// test if in inventory or in room
			if(this->currentPlayer.itemInInventory(this->itemMap[nounIn]) == true || (this->currentPlayer.getLocation())->isItemInRoom(this->itemMap[nounIn]) == true)
			{
				// if so, test if analyzed
				if(this->itemMap[nounIn]->getAnalyzed() == false) // if item not analyzed yet, analyze
				{
					
					this->itemMap[nounIn]->analyzeItem(&playerNotebook);
					
					// TODO: In Notebook
					// TODO: set item analyzed true
					
					
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
		ACCUSE 
------------------------------------------------------------------------------*/

void Gamestate::accuseSuspect(std::string personIn)
{
	if (currentPlayer.getLocation() == getRoom("station"))
	{
		// if witness
		if (witnessMap.find(personIn) != witnessMap.end())
		{
			Witness* currentWitness = getWitness(personIn);
			std::cout << currentWitness->getAccuseResponse() << std::endl;
		}
		// if chief
		else if (personIn == "chief")
		{
			std::cout << "Ha Ha Ha. Get back to work!" << std::endl;
		}
		else if (suspectMap.find(personIn) != suspectMap.end())
		{
			std::cout << "They can't hear you from this room. Try again in the cells." << std::endl;
		}
		// not a suspect, witness, or chief
		else
		{
			std::cout << "Who is that?  They're not involved in this case." << std::endl;
		}
	}
	else if (currentPlayer.getLocation() == getRoom("cells"))
	{
		// if suspect
		if (suspectMap.find(personIn) != suspectMap.end())
		{
			// If suspect is cleared
			Suspect* currentSuspect = getSuspect(personIn);
			if (currentSuspect->getIsCleared())
			{
				std::cout << currentSuspect->getAccuseResponseFalse() << std::endl;
			}
			// Suspect is not cleared.
			else
			{
				// test if other two suspects exonerated
				// Iterator pointing to begining of map
				std::unordered_map<std::string, Suspect*>::iterator it = suspectMap.begin();
				// check how many suspects have been cleared
				int clearedSuspects = 0;
				while (it != suspectMap.end())
				{
					if (it->second->getIsCleared())
					{
						clearedSuspects++;
					}
					it++;
				}

				// accused is not clear, but the other two are
				// WINNING CONDITION
				if (clearedSuspects == 2)
				{
					std::cout << "You got him!" << std::endl;
				}
				//accused is not clear, and one or both of the others isn't either.
				else
				{
					std::cout << currentSuspect->getAccuseResponseFalse() << std::endl;
					std::cout << "You can't say it's " << personIn
						<< " for sure. You need to clear the other suspects first." << std::endl;
				}
			}
		}
		else if (witnessMap.find(personIn) != witnessMap.end() || personIn == "chief")
		{
			std::cout << "They can't hear you in the station from this room.  That might be for the best!" << std::endl;
		}
		else
		{
			std::cout << "Who is that?  They're not involved in this case." << std::endl;
		}
	}
	else
	{
		std::cout << "No one hears your accusation.  Try again at the station or in the cells." << std::endl;
	}
	
	
	
	
	
	// test if suspect, witness, chief
	
	// if suspect
		
		// test if other two suspects exonerated
			// if not - prompt to clear innocent parties first
				// send response from suspect as well
				// can be generic "You've got nothing on me"
		
			// if so
				// test if enough evidence gathered
					// if so - success
					// game ends
	
	// if witness
		// incredulous response
	
	// if chief
		// generic response
}


/*------------------------------------------------------------------------------
		SAMPLE FEATURE 
------------------------------------------------------------------------------*/
void Gamestate::sampleFeature(std::string featureIn)
{
	if(featureIn == "nonoun")
	{
		std::cout << "You must specify what you want to try to sample" << std::endl;
		return;
	}
	if(this->featureMap.find(featureIn) != this->featureMap.end()) // test if feature
	{
		Feature* currentFeature = featureMap[featureIn];
		Room* currentRoom = this->currentPlayer.getLocation();
	
		// test if featureIn is able to be sampled
		if(currentFeature->getCanSample() == true) // if can sample
		{
			// test if sample has already been taken
			if(currentFeature->getAlreadyActioned() == true)
			{
				// if so - prompt that sample has already been taken and return
				std::cout << "You have already sampled " << featureIn << " ." << std::endl;
				
			}
			else // sample not yet taken
			{
				// if not - set sample taken to true, flag in notebook, add sample item to inventory
				currentFeature->sampled(&playerNotebook);
				
				this->currentPlayer.pickUpItem(currentFeature->getitemAffected(), &playerNotebook);
				
									
				// TODO: In Notebook
				// TODO: set item location to inventory
				// TODO: set feature alreadyActioned true
				
				
			}
		}
		else // can not sample
		{
				// if not, do nothing
				// prompt "Sampling this will not accomplish anything"
				
				std::cout << "You can not sample " << featureIn << " ." << std::endl;
		}
			

	}
	else // not feature
	{
		std::cout << "You can not sample " << featureIn << " ." << std::endl;
	}
}

/*------------------------------------------------------------------------------
		ASK ABOUT ITEM
------------------------------------------------------------------------------*/

void Gamestate::askAboutItem(std::string personIn, std::string itemIn)
{

	if(personIn == "nonoun")
	{
		std::cout << "You must ask a person about an item.. ie, 'Ask dan about key'" << std::endl;
		
		return;
	}
	
	if(this->itemMap.find(itemIn) != this->itemMap.end())
	{
		Item* currentItem = getItem(itemIn);
		
		// test if item is in player's inventory
		if(this->currentPlayer.itemInInventory(currentItem) == true) // item in inventory
		{

			Room* currentRoom = this->currentPlayer.getLocation();
			
			// test if suspect and current location is in cells
			if(suspectMap.find(personIn) != suspectMap.end() &&	currentRoom->getName() == "cells")
			{
				
				Suspect* currentSuspect = getSuspect(personIn);
				
				std::ifstream inFile;
				

				inFile.open(currentSuspect->askItemResponse(itemIn, &playerNotebook), std::ios::out);
				readFileDefault(inFile);
				inFile.close();
				// suspect
					// test if they have a response to item
						// if so - flag in notebook and return response
						// if not - return generic response
			}		
			// test if witness or chief, and current location is in station
			else if(currentRoom->getName() == "station"	&& (witnessMap.find(personIn) != witnessMap.end() || personIn == "chief"))
			{
				// chief
					// generic response about being the brass and not going to do your job
				
				if(personIn == "chief")
				{
					std::cout << "Why are you asking me about " << itemIn << "? You should be investigating these things, not me." <<  std::endl;
				}
				else
				{
					Witness* currentWitness = getWitness(personIn);
				
				
					std::ifstream inFile;
				
					inFile.open(currentWitness->askItemResponse(itemIn, &playerNotebook), std::ios::out);
					readFileDefault(inFile);
					inFile.close();
				}
					
			}
			// if neither of the above then operation is not possible
			else
			{
				std::cout << "that person isn't here to ask" <<  std::endl;
			}

		}
		else // Item not in inventory
		{
			std::cout << itemIn << " is not in your inventory" <<  std::endl;
		}
	}
}

	


/*------------------------------------------------------------------------------
		USE ITEM ON FEATURE
------------------------------------------------------------------------------*/
void Gamestate::useItemOnFeature(std::string itemIn, std::string featureIn)
{
	
	Feature* currentFeature = featureMap[featureIn];
	Room* currentRoom = this->currentPlayer.getLocation();
	
	if((this->featureMap.find(featureIn) != this->featureMap.end()) 				&& // test that featureIn is a feature
		(this->itemMap.find(itemIn) != this->itemMap.end())										&& // test that itemIn is an item
		(currentRoom->isFeatureInRoom(currentFeature) == true)								&& // test that the feature is in the room
		(this->currentPlayer.itemInInventory(this->itemMap[itemIn]) == true))		 // test that the item is in the players inventory
	{
		
		// test if featureIn is affected by an item - feature variable actionAble
		
		if(currentFeature->getActionAble() == true) // if the feature can have an item used on it
		{
			
			// test if itemIn is the item that can affect feature
			
			if(currentFeature->getUseItem() == itemIn) // itemIn can be used on feature
			{
				
				// if so - test if itemIn already used on feature - feature variable alreadyActioned
				
				if(currentFeature->getAlreadyActioned() == false) // item Has Not been used on feature yet
				{
					
					// if not - flag in notebook - set alreadyActioned to true - and reveal item
					currentFeature->itemUsed(&playerNotebook);
				
					// TODO: In Notebook
					// TODO: set feature alreadyActioned true
					// TODO: set item affected to revealed
					
				}
				else // item Has been used on feature
				{
					
					// if so - prompt that nothing more can be done		
					std::cout << "Using " << itemIn << " again accomplished nothing." <<  std::endl;
					
				}
				
				
			}
			else // itemIn can NOT be used on feature
			{
				std::cout << "Using " << itemIn << " on " << featureIn << " doesn't accomplish anything. Try something else." << std::endl;
			}
			
		}
		else // if the feature can NOT have an item used on it
		{
			std::cout << featureIn << " doesn't look like anythin useful will happen by using an item on it" << std::endl;
		}
	}
	else // if all 4 conditions are not true, then operation can not be complete
	{
		std::cout << "You can not do that under the current conditions" << std::endl;
	}
		
}


/*------------------------------------------------------------------------------
		DRINK FEATURE
------------------------------------------------------------------------------*/
void Gamestate::drinkFeature(std::string featureIn)
{
	// test if featureIn is drinkable
	if(featureIn == "coffee" || featureIn == "canteen" || featureIn == "flask")
	{
		Feature* currentFeature = featureMap[featureIn];
		Room* currentRoom = this->currentPlayer.getLocation();
		
		
		if(currentRoom->isFeatureInRoom(currentFeature) == true)
		{
			
			if(featureIn == "coffee")
			{
				// set game flag coffeeBreath
				
			}
			else if(featureIn == "canteen")
			{
				// test flag drinkCoffee
				
			}
			else if(featureIn == "flask")
			{
				// test flag drinkCoffee
				
			}

		}
		else
		{
			std::cout << "You don't see any " << featureIn << " in this room" << std::endl;
		}

	}
	else
	{
		std::cout << "Trying to drink that is a bad idea" << std::endl;
	}
		

}


/*------------------------------------------------------------------------------
		LISTEN
------------------------------------------------------------------------------*/
void Gamestate::listenToRecording(std::string itemIn)
{
	
	if (itemIn == "answering")
	{
		Feature* currentFeature = getFeature(itemIn);
		Item* currentItem = currentFeature->getitemAffected();

		if (currentPlayer.getLocation() == getRoom(currentFeature->getLocation()))
		{
			if (currentFeature->getAlreadyActioned())
			{
				std::cout << "You've already added the recording to your inventory." << std::endl;
			}
			else
			{
				
				std::cout << "You listen to the recording." << std::endl;
				std::cout << currentItem->getDescription() << std::endl;
				std::cout << "You add the recording to your inventory." << std::endl;
				
				
				currentFeature->listened(&playerNotebook);
				
				// add recording to inventory
				currentPlayer.pickUpItem(currentItem, &playerNotebook);

			}
		}
		else
		{
			std::cout << "You're not in the same room as the answering machine." << std::endl;
		}
	}
	else if (itemIn == "recording")
	{
		
		Item* currentItem = getItem(itemIn);
		// test if in inventory
		if(this->currentPlayer.itemInInventory(currentItem) == true)
		{		
			// Play recording.
			std::cout << currentItem->getDescription() << std::endl;
		}
		else
		{
			std::cout << "the recording is not in your inventory." << std::endl;
		}
	}
	else
	{
		std::cout << "You can't listen to that." << std::endl;
	}

	
	// test if answering machine (feature) or recording (item)
	
	// if answering machine - test if listened to before
		// if not - prompt with recording dialog and add recording item to inventory
		// if so - prompt that you've already taken the recording
	
	// if recording
		// if in inventory or room - prompt with recording dialog
		// if not in room - say you dont have it right now
		
		
}


/*------------------------------------------------------------------------------
		TALK
------------------------------------------------------------------------------*/
void Gamestate::talkToPerson(std::string personIn)
{

	if (currentPlayer.getLocation() == getRoom("station"))
	{
		// if witness
		if (witnessMap.find(personIn) != witnessMap.end())
		{
			Witness* currentWitness = getWitness(personIn);
			std::cout << currentWitness->getTalkResponse() << std::endl;
		}
		// if chief
		else if (personIn == "chief")
		{
			std::cout << "Let's have a look at your progress." << std::endl;
			reflectOnCase();
		}
		else if (suspectMap.find(personIn) != suspectMap.end())
		{
			std::cout << "They can't hear you from this room. Try again in the cells." << std::endl;
		}
		// not a suspect, witness, or chief
		else
		{
			std::cout << "Who is that? It's not really healthy to talk to yourself, is it?" << std::endl;
		}
	}
	else if (currentPlayer.getLocation() == getRoom("cells"))
	{
		// if suspect
		if (suspectMap.find(personIn) != suspectMap.end())
		{
			Suspect* currentSuspect = getSuspect(personIn);
			std::cout << currentSuspect->getTalkResponse() << std::endl;
		}
		else if (witnessMap.find(personIn) != witnessMap.end() || personIn == "chief")
		{
			std::cout << "They can't hear you in the station from this room." << std::endl;
		}
		else
		{
			std::cout << "Who is that? It's not really healthy to talk to yourself, is it?" << std::endl;
		}
	}
	else
	{
		std::cout << "It's not really healthy to talk to yourself, is it?" << std::endl;
	}
	
	// if personIn is suspect or witness and in the same room
		// prompt with response
		
	// if personIn is chief and in the same room
		// test notebook for progress
			// return with appropriate response 
			
	// if personIn is none of the above or not in the room
		// prompt that its not healthy to talk to oneself
}


/*------------------------------------------------------------------------------
		REFLECT
------------------------------------------------------------------------------*/
void Gamestate::reflectOnCase()
{
	// prompt with status of each suspect and the evidence
	// prompt with status of each suspect and the evidence
	
	// vince and roy
	
	
	// carl and
	
	
	// dan and 

	std::cout << "Here's what we know so far." << std::endl << std::endl;
	std::unordered_map<std::string, Suspect*>* suspectMapPointer = getSuspectMap();
	std::unordered_map<std::string, Suspect*>::iterator it = suspectMapPointer->begin();
	while (it != suspectMapPointer->end())
	{	
		// name of suspect
		std::cout << "   -" << it->second->getName();
		if (it->second->getIsCleared())
		{
			std::cout << " has been cleared of this murder." << std::endl;
		}
		else
		{
			std::cout << " has NOT been cleared of this murder." << std::endl;
		}
		it++;
	}
//>>>>>>THOUGHT - should the relevant evidence only be listed if the suspect is not cleared?  keep things clear and concise?
		// get relevant evidence that has been found and analyzed

	std::cout << "The following analyzed evidence has been found:" << std::endl;
	bool evidenceFound = false;

	std::unordered_map<std::string, Item*>* itemMapPointer = getItemMap();
	std::unordered_map<std::string, Item*>::iterator itemit = itemMapPointer->begin();
	while (itemit != itemMapPointer->end())
	{
		std::string currentItemString = itemit->first;

		Item* currentItem = getItem(currentItemString);
		// if item belongs to current suspect and has already been analyzed
		if (currentItem->getAnalyzed() == true)
		{
			// item name and analysis results
			std::cout << "   - " << currentItem->getName() << " : " << currentItem->getForensicAnalysis()<< std::endl;
			evidenceFound = true;
		}

		// increment iterator
		itemit++;
	}

	if (!evidenceFound)
	{
		std::cout << "No analyzed evidence has been found yet." << std::endl;
	}

}


/*------------------------------------------------------------------------------
		CLEAR SUSPECT
------------------------------------------------------------------------------*/
void Gamestate::clearSuspect(std::string personIn)
{
	
	if(currentPlayer.getLocation() == getRoom("station"))
	{
		// if witness
		if (witnessMap.find(personIn) != witnessMap.end())
		{
			std::cout << "Well of course I'm cleared!  I wasn't ever a suspect!" << std::endl;
		}
		// if chief
		else if (personIn == "chief")
		{
			std::cout << "You're hilarious.  Now get back to work!" << std::endl;
		}
	}
	else if(currentPlayer.getLocation() == getRoom("cells"))
	{
		//suspect
		if (suspectMap.find(personIn) != suspectMap.end())
		{
			
			if(personIn == "vince")
			{
				if(playerNotebook.vinceCanClear() == true)
				{
					playerNotebook.setGameFlags("vinceCleared", true);
				}
				else
				{
					std::cout << "You're going to need some more evidence to clear them" << std::endl;
				}
			}
			else if(personIn == "carl")
			{
				if(playerNotebook.carlCanClear() == true)
				{
					playerNotebook.setGameFlags("carlCleared", true);
				}
				else
				{
					std::cout << "You're going to need some more evidence to clear them" << std::endl;
				}
			}
			else if(personIn == "dan")
			{
				std::cout << "You're going to need some more evidence to clear them" << std::endl;
			}
			// test if enough evidence to clear them
			// if so, set flag for suspect to cleared in notebook
				// remove suspect from cells

			// if not, prompt that more evidence is needed before they can be released
		}
		// not a suspect, witness, or chief
		else
		{
			std::cout << "Who is that?" << std::endl;
		}
	}
	else
	{
		std::cout << "You need to be in the same room as the person you are trying to clear of the crime" << std::endl;
	}
	
	
	// test if personIn is suspect
		// if so
			// test if enough evidence to clear them
				// if so, set flag for suspect to cleared in notebook
					// remove suspect from cells
				
				// if not, prompt that more evidence is needed before they can be released
				
		// if not suspect
			// if witness and in same room
				// prompt "I know I didn't do it"
		
			// if chief and in the same room
				// prompt "get back to work" or something
}




/*------------------------------------------------------------------------------
		SAVE GAME
------------------------------------------------------------------------------*/
void Gamestate::saveGame()
{
	std::ofstream saveFile;

	saveFile.open("savefile.txt");

	// Open the given file.
	if (!saveFile.is_open())
	{
		std::cout << "The save file could not be opened.\n";
		return;
	}

	// playerLocation
	std::string playerLoc = this->currentPlayer.getLocation()->getName();

	saveFile << playerLoc << std::endl;

	// gameFlags
	std::unordered_map<std::string, bool>* saveGameFlags = this->playerNotebook.getGameFlags();

	int numGameFlags = saveGameFlags->size();
	std::string stringNumGameFlags = std::to_string(numGameFlags);
	saveFile << stringNumGameFlags << std::endl;

	std::unordered_map<std::string, bool>::iterator gameFlagsIterator = saveGameFlags->begin();
	while (gameFlagsIterator != saveGameFlags->end())
	{
		std::string key = gameFlagsIterator->first;
		std::string boolean = getBoolString(gameFlagsIterator->second);

		saveFile << key << " " << boolean << std::endl;
		gameFlagsIterator++;
	}
	// itemAvailable
	std::unordered_map<std::string, bool>* saveItemAvailable = this->playerNotebook.getItemAvailable();

	int numItemAvailable = saveItemAvailable->size();
	std::string stringNumItemAvailable = std::to_string(numItemAvailable);
	saveFile << stringNumItemAvailable << std::endl;

	std::unordered_map<std::string, bool>::iterator itemAvailableIterator = saveItemAvailable->begin();
	while (itemAvailableIterator != saveItemAvailable->end())
	{
		std::string key = itemAvailableIterator->first;
		std::string boolean = getBoolString(itemAvailableIterator->second);

		saveFile << key << " " << boolean << std::endl;
		itemAvailableIterator++;
	}

	// itemAnalyzed
	std::unordered_map<std::string, bool>* saveItemAnalyzed = this->playerNotebook.getItemAnalyzed();

	int numItemAnalyzed = saveItemAnalyzed->size();
	std::string stringNumItemAnalyzed = std::to_string(numItemAnalyzed);
	saveFile << stringNumItemAnalyzed << std::endl;

	std::unordered_map<std::string, bool>::iterator itemAnalyzedIterator = saveItemAnalyzed->begin();
	while (itemAnalyzedIterator != saveItemAnalyzed->end())
	{
		std::string key = itemAnalyzedIterator->first;
		std::string boolean = getBoolString(itemAnalyzedIterator->second);

		saveFile << key << " " << boolean << std::endl;
		itemAnalyzedIterator++;
	}

	// featureInspected
	std::unordered_map<std::string, bool>* saveFeatureInspected = this->playerNotebook.getFeatureInspected();

	int numFeatureInspected = saveFeatureInspected->size();
	std::string stringNumFeatureInspected = std::to_string(numFeatureInspected);
	saveFile << stringNumFeatureInspected << std::endl;

	std::unordered_map<std::string, bool>::iterator FeatureInspectedIterator = saveFeatureInspected->begin();
	while (FeatureInspectedIterator != saveFeatureInspected->end())
	{
		std::string key = FeatureInspectedIterator->first;
		std::string boolean = getBoolString(FeatureInspectedIterator->second);

		saveFile << key << " " << boolean << std::endl;
		FeatureInspectedIterator++;
	}

	// featureActioned
	std::unordered_map<std::string, bool>* saveFeatureActioned = this->playerNotebook.getFeatureActioned();

	int numFeatureActioned = saveFeatureActioned->size();
	std::string stringNumFeatureActioned = std::to_string(numFeatureActioned);
	saveFile << stringNumFeatureActioned << std::endl;

	std::unordered_map<std::string, bool>::iterator FeatureActionedIterator = saveFeatureActioned->begin();
	while (FeatureActionedIterator != saveFeatureActioned->end())
	{
		std::string key = FeatureActionedIterator->first;
		std::string boolean = getBoolString(FeatureActionedIterator->second);

		saveFile << key << " " << boolean << std::endl;
		FeatureActionedIterator++;
	}

	// roomVisited
	std::unordered_map<std::string, bool>* saveRoomVisited = this->playerNotebook.getRoomVisited();

	int numRoomVisited = saveRoomVisited->size();
	std::string stringNumRoomVisited = std::to_string(numRoomVisited);
	saveFile << stringNumRoomVisited << std::endl;

	std::unordered_map<std::string, bool>::iterator roomVisitedIterator = saveRoomVisited->begin();
	while (roomVisitedIterator != saveRoomVisited->end())
	{
		std::string key = roomVisitedIterator->first;
		std::string boolean = getBoolString(roomVisitedIterator->second);

		saveFile << key << " " << boolean << std::endl;
		roomVisitedIterator++;
	}

	// itemLocations
	std::unordered_map<std::string, std::string>* itemLocPointer = this->playerNotebook.getItemLocations();

	int numItemLocations = itemLocPointer->size();
	std::string stringNumItemLocations = std::to_string(numItemLocations);
	saveFile << stringNumItemLocations << std::endl;

	std::unordered_map<std::string, std::string>::iterator itemLocIterator = itemLocPointer->begin();
	while (itemLocIterator != itemLocPointer->end())
	{
		std::string item = itemLocIterator->first;
		std::string location = itemLocIterator->second;

		saveFile << item << " " << location << std::endl;
		itemLocIterator++;
	}

	// suspects cleared
	std::unordered_map<std::string, Suspect*>* suspectMapPointer = getSuspectMap();

	int numSuspectsCleared = suspectMapPointer->size();
	std::string stringNumSuspectsCleared = std::to_string(numSuspectsCleared);
	//std::cout << "Number of Suspects is: " << numSuspectsCleared << std::endl;
	saveFile << stringNumSuspectsCleared << std::endl;

	std::unordered_map<std::string, Suspect*>::iterator suspectIterator = suspectMapPointer->begin();
	while (suspectIterator != suspectMapPointer->end())
	{
		std::string key = suspectIterator->first;
		std::string boolean = getBoolString(suspectIterator->second->getIsCleared());

		//std::cout << "Suspect: " << key << "   Cleared: " << boolean << std::endl;
		saveFile << key << " " << boolean << "\n" << std::endl;
		suspectIterator++;
	}
}

/*------------------------------------------------------------------------------
		LOAD GAME
------------------------------------------------------------------------------*/
void Gamestate::loadGame()
{
	std::ifstream saveFile;

	std::string fileLine;

	saveFile.open("savefile.txt");

	// Open the given file.
	if (!saveFile.is_open())
	{
		std::cout << "The save file could not be opened.\n";
		return;
	}

	// Get the current line as a string.
	getline(saveFile, fileLine);

	std::string currentLocation = fileLine;
	this->checkLineEndings(&currentLocation);
	Room* currentRoom = getRoom(currentLocation);

	// Update player's location.
	this->currentPlayer.changeLocation(currentRoom, &this->playerNotebook);
	
	// GAME FLAGS
	getline(saveFile, fileLine);
	std::stringstream currentLine(fileLine);
	int numGameFlags = 0;
	// Stream line into an integer.
	currentLine >> numGameFlags;

	for (int i = 0; i < numGameFlags; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setGameFlags(key, boolValue);
	}

	// ITEM AVAILABLE
	getline(saveFile, fileLine);
	std::stringstream currentLine1(fileLine);
	int numItemAvailable = 0;
	// Stream line into an integer.
	currentLine >> numItemAvailable;

	for (int i = 0; i < numItemAvailable; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setItemAvailable(key, boolValue);
	}

	// ITEM ANALYZED
	getline(saveFile, fileLine);
	std::stringstream currentLine2(fileLine);
	int numItemAnalyzed = 0;
	// Stream line into an integer.
	currentLine >> numItemAnalyzed;

	for (int i = 0; i < numItemAnalyzed; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setItemAnalyzed(key, boolValue);
	}
	
	// FEATURE INSPECTED
	getline(saveFile, fileLine);
	std::stringstream currentLine3(fileLine);
	int numFeatureInspected = 0;
	// Stream line into an integer.
	currentLine >> numFeatureInspected;

	for (int i = 0; i < numFeatureInspected; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setFeatureInspected(key, boolValue);
	}

	// FEATURE ACTIONED
	getline(saveFile, fileLine);
	std::stringstream currentLine4(fileLine);
	int numFeatureActioned = 0;
	// Stream line into an integer.
	currentLine >> numFeatureActioned;

	for (int i = 0; i < numFeatureActioned; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setFeatureActioned(key, boolValue);
	}

	// ROOM VISITED
	getline(saveFile, fileLine);
	std::stringstream currentLine5(fileLine);
	int numRoomVisited = 0;
	// Stream line into an integer.
	currentLine >> numRoomVisited;

	for (int i = 0; i < numRoomVisited; i++)
	{
		std::string key, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> key;
		this->checkLineEndings(&key);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		this->playerNotebook.setRoomVisited(key, boolValue);
	}

	// ITEM LOCATIONS
	getline(saveFile, fileLine);
	std::stringstream currentLine6(fileLine);
	int numItemLoc = 0;
	// Stream line into an integer.
	currentLine >> numItemLoc;

	for (int i = 0; i < numItemLoc; i++)
	{
		std::string item, location;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> item;
		this->checkLineEndings(&item);
		currentLine0 >> location;
		this->checkLineEndings(&location);

		Item* currentItem = getItem(item);
		
		if (location == "inventory")
		{
			this->currentPlayer.pickUpItem(currentItem, &this->playerNotebook);
		}
		else
		{
			Room* currentRoom = getRoom(location);
			currentRoom->addItemInRoom(currentItem);
		}

		this->playerNotebook.setItemLocations(item, location);
	}

	// CLEARED SUSPECTS
	getline(saveFile, fileLine);
	std::stringstream currentLine7(fileLine);
	int numSuspects = 0;
	// Stream line into an integer.
	currentLine >> numSuspects;

	for (int i = 0; i < numSuspects; i++)
	{
		std::string suspect, boolean;

		getline(saveFile, fileLine);
		std::stringstream currentLine0(fileLine);
		// Get the current line as a string.
		currentLine0 >> suspect;
		this->checkLineEndings(&suspect);
		currentLine0 >> boolean;
		this->checkLineEndings(&boolean);
		bool boolValue = getStringFromBool(boolean);

		Suspect* currentSuspect = getSuspect(suspect);

		currentSuspect->setIsCleared(boolValue);
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

void Gamestate::cleanup()
{
	// Deletes all instantiated class Word derived objects
	this->commandParser.clearMessage();
	
	//delete currentParser;
	//delete currentPlayer;
	
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

/*------------------------------------------------------------------------------
		TEST HACK / SAMPLE

	std::string getName();
	std::string getDescriptionFirst();
	std::string getDescriptionAfter();
	std::string getLocation();
	std::string getUseItem();
	
	bool getAlreadyInspected();
	bool getAlreadyActioned();
	bool getCanSample();
	bool getCanHack();
	bool getActionAble();
	Item* getitemAffected();

------------------------------------------------------------------------------*/

void Gamestate::testFeature(Feature* currentFeature)
{
	bool testBool;
	
	std::cout << "Feature Name: " << currentFeature->getName() << std::endl;
	
	std::cout << "Can be hacked: " << currentFeature->getCanSample()<< std::endl;
	
	std::cout << "can be Sampled: " << currentFeature->getCanHack()<< std::endl;
	
	std::cout << "Can have Item used on it: " << currentFeature->getActionAble() << std::endl;
	
	std::cout << "Already Inspected: " << currentFeature->getAlreadyInspected() << std::endl;
	
	std::cout << "Already Actioned: " << currentFeature->getAlreadyActioned() << std::endl;
	
	
}

void Gamestate::keyValuePrint()
{
	for(auto keys : this->itemMap) 
	{
    std::cout << keys.first << std::endl;

	}
}

std::string Gamestate::getBoolString(bool givenBool)
{
	if (givenBool)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

bool Gamestate::getStringFromBool(std::string boolean)
{
	if (boolean == "true")
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::unordered_map<std::string, Item*>*  Gamestate::getItemMap()
{
	return &itemMap;
}

std::unordered_map<std::string, Room*>* Gamestate::getRoomMap()
{
	return &roomMap;
}

std::unordered_map<std::string, Feature*>* Gamestate::getFeatureMap()
{
	return &featureMap;
}

std::unordered_map<std::string, Suspect*>* Gamestate::getSuspectMap()
{
	return &suspectMap;
}

std::unordered_map<std::string, Witness*>* Gamestate::getWitnessMap()
{
	return &witnessMap;
}