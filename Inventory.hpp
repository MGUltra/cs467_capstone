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

struct Inventory
{
	private:
	std::vector<Item*> itemsInInventory;
	
	int numItemsInInventory;

	public:
	// constructor
	Inventory();

	std::vector<Item*>* getItemsFromInventory();

	void addItemToInventory(Item*);

	void removeItemFromInventory(Item*);

	int findVectorIndex(Item*);
	
	void printCurrentInventory();
	
	// Test Function
	bool isItemInInventory(Item*);
	
	
};
#endif