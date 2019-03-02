/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat, Matthew Garner, Kendal Droddy
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

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
#include "dataRead.hpp"




/***************************************************************
***                        Class                             ***
****************************************************************/
class Gamestate
{
private:

	std::unordered_map<std::string, Item*> itemMap;
	std::unordered_map<std::string, Room*> roomMap;
	std::unordered_map<std::string, Feature*> featureMap;
	std::unordered_map<std::string, Suspect*> suspectMap;
	std::unordered_map<std::string, Witness*> witnessMap;
	std::vector<std::string> roomTestVector;

	std::string RoomsFile;
	std::string FeaturesFile;
	std::string ItemsFile;
	std::string VictimFile;
	std::string SuspectsFile;
	std::string WitnessesFile;
	std::string MurderNotes;

	std::string inputString;
	
	std::vector<Word*>* actionsInCurrentMessage;
	
	int numberOfActions, numberOfNouns;
	
	bool exitStatus;
	
	
	// pointers or actual objects?
	Parser commandParser;
	
	Player currentPlayer;

	Notebook playerNotebook;

public:

	// play game
	void playGame();


	// Game Initialization functions
	
	void createNotebook();

	
	// helper functions
	int findArrayIndex(std::string);
	Room* getRoom(std::string);
	void printRooms();
	void printRoom(Room*);
	void checkLineEndings(std::string*);



	// Game Prompts
	void currentRoomPrompt(Room*);
	void featuresInRoomPrompt(Room*);
	void itemsInRoomPrompt(Room*);
	void clearScreen();


	// GAME ACTIONS



	void helpPlayer();

	// Cleanup function
	void cleanup(Parser*, Player*);






};
#endif
