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
	std::string inspectResponse;
	std::string talkResponse;
	std::string interrogateResponse;
	std::string accuseResponseTrue;
	std::string accuseResponseFalse;
	std::string itemResponse1;
	std::string itemResponse2;
	std::string itemResponse3;
	std::string itemResponseGeneric;
	std::string item1;
	std::string item2;
	std::string item3;
	
	bool isGuilty;
	bool isCleared;
	


public:
	//constructor
	Suspect(std::string, std::string, std::string, std::string, std::string,
					std::string, std::string, std::string, std::string, std::string, bool,
					std::string, std::string, std::string);

	//get
	std::string getName();
	std::string getInspectResponse();
	std::string getTalkResponse();
	std::string getInterrogateResponse();
	std::string getAccuseResponseTrue();
	std::string getAccuseResponseFalse();
	std::string getItemResponse1();
	std::string getItemResponse2();
	std::string getItemResponse3();
	std::string getItemResponseGeneric();
	std::string getItem1();
	std::string getItem2();
	std::string getItem3();
	
	bool getIsGuilty();
	bool getIsCleared();

	//set
	void setName(std::string);
	void setInspectResponse(std::string);
	void setTalkResponse(std::string);
	void setInterrogateResponse(std::string);
	void setAccuseResponseTrue(std::string);
	void setAccuseResponseFalse(std::string);
	void setItemResponse1(std::string);
	void setItemResponse2(std::string);
	void setItemResponse3(std::string);
	void setItemResponseGeneric(std::string);
	void setItem1(std::string);
	void setItem2(std::string);
	void setItem3(std::string);
	
	void setIsGuilty(bool);
	void setIsCleared(bool);
	
	
	// other
	std::string askItemResponse(std::string);
	
	
};

#endif