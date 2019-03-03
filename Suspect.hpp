/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef SUSPECT_HPP
#define SUSPECT_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

class Suspect
{
private:
	std::string name;
	std::string description;
	std::string talkResponse;
	std::string interrogateResponse;
	std::string accuseResponseTrue;
	std::string accuseResponseFalse;
	std::string itemResponse1;
	std::string itemResponse2;
	std::string itemResponse3;
	std::string itemResponseGeneric;
	
	bool isGuilty;
	bool isCleared;
	bool isAccused;
	
	bool sigItemFound;

public:
	//constructor
	Suspect(std::string, std::string, std::string, std::string);

	//get
	std::string getName();
	std::string getDescription();
	bool getSigItemFound();

	//set
	void setName(std::string);
	void setDescription(std::string);
	void setSigItemFound();
};

#endif