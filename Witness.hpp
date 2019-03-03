/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef WITNESS_HPP
#define WITNESS_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

#include "Room.hpp"

class Witness
{
private:
	std::string name;
	std::string talkResponse;
	std::string interrogateResponse;
	std::string accuseResponse;
	std::string itemResponse1;
	std::string itemResponse2;
	std::string itemResponse3;
	std::string itemResponseGeneric;
	Room* location;

public:
	//constructor
	Witness(std::string, std::string, std::string, std::string, Room*);

	//get
	std::string getName();
	std::string getIntroduction();
	std::string getAnswer1();
	std::string getAnswer2();
	Room* getLocation();

	//set
	void setName(std::string);
	void setIntroduction(std::string);
	void setAnswer1(std::string);
	void setAnswer2(std::string);
	void setLocation(Room*);
};

#endif