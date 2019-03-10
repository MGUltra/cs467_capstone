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
#include "Notebook.hpp"

class Witness
{
private:
	std::string name;
	std::string inspectResponse;	
	std::string talkResponse;
	std::string interrogateResponse;
	std::string accuseResponse;
	std::string itemResponse1;
	std::string itemResponse2;
	std::string itemResponse3;
	std::string itemResponseGeneric;
	Room* location;
	std::string item1;
	std::string	item2;
	std::string	item3;

public:
	//constructor
	Witness(std::string, std::string, std::string, std::string, std::string,
					std::string, std::string, std::string, std::string, Room*,
					std::string, std::string, std::string);

	//get
	std::string getName();
	std::string getInspectResponse();
	std::string getTalkResponse();
	std::string getInterrogateResponse();
	std::string getAccuseResponse();
	std::string getItemResponse1();
	std::string getItemResponse2();
	std::string getItemResponse3();
	std::string getItemResponseGeneric();
	std::string getItem1();
	std::string getItem2();
	std::string getItem3();
	Room* getLocation();

	//set
	void setName(std::string);
	void setInspectResponse(std::string);
	void setTalkResponse(std::string);
	void setInterrogateResponse(std::string);
	void setAccuseResponse(std::string);
	void setItemResponse1(std::string);
	void setItemResponse2(std::string);
	void setItemResponse3(std::string);
	void setItemResponseGeneric(std::string);
	void setItem1(std::string);
	void setItem2(std::string);
	void setItem3(std::string);
	void setLocation(Room*);
	
	// other
	std::string askItemResponse(std::string, Notebook*);

	
};

#endif