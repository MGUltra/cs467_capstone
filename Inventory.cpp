/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Inventory.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Inventory::Inventory()
{
	// Blank Default Constructor
	numItemsInInventory = 0;
}

std::vector<std::string>* Inventory::getItemsFromInventory()
{
	return &itemsInInventory;
}

/*******************************************************************************
*		ADD FUNCTIONS
*******************************************************************************/
void Inventory::addItemToInventory(std::string newItem)
{
	itemsInInventory.push_back(newItem);
	
	numItemsInInventory++;
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Inventory::removeItemFromInventory(std::string removeThisItem)
{

	int index = findVectorIndex(removeThisItem, itemsInInventory);
	itemsInInventory.erase(itemsInInventory.begin() + index);
		
	numItemsInInventory--;

	

}

/*******************************************************************************
*		FIND VECTOR INDEX
*******************************************************************************/
int Inventory::findVectorIndex(std::string thisString, std::vector<std::string> thisVector)
{
	int size = thisVector.size();

	for (int i = 0; i <= size; i++)
	{
		if (thisString == thisVector[i])
		{
			return i;
		}
	}
}


/*******************************************************************************
*		PRINT CURRENT INVENTORY
*******************************************************************************/
void Inventory::printCurrentInventory()
{
	std::cout << std::endl;
	std::cout << "Current Inventory" << std::endl;
	std::cout << "-----------------" << std::endl;
	
	if(numItemsInInventory > 0)
	{
		for(auto i : itemsInInventory)
		{
			std::cout << "| " << i << std::endl;
		}
	}
	else
	{
		std::cout << "Inventory Empty" << std::endl;
	}
	std::cout << "-----------------" << std::endl;
	std::cout << std::endl;
}


bool Inventory::isItemInInventory(std::string itemPresent)
{
	for(auto i : itemsInInventory)
	{
		if(itemPresent == i)
			return true;
	}
	
	return false;
}

