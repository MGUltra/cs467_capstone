/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Feature.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Feature::Feature(std::string nameIn, std::string descriptionFirstIn, std::string descriptionAfterIn, std::string locationIn, Item* itemAffectedIn, 
								 bool canSampleIn, bool canHackIn, bool actionAbleIn, std::string useItemIn)
{
	setName(nameIn);
	setDescriptionFirst(descriptionFirstIn);
	setDescriptionAfter(descriptionAfterIn);
	setLocation(locationIn);
	setItemAffected(itemAffectedIn);
	setAlreadyInspected(false);
	setCanSample(canSampleIn);
	setCanHack(canHackIn);
	setActionAble(actionAbleIn);
	setUseItem(useItemIn);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Feature::getName()
{
	return name;
}

std::string Feature::getDescriptionFirst()
{
	return descriptionFirst;
}

std::string Feature::getDescriptionAfter()
{
	return descriptionAfter;
}

std::string Feature::getLocation()
{
	return location;
}

std::string Feature::getUseItem()
{
	return this->itemToUse;
}

bool Feature::getAlreadyInspected()
{
	return alreadyInspected;
}

bool Feature::getAlreadyActioned()
{
	return alreadyActioned;
}

bool Feature::getCanSample()
{
	return canSample;
}

bool Feature::getCanHack()
{
	return canHack;
}

bool Feature::actionAble()
{
	return alreadyInspected;
}

Item* Feature::getitemAffected()
{
	return this->itemAffected;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Feature::setName(std::string givenName)
{
	name = givenName;
}

void Feature::setLocation(std::string givenLocation)
{
	location = givenLocation;
}

void Feature::setAlreadyInspected(bool newBool)
{
	alreadyInspected = newBool;
}

void Feature::setItemAffected(Item* newItem)
{
	this->itemAffected = newItem;
}

void Feature::setAlreadyActioned(bool boolIn)
{
	this->alreadyActioned = boolIn;
}

void Feature::setCanSample(bool boolIn)
{
	this->canSample = boolIn;
}

void Feature::setCanHack(bool boolIn)
{
	this->canHack = boolIn;
}

void Feature::setActionAble(bool boolIn)
{
	this->actionAble = boolIn;
}

void Feature::setUseItem(std::string itemIn)
{
	this->useItem = itemIn;
}

/*******************************************************************************
*		OTHER FUNCTIONS
*******************************************************************************/

void Feature::inspected()
{
	
	this->itemAffected->revealedByFeature();
	
	this->setAlreadyInspected(true);
	
}

void Feature::hacked()
{
		this->itemAffected->revealedByHack(this->name);
		
		this->setAlreadyActioned(true);
}

void Feature::sampled()
{
		this->itemAffected->revealedByFeature(this->name);
		
		this->setAlreadyActioned(true);
}

void Feature::itemUsed()
{
		this->itemAffected->revealedByFeature(this->name, this->useItem);
		
		this->setAlreadyActioned(true);
}


