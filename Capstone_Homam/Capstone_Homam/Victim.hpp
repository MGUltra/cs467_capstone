/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef VICTIM_HPP
#define VICTIM_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

using namespace std;

class Victim
{
private:
	std::string name;
	std::string description;


public:
	//constructor
	Victim(std::string, std::string);

	//get
	std::string getName();
	std::string getDescription();

	//set
	void setName(std::string);
	void setDescription(std::string);

};

#endif