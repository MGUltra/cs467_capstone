/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>

#include "Item.hpp"

using namespace std;

struct Inventory
{
	private:
	std::vector<std::string> itemsInInventory;

	public:
	// constructor
	Inventory();

	std::vector<std::string>* getItemsFromInventory();

	void addItemToInventory(std::string);

	void removeItemFromInventory(std::string);

	int findVectorIndex(std::string, std::vector<std::string>);
};
#endif