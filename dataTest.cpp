 /******************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Kendal Droddy (Rozalija Zibrat, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has 
** to interrogate suspects, investigate the crime scene, search 
** for evidence, and ultimately decide who committed the murder.
*******************************************************************/
#include "dataRead.hpp"
#include <iostream>
#include <fstream>

int main()
{
  int num = 0;
  std::ifstream inFile;
  std::string input;

  //Test window size
  int winFlag = calcWindowSize();
  if (winFlag == 0)
    return 0;

  //Switch for rooms
  while(num != -1)
  {
    //Test Menu
    inFile.open("testMenu.txt", std::ios::out);
    readFileDefault(inFile);
    inFile.close();
    std::cin >> num;
    switch(num)
    {
      case 1:
        inFile.open("roomText/cellLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/cellShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/cellLight.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/cellSuspects.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 2:
        inFile.open("roomText/policeStationLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/policeStationShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/policeChief.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/policeDesk.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 3:
        inFile.open("roomText/labLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/labShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/forensicBeaker.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/forensicComp.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 4:
        inFile.open("roomText/carlsDenLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsDenShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlLivingChair.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlLivingDresser.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 5:
        inFile.open("roomText/carlsGarageLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsGarageShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlGarageHammer.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlGarageBlood.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 6:
        inFile.open("roomText/carlsBathroomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsBathroomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlBathMedCabinet.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlBathFirstAid.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 7:
        inFile.open("roomText/carlsKitchenLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsKitchenShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlKitchenBlood.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/carlKitchenUtensils.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 8:
        inFile.open("roomText/dansGalleyLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansGalleyShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danKitchenPic.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danKitchenPizza.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 9:
        inFile.open("roomText/dansLivingRoomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansLivingRoomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danLivingCoat.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danLivingWallet.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 10:
        inFile.open("roomText/dansBedroomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansBedroomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danBedroomCell.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danBedroomPill.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 11:
        inFile.open("roomText/dansPorchLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansPorchShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danPorchRag.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/danPorchWrench.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 12:
        inFile.open("roomText/vincesFoyerLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesFoyerShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceFoyerBoots.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceFoyerStatue.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 13:
        inFile.open("roomText/vincesSalonLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesSalonShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceLivingNews.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceLivingPainting.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 14:
        inFile.open("roomText/vincesBedchamberLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesBedchamberShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceBedroomRobe.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceBedroomTrophy.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 15:
        inFile.open("roomText/vincesOfficeLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesOfficeShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceOfficeCigar.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/vinceOfficeTickets.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 16:
        inFile.open("roomText/copCarLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/copCarShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/copCarCoffee.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomFeatures/copCarRadio.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
    case 17:
        inFile.open("suspectText/vince.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/vinceAnsOne.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/vinceAnsTwo.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
    case 18:
        inFile.open("suspectText/carl.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/carlAnsOne.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/carlAnsTwo.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
    case 19:
        inFile.open("suspectText/dan.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/danAnsOne.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("suspectText/danAnsTwo.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
    } 
  }
  return 0;
}