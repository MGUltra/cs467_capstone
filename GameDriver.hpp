/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Room.hpp"
#include "Player.hpp"
#include "Victim.hpp"
#include "Suspect.hpp"
#include "Witness.hpp"
#include "Item.hpp"
#include "Notebook.hpp"
#include "parser.hpp"
#include "dataRead.hpp"


class GameDriver
{
public:
	/*------------------------------------------------------------------------------
	TEXT FILES
	------------------------------------------------------------------------------*/
	std::string RoomsFile = "Rooms.txt";
	std::string FeaturesFile = "Features.txt";
	std::string ItemsFile = "Items.txt";
	std::string VictimFile = "Victim.txt";
	std::string SuspectsFile = "Suspects.txt";
	std::string WitnessesFile = "Witnesses.txt";
	std::string MurderNotes = "MurderNotes.txt";

	/*------------------------------------------------------------------------------
	GAME VARIABLES
	------------------------------------------------------------------------------*/
	std::unordered_map<std::string, Item*> itemMap;
	std::unordered_map<std::string, Room*> roomMap;
	std::unordered_map<std::string, Feature*> featureMap;
	std::unordered_map<std::string, Suspect*> suspectMap;
	std::unordered_map<std::string, Witness*> witnessMap;
	std::vector<std::string> roomTestVector;
	Notebook playerNotebook;

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
	
	void movePlayer(Player*, std::string, std::string);
	void dropItem(Player*, std::string);
	void takeItem(Player*, std::string);
	void inspectObject(Player*, std::string);
	void showInventory(Player*);

	void hackComputer(Player*, std::string);
	void getStatement(Player*, std::string);
	void interrogateSuspect(Player*, std::string);
	void analyzeItem(Player*, std::string);


	void helpPlayer();

	// Cleanup function
	void cleanup(Parser*, Player*);

	GameDriver();
};

#endif