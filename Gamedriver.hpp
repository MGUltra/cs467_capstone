/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat, Matthew Garner, Kendal Droddy
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef GAMEDRIVER_HPP
#define GAMEDRIVER_HPP

/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

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
	std::vector<std::string> nounVector;
	
	
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
	
	Parser commandParser;
	
	Player currentPlayer;

	Notebook playerNotebook;

public:

	Gamestate();
	~Gamestate();


	// play game
	void playGame();


	// Game Initialization functions
	void createGame();
	
	void createRooms();
	void createFeatures();
	void createItems();
	void createVictim();
	void createSuspects();
	void createWitnesses();
	void createNotebook();

	
	// helper functions
	int findArrayIndex(std::string);
	Room* getRoom(std::string);
	Suspect* getSuspect(std::string);
	void printRooms();
	void printRoom(Room*);
	void checkLineEndings(std::string*);


	// Game Prompts
	void currentRoomPrompt(Room*);
	void featuresInRoomPrompt(Room*);
	void itemsInRoomPrompt(Room*);
	void clearScreen();


	// GAME ACTIONS
	void exeCommand(std::string);
	void movePlayer(std::string, std::string);
	void dropItem(std::string);
	void takeItem(std::string);
	void inspectObject(std::string);
	void showInventory();
	void hackComputer(std::string);
	void getStatement(std::string);
	void interrogateSuspect(std::string);
	void analyzeItem(std::string);
	void accuseSuspect(std::string);
	void sampleFeature(std::string);
	void askAboutItem(std::string, std::string);
	void useItemOnFeature(std::string, std::string);
	void drinkFeature(std::string);
	void listenToRecording(std::string);
	void talkToPerson(std::string);
	void reflectOnCase();
	void clearSuspect(std::string);

	// game meta functions
	void saveGame();
	void loadGame();
	void helpPlayer();
	
	// Cleanup function
	void cleanup();
};
#endif