/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "GameDriver.hpp"

int main()
{

	/*------------------------------------------------------------------------------
	GAME VARIABLES
	------------------------------------------------------------------------------*/
	GameDriver* newGame;

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

	// Create Rooms
	newGame->createRooms(commandParser);

	// create suspects
	newGame->createSuspects(commandParser);

	// Create Items - requires rooms and suspects be completed
	newGame->createItems(commandParser);


	// create features - requires rooms and items be completed	
	newGame->createFeatures(commandParser);

	// create victim


	currentPlayer = new Player("player 1", newGame->getRoom("bedroom"));

	/*------------------------------------------------------------------------------
	GAME LOOP
	------------------------------------------------------------------------------*/
	do
	{
		newGame->currentRoomPrompt(currentPlayer->getLocation());

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(Type 'help' if you need a list of actions you can take!)" << std::endl;

		getline(cin, inputString);

		if (inputString == "exit")
		{
			break;
		}

		if (inputString == "save")
		{
			newGame->save(currentPlayer);
		}

		newGame->clearScreen();

		// Call newMessage to run parser on input
		commandParser->newMessage(inputString);

		// get pointer to vector of word pointers
		actionsInCurrentMessage = commandParser->getGameActions();

		// number of actions will be number of verbs
		// verbs may have multiple nouns
		numberOfActions = commandParser->getNumActions();

		// Iterate through verbs
		for (int x = 0; x < numberOfActions; x++)
		{
			// get number of nouns for current verb
			numberOfNouns = (((Verb*)((*actionsInCurrentMessage)[x]))->getNumberOfNouns());

			if (numberOfNouns > 0)
			{
				// iterate through nouns of current verb
				for (int y = 0; y < numberOfNouns; y++)
				{
					newGame->exeCommand((*actionsInCurrentMessage)[x]->getText(), (((Verb*)((*actionsInCurrentMessage)[x]))->getIndexNounText(y)), currentPlayer);
				}
			}
			else
			{
				newGame->exeCommand((*actionsInCurrentMessage)[x]->getText(), "nonoun", currentPlayer);
			}
		}
	} while (exitStatus != true);


	//printRooms();
	//parserTest(commandParser);

	newGame->cleanup(commandParser, currentPlayer);

	return 0;
}

GameDriver* load(GameDriver* newGame)
{
	std::ifstream inputFileStream("saveFile");
	boost::archive::text_iarchive inputArchive(inputFileStream);
	inputArchive >> newGame;
}